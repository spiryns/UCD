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


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "extract":
        extract()
    else:
        generate()
