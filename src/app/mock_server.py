#!/usr/bin/env python3
"""SensePath mock-server voor laptop-ontwikkeling van de telefoon-app.

Serveert dezelfde app (src/app/index.html) als de stok-XIAO, maar dan op je
laptop - zodat je de UI kunt aanpassen en testen zonder elke keer te flashen.

Run vanuit deze map (src/app/):
    python mock_server.py

Open in de browser:
    http://localhost:8080/        -> de app
    http://localhost:8080/dev     -> dev-panel (knop-simulatie + servo-slider)

Wat het doet:
  - Serveert index.html (elke request opnieuw -> edits zichtbaar na refresh)
  - Mockt alle /api/-endpoints met in-memory state (geen echte hardware)
  - Logt elke trigger naar de terminal (trillingen, servo, route, afslag)
  - Leest de Google Maps-key uit ../firmware/handle/secrets.h indien aanwezig
"""

import http.server
import json
import os
import re
import sys
from urllib.parse import urlparse, parse_qs

PORT = 8080
APP_DIR = os.path.dirname(os.path.abspath(__file__))
INDEX_PATH = os.path.join(APP_DIR, "index.html")
# De Google-key staat in de (gitignored) firmware-secrets; we hergebruiken die.
SECRETS_PATH = os.path.join(APP_DIR, "..", "firmware", "handle", "secrets.h")

# ───────────────────────── In-memory state (vervangt NVS) ─────────────────────────
# Defaults gelijk aan de Settings-struct in handle/main.cpp.
DEFAULT_SETTINGS = {
    "btn_short": 7,        # Spreek ETA op handvat
    "btn_double": 8,       # Spreek locatie op handvat
    "btn_long": 0,         # Niets
    "vib_intensity": 1,    # Medium
    "vib_m4": 47,
    "vib_m6": 12,
    "vib_turn_right": 1,   # 1 trilling
    "vib_turn_left": 2,    # 2 trillingen
    "audio_enabled": 1,
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


def google_key():
    if os.path.exists(SECRETS_PATH):
        with open(SECRETS_PATH, encoding="utf-8") as f:
            m = re.search(r'#define\s+GOOGLE_MAPS_API_KEY\s+"([^"]+)"', f.read())
            if m:
                return m.group(1)
    return "PLAK_HIER_JE_KEY"


def load_html():
    """Lees index.html en injecteer de Google-key (zoals de firmware doet)."""
    if not os.path.exists(INDEX_PATH):
        print(f"FOUT: kan index.html niet vinden op {INDEX_PATH}")
        sys.exit(1)
    with open(INDEX_PATH, encoding="utf-8") as f:
        html = f.read()
    return html.replace("PLAK_HIER_JE_KEY", google_key())


# ───────────────────────── Dev-panel ─────────────────────────
DEV_PANEL_HTML = """<!DOCTYPE html>
<html><head><meta charset="UTF-8"><title>SensePath dev-panel</title>
<style>
body{background:#1a1a1a;color:#eee;font-family:sans-serif;padding:20px;max-width:600px;margin:0 auto}
h1,h2{color:#d4a574}h2{margin-top:28px}
button{display:block;width:100%;padding:14px;margin:6px 0;background:#2a2a2a;color:#eee;
border:1px solid #d4a574;border-radius:8px;font-size:16px;cursor:pointer}
button:hover{background:#d4a574;color:#000}
.row{display:flex;gap:8px}.row button{flex:1}
a{color:#d4a574}.log{background:#000;padding:10px;border-radius:8px;margin-top:20px;
font-family:monospace;font-size:12px;max-height:300px;overflow-y:auto;white-space:pre-wrap}
</style></head><body>
<h1>SensePath dev-panel</h1>
<p><a href="/">Terug naar de app</a></p>

<h2>Simuleer knop op handvat</h2>
<div class="row">
  <button onclick="sim('short')">Korte druk</button>
  <button onclick="sim('double')">Dubbel-druk</button>
  <button onclick="sim('long')">Lange druk</button>
</div>

<h2>Servo-positie (simuleer controller-encoder)</h2>
<input type="range" id="servo-slider" min="0" max="180" value="90" style="width:100%;height:40px"
       oninput="setServo(this.value)">
<div style="text-align:center;margin-top:6px">Hoek: <span id="servo-val">90</span>&deg;</div>
<button onclick="sweepServo()" style="margin-top:6px">Sweep 0 &harr; 180 (3s)</button>

<h2>Afslag-trilling (preview)</h2>
<div class="row">
  <button onclick="turn(1)">1 trilling</button>
  <button onclick="turn(2)">2 trillingen</button>
  <button onclick="turn(4)">1 lange</button>
</div>

<h2>Mock state</h2>
<button onclick="getState()">Toon huidige state</button>
<button onclick="resetState()">Reset alle state</button>

<div class="log" id="log">Console-output verschijnt hier en in de terminal.</div>
<script>
async function post(url, body){return fetch(url,{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:body});}
async function sim(t){await post('/api/_dev/button?type='+t,'');log('Knop: '+t);}
async function turn(id){await post('/api/turn-preview','id='+id);log('Afslag-patroon: '+id);}
let dbi=null;
async function setServo(a){document.getElementById('servo-val').textContent=a;clearTimeout(dbi);
  dbi=setTimeout(async()=>{await post('/api/servo','angle='+a);log('Servo -> '+a);},30);}
async function sweepServo(){const s=document.getElementById('servo-slider');
  for(let i=0;i<=60;i++){const a=Math.round(90+90*Math.sin(i/60*Math.PI*2));s.value=a;setServo(a);await new Promise(r=>setTimeout(r,50));}}
async function getState(){const r=await fetch('/api/_dev/state');log(JSON.stringify(await r.json(),null,2));}
async function resetState(){await post('/api/_dev/reset','');log('State gereset');}
function log(m){const e=document.getElementById('log');e.textContent='['+new Date().toLocaleTimeString()+'] '+m+'\\n'+e.textContent;}
</script></body></html>
"""


# ───────────────────────── HTTP handler ─────────────────────────
class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        pass

    def _log(self, msg):
        print(f"[{self.command}] {self.path} -> {msg}")

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
        return self.rfile.read(length).decode("utf-8") if length else ""

    def do_GET(self):
        path = urlparse(self.path).path
        if path in ("/", ""):
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
            self.send_json({"route_active": state["route_active"],
                            "destination": state["active_destination"]})
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
                state["settings"].update(json.loads(body))
                self._log("Instellingen opgeslagen")
                self.send_text("ok")
            except Exception as e:
                self.send_text(str(e), 400)
        elif path == "/api/settings/reset":
            state["settings"] = dict(DEFAULT_SETTINGS)
            self._log("Instellingen gereset")
            self.send_text("ok")
        elif path == "/api/destinations":
            try:
                state["destinations"] = json.loads(body)
                self.send_text("ok")
            except Exception as e:
                self.send_text(str(e), 400)
        elif path == "/api/route/start":
            dest = parse_qs(body).get("destination", [""])[0]
            state["active_destination"] = dest
            state["route_active"] = True
            self._log(f"Route gestart naar: {dest}")
            self.send_text("ok")
        elif path == "/api/route/stop":
            state["route_active"] = False
            state["active_destination"] = ""
            self._log("Route gestopt")
            self.send_text("ok")
        elif path == "/api/trigger-effect":
            eid = parse_qs(body).get("id", [""])[0]
            self._log(f"TRILLING effect {eid}" if eid not in ("", "0") else "STERKTE-preview")
            self.send_text("ok")
        elif path == "/api/turn-preview":
            tid = parse_qs(body).get("id", [""])[0]
            self._log(f"AFSLAG-patroon {tid}")
            self.send_text("ok")
        elif path == "/api/servo":
            try:
                angle = max(0, min(180, int(parse_qs(body).get("angle", ["90"])[0])))
            except ValueError:
                angle = 90
            state["servo_angle"] = angle
            self._log(f"SERVO -> {angle}")
            self.send_text("ok")
        # ───────── dev-only ─────────
        elif path == "/api/_dev/button":
            params = parse_qs(url.query) or parse_qs(body)
            press_type = params.get("type", ["short"])[0]
            action_id = state["settings"].get(f"btn_{press_type}", 0)
            # Alleen noodhulp (5) duwt een commando naar de app; de overige
            # spraak-acties spelen op het handvat zelf (clips), zie executeAction().
            cmd = "EMERGENCY" if action_id == 5 else ""
            if cmd:
                state["pending_command"] = cmd
            self._log(f"KNOP {press_type} -> actie={action_id} -> cmd={cmd or '(handvat-zijde)'}")
            self.send_text("ok")
        elif path == "/api/_dev/reset":
            state.update({"settings": dict(DEFAULT_SETTINGS), "destinations": [],
                          "active_destination": "", "route_active": False,
                          "pending_command": "", "servo_angle": 90})
            self._log("Volledige state reset")
            self.send_text("ok")
        else:
            self.send_text("not found", 404)


if __name__ == "__main__":
    key = google_key()
    key_status = ("ACTIEF (" + key[:8] + "...)") if key != "PLAK_HIER_JE_KEY" else "PLACEHOLDER (manuele modus)"
    print("=" * 64)
    print("  SensePath MOCK-SERVER (telefoon-app, laptop-ontwikkeling)")
    print("=" * 64)
    print(f"  App-bron:        {os.path.relpath(INDEX_PATH, APP_DIR)}")
    print(f"  HTML grootte:    {len(load_html())} bytes")
    print(f"  Google API key:  {key_status}")
    print(f"  Server:          http://localhost:{PORT}/")
    print(f"  Dev-panel:       http://localhost:{PORT}/dev")
    print("  Stop:            Ctrl+C")
    print("=" * 64)
    print("Edits in index.html zijn direct zichtbaar na een browser-refresh.")
    print()
    httpd = http.server.HTTPServer(("0.0.0.0", PORT), Handler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nMock-server gestopt")
