#!/usr/bin/env python3
# ---------------------------------------------------------------------------
# SensePath - genereert de firmware-include handle/webapp.h uit de ECHTE
# app-broncode src/app/index.html.
#
# De telefoon-app is een gewone HTML/CSS/JS-pagina (src/app/index.html). De
# ESP32-webserver serveert die als een PROGMEM-string, dus de firmware heeft
# er een .h-versie van nodig. Dit script maakt die .h automatisch aan - net
# zoals tools/wav2header.py de audioclips inbedt.
#
# Gebruik (vanuit de repo-root):
#   python src/firmware/tools/html2header.py            # index.html -> webapp.h
#   python src/firmware/tools/html2header.py extract    # webapp.h  -> index.html (eenmalig)
#
# Bewerk dus index.html en draai dit script; bewerk NIET rechtstreeks webapp.h.
# ---------------------------------------------------------------------------
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", ".."))   # repo-root
SRC  = os.path.join(ROOT, "src", "app", "index.html")
OUT  = os.path.join(ROOT, "src", "firmware", "handle", "webapp.h")
DEMO = os.path.join(ROOT, "src", "app", "demo.html")

# Mini-mock die de hardware-backend (/api/...) in de pagina zelf nabootst, zodat
# de app ook als losse link werkt (GitHub Pages / htmlpreview). De twin-naald
# beweegt automatisch; POSTs antwoorden netjes met "ok". Wordt vooraan in <head>
# ingespoten zodat de override actief is voordat de app-code draait.
DEMO_MOCK = """<script>
/* SensePath DEMO-modus: bootst de handvat-backend na zodat de app ook zonder
   hardware werkt. De digital-twin-naald beweegt vanzelf. */
(function () {
  const real = window.fetch ? window.fetch.bind(window) : null;
  const t0 = Date.now();
  const demoAngle = () => Math.round(90 + 28 * Math.sin((Date.now() - t0) / 1500));
  const settings = {btn_short:7,btn_double:8,btn_long:0,vib_intensity:1,vib_m4:47,
    vib_m6:12,vib_turn_right:1,vib_turn_left:2,audio_enabled:1,tts_rate:10,emergency:""};
  const J = (o) => Promise.resolve(new Response(JSON.stringify(o), {status:200, headers:{'Content-Type':'application/json'}}));
  const T = (s) => Promise.resolve(new Response(s, {status:200, headers:{'Content-Type':'text/plain'}}));
  window.fetch = function (url, opts) {
    const u = String(url);
    const get = !opts || !opts.method || String(opts.method).toUpperCase() === 'GET';
    if (u.includes('/api/servo') && get) return J({angle: demoAngle()});
    if (u.includes('/api/settings') && get) return J(settings);
    if (u.includes('/api/destinations') && get) return J([]);
    if (u.includes('/api/state')) return J({route_active:true, destination:''});
    if (u.includes('/api/pending')) return T('');
    if (u.includes('/api/')) return T('ok');
    return real ? real(url, opts) : Promise.reject(new Error('geen netwerk in demo'));
  };
})();
</script>
"""

DELIM_OPEN  = 'R"HTML('
DELIM_CLOSE = ')HTML"'

HEADER = (
    "// SensePath telefoon-app als PROGMEM-string voor de ESP32-webserver.\n"
    "// AUTO-GEGENEREERD uit src/app/index.html door tools/html2header.py.\n"
    "// Bewerk index.html, NIET dit bestand. Regenereer met:\n"
    "//   python src/firmware/tools/html2header.py\n"
    "#pragma once\n"
    "#include <Arduino.h>\n\n"
    'const char INDEX_HTML[] PROGMEM = R"HTML(\n'
)


def generate():
    with open(SRC, encoding="utf-8") as f:
        html = f.read()
    if DELIM_CLOSE in html:
        sys.exit('FOUT: index.html bevat de delimiter )HTML" en kan niet veilig '
                 "in een raw-string ingebed worden.")
    out = HEADER + html
    if not out.endswith("\n"):
        out += "\n"
    out += DELIM_CLOSE + ";\n"
    with open(OUT, "w", encoding="utf-8", newline="\n") as f:
        f.write(out)
    print(f"webapp.h gegenereerd: {len(out)} bytes (uit {os.path.relpath(SRC, ROOT)})")


def extract():
    # Eenmalig: haalt de HTML uit een bestaande webapp.h en schrijft index.html.
    with open(OUT, encoding="utf-8") as f:
        raw = f.read()
    a = raw.index(DELIM_OPEN) + len(DELIM_OPEN)
    b = raw.rindex(DELIM_CLOSE)
    html = raw[a:b].lstrip("\n")
    os.makedirs(os.path.dirname(SRC), exist_ok=True)
    with open(SRC, "w", encoding="utf-8", newline="\n") as f:
        f.write(html)
    print(f"index.html geschreven: {len(html)} bytes (uit {os.path.relpath(OUT, ROOT)})")


def build_demo():
    # Maakt een zelfstandige demo.html uit index.html door de mock in <head> te
    # zetten. Werkt als losse link (GitHub Pages / htmlpreview), zonder hardware.
    with open(SRC, encoding="utf-8") as f:
        html = f.read()
    marker = "</head>"
    if marker in html:
        html = html.replace(marker, DEMO_MOCK + marker, 1)
    else:
        html = DEMO_MOCK + html
    with open(DEMO, "w", encoding="utf-8", newline="\n") as f:
        f.write(html)
    print(f"demo.html gegenereerd: {len(html)} bytes (uit {os.path.relpath(SRC, ROOT)})")


if __name__ == "__main__":
    mode = sys.argv[1] if len(sys.argv) > 1 else "generate"
    if mode == "extract":
        extract()
    elif mode == "demo":
        build_demo()
    else:
        generate()
