// SensePath web-app ; HTML+CSS+JS als één PROGMEM string
// Gehost door de XIAO ESP32-S3 op http://<ip>/
// Volledig accessibility-first ontworpen voor blinde gebruikers.
// Pattern: 1 tap = label voorlezen, 2 taps binnen 400ms = activeren.
#pragma once
#include <Arduino.h>

const char INDEX_HTML[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="nl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no,viewport-fit=cover">
<meta name="theme-color" content="#0a0a0a">
<meta name="mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<title>SensePath</title>
<style>
*{box-sizing:border-box;-webkit-tap-highlight-color:transparent}
:root{
  --bg:#0a0a0a;
  --surface:#1f1f1f;
  --surface-2:#2d2d2d;
  --surface-3:#3a3a3a;
  --primary:#ffd166;
  --primary-dark:#b58a3c;
  --text:#ffffff;
  --text-dim:#cccccc;
  --danger:#ff6b6b;
  --danger-dark:#3a1010;
  --success:#51cf66;
  --warn:#ffd43b;
  --focus:#ffd166;
}
html,body{
  background:var(--bg);
  color:var(--text);
  font-family:-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,sans-serif;
  margin:0;padding:0;
  font-size:19px;line-height:1.5;
  -webkit-user-select:none;user-select:none;
  -webkit-touch-callout:none;
  overscroll-behavior:none;
}
.container{max-width:520px;margin:0 auto;padding:16px;padding-bottom:140px}

h1{color:var(--primary);font-size:28px;font-weight:700;margin:12px 0 20px;text-align:center;letter-spacing:.5px}
h2{color:var(--primary);font-size:22px;margin:24px 0 12px;font-weight:600}
h3{color:var(--text);font-size:18px;margin:14px 0 8px;font-weight:500}

/* ───── Universal button ───── */
button,.btn{
  background:var(--surface);
  color:var(--text);
  border:2px solid var(--surface-3);
  padding:18px 20px;
  min-height:80px;
  font-size:18px;font-weight:500;
  width:100%;margin:8px 0;
  border-radius:14px;
  cursor:pointer;
  display:flex;align-items:center;justify-content:flex-start;gap:14px;
  font-family:inherit;text-align:left;
  transition:transform .1s ease, background .15s ease, border-color .15s ease;
  -webkit-user-select:none;user-select:none;
}
button:active,.btn:active{transform:scale(0.98)}
button.primary{
  background:var(--primary);color:#000;
  border-color:var(--primary);font-weight:700;
  justify-content:center;font-size:22px;min-height:90px;
}
button.danger{
  background:var(--danger-dark);color:#ffb3b3;
  border-color:var(--danger);
  justify-content:center;font-weight:600;
}
button.danger.confirming{
  background:var(--danger);color:#000;
  animation:pulse-danger 1s infinite;
}
@keyframes pulse-danger{0%,100%{box-shadow:0 0 0 0 var(--danger)}50%{box-shadow:0 0 20px 4px var(--danger)}}

/* ───── A11y visual feedback ───── */
.a11y-reading{
  outline:5px solid var(--focus) !important;
  outline-offset:-2px;
  background:var(--surface-2) !important;
}
.a11y-activated{
  background:var(--primary) !important;
  color:#000 !important;
  outline:5px solid var(--primary) !important;
}

/* ───── Tabs ───── */
.tabs{
  display:flex;
  position:fixed;
  bottom:0;left:0;right:0;
  background:var(--surface);
  border-top:3px solid var(--primary);
  z-index:100;
  padding:8px 6px calc(env(safe-area-inset-bottom) + 8px);
}
.tab-btn{
  flex:1;background:transparent;
  border:2px solid transparent;
  color:var(--text-dim);
  font-size:14px;font-weight:600;
  padding:10px 4px;min-height:auto;
  margin:0 3px;border-radius:10px;
  display:flex;flex-direction:column;align-items:center;gap:6px;
}
.tab-btn .ico{width:30px;height:30px}
.tab-btn .ico svg{width:100%;height:100%;stroke:currentColor;fill:none;stroke-width:2;stroke-linecap:round;stroke-linejoin:round}
.tab-btn.active{color:var(--primary);background:var(--surface-2);border-color:var(--primary)}

/* ───── Pages ───── */
.page{display:none}
.page.active{display:block;animation:fadeIn .2s ease}
@keyframes fadeIn{from{opacity:.5}to{opacity:1}}

/* ───── Native inputs (geen custom tap-zone) ───── */
.native-input{
  background:var(--surface);
  border:2px solid var(--surface-3);
  border-radius:14px;
  padding:20px;
  margin:8px 0;
  min-height:80px;
  color:var(--text);font-size:18px;
  width:100%;outline:none;font-family:inherit;
  -webkit-user-select:text;user-select:text;
}
.native-input::placeholder{color:var(--text-dim);opacity:.7}
.native-input:focus{
  border-color:var(--focus);
  outline:4px solid var(--focus);
  outline-offset:-2px;
}

/* ───── Voice search (primary, hero placement) ───── */
.voice-btn{
  background:linear-gradient(135deg,var(--primary),#ffb83a);
  color:#000;
  border:none;
  min-height:120px;
  font-size:22px;font-weight:800;
  border-radius:18px;
  justify-content:center;text-align:center;
  gap:18px;
  box-shadow:0 6px 24px rgba(255,209,102,.25);
}
.voice-btn .mic-large{
  width:48px;height:48px;
  background:rgba(0,0,0,.15);
  border-radius:50%;
  display:flex;align-items:center;justify-content:center;
}
.voice-btn .mic-large svg{width:28px;height:28px;stroke:#000;fill:none;stroke-width:2.5;stroke-linecap:round;stroke-linejoin:round}
.voice-btn.listening{
  animation:pulse-voice 1.2s infinite;
  background:linear-gradient(135deg,#ff6b6b,#c0392b);
  color:#fff;
}
.voice-btn.listening .mic-large svg{stroke:#fff}
@keyframes pulse-voice{
  0%,100%{box-shadow:0 0 0 0 rgba(255,107,107,.5)}
  50%{box-shadow:0 0 0 24px rgba(255,107,107,0)}
}

/* ───── Section labels (smaller, integrated) ───── */
.section-label{
  color:var(--text-dim);
  font-size:14px;font-weight:600;
  text-transform:uppercase;letter-spacing:.8px;
  margin:24px 4px 8px;
}

/* ───── Lists ───── */
.dest-item,.result-item{
  background:var(--surface);
  border:2px solid var(--surface-3);
  padding:18px;margin:8px 0;border-radius:12px;
  display:flex;justify-content:space-between;align-items:center;
  min-height:80px;font-size:18px;cursor:pointer;
}
.dest-name,.result-text{flex:1;font-weight:500}
.dest-del{
  width:60px;min-height:60px;padding:0;
  background:transparent;border:2px solid var(--danger);
  color:var(--danger);justify-content:center;
  margin:0 0 0 12px;
}
.dest-del svg{width:24px;height:24px;stroke:var(--danger)}
.dest-del.confirming{background:var(--danger);color:#000}
.dest-del.confirming svg{stroke:#000}

/* ───── Settings ───── */
.setting-row{
  background:var(--surface);
  border:2px solid var(--surface-3);
  border-radius:14px;
  padding:14px 16px;
  margin:14px 0;
}
.setting-row h3{margin:0 0 12px;color:var(--primary)}
.setting-row .setting-value{
  background:var(--surface-2);
  border:2px solid var(--primary-dark);
  margin:0;font-size:18px;
  min-height:70px;
  justify-content:space-between;
}
.setting-value .cur{color:var(--primary);font-weight:700}
.setting-value .cycle-hint{color:var(--text-dim);font-size:14px}
.opt-row{display:flex;gap:8px;flex-wrap:wrap}
.opt-row button{
  flex:1;min-width:0;margin:0;
  padding:14px 8px;font-size:16px;
  min-height:70px;justify-content:center;text-align:center;
}
.opt-row button.selected{
  background:var(--primary);color:#000;
  border-color:var(--primary);font-weight:700;
}

/* ───── Banners / status ───── */
.banner{
  padding:20px;border-radius:14px;margin:14px 0;text-align:center;
  font-size:18px;font-weight:500;min-height:90px;
  display:flex;flex-direction:column;align-items:center;justify-content:center;gap:8px;
}
.banner-info{background:#1c3a4f;color:#bae6fd;border:2px solid #38bdf8}
.banner-success{background:#0e3b1e;color:#86efac;border:2px solid #22c55e}
.banner-warn{background:#3b2a0a;color:#fde047;border:2px solid #eab308}
.banner-danger{background:#3a1010;color:#fecaca;border:2px solid #ef4444}

.status-text{font-size:22px;font-weight:600;margin:14px 0}
.muted{color:var(--text-dim);font-size:16px}
.divider{height:2px;background:var(--surface-3);margin:24px 0;border:none}

/* ───── Icons ───── */
.ic,.ico{
  display:inline-flex;align-items:center;justify-content:center;
  flex-shrink:0;width:28px;height:28px;
}
.ic svg{width:100%;height:100%;stroke:currentColor;fill:none;stroke-width:2;stroke-linecap:round;stroke-linejoin:round}

/* ───── Screen-reader-only text (for native VO/TalkBack) ───── */
.sr-only{
  position:absolute;width:1px;height:1px;padding:0;margin:-1px;
  overflow:hidden;clip:rect(0,0,0,0);white-space:nowrap;border:0;
}

/* ───── Digital twin (live servo-spiegel) ───── */
.twin-card{
  background:var(--surface);
  border:2px solid var(--primary-dark);
  border-radius:14px;
  padding:18px 14px;
  margin:14px 0;
  display:flex;flex-direction:column;align-items:center;gap:10px;
}
.twin-card .twin-title{
  color:var(--text-dim);font-size:14px;font-weight:600;
  text-transform:uppercase;letter-spacing:.6px;
}
.twin-dial{
  width:200px;height:200px;
  position:relative;
}
.twin-dial svg{width:100%;height:100%}
.twin-dial .needle{
  transform-box:view-box;
  transform-origin:100px 100px;
  transition:transform 120ms ease-out;
}
.twin-dial.stale .needle{opacity:.35}
.twin-card .twin-angle{
  color:var(--primary);font-size:22px;font-weight:700;
  font-variant-numeric:tabular-nums;
}
.twin-card .twin-status{color:var(--text-dim);font-size:13px}

/* ───── Gesture hint banner (read-all swipe) ───── */
.gesture-hint{
  position:fixed;top:env(safe-area-inset-top,20px);left:50%;
  transform:translate(-50%,-200%);
  background:var(--primary);color:#000;
  padding:16px 24px;border-radius:12px;
  font-weight:700;font-size:18px;
  z-index:200;transition:transform .3s ease;
  box-shadow:0 8px 30px rgba(0,0,0,.5);
}
.gesture-hint.show{transform:translate(-50%,20px)}
</style>
</head>
<body>

<!-- Live regions voor native screen readers (VoiceOver / TalkBack) -->
<div role="status" aria-live="polite" aria-atomic="true" id="live-status" class="sr-only"></div>
<div role="alert" aria-live="assertive" id="live-alert" class="sr-only"></div>

<!-- Gesture hint banner -->
<div id="gesture-hint" class="gesture-hint"></div>

<div class="container" id="main">
  <h1>SensePath</h1>

  <!-- ═══════════════ BESTEMMING ═══════════════ -->
  <div id="page-home" class="page active" data-page-label="Bestemming. Spreek je bestemming uit, gebruik je locatie, of kies uit recente of opgeslagen bestemmingen.">

    <!-- VOICE SEARCH: primaire input voor blinde gebruikers -->
    <button class="voice-btn" data-a11y data-action="startVoiceSearch" id="voice-btn"
            data-label="Spreek je bestemming. Dubbel-tik en spreek hardop het adres of de plaats."
            data-role="hoofdknop voor spraak-invoer"
            data-hint="Spraakherkenning is sneller dan typen.">
      <span class="mic-large"><svg viewBox="0 0 24 24"><path d="M12 1a3 3 0 0 0-3 3v8a3 3 0 0 0 6 0V4a3 3 0 0 0-3-3z"/><path d="M19 10v2a7 7 0 0 1-14 0v-2"/><line x1="12" y1="19" x2="12" y2="23"/><line x1="8" y1="23" x2="16" y2="23"/></svg></span>
      <span id="voice-label">Spreek bestemming</span>
    </button>

    <button data-a11y data-action="useCurrentLocation"
            data-label="Gebruik mijn huidige locatie als bestemming"
            data-role="knop"
            data-hint="GPS bepaalt waar je nu bent.">
      <span class="ic"><svg viewBox="0 0 24 24"><path d="M21 10c0 7-9 13-9 13s-9-6-9-13a9 9 0 0 1 18 0z"/><circle cx="12" cy="10" r="3"/></svg></span>
      Mijn locatie
    </button>

    <!-- RECENT (auto-tracked, top 5) -->
    <div id="recent-section" style="display:none">
      <div class="section-label">Recent</div>
      <div id="recent-list" aria-live="polite"></div>
    </div>

    <!-- OPGESLAGEN (user-managed) -->
    <div class="section-label">Opgeslagen bestemmingen</div>
    <div id="dest-list" aria-live="polite"></div>

    <button data-a11y data-action="saveCurrentAsDest"
            data-label="Bewaar de huidige bestemming in opgeslagen lijst"
            data-role="knop">
      <span class="ic"><svg viewBox="0 0 24 24"><line x1="12" y1="5" x2="12" y2="19"/><line x1="5" y1="12" x2="19" y2="12"/></svg></span>
      Bewaar bestemming
    </button>

    <!-- TYP-VELD (secundair pad, voor wie voice niet werkt) -->
    <div class="section-label">Of typ adres</div>
    <input type="search" id="custom-dest" class="native-input"
           role="searchbox" aria-label="Bestemming zoekveld, typ adres of plaats"
           aria-describedby="search-hint"
           placeholder="Adres, plaats, of bedrijfsnaam..." autocomplete="off">
    <small id="search-hint" class="sr-only">Druk op Enter of de Zoek-knop om te zoeken. Resultaten verschijnen eronder.</small>

    <button data-a11y data-action="searchPlaces"
            data-label="Zoek de getypte bestemming"
            data-role="knop">
      <span class="ic"><svg viewBox="0 0 24 24"><circle cx="11" cy="11" r="8"/><line x1="21" y1="21" x2="16.65" y2="16.65"/></svg></span>
      Zoek
    </button>

    <div id="search-results" aria-live="polite"></div>

    <div class="divider"></div>

    <button class="primary" data-a11y data-action="startRoute"
            data-label="Start route naar de gekozen bestemming"
            data-role="hoofdknop"
            data-hint="Begint navigatie met trillingen en stem.">
      <span class="ic"><svg viewBox="0 0 24 24"><polygon points="5 3 19 12 5 21 5 3" fill="currentColor" stroke="none"/></svg></span>
      Start route
    </button>
  </div>

  <!-- ═══════════════ NAVIGATIE ═══════════════ -->
  <div id="page-nav" class="page" data-page-label="Navigatie.">
    <div id="no-route" class="banner banner-warn" data-a11y data-action="goToPage" data-arg="home"
         data-label="Er is geen actieve route. Tik dubbel om naar Bestemming te gaan."
         data-role="info">
      <strong>Geen actieve route</strong>
      <small>Dubbel-tik om bestemming te kiezen</small>
    </div>

    <div id="active-route" style="display:none">
      <div class="banner banner-success" id="nav-dest-banner" data-a11y data-action="speakRouteOverview"
           data-label="Onderweg. Tik voor route-overzicht.">
        <div class="muted">Onderweg naar</div>
        <div class="status-text" id="nav-dest-name">...</div>
      </div>

      <div class="banner banner-info" id="nav-instruction-banner" data-a11y data-action="repeatLast"
           data-label="Huidige instructie. Tik om te herhalen.">
        <div class="muted">Volgende stap</div>
        <div class="status-text" id="nav-instruction">Wachten op instructies...</div>
      </div>

      <!-- Digital twin: live spiegel van de servo-kompas op de stok.
           aria-hidden zodat blinde gebruikers er niet door gestoord worden
           (puur visuele feedback voor expo/begeleider). -->
      <div class="twin-card" id="twin-card" aria-hidden="true">
        <div class="twin-title">Live kompas op stok</div>
        <div class="twin-dial" id="twin-dial">
          <svg viewBox="0 0 200 200">
            <circle cx="100" cy="100" r="92" fill="#0a0a0a" stroke="#3a3a3a" stroke-width="3"/>
            <!-- Tick-marks om de 30° -->
            <g stroke="#3a3a3a" stroke-width="2" stroke-linecap="round">
              <line x1="100" y1="14"  x2="100" y2="26"/>
              <line x1="100" y1="174" x2="100" y2="186"/>
              <line x1="14"  y1="100" x2="26"  y2="100"/>
              <line x1="174" y1="100" x2="186" y2="100"/>
              <line x1="43"  y1="43"  x2="51"  y2="51"/>
              <line x1="149" y1="43"  x2="157" y2="51"/>
              <line x1="43"  y1="157" x2="51"  y2="149"/>
              <line x1="149" y1="157" x2="157" y2="149"/>
            </g>
            <!-- Forward-kompas: 0 = recht vooruit (nulpunt), L/R = uitwijking -->
            <text x="20" y="106" fill="#666" font-size="12" font-weight="600">L</text>
            <text x="172" y="106" fill="#666" font-size="12" font-weight="600">R</text>
            <text x="96" y="22"  fill="#ffd166" font-size="13" font-weight="700">0</text>
            <!-- Naald: bij angle 90 wijst rechtop; uitwijking = angle-90 graden -->
            <g class="needle" id="twin-needle">
              <polygon points="100,22 108,100 100,108 92,100" fill="#ffd166" stroke="#b58a3c" stroke-width="1.5"/>
              <circle cx="100" cy="100" r="8" fill="#ffd166" stroke="#0a0a0a" stroke-width="2"/>
            </g>
          </svg>
        </div>
        <div class="twin-angle"><span id="twin-angle-val">0</span>°</div>
        <div class="twin-status" id="twin-status">Verbinding maken...</div>
      </div>

      <button data-a11y data-action="askLocation"
              data-label="Waar ben ik nu?"
              data-hint="Spreekt straatnaam of GPS-coördinaten uit.">
        <span class="ic"><svg viewBox="0 0 24 24"><circle cx="12" cy="12" r="10"/><circle cx="12" cy="12" r="3"/></svg></span>
        Waar ben ik?
      </button>

      <button data-a11y data-action="repeatLast"
              data-label="Herhaal de laatste gesproken instructie.">
        <span class="ic"><svg viewBox="0 0 24 24"><polyline points="23 4 23 10 17 10"/><path d="M3.51 9a9 9 0 0 1 14.85-3.36L23 10"/></svg></span>
        Herhaal instructie
      </button>

      <button id="pause-btn" data-a11y data-action="togglePause"
              data-label="Pauzeer de route."
              data-hint="Stopt tijdelijk de navigatie.">
        <span class="ic" id="pause-icon"><svg viewBox="0 0 24 24"><rect x="6" y="4" width="4" height="16"/><rect x="14" y="4" width="4" height="16"/></svg></span>
        <span id="pause-label">Pauzeer</span>
      </button>

      <button class="danger" data-a11y data-action="confirmStopRoute" id="stop-btn"
              data-label="Stop de route helemaal."
              data-hint="Vereist twee bevestigingen om per ongeluk stoppen te voorkomen.">
        <span class="ic"><svg viewBox="0 0 24 24"><rect x="5" y="5" width="14" height="14" rx="1" fill="currentColor" stroke="none"/></svg></span>
        <span id="stop-label">Stop route</span>
      </button>
    </div>
  </div>

  <!-- ═══════════════ SETTINGS ═══════════════ -->
  <div id="page-settings" class="page" data-page-label="Instellingen.">
    <h2>Knop op handvat</h2>

    <div class="setting-row">
      <h3>Korte druk doet</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="btn_short" id="val-btn_short">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <div class="setting-row">
      <h3>Dubbel-druk doet</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="btn_double" id="val-btn_double">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <div class="setting-row">
      <h3>Lange druk doet</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="btn_long" id="val-btn_long">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <h2>Trillingen</h2>

    <div class="setting-row">
      <h3>Sterkte</h3>
      <div class="opt-row" id="opts-vib_intensity">
        <button data-a11y data-action="setSetting" data-arg="vib_intensity:0" data-key="vib_intensity" data-val="0" data-label-base="Sterkte laag">Laag</button>
        <button data-a11y data-action="setSetting" data-arg="vib_intensity:1" data-key="vib_intensity" data-val="1" data-label-base="Sterkte medium">Medium</button>
        <button data-a11y data-action="setSetting" data-arg="vib_intensity:2" data-key="vib_intensity" data-val="2" data-label-base="Sterkte hoog">Hoog</button>
      </div>
    </div>

    <div class="setting-row">
      <h3>Trilling bij obstakel</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="vib_m4" id="val-vib_m4">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <div class="setting-row">
      <h3>Trilling bij koersafwijking</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="vib_m6" id="val-vib_m6">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <p style="color:var(--text-dim);font-size:13px;margin:4px 2px 8px">
      Op de controller-knop: 1 keer klikken = afslag rechts, 2 keer klikken = afslag links.
      Stel hieronder per kant in welke trilling je krijgt (mag ook dezelfde zijn).
    </p>
    <div class="setting-row">
      <h3>Afslag rechts (1 keer klikken)</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="vib_turn_right" id="val-vib_turn_right">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <div class="setting-row">
      <h3>Afslag links (2 keer klikken)</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="vib_turn_left" id="val-vib_turn_left">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <h2>Stem</h2>

    <div class="setting-row">
      <h3>Audio fallback</h3>
      <div class="opt-row" id="opts-audio_enabled">
        <button data-a11y data-action="setSetting" data-arg="audio_enabled:0" data-key="audio_enabled" data-val="0" data-label-base="Audio uit">Uit</button>
        <button data-a11y data-action="setSetting" data-arg="audio_enabled:1" data-key="audio_enabled" data-val="1" data-label-base="Audio aan">Aan</button>
      </div>
    </div>

    <div class="setting-row">
      <h3>Spraak-snelheid</h3>
      <button class="setting-value" data-a11y data-action="cycleSetting" data-arg="tts_rate" id="val-tts_rate">
        <span class="cur">...</span>
        <span class="cycle-hint">▶</span>
      </button>
    </div>

    <h2>Noodcontact</h2>
    <input type="tel" id="emergency" class="native-input"
           aria-label="Noodcontact telefoonnummer"
           placeholder="+32 XXX XX XX XX" autocomplete="off">

    <div class="divider"></div>

    <button class="primary" data-a11y data-action="saveSettings"
            data-label="Sla alle instellingen op">
      <span class="ic"><svg viewBox="0 0 24 24"><path d="M19 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h11l5 5v11a2 2 0 0 1-2 2z"/><polyline points="17 21 17 13 7 13 7 21"/><polyline points="7 3 7 8 15 8"/></svg></span>
      Opslaan
    </button>

    <button data-a11y data-action="testSpeech"
            data-label="Test de stem-uitvoer">
      <span class="ic"><svg viewBox="0 0 24 24"><polygon points="11 5 6 9 2 9 2 15 6 15 11 19 11 5"/><path d="M19.07 4.93a10 10 0 0 1 0 14.14"/></svg></span>
      Test stem
    </button>

    <button class="danger" id="reset-btn" data-a11y data-action="confirmResetSettings"
            data-label="Reset alle instellingen naar standaard"
            data-hint="Vereist twee bevestigingen.">
      <span class="ic"><svg viewBox="0 0 24 24"><polyline points="1 4 1 10 7 10"/><path d="M3.51 15a9 9 0 1 0 2.13-9.36L1 10"/></svg></span>
      <span id="reset-label">Reset</span>
    </button>
  </div>
</div>

<!-- Bottom tab-bar -->
<nav class="tabs" role="tablist" aria-label="Hoofdnavigatie">
  <button class="tab-btn active" id="tab-home" data-a11y data-action="goToPage" data-arg="home"
          data-label="Tab Bestemming" data-role="tab">
    <span class="ico"><svg viewBox="0 0 24 24"><path d="M21 10c0 7-9 13-9 13s-9-6-9-13a9 9 0 0 1 18 0z"/><circle cx="12" cy="10" r="3"/></svg></span>
    <span>Bestemming</span>
  </button>
  <button class="tab-btn" id="tab-nav" data-a11y data-action="goToPage" data-arg="nav"
          data-label="Tab Navigatie" data-role="tab">
    <span class="ico"><svg viewBox="0 0 24 24"><circle cx="12" cy="12" r="10"/><polygon points="16.24 7.76 14.12 14.12 7.76 16.24 9.88 9.88 16.24 7.76"/></svg></span>
    <span>Navigatie</span>
  </button>
  <button class="tab-btn" id="tab-settings" data-a11y data-action="goToPage" data-arg="settings"
          data-label="Tab Instellingen" data-role="tab">
    <span class="ico"><svg viewBox="0 0 24 24"><circle cx="12" cy="12" r="3"/><path d="M19.4 15a1.65 1.65 0 0 0 .33 1.82l.06.06a2 2 0 0 1-2.83 2.83l-.06-.06a1.65 1.65 0 0 0-1.82-.33 1.65 1.65 0 0 0-1 1.51V21a2 2 0 0 1-4 0v-.09A1.65 1.65 0 0 0 9 19.4a1.65 1.65 0 0 0-1.82.33l-.06.06a2 2 0 0 1-2.83-2.83l.06-.06a1.65 1.65 0 0 0 .33-1.82 1.65 1.65 0 0 0-1.51-1H3a2 2 0 0 1 0-4h.09A1.65 1.65 0 0 0 4.6 9a1.65 1.65 0 0 0-.33-1.82l-.06-.06a2 2 0 0 1 2.83-2.83l.06.06a1.65 1.65 0 0 0 1.82.33H9a1.65 1.65 0 0 0 1-1.51V3a2 2 0 0 1 4 0v.09a1.65 1.65 0 0 0 1 1.51 1.65 1.65 0 0 0 1.82-.33l.06-.06a2 2 0 0 1 2.83 2.83l-.06.06a1.65 1.65 0 0 0-.33 1.82V9a1.65 1.65 0 0 0 1.51 1H21a2 2 0 0 1 0 4h-.09a1.65 1.65 0 0 0-1.51 1z"/></svg></span>
    <span>Instellingen</span>
  </button>
</nav>

<script>
// ╔═══════════════════════════════════════════════════════════════════╗
// ║   GOOGLE MAPS API KEY (vervangen door main.cpp / mock_server)     ║
// ╚═══════════════════════════════════════════════════════════════════╝
const GOOGLE_MAPS_API_KEY = "PLAK_HIER_JE_KEY";
const GOOGLE_ENABLED = GOOGLE_MAPS_API_KEY.startsWith("AIza") && GOOGLE_MAPS_API_KEY.length > 30;

// ═══════════════ Action-types (synced met main.cpp) ═══════════════
const ACTIONS = [
  {id:0, name:"Niets"},
  {id:1, name:"Vraag huidige locatie"},
  {id:2, name:"Vraag overzicht route"},
  {id:3, name:"Herhaal laatste instructie"},
  {id:4, name:"Trilling-bevestiging"},
  {id:5, name:"Activeer noodhulp"},
  {id:6, name:"Audio aan of uit"},
  {id:7, name:"Spreek ETA op handvat"},
  {id:8, name:"Spreek locatie op handvat"},
  {id:9, name:"Slaapstand (deep sleep)"},
];
const DRV_EFFECTS = [
  {id:1,  name:"Strong Click 100%"},
  {id:10, name:"Double Click 100%"},
  {id:12, name:"Triple Click 100%"},
  {id:14, name:"Strong Click"},
  {id:24, name:"Sharp Tick"},
  {id:47, name:"Buzz oplopend"},
  {id:58, name:"Pulsing Strong"},
  {id:84, name:"Long Buzz 1 seconde"},
  {id:117,name:"Smooth Click"},
];
const INTENSITY_OPTS = [
  {id:0,name:"Laag"},{id:1,name:"Medium"},{id:2,name:"Hoog"},
];
const TTS_RATE_OPTS = [
  {id:5, name:"Zeer langzaam"},
  {id:7, name:"Langzaam"},
  {id:10,name:"Normaal"},
  {id:13,name:"Snel"},
  {id:16,name:"Zeer snel"},
  {id:20,name:"Maximaal"},
];
const AUDIO_OPTS = [
  {id:0,name:"Uit"},{id:1,name:"Aan"},
];
// Afslag-trilpatronen (gesynced met playTurnPattern in main.cpp). Coin-ERM
// voelt alleen lange pulsen, dus dit zijn voelbare patronen, geen ROM-effecten.
const TURN_PATTERNS = [
  {id:1, name:"1 trilling"},
  {id:2, name:"2 trillingen"},
  {id:3, name:"3 trillingen"},
  {id:4, name:"1 lange trilling"},
  {id:5, name:"kort dan lang"},
];

const SETTING_DEFS = {
  btn_short: ACTIONS,
  btn_double: ACTIONS,
  btn_long: ACTIONS,
  vib_intensity: INTENSITY_OPTS,
  vib_m4: DRV_EFFECTS,
  vib_m6: DRV_EFFECTS,
  vib_turn_right: TURN_PATTERNS,
  vib_turn_left:  TURN_PATTERNS,
  audio_enabled: AUDIO_OPTS,
  tts_rate: TTS_RATE_OPTS,
};
const SETTING_LABELS = {
  btn_short: "Korte druk doet",
  btn_double: "Dubbel-druk doet",
  btn_long: "Lange druk doet",
  vib_intensity: "Trilling sterkte",
  vib_m4: "Trilling bij obstakel",
  vib_m6: "Trilling bij koersafwijking",
  vib_turn_right: "Afslag rechts (1 keer klikken)",
  vib_turn_left:  "Afslag links (2 keer klikken)",
  audio_enabled: "Audio fallback",
  tts_rate: "Spraak snelheid",
};
const PAGE_LABELS = {
  home: "Bestemming. Zoek een plek of kies een opgeslagen bestemming.",
  nav: "Navigatie.",
  settings: "Instellingen.",
};

// ═══════════════ Global state ═══════════════
let state = {
  destinations: [],
  activeRoute: null,
  lastInstruction: "",
  settings: {
    btn_short:1, btn_double:2, btn_long:5,
    vib_intensity:1, vib_m4:14, vib_m6:12, vib_turn_right:1, vib_turn_left:2,
    audio_enabled:0, tts_rate:10, emergency:"",
  },
  ttsRate: 1.0,
  selectedPlace: null,
  searchResults: [],
  // Google
  autocompleteService: null,
  placesService: null,
  directionsService: null,
  geocoder: null,
  directions: null,
  currentStepIdx: 0,
  gpsWatchId: null,
  // Confirmation pattern
  pendingConfirm: null,
  // Pause
  paused: false,
};

// ═══════════════ TTS (Text-to-Speech) ═══════════════
const Speak = {
  now(text, opts) {
    if (!text || !('speechSynthesis' in window)) return;
    try { speechSynthesis.cancel(); } catch(e){}
    const u = new SpeechSynthesisUtterance(text);
    u.lang = (opts && opts.lang) || 'nl-NL';
    u.rate = (opts && opts.rate) || state.ttsRate || 1.0;
    u.pitch = (opts && opts.pitch) || 1.0;
    u.volume = 1.0;
    speechSynthesis.speak(u);
    state.lastInstruction = text;
    // Mirror to live-region for native screen readers
    const live = document.getElementById('live-status');
    if (live) { live.textContent = ''; setTimeout(() => live.textContent = text, 50); }
  },
  alert(text) {
    this.now(text, {pitch:1.2});
    const live = document.getElementById('live-alert');
    if (live) { live.textContent = ''; setTimeout(() => live.textContent = text, 50); }
  },
  cancel() {
    if ('speechSynthesis' in window) {
      try { speechSynthesis.cancel(); } catch(e){}
    }
  },
};

// ═══════════════ A11y CORE  (1-tap-read, 2-tap-activate) ═══════════════
const A11y = {
  lastTap: { el: null, time: 0 },
  DOUBLE_TAP_MS: 400,
  longPressTimer: null,
  LONG_PRESS_MS: 800,
  _twoFingerStart: null,

  _lastAnnouncedInput: null,

  init() {
    // Capture-phase click interceptor → eet alle taps op data-a11y elementen
    document.addEventListener('click', this.onClick.bind(this), true);
    // Touch tracking voor long-press en two-finger gestures
    document.addEventListener('touchstart', this.onTouchStart.bind(this), {passive:true});
    document.addEventListener('touchmove', this.onTouchMove.bind(this), {passive:true});
    document.addEventListener('touchend', this.onTouchEnd.bind(this), {passive:true});
    // Native input focus → spreek label uit (vervangt onze custom tap-zone aanpak)
    document.addEventListener('focusin', (e) => {
      const t = e.target;
      if (t.tagName !== 'INPUT' && t.tagName !== 'TEXTAREA') return;
      if (this._lastAnnouncedInput === t.id) return;
      this._lastAnnouncedInput = t.id;
      const label = t.getAttribute('aria-label') || t.getAttribute('placeholder') || '';
      if (label) Speak.now(label + '. Typ je tekst of druk op Enter om te zoeken.');
    });
    document.addEventListener('focusout', () => {
      setTimeout(() => { this._lastAnnouncedInput = null; }, 200);
    });
  },

  onClick(e) {
    // Native inputs: nooit intercepten ; laat OS-keyboard + iOS dictation knop werken.
    // De focusin-handler hieronder spreekt het label uit zodra focus arriveert.
    if (e.target.tagName === 'INPUT' || e.target.tagName === 'TEXTAREA' || e.target.tagName === 'SELECT') {
      return;
    }
    const el = e.target.closest('[data-a11y]');
    if (!el) return;

    const now = Date.now();
    const isDouble = this.lastTap.el === el && (now - this.lastTap.time) < this.DOUBLE_TAP_MS;

    if (isDouble) {
      this.lastTap = { el: null, time: 0 };
      e.preventDefault();
      e.stopImmediatePropagation();
      this.activate(el);
    } else {
      e.preventDefault();
      e.stopImmediatePropagation();
      this.lastTap = { el, time: now };
      this.haptic(40);
      this.read(el);
      this.highlight(el);
    }
  },

  read(el) {
    let label = el.getAttribute('data-label')
      || el.getAttribute('aria-label')
      || (el.textContent || '').trim();
    const role = el.getAttribute('data-role');
    if (role) label = label + ', ' + role;
    const valueEl = el.querySelector('.cur');
    if (valueEl && !label.includes(valueEl.textContent)) {
      label = label + ', huidige waarde ' + valueEl.textContent.trim();
    }
    Speak.now(label);
  },

  activate(el) {
    this.haptic([80, 40, 80]);
    this.highlightActive(el);
    const fn = el.getAttribute('data-action');
    const arg = el.getAttribute('data-arg');
    if (fn && typeof window[fn] === 'function') {
      window[fn](arg);
    }
  },

  highlight(el) {
    el.classList.add('a11y-reading');
    clearTimeout(el._a11yTimer);
    el._a11yTimer = setTimeout(() => el.classList.remove('a11y-reading'), 800);
  },

  highlightActive(el) {
    el.classList.remove('a11y-reading');
    el.classList.add('a11y-activated');
    setTimeout(() => el.classList.remove('a11y-activated'), 350);
  },

  haptic(pattern) {
    if (navigator.vibrate) {
      try { navigator.vibrate(pattern); } catch(e){}
    }
  },

  // Two-finger swipe-up → lees hele scherm
  onTouchStart(e) {
    if (e.touches.length === 1) {
      const target = e.target.closest('[data-a11y]');
      if (!target) return;
      clearTimeout(this.longPressTimer);
      this.longPressTimer = setTimeout(() => {
        const hint = target.getAttribute('data-hint');
        if (hint) {
          Speak.now('Tip: ' + hint);
          this.haptic([100, 50, 100, 50, 100]);
        }
      }, this.LONG_PRESS_MS);
    } else if (e.touches.length === 2) {
      this._twoFingerStart = {
        y: (e.touches[0].clientY + e.touches[1].clientY) / 2,
      };
    }
  },

  onTouchMove(e) {
    if (e.touches.length === 1) clearTimeout(this.longPressTimer);
    if (e.touches.length === 2 && this._twoFingerStart) {
      const y = (e.touches[0].clientY + e.touches[1].clientY) / 2;
      const dy = this._twoFingerStart.y - y;
      if (dy > 80) {
        this.readEntirePage();
        this._twoFingerStart = null;
      }
    }
  },

  onTouchEnd(e) {
    clearTimeout(this.longPressTimer);
    if (e.touches.length === 0) this._twoFingerStart = null;
  },

  readEntirePage() {
    this.haptic([50, 30, 50, 30, 50]);
    const activePage = document.querySelector('.page.active');
    if (!activePage) return;
    const pageLabel = activePage.getAttribute('data-page-label') || '';
    const items = activePage.querySelectorAll('[data-a11y]');
    const texts = Array.from(items).map(el => {
      return el.getAttribute('data-label')
        || el.getAttribute('aria-label')
        || (el.textContent || '').trim().replace(/\s+/g,' ');
    }).filter(t => t && t.length < 200);
    showHint('Hele scherm wordt voorgelezen');
    Speak.now(pageLabel + ' ' + texts.join('. '));
  },
};

function showHint(text) {
  const el = document.getElementById('gesture-hint');
  if (!el) return;
  el.textContent = text;
  el.classList.add('show');
  setTimeout(() => el.classList.remove('show'), 2500);
}

// ═══════════════ Page navigation ═══════════════
function goToPage(name) {
  document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
  document.querySelectorAll('.tab-btn').forEach(b => b.classList.remove('active'));
  const pageEl = document.getElementById('page-' + name);
  const tabEl = document.getElementById('tab-' + name);
  if (pageEl) pageEl.classList.add('active');
  if (tabEl) tabEl.classList.add('active');

  let label = PAGE_LABELS[name] || '';
  if (name === 'nav') {
    if (state.activeRoute) {
      label = `Navigatie. Onderweg naar ${state.activeRoute}.`;
      updateNavView();
      startTwinPolling();
    } else {
      label = 'Navigatie. Er is geen actieve route.';
      stopTwinPolling();
    }
  } else {
    // Andere pagina's: pauzeer twin-polling om bandbreedte te besparen
    stopTwinPolling();
  }
  if (name === 'settings') refreshAllSettingDisplays();
  Speak.now(label);
}

// ═══════════════ Destinations ═══════════════
async function loadDestinations() {
  try {
    const r = await fetch('/api/destinations');
    state.destinations = await r.json();
  } catch(e) { state.destinations = []; }
  renderDestinations();
}
function renderDestinations() {
  const div = document.getElementById('dest-list');
  if (!div) return;
  if (state.destinations.length === 0) {
    div.innerHTML = '<p class="muted">Geen opgeslagen bestemmingen. Zoek of bewaar een bestemming hierboven.</p>';
    return;
  }
  div.innerHTML = state.destinations.map((d,i) => `
    <div class="dest-item" data-a11y data-action="selectDestination" data-arg="${i}"
         data-label="Opgeslagen bestemming ${i+1} van ${state.destinations.length}: ${escapeHtml(d.name)}"
         data-role="lijst-item"
         data-hint="Dubbel-tik om te kiezen als route-bestemming.">
      <span class="dest-name">${escapeHtml(d.name)}</span>
      <button class="dest-del" data-a11y data-action="confirmDeleteDest" data-arg="${i}"
              data-label="Verwijder ${escapeHtml(d.name)} uit opgeslagen bestemmingen"
              data-hint="Vereist twee bevestigingen.">
        <svg viewBox="0 0 24 24" fill="none" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><polyline points="3 6 5 6 21 6"/><path d="M19 6v14a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2V6m3 0V4a2 2 0 0 1 2-2h4a2 2 0 0 1 2 2v2"/></svg>
      </button>
    </div>
  `).join('');
}
function selectDestination(arg) {
  const i = parseInt(arg);
  const d = state.destinations[i];
  if (!d) return;
  document.getElementById('custom-dest').value = d.name;
  state.selectedPlace = d.place || null;
  Speak.now(`Gekozen: ${d.name}. Tik op Start route om te beginnen.`);
}
function confirmDeleteDest(arg) {
  const i = parseInt(arg);
  const d = state.destinations[i];
  if (!d) return;
  const btn = document.querySelector(`[data-action="confirmDeleteDest"][data-arg="${i}"]`);
  if (state.pendingConfirm && state.pendingConfirm.action === 'deleteDest' && state.pendingConfirm.arg === arg && (Date.now() - state.pendingConfirm.time) < 5000) {
    state.pendingConfirm = null;
    if (btn) btn.classList.remove('confirming');
    deleteDestination(i);
  } else {
    state.pendingConfirm = { action: 'deleteDest', arg: arg, time: Date.now() };
    if (btn) btn.classList.add('confirming');
    Speak.alert(`Verwijder ${d.name}? Tik opnieuw dubbel om te bevestigen.`);
    setTimeout(() => {
      if (btn) btn.classList.remove('confirming');
      if (state.pendingConfirm && state.pendingConfirm.action === 'deleteDest') state.pendingConfirm = null;
    }, 5000);
  }
}
async function deleteDestination(i) {
  const name = state.destinations[i].name;
  state.destinations.splice(i, 1);
  await saveDestinationsToServer();
  renderDestinations();
  Speak.now(`${name} verwijderd.`);
}
async function saveCurrentAsDest() {
  const name = document.getElementById('custom-dest').value.trim();
  if (!name) { Speak.alert('Eerst een bestemming typen of zoeken.'); return; }
  state.destinations.push({name, place: state.selectedPlace});
  await saveDestinationsToServer();
  renderDestinations();
  Speak.now(`${name} bewaard in opgeslagen bestemmingen.`);
}
async function saveDestinationsToServer() {
  await fetch('/api/destinations', {
    method:'POST', headers:{'Content-Type':'application/json'},
    body: JSON.stringify(state.destinations.map(d => ({name:d.name})))
  });
}

// ═══════════════ Google Maps loader ═══════════════
function loadGoogleMaps() {
  if (!GOOGLE_ENABLED) {
    console.log("Google API key niet ingesteld ; manuele mode actief");
    return;
  }
  const script = document.createElement('script');
  script.src = `https://maps.googleapis.com/maps/api/js?key=${GOOGLE_MAPS_API_KEY}&libraries=places&callback=onGoogleMapsLoaded&loading=async`;
  script.async = true;
  script.onerror = () => console.error("Google Maps script kon niet laden");
  document.head.appendChild(script);
}
function onGoogleMapsLoaded() {
  state.autocompleteService = new google.maps.places.AutocompleteService();
  // PlacesService heeft een DOM-element nodig, we maken er een aan
  const dummy = document.createElement('div');
  state.placesService = new google.maps.places.PlacesService(dummy);
  state.directionsService = new google.maps.DirectionsService();
  state.geocoder = new google.maps.Geocoder();
  console.log('Google Maps geladen');
}

// ═══════════════ Custom accessible Places search ═══════════════
function searchPlaces() {
  const query = (document.getElementById('custom-dest').value || '').trim();
  if (!query) {
    Speak.alert('Typ eerst een adres in het zoekveld.');
    return;
  }
  if (!GOOGLE_ENABLED || !state.autocompleteService) {
    state.selectedPlace = null;
    Speak.alert('Google Maps niet beschikbaar. Bestemming wordt manueel gebruikt.');
    return;
  }
  Speak.now('Zoeken...');
  state.autocompleteService.getPlacePredictions({
    input: query,
    componentRestrictions: { country: 'be' },
  }, (predictions, status) => {
    if (status !== google.maps.places.PlacesServiceStatus.OK || !predictions) {
      Speak.alert('Geen resultaten gevonden voor ' + query);
      return;
    }
    state.searchResults = predictions.slice(0, 5);
    renderSearchResults();
    Speak.now(`${state.searchResults.length} resultaten gevonden. Tik op een resultaat om te kiezen.`);
  });
}
function renderSearchResults() {
  const div = document.getElementById('search-results');
  if (!div) return;
  div.innerHTML = state.searchResults.map((p, i) => `
    <div class="result-item" data-a11y data-action="pickSearchResult" data-arg="${i}"
         data-label="Resultaat ${i+1} van ${state.searchResults.length}: ${escapeHtml(p.description)}"
         data-role="zoekresultaat"
         data-hint="Dubbel-tik om dit resultaat als bestemming te kiezen.">
      <span class="result-text">${escapeHtml(p.description)}</span>
    </div>
  `).join('');
}
function pickSearchResult(arg) {
  const i = parseInt(arg);
  const pred = state.searchResults[i];
  if (!pred) return;
  state.placesService.getDetails({
    placeId: pred.place_id,
    fields: ['name','formatted_address','geometry','place_id'],
  }, (place, status) => {
    if (status !== google.maps.places.PlacesServiceStatus.OK) {
      Speak.alert('Kon details van resultaat niet ophalen.');
      return;
    }
    state.selectedPlace = place;
    document.getElementById('custom-dest').value = (place.name || '') + (place.formatted_address ? ', ' + place.formatted_address : '');
    document.getElementById('search-results').innerHTML = '';
    Speak.now(`Gekozen: ${place.name || pred.description}. Tik op Start route om te navigeren.`);
  });
}

// ═══════════════ Geolocation ═══════════════
function useCurrentLocation() {
  if (!navigator.geolocation) { Speak.alert('GPS niet beschikbaar op dit toestel.'); return; }
  Speak.now('Locatie bepalen...');
  navigator.geolocation.getCurrentPosition(
    (pos) => {
      const lat = pos.coords.latitude;
      const lng = pos.coords.longitude;
      if (GOOGLE_ENABLED && state.geocoder) {
        state.geocoder.geocode({location:{lat,lng}}, (results, status) => {
          if (status === 'OK' && results[0]) {
            document.getElementById('custom-dest').value = results[0].formatted_address;
            state.selectedPlace = {
              name: results[0].formatted_address,
              formatted_address: results[0].formatted_address,
              geometry: {location: results[0].geometry.location},
            };
            Speak.now('Huidige locatie ingesteld: ' + results[0].formatted_address);
          } else {
            const txt = `Locatie ${lat.toFixed(5)} ${lng.toFixed(5)}`;
            document.getElementById('custom-dest').value = txt;
            Speak.now('Huidige locatie ingesteld op GPS-coördinaten.');
          }
        });
      } else {
        const txt = `Locatie ${lat.toFixed(5)} ${lng.toFixed(5)}`;
        document.getElementById('custom-dest').value = txt;
        Speak.now('Huidige locatie ingesteld op GPS-coördinaten.');
      }
    },
    (err) => Speak.alert('Locatie kon niet bepaald worden. ' + err.message)
  );
}

// ═══════════════ Voice search (Web Speech API) ═══════════════
// Belangrijk: werkt alleen op HTTPS of localhost. Op HTTP IP-adressen → Chrome flag of HTTPS opzetten.
// iOS Safari: werkt sinds 14.5 met webkitSpeechRecognition; NIET in "Add to Home Screen" PWA-modus.
function startVoiceSearch() {
  const SR = window.SpeechRecognition || window.webkitSpeechRecognition;
  if (!SR) {
    Speak.alert('Spraakherkenning niet beschikbaar op dit toestel. Gebruik typen of mijn locatie.');
    return;
  }
  const btn = document.getElementById('voice-btn');
  const lbl = document.getElementById('voice-label');
  if (btn.classList.contains('listening')) {
    // Al aan het luisteren → stop
    if (state._voiceRec) try { state._voiceRec.stop(); } catch(e){}
    return;
  }

  Speak.now('Spreek je bestemming.');
  A11y.haptic([60, 40, 60]);

  // Korte vertraging zodat user de TTS-prompt hoort vóór hij begint te praten
  setTimeout(() => {
    let rec;
    try { rec = new SR(); }
    catch(e) { Speak.alert('Kon spraakherkenning niet starten.'); return; }
    state._voiceRec = rec;
    rec.lang = 'nl-NL';
    rec.interimResults = false;
    rec.maxAlternatives = 1;
    rec.continuous = false;

    let gotResult = false;
    let silenceTimer = null;

    rec.onstart = () => {
      btn.classList.add('listening');
      if (lbl) lbl.textContent = 'Luistert...';
      A11y.haptic(120);
      // Fallback: als binnen 8s niets komt, abort
      silenceTimer = setTimeout(() => {
        try { rec.stop(); } catch(e){}
      }, 8000);
    };

    rec.onresult = (e) => {
      gotResult = true;
      clearTimeout(silenceTimer);
      const transcript = (e.results[0] && e.results[0][0] && e.results[0][0].transcript) || '';
      const input = document.getElementById('custom-dest');
      input.value = transcript;
      state.selectedPlace = null;
      Speak.now('Je zei: ' + transcript + '. Ik zoek.');
      // Auto-search na korte pauze
      setTimeout(() => searchPlaces(), 800);
    };

    rec.onerror = (e) => {
      clearTimeout(silenceTimer);
      const err = e.error || 'onbekend';
      if (err === 'not-allowed' || err === 'service-not-allowed') {
        Speak.alert('Microfoon-toegang geweigerd. Sta microfoon toe in de browser-instellingen.');
      } else if (err === 'no-speech') {
        Speak.alert('Niets gehoord. Tik opnieuw en spreek duidelijk.');
      } else if (err === 'network') {
        Speak.alert('Internet vereist voor spraakherkenning. Geen verbinding.');
      } else {
        Speak.alert('Spraak-fout: ' + err);
      }
    };

    rec.onend = () => {
      clearTimeout(silenceTimer);
      btn.classList.remove('listening');
      if (lbl) lbl.textContent = 'Spreek bestemming';
      state._voiceRec = null;
      if (!gotResult) {
        // onerror heeft mogelijk al gesproken; alleen fallback als stil
        setTimeout(() => {
          if (!gotResult && !speechSynthesis.speaking) {
            // Stille fallback ; geen spam
          }
        }, 500);
      }
    };

    try { rec.start(); }
    catch(e) {
      btn.classList.remove('listening');
      if (lbl) lbl.textContent = 'Spreek bestemming';
      Speak.alert('Kon niet starten met luisteren. Probeer opnieuw.');
    }
  }, 1400);
}

// ═══════════════ Recents (auto-tracked, localStorage) ═══════════════
const RECENTS_KEY = 'sensepath_recents';
const RECENTS_MAX = 5;

function loadRecents() {
  try {
    const raw = localStorage.getItem(RECENTS_KEY);
    state.recents = raw ? JSON.parse(raw) : [];
  } catch(e) { state.recents = []; }
  renderRecents();
}
function addToRecents(name, place) {
  if (!name) return;
  state.recents = (state.recents || []).filter(r => r.name !== name);
  state.recents.unshift({name, place: place || null, ts: Date.now()});
  state.recents = state.recents.slice(0, RECENTS_MAX);
  try { localStorage.setItem(RECENTS_KEY, JSON.stringify(state.recents)); } catch(e){}
  renderRecents();
}
function renderRecents() {
  const section = document.getElementById('recent-section');
  const div = document.getElementById('recent-list');
  if (!div || !section) return;
  if (!state.recents || state.recents.length === 0) {
    section.style.display = 'none';
    return;
  }
  section.style.display = 'block';
  div.innerHTML = state.recents.map((r,i) => `
    <div class="dest-item" data-a11y data-action="selectRecent" data-arg="${i}"
         data-label="Recent ${i+1}: ${escapeHtml(r.name)}"
         data-role="recente bestemming"
         data-hint="Dubbel-tik om te kiezen.">
      <span class="dest-name">${escapeHtml(r.name)}</span>
    </div>
  `).join('');
}
function selectRecent(arg) {
  const i = parseInt(arg);
  const r = state.recents[i];
  if (!r) return;
  document.getElementById('custom-dest').value = r.name;
  state.selectedPlace = r.place || null;
  Speak.now(`Gekozen: ${r.name}. Tik op Start route om te beginnen.`);
}

// ═══════════════ Route start/stop ═══════════════
async function startRoute() {
  const dest = (document.getElementById('custom-dest').value || '').trim();
  if (!dest) { Speak.alert('Kies eerst een bestemming.'); return; }

  let directionsLoaded = false;
  if (GOOGLE_ENABLED && state.directionsService && navigator.geolocation) {
    try {
      Speak.now('Route berekenen...');
      directionsLoaded = await fetchDirections(dest);
    } catch(e) {
      console.error('Directions fout:', e);
    }
  }

  await fetch('/api/route/start', {
    method:'POST', headers:{'Content-Type':'application/x-www-form-urlencoded'},
    body: 'destination=' + encodeURIComponent(dest)
  });

  state.activeRoute = dest;
  state.currentStepIdx = 0;
  state.paused = false;
  addToRecents(dest, state.selectedPlace);
  goToPage('nav');

  if (directionsLoaded && state.directions && state.directions.steps.length > 0) {
    const totalKm = (state.directions.totalDistance / 1000).toFixed(1);
    const totalMin = Math.round(state.directions.totalDuration / 60);
    Speak.now(`Route gestart naar ${dest}. Afstand ${totalKm} kilometer, ongeveer ${totalMin} minuten lopen. Eerste instructie: ${state.directions.steps[0].instruction}`);
    startGPSTracking();
  } else {
    Speak.now('Route gestart naar ' + dest + '. Volg de trillingen op het handvat.');
  }

  // Digital twin: live spiegel van servo-kompas op stok
  startTwinPolling();
}

function fetchDirections(destination) {
  return new Promise((resolve, reject) => {
    navigator.geolocation.getCurrentPosition((pos) => {
      const origin = {lat:pos.coords.latitude, lng:pos.coords.longitude};
      const dest = (state.selectedPlace && state.selectedPlace.geometry)
        ? state.selectedPlace.geometry.location
        : destination;
      state.directionsService.route({
        origin, destination: dest,
        travelMode: google.maps.TravelMode.WALKING,
      }, (result, status) => {
        if (status === 'OK') {
          const leg = result.routes[0].legs[0];
          state.directions = {
            steps: leg.steps.map(s => ({
              instruction: stripHtml(s.instructions),
              distance: s.distance.value,
              duration: s.duration.value,
              endLocation: {lat:s.end_location.lat(), lng:s.end_location.lng()},
              maneuver: s.maneuver || 'straight',
            })),
            totalDistance: leg.distance.value,
            totalDuration: leg.duration.value,
          };
          resolve(true);
        } else { reject(status); }
      });
    }, reject, {enableHighAccuracy:true});
  });
}
function startGPSTracking() {
  if (!navigator.geolocation) return;
  stopGPSTracking();
  state.gpsWatchId = navigator.geolocation.watchPosition((pos) => {
    if (state.paused || !state.directions || !state.activeRoute) return;
    checkProgress(pos.coords.latitude, pos.coords.longitude);
  }, null, {enableHighAccuracy:true, maximumAge:2000});
}
function stopGPSTracking() {
  if (state.gpsWatchId !== null) {
    navigator.geolocation.clearWatch(state.gpsWatchId);
    state.gpsWatchId = null;
  }
}
function checkProgress(lat, lng) {
  if (state.currentStepIdx >= state.directions.steps.length) return;
  const step = state.directions.steps[state.currentStepIdx];
  const dist = haversine(lat, lng, step.endLocation.lat, step.endLocation.lng);
  if (dist < 50 && !step._preAnnounced) {
    step._preAnnounced = true;
    Speak.now(`Over ${Math.round(dist)} meter: ${step.instruction}`);
    if (step.maneuver.includes('turn')) {
      triggerEffect(state.settings.vib_m9 || 47);
    }
  }
  if (dist < 8 && !step._announced) {
    step._announced = true;
    Speak.now(step.instruction);
    state.currentStepIdx++;
    updateNavView();
    if (state.currentStepIdx >= state.directions.steps.length) {
      Speak.alert('Bestemming bereikt');
      triggerEffect(1);
      stopGPSTracking();
    }
  }
}
function haversine(lat1, lng1, lat2, lng2) {
  const R = 6371000;
  const dLat = (lat2 - lat1) * Math.PI / 180;
  const dLng = (lng2 - lng1) * Math.PI / 180;
  const a = Math.sin(dLat/2)**2 + Math.cos(lat1*Math.PI/180)*Math.cos(lat2*Math.PI/180)*Math.sin(dLng/2)**2;
  return 2 * R * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
}
function stripHtml(html) {
  const tmp = document.createElement('div');
  tmp.innerHTML = html;
  return tmp.textContent || tmp.innerText || '';
}
async function triggerEffect(id) {
  try {
    await fetch('/api/trigger-effect', {
      method:'POST', headers:{'Content-Type':'application/x-www-form-urlencoded'},
      body: 'id=' + id
    });
  } catch(e){}
}

// ═══════════════ Digital twin (live spiegel van servo-positie) ═══════════════
// Polt GET /api/servo elke 100ms terwijl een route actief is. De wijzer is een
// puur visuele weergave voor zichtende begeleiders/expo; aria-hidden=true zodat
// VoiceOver/TalkBack het overslaat en de blinde gebruiker niet stoort.
let twinPollTimer = null;
let twinLastFailed = false;

async function twinPollOnce() {
  try {
    const r = await fetch('/api/servo', {cache:'no-store'});
    if (!r.ok) throw new Error('http ' + r.status);
    const j = await r.json();
    const angle = Math.max(0, Math.min(180, parseInt(j.angle) || 0));
    const needle = document.getElementById('twin-needle');
    const dial = document.getElementById('twin-dial');
    const val = document.getElementById('twin-angle-val');
    const status = document.getElementById('twin-status');
    // Roteer via CSS-transform (transform-box:view-box → strak om het midden,
    // geen verschuiving). angle 90 = nulpunt; uitwijking in graden = angle-90.
    const dev = angle - 90;
    if (needle) needle.style.transform = `rotate(${dev}deg)`;
    if (val) val.textContent = (dev > 0 ? '+' : '') + dev;
    if (dial) dial.classList.remove('stale');
    if (status && twinLastFailed) status.textContent = 'Verbonden';
    twinLastFailed = false;
  } catch(e) {
    const dial = document.getElementById('twin-dial');
    const status = document.getElementById('twin-status');
    if (dial) dial.classList.add('stale');
    if (status) status.textContent = 'Geen verbinding met stok';
    twinLastFailed = true;
  }
}
function startTwinPolling() {
  stopTwinPolling();
  twinPollOnce();
  twinPollTimer = setInterval(twinPollOnce, 100);
}
function stopTwinPolling() {
  if (twinPollTimer !== null) {
    clearInterval(twinPollTimer);
    twinPollTimer = null;
  }
}

function confirmStopRoute() {
  const btn = document.getElementById('stop-btn');
  const lbl = document.getElementById('stop-label');
  if (state.pendingConfirm && state.pendingConfirm.action === 'stopRoute' && (Date.now() - state.pendingConfirm.time) < 5000) {
    state.pendingConfirm = null;
    btn.classList.remove('confirming');
    if (lbl) lbl.textContent = 'Stop route';
    btn.setAttribute('data-label', 'Stop de route helemaal.');
    stopRoute();
  } else {
    state.pendingConfirm = { action: 'stopRoute', time: Date.now() };
    btn.classList.add('confirming');
    if (lbl) lbl.textContent = 'Bevestig stoppen';
    btn.setAttribute('data-label', 'Bevestig stoppen van route. Tik opnieuw dubbel.');
    Speak.alert('Weet je zeker dat je de route wil stoppen? Tik opnieuw dubbel om te bevestigen.');
    setTimeout(() => {
      if (state.pendingConfirm && state.pendingConfirm.action === 'stopRoute') {
        state.pendingConfirm = null;
        btn.classList.remove('confirming');
        if (lbl) lbl.textContent = 'Stop route';
        btn.setAttribute('data-label', 'Stop de route helemaal.');
      }
    }, 5000);
  }
}
async function stopRoute() {
  await fetch('/api/route/stop', {method:'POST'});
  state.activeRoute = null;
  state.directions = null;
  state.currentStepIdx = 0;
  state.paused = false;
  stopGPSTracking();
  stopTwinPolling();
  updateNavView();
  Speak.now('Route gestopt.');
}
function togglePause() {
  state.paused = !state.paused;
  const lbl = document.getElementById('pause-label');
  const ic = document.getElementById('pause-icon');
  if (state.paused) {
    if (lbl) lbl.textContent = 'Hervat';
    if (ic) ic.innerHTML = '<svg viewBox="0 0 24 24"><polygon points="5 3 19 12 5 21 5 3" fill="currentColor" stroke="none"/></svg>';
    document.getElementById('pause-btn').setAttribute('data-label', 'Hervat de route.');
    Speak.now('Route gepauzeerd.');
  } else {
    if (lbl) lbl.textContent = 'Pauzeer';
    if (ic) ic.innerHTML = '<svg viewBox="0 0 24 24"><rect x="6" y="4" width="4" height="16"/><rect x="14" y="4" width="4" height="16"/></svg>';
    document.getElementById('pause-btn').setAttribute('data-label', 'Pauzeer de route.');
    Speak.now('Route hervat.');
  }
}
function updateNavView() {
  if (state.activeRoute) {
    document.getElementById('no-route').style.display = 'none';
    document.getElementById('active-route').style.display = 'block';
    document.getElementById('nav-dest-name').textContent = state.activeRoute;
    document.getElementById('nav-dest-banner').setAttribute('data-label', `Onderweg naar ${state.activeRoute}. Tik voor route-overzicht.`);

    let instructionText = state.lastInstruction || 'Wachten op instructies...';
    if (state.directions && state.currentStepIdx < state.directions.steps.length) {
      const step = state.directions.steps[state.currentStepIdx];
      const remaining = state.directions.steps.slice(state.currentStepIdx)
        .reduce((sum, s) => sum + s.distance, 0);
      instructionText = step.instruction;
      document.getElementById('nav-instruction').innerHTML =
        `<div>${escapeHtml(step.instruction)}</div>` +
        `<div class="muted" style="margin-top:8px;font-size:16px">Nog ${Math.round(remaining)} meter, stap ${state.currentStepIdx + 1} van ${state.directions.steps.length}</div>`;
    } else {
      document.getElementById('nav-instruction').textContent = instructionText;
    }
    document.getElementById('nav-instruction-banner').setAttribute('data-label', 'Huidige instructie: ' + instructionText + '. Tik om te herhalen.');
  } else {
    document.getElementById('no-route').style.display = 'block';
    document.getElementById('active-route').style.display = 'none';
  }
}
function askLocation() {
  if (!navigator.geolocation) { Speak.alert('GPS niet beschikbaar.'); return; }
  Speak.now('Locatie bepalen...');
  navigator.geolocation.getCurrentPosition(
    (pos) => {
      if (GOOGLE_ENABLED && state.geocoder) {
        state.geocoder.geocode({location:{lat:pos.coords.latitude, lng:pos.coords.longitude}}, (results, status) => {
          if (status === 'OK' && results[0]) {
            Speak.now('Je bent in ' + results[0].formatted_address);
          } else {
            Speak.now(`Je bent op breedte ${pos.coords.latitude.toFixed(4)}, lengte ${pos.coords.longitude.toFixed(4)}`);
          }
        });
      } else {
        Speak.now(`Je bent op breedte ${pos.coords.latitude.toFixed(4)}, lengte ${pos.coords.longitude.toFixed(4)}`);
      }
    },
    () => Speak.alert('Locatie kon niet bepaald worden.')
  );
}
function repeatLast() {
  Speak.now(state.lastInstruction || 'Er is nog geen instructie om te herhalen.');
}
function speakRouteOverview() {
  if (!state.activeRoute) { Speak.now('Geen actieve route.'); return; }
  if (state.directions) {
    const totalKm = (state.directions.totalDistance / 1000).toFixed(1);
    const totalMin = Math.round(state.directions.totalDuration / 60);
    const remaining = state.directions.steps.slice(state.currentStepIdx)
      .reduce((sum, s) => sum + s.distance, 0);
    Speak.now(`Onderweg naar ${state.activeRoute}. Totaal ${totalKm} kilometer, ongeveer ${totalMin} minuten. Nog ${Math.round(remaining)} meter te gaan.`);
  } else {
    Speak.now('Onderweg naar ' + state.activeRoute);
  }
}

// ═══════════════ Settings cycle / discrete ═══════════════
// Speelt een trilling op het handvat als preview bij het wijzigen van een
// trilling-instelling. id>0 = specifiek DRV-effect; id=0 = standaard RTP-puls
// op de huidige sterkte (voor de sterkte-keuze).
function previewEffect(id) {
  fetch('/api/trigger-effect', {
    method:'POST', headers:{'Content-Type':'application/x-www-form-urlencoded'},
    body: 'id=' + id
  }).catch(()=>{});
}
function previewTurn(id) {
  fetch('/api/turn-preview', {
    method:'POST', headers:{'Content-Type':'application/x-www-form-urlencoded'},
    body: 'id=' + id
  }).catch(()=>{});
}
const VIB_EFFECT_KEYS = ['vib_m4','vib_m6'];
const TURN_KEYS = ['vib_turn_right','vib_turn_left'];
function cycleSetting(key) {
  const opts = SETTING_DEFS[key];
  if (!opts) return;
  const cur = state.settings[key];
  let idx = opts.findIndex(o => o.id === cur);
  if (idx < 0) idx = 0;
  const next = opts[(idx + 1) % opts.length];
  state.settings[key] = next.id;
  if (key === 'tts_rate') state.ttsRate = next.id / 10;
  refreshSettingDisplay(key);
  // Sla op en speel daarna een preview op het handvat (na opslaan, zodat het
  // de nieuwe waarde gebruikt).
  saveSettingsImmediate().then(() => {
    if (VIB_EFFECT_KEYS.includes(key)) previewEffect(next.id);
    else if (TURN_KEYS.includes(key)) previewTurn(next.id);
  });
  Speak.now(`${SETTING_LABELS[key]}: ${next.name}`);
}
function setSetting(arg) {
  const parts = arg.split(':');
  const key = parts[0];
  const val = parseInt(parts[1]);
  state.settings[key] = val;
  if (key === 'tts_rate') state.ttsRate = val / 10;
  refreshSettingDisplay(key);
  saveSettingsImmediate().then(() => {
    if (key === 'vib_intensity') previewEffect(0);   // voel de nieuwe sterkte
  });
  const opts = SETTING_DEFS[key];
  const opt = opts ? opts.find(o => o.id === val) : null;
  Speak.now(`${SETTING_LABELS[key]}: ${opt ? opt.name : val}`);
}
function refreshSettingDisplay(key) {
  const valEl = document.getElementById('val-' + key);
  if (valEl) {
    const opts = SETTING_DEFS[key];
    const cur = state.settings[key];
    const opt = opts ? opts.find(o => o.id === cur) : null;
    const name = opt ? opt.name : String(cur);
    const curSpan = valEl.querySelector('.cur');
    if (curSpan) curSpan.textContent = name;
    valEl.setAttribute('data-label', `${SETTING_LABELS[key]} staat op ${name}. Dubbel-tik om naar volgende optie te wisselen.`);
  }
  document.querySelectorAll(`[data-key="${key}"]`).forEach(btn => {
    const isSelected = parseInt(btn.dataset.val) === state.settings[key];
    btn.classList.toggle('selected', isSelected);
    const base = btn.getAttribute('data-label-base') || (btn.textContent || '').trim();
    btn.setAttribute('data-label', isSelected ? `${base}, geselecteerd` : base);
  });
}
function refreshAllSettingDisplays() {
  Object.keys(SETTING_DEFS).forEach(refreshSettingDisplay);
}
async function saveSettingsImmediate() {
  const settings = Object.assign({}, state.settings);
  settings.emergency = document.getElementById('emergency').value;
  await fetch('/api/settings', {
    method:'POST', headers:{'Content-Type':'application/json'},
    body: JSON.stringify(settings)
  });
}
async function saveSettings() {
  await saveSettingsImmediate();
  Speak.now('Instellingen opgeslagen.');
}
async function loadSettings() {
  try {
    const r = await fetch('/api/settings');
    const s = await r.json();
    Object.assign(state.settings, s);
    if (s.tts_rate) state.ttsRate = s.tts_rate / 10;
    document.getElementById('emergency').value = s.emergency || '';
  } catch(e) { console.error(e); }
  refreshAllSettingDisplays();
}
function testSpeech() {
  Speak.now('Dit is een test van de stem. De huidige snelheid is ' + state.ttsRate.toFixed(1) + ' keer.');
}
function confirmResetSettings() {
  const btn = document.getElementById('reset-btn');
  const lbl = document.getElementById('reset-label');
  if (state.pendingConfirm && state.pendingConfirm.action === 'resetSettings' && (Date.now() - state.pendingConfirm.time) < 5000) {
    state.pendingConfirm = null;
    btn.classList.remove('confirming');
    if (lbl) lbl.textContent = 'Reset';
    resetSettings();
  } else {
    state.pendingConfirm = { action: 'resetSettings', time: Date.now() };
    btn.classList.add('confirming');
    if (lbl) lbl.textContent = 'Bevestig reset';
    Speak.alert('Reset alle instellingen? Tik opnieuw dubbel om te bevestigen.');
    setTimeout(() => {
      if (state.pendingConfirm && state.pendingConfirm.action === 'resetSettings') {
        state.pendingConfirm = null;
        btn.classList.remove('confirming');
        if (lbl) lbl.textContent = 'Reset';
      }
    }, 5000);
  }
}
async function resetSettings() {
  await fetch('/api/settings/reset', {method:'POST'});
  await loadSettings();
  Speak.now('Alle instellingen zijn gereset.');
}

// ═══════════════ Polling voor button-press events ═══════════════
async function pollEvents() {
  try {
    const r = await fetch('/api/pending');
    const cmd = await r.text();
    if (cmd && cmd !== '') handleCommand(cmd);
  } catch(e) {}
}
function handleCommand(cmd) {
  if (cmd === 'ASK_LOCATION') askLocation();
  else if (cmd === 'REPEAT_LAST') repeatLast();
  else if (cmd === 'ROUTE_OVERVIEW') speakRouteOverview();
  else if (cmd === 'EMERGENCY') {
    const num = state.settings.emergency || document.getElementById('emergency').value;
    if (num) {
      Speak.alert('Noodcontact wordt gebeld');
      // Zo direct mogelijk bellen: een anchor-klik triggert de telefoon-app
      // meteen. (Het laatste "Bellen?"-venster is iOS-systeembeveiliging en
      // kan een webpagina niet overslaan; alleen een native app kan dat.)
      const a = document.createElement('a');
      a.href = 'tel:' + num.replace(/[^0-9+]/g, '');
      document.body.appendChild(a);
      a.click();
      a.remove();
    } else {
      Speak.alert('Geen noodcontact ingesteld');
    }
  }
  else if (cmd.startsWith('SPEAK:')) Speak.now(cmd.substring(6));
}

// ═══════════════ Utility ═══════════════
function escapeHtml(s) {
  return String(s).replace(/[&<>"']/g, c => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
}

// ═══════════════ Init ═══════════════
window.addEventListener('load', async () => {
  A11y.init();
  loadRecents();
  await loadDestinations();
  await loadSettings();
  loadGoogleMaps();
  setInterval(pollEvents, 600);

  // Enter-toets op zoekveld → submit search + sluit keyboard
  const searchInput = document.getElementById('custom-dest');
  if (searchInput) {
    searchInput.addEventListener('keydown', (e) => {
      if (e.key === 'Enter') {
        e.preventDefault();
        searchInput.blur();
        searchPlaces();
      }
    });
  }
  // Enter op noodcontact veld → bevestig opslaan
  const emerInput = document.getElementById('emergency');
  if (emerInput) {
    emerInput.addEventListener('keydown', (e) => {
      if (e.key === 'Enter') {
        e.preventDefault();
        emerInput.blur();
        saveSettings();
      }
    });
  }
});
</script>
</body>
</html>
)HTML";
