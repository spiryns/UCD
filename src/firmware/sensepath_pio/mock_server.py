#!/usr/bin/env python3
"""SensePath mock server voor laptop-development.

Run vanuit de project-folder:
    python mock_server.py

Open in browser:
    http://localhost:8080/

Wat het doet:
  - Serveert dezelfde HTML/CSS/JS als de XIAO (uit src/webapp.h)
  - Mockt alle /api/ endpoints met in-memory state
  - Logt elke trigger naar de terminal (trillingen, servo, route)
  - HTML wordt elke request opnieuw geladen → edits zichtbaar na browser-refresh
  - Google Maps API key wordt automatisch uit src/secrets.h gelezen

Dev-tools:
  - http://localhost:8080/dev → mini control-panel om button-presses te simuleren
  - POST /api/_dev/button?type=short|double|long via curl of de /dev pagina
"""

import http.server
import json
import re
import os
import sys
from urllib.parse import urlparse, parse_qs

PORT = 8080
PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
WEBAPP_PATH = os.path.join(PROJECT_ROOT, "src", "webapp.h")
SECRETS_PATH = os.path.join(PROJECT_ROOT, "src", "secrets.h")

# ═════════════════════════ In-memory state (vervangt NVS) ═════════════════════════

DEFAULT_SETTINGS = {
    "btn_short": 1,
    "btn_double": 2,
    "btn_long": 5,
    "vib_intensity": 1,
    "vib_m4": 14,
    "vib_m6": 12,
    "vib_m9": 47,
    "audio_enabled": 0,
    "tts_rate": 10,
    "emergency": "",
}

state = {
    "settings": dict(DEFAULT_SETTINGS),
    "destinations": [],
    "active_destination": "",
    "route_active": False,
    "pending_command": "",
    "servo_angle": 90,
}

# ═════════════════════════ HTML extractie ═════════════════════════

def load_html():
    """Extract HTML uit webapp.h en substitueer Google API key uit secrets.h."""
    if not os.path.exists(WEBAPP_PATH):
        print(f"FOUT: kan webapp.h niet vinden op {WEBAPP_PATH}")
        sys.exit(1)

    with open(WEBAPP_PATH, encoding="utf-8") as f:
        content = f.read()

    # Vind R"HTML(...)HTML" raw string literal
    match = re.search(r'R"HTML\((.*?)\)HTML"', content, re.DOTALL)
    if not match:
        print("FOUT: kan HTML niet extraheren uit webapp.h (zoekt naar R\"HTML(...)HTML\")")
        sys.exit(1)

    html = match.group(1)

    # Substitueer Google API key uit secrets.h indien aanwezig
    api_key = "PLAK_HIER_JE_KEY"
    if os.path.exists(SECRETS_PATH):
        with open(SECRETS_PATH, encoding="utf-8") as f:
            sc = f.read()
        m = re.search(r'#define\s+GOOGLE_MAPS_API_KEY\s+"([^"]+)"', sc)
        if m:
            api_key = m.group(1)

    html = html.replace("PLAK_HIER_JE_KEY", api_key)
    return html

# ═════════════════════════ Dev-panel HTML ═════════════════════════

DEV_PANEL_HTML = """<!DOCTYPE html>
<html><head>
<meta charset="UTF-8"><title>SensePath dev-panel</title>
<style>
body{background:#1a1a1a;color:#eee;font-family:sans-serif;padding:20px;max-width:600px;margin:0 auto}
h1{color:#d4a574}h2{color:#d4a574;margin-top:30px}
button{display:block;width:100%;padding:14px;margin:6px 0;background:#2a2a2a;color:#eee;
border:1px solid #d4a574;border-radius:8px;font-size:16px;cursor:pointer}
button:hover{background:#d4a574;color:#000}
.row{display:flex;gap:8px}.row button{flex:1}
a{color:#d4a574}.log{background:#000;padding:10px;border-radius:8px;margin-top:20px;
font-family:monospace;font-size:12px;max-height:300px;overflow-y:auto}
</style></head><body>
<h1>SensePath dev-panel</h1>
<p><a href="/">Terug naar de app</a></p>

<h2>Simuleer HOTUT-knop</h2>
<div class="row">
  <button onclick="sim('short')">Korte druk</button>
  <button onclick="sim('double')">Dubbel-druk</button>
  <button onclick="sim('long')">Lange druk</button>
</div>

<h2>Trigger trilling-effect</h2>
<div class="row">
  <button onclick="effect(1)">Strong Click</button>
  <button onclick="effect(14)">Strong Buzz</button>
  <button onclick="effect(47)">Buzz oplopend</button>
</div>

<h2>Servo-positie (simuleer controller-encoder)</h2>
<input type="range" id="servo-slider" min="0" max="180" value="90" style="width:100%;height:40px"
       oninput="setServo(this.value)">
<div style="text-align:center;margin-top:6px">Hoek: <span id="servo-val">90</span>°</div>
<div class="row" style="margin-top:10px">
  <button onclick="setServo(0);document.getElementById('servo-slider').value=0">0°</button>
  <button onclick="setServo(90);document.getElementById('servo-slider').value=90">90°</button>
  <button onclick="setServo(180);document.getElementById('servo-slider').value=180">180°</button>
</div>
<button onclick="sweepServo()" style="margin-top:6px">Sweep 0 ↔ 180 (3s)</button>

<h2>Mock state</h2>
<button onclick="getState()">Toon huidige state</button>
<button onclick="resetState()">Reset alle state</button>

<div class="log" id="log">Console-output verschijnt hier en in de terminal.</div>

<script>
async function sim(type) {
  await fetch('/api/_dev/button?type=' + type, {method:'POST'});
  log('Button press: ' + type);
}
async function effect(id) {
  await fetch('/api/trigger-effect', {
    method:'POST',
    headers:{'Content-Type':'application/x-www-form-urlencoded'},
    body: 'id=' + id
  });
  log('Effect: ' + id);
}
let servoDebounce = null;
async function setServo(angle) {
  document.getElementById('servo-val').textContent = angle;
  clearTimeout(servoDebounce);
  servoDebounce = setTimeout(async () => {
    await fetch('/api/servo', {
      method:'POST',
      headers:{'Content-Type':'application/x-www-form-urlencoded'},
      body: 'angle=' + angle
    });
    log('Servo → ' + angle + '°');
  }, 30);
}
async function sweepServo() {
  const slider = document.getElementById('servo-slider');
  const steps = 60;
  for (let i = 0; i <= steps; i++) {
    const a = Math.round(90 + 90 * Math.sin(i / steps * Math.PI * 2));
    slider.value = a;
    setServo(a);
    await new Promise(r => setTimeout(r, 50));
  }
}
async function getState() {
  const r = await fetch('/api/_dev/state');
  log(JSON.stringify(await r.json(), null, 2));
}
async function resetState() {
  await fetch('/api/_dev/reset', {method:'POST'});
  log('State gereset');
}
function log(msg) {
  const el = document.getElementById('log');
  el.textContent = '[' + new Date().toLocaleTimeString() + '] ' + msg + '\\n' + el.textContent;
}
</script>
</body></html>
"""

# ═════════════════════════ HTTP handler ═════════════════════════

class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        pass  # Eigen logging, niet de default

    def _log(self, msg):
        print(f"[{self.command}] {self.path} → {msg}")

    def send_json(self, data, status=200):
        body = json.dumps(data, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def send_text(self, text, status=200, content_type="text/plain"):
        body = text.encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", f"{content_type}; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def read_body(self):
        length = int(self.headers.get("Content-Length", 0))
        if length == 0:
            return ""
        return self.rfile.read(length).decode("utf-8")

    def do_GET(self):
        url = urlparse(self.path)
        path = url.path

        if path == "/" or path == "":
            # HTML wordt elke request opnieuw geladen → edits direct zichtbaar
            html = load_html()
            self.send_text(html, content_type="text/html")
            self._log(f"HTML serveert ({len(html)} bytes)")
        elif path == "/dev":
            self.send_text(DEV_PANEL_HTML, content_type="text/html")
        elif path == "/api/settings":
            self.send_json(state["settings"])
        elif path == "/api/destinations":
            self.send_json(state["destinations"])
        elif path == "/api/state":
            self.send_json({
                "route_active": state["route_active"],
                "destination": state["active_destination"],
            })
        elif path == "/api/pending":
            cmd = state["pending_command"]
            state["pending_command"] = ""
            self.send_text(cmd)
        elif path == "/api/servo":
            self.send_json({"angle": state["servo_angle"]})
        elif path == "/api/_dev/state":
            self.send_json(state)
        else:
            self.send_text("not found", 404)

    def do_POST(self):
        url = urlparse(self.path)
        path = url.path
        body = self.read_body()

        if path == "/api/settings":
            try:
                new_settings = json.loads(body)
                state["settings"].update(new_settings)
                self._log(f"Settings opgeslagen: {list(new_settings.keys())}")
                self.send_text("ok")
            except Exception as e:
                self.send_text(str(e), 400)
        elif path == "/api/settings/reset":
            state["settings"] = dict(DEFAULT_SETTINGS)
            self._log("Settings gereset")
            self.send_text("ok")
        elif path == "/api/destinations":
            try:
                state["destinations"] = json.loads(body)
                self._log(f"Destinations: {len(state['destinations'])} items")
                self.send_text("ok")
            except Exception as e:
                self.send_text(str(e), 400)
        elif path == "/api/route/start":
            params = parse_qs(body)
            dest = params.get("destination", [""])[0]
            state["active_destination"] = dest
            state["route_active"] = True
            self._log(f"▶ Route gestart naar: {dest}")
            self.send_text("ok")
        elif path == "/api/route/stop":
            state["route_active"] = False
            state["active_destination"] = ""
            self._log("⏹ Route gestopt")
            self.send_text("ok")
        elif path == "/api/trigger-effect":
            params = parse_qs(body)
            eid = params.get("id", [""])[0]
            self._log(f"🔔 TRILLING effect {eid}")
            self.send_text("ok")
        elif path == "/api/servo":
            params = parse_qs(body)
            try:
                angle = max(0, min(180, int(params.get("angle", ["90"])[0])))
            except ValueError:
                angle = 90
            state["servo_angle"] = angle
            self._log(f"🧭 SERVO → {angle}°")
            self.send_text("ok")
        # ═════════════════════════ Dev-only ═════════════════════════
        elif path == "/api/_dev/button":
            params = parse_qs(url.query) or parse_qs(body)
            press_type = params.get("type", ["short"])[0]
            action_key = f"btn_{press_type}"
            action_id = state["settings"].get(action_key, 0)
            # Mapping zelfde als executeAction() in main.cpp
            cmd_map = {
                1: "ASK_LOCATION",
                2: "ROUTE_OVERVIEW",
                3: "REPEAT_LAST",
                4: "",  # interne trilling
                5: "EMERGENCY",
                6: f"SPEAK:Audio {'aan' if state['settings'].get('audio_enabled', 0) == 0 else 'uit'}",
            }
            cmd = cmd_map.get(action_id, "")
            if cmd:
                state["pending_command"] = cmd
            self._log(f"🔘 HOTUT {press_type}-press → action={action_id} → cmd={cmd or '(geen)'}")
            self.send_text("ok")
        elif path == "/api/_dev/reset":
            state["settings"] = dict(DEFAULT_SETTINGS)
            state["destinations"] = []
            state["active_destination"] = ""
            state["route_active"] = False
            state["pending_command"] = ""
            self._log("Volledige state reset")
            self.send_text("ok")
        else:
            self.send_text("not found", 404)


# ═════════════════════════ Main ═════════════════════════

if __name__ == "__main__":
    html_size = len(load_html())

    api_key_status = "PLAK_HIER_JE_KEY"
    if os.path.exists(SECRETS_PATH):
        with open(SECRETS_PATH, encoding="utf-8") as f:
            m = re.search(r'#define\s+GOOGLE_MAPS_API_KEY\s+"([^"]+)"', f.read())
            if m:
                key = m.group(1)
                api_key_status = "ACTIEF (" + key[:8] + "...)" if key != "PLAK_HIER_JE_KEY" else "PLACEHOLDER"

    print("=" * 64)
    print("  SensePath MOCK-SERVER (laptop development)")
    print("=" * 64)
    print(f"  HTML grootte:    {html_size} bytes")
    print(f"  Google API key:  {api_key_status}")
    print(f"  Server:          http://localhost:{PORT}/")
    print(f"  Dev-panel:       http://localhost:{PORT}/dev")
    print(f"  Stop:            Ctrl+C")
    print("=" * 64)
    print("Edits in src/webapp.h zijn direct zichtbaar na browser-refresh.")
    print()

    httpd = http.server.HTTPServer(("0.0.0.0", PORT), Handler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nMock-server gestopt")
