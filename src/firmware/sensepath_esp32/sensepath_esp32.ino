/*
  SensePath ESP32 prototype firmware

  Hardware:
  - ESP32 DevKit
  - Adafruit DRV2605L haptic driver on I2C
  - LRA vibration motor connected to DRV2605L

  WiFi:
  - Access point: SensePath
  - Password: sensepath
  - Open http://192.168.4.1/
*/

#include <Adafruit_DRV2605.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>

namespace {

constexpr const char *AP_SSID = "SensePath";
constexpr const char *AP_PASSWORD = "sensepath";

constexpr uint8_t I2C_SDA_PIN = 21;
constexpr uint8_t I2C_SCL_PIN = 22;

constexpr uint16_t DEFAULT_FADE_IN_MS = 80;
constexpr uint8_t MAX_RTP_VALUE = 127;

Adafruit_DRV2605 drv;
WebServer server(80);

bool drvFound = false;
float intensityScale = 1.0f;
uint8_t lastRtpValue = 255;

struct Segment {
  uint32_t durationMs;
  uint8_t targetPercent;
  bool ramp;
};

constexpr uint8_t MAX_SEGMENTS = 32;

struct PatternState {
  Segment segments[MAX_SEGMENTS];
  uint8_t count = 0;
  uint8_t index = 0;
  bool active = false;
  bool loop = false;
  String name = "idle";
  uint32_t segmentStartedAt = 0;
  uint8_t segmentStartPercent = 0;
  uint8_t outputPercent = 0;
};

PatternState pattern;

uint8_t clampPercent(int value) {
  if (value < 0) return 0;
  if (value > 100) return 100;
  return static_cast<uint8_t>(value);
}

uint8_t scaledPercent(uint8_t percent) {
  return clampPercent(static_cast<int>(percent * intensityScale));
}

uint8_t percentToRtp(uint8_t percent) {
  return map(clampPercent(percent), 0, 100, 0, MAX_RTP_VALUE);
}

void writeMotor(uint8_t percent) {
  pattern.outputPercent = clampPercent(percent);
  if (!drvFound) return;

  const uint8_t rtpValue = percentToRtp(scaledPercent(pattern.outputPercent));
  if (rtpValue == lastRtpValue) return;

  drv.setRealtimeValue(rtpValue);
  lastRtpValue = rtpValue;
}

void stopPattern() {
  pattern.active = false;
  pattern.loop = false;
  pattern.count = 0;
  pattern.index = 0;
  pattern.name = "idle";
  pattern.segmentStartPercent = 0;
  writeMotor(0);
}

void addSegment(uint32_t durationMs, uint8_t targetPercent, bool ramp = false) {
  if (pattern.count >= MAX_SEGMENTS) return;
  pattern.segments[pattern.count++] = {durationMs, clampPercent(targetPercent), ramp};
}

void beginPattern(const String &name, bool loop = false) {
  pattern.name = name;
  pattern.loop = loop;
  pattern.index = 0;
  pattern.active = pattern.count > 0;
  pattern.segmentStartedAt = millis();
  pattern.segmentStartPercent = pattern.outputPercent;

  if (!pattern.active) {
    stopPattern();
  }
}

void clearPattern() {
  pattern.count = 0;
  pattern.index = 0;
  pattern.segmentStartPercent = pattern.outputPercent;
}

void pulse(uint16_t onMs, uint8_t percent, uint32_t offMs = 0, uint16_t fadeInMs = DEFAULT_FADE_IN_MS) {
  uint32_t holdMs = onMs > fadeInMs ? onMs - fadeInMs : 0;
  addSegment(fadeInMs, percent, true);
  if (holdMs > 0) addSegment(holdMs, percent, false);
  addSegment(20, 0, false);
  if (offMs > 0) addSegment(offMs, 0, false);
}

void makeM1RouteStarted() {
  clearPattern();
  pulse(120, 40, 200);
  pulse(120, 40);
  beginPattern("M1 route gestart");
}

void makeM2ConfidenceHeartbeat() {
  clearPattern();
  pulse(60, 25, 250, 40);
  pulse(60, 25, 45000, 40);
  beginPattern("M2 confidence heartbeat", true);
}

void makeM4TurnApproaching(const String &direction) {
  clearPattern();
  const uint16_t intervals[] = {1000, 825, 650, 475, 300};
  const uint8_t intensities[] = {35, 41, 48, 54, 60};
  for (uint8_t i = 0; i < 5; i++) {
    pulse(100, intensities[i], intervals[i]);
  }

  String name = "M4 bocht nadert";
  if (direction == "left") name += " links";
  if (direction == "right") name += " rechts";
  beginPattern(name);
}

void makeM5TurnConfirmed() {
  clearPattern();
  pulse(40, 50, 80, 20);
  pulse(40, 50, 0, 20);
  beginPattern("M5 bocht correct");
}

void makeM6OffPath() {
  clearPattern();
  for (uint8_t i = 0; i < 3; i++) {
    addSegment(1000, 40, true);
    addSegment(1000, 15, true);
  }
  addSegment(20, 0, false);
  beginPattern("M6 afwijking route");
}

void makeM7Failsafe() {
  clearPattern();
  pulse(800, 30, 1500, 120);
  beginPattern("M7 herorienteren", true);
}

void makeM8DestinationReached() {
  clearPattern();
  addSegment(200, 70, true);
  addSegment(100, 70, false);
  addSegment(300, 0, true);
  beginPattern("M8 bestemming bereikt");
}

void makeM9BatteryLow() {
  clearPattern();
  pulse(30, 20, 300, 10);
  pulse(30, 20, 300, 10);
  pulse(30, 20, 600000, 10);
  beginPattern("M9 batterij laag", true);
}

bool startPatternById(const String &id, const String &direction = "") {
  stopPattern();

  if (id == "m1") makeM1RouteStarted();
  else if (id == "m2") makeM2ConfidenceHeartbeat();
  else if (id == "m3") stopPattern();
  else if (id == "m4") makeM4TurnApproaching(direction);
  else if (id == "m5") makeM5TurnConfirmed();
  else if (id == "m6") makeM6OffPath();
  else if (id == "m7") makeM7Failsafe();
  else if (id == "m8") makeM8DestinationReached();
  else if (id == "m9") makeM9BatteryLow();
  else return false;

  return true;
}

void updatePattern() {
  if (!pattern.active || pattern.count == 0) return;

  const uint32_t now = millis();
  Segment &segment = pattern.segments[pattern.index];
  const uint32_t elapsed = now - pattern.segmentStartedAt;

  if (elapsed >= segment.durationMs) {
    writeMotor(segment.targetPercent);
    pattern.index++;

    if (pattern.index >= pattern.count) {
      if (pattern.loop) {
        pattern.index = 0;
      } else {
        stopPattern();
        return;
      }
    }

    pattern.segmentStartedAt = now;
    pattern.segmentStartPercent = pattern.outputPercent;
    return;
  }

  if (segment.ramp && segment.durationMs > 0) {
    const int delta = static_cast<int>(segment.targetPercent) - static_cast<int>(pattern.segmentStartPercent);
    const uint8_t value = pattern.segmentStartPercent + (delta * static_cast<int>(elapsed)) / segment.durationMs;
    writeMotor(value);
  } else {
    writeMotor(segment.targetPercent);
  }
}

String jsonStatus() {
  String json = "{";
  json += "\"device\":\"SensePath\",";
  json += "\"drv2605l\":";
  json += drvFound ? "true" : "false";
  json += ",";
  json += "\"playing\":";
  json += pattern.active ? "true" : "false";
  json += ",";
  json += "\"pattern\":\"";
  json += pattern.name;
  json += "\",";
  json += "\"outputPercent\":";
  json += String(pattern.outputPercent);
  json += ",";
  json += "\"intensityScale\":";
  json += String(intensityScale, 2);
  json += ",";
  json += "\"ip\":\"";
  json += WiFi.softAPIP().toString();
  json += "\"";
  json += "}";
  return json;
}

String pageHtml() {
  return R"HTML(
<!doctype html>
<html lang="nl">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>SensePath Controller</title>
  <style>
    :root {
      color-scheme: light;
      --ink: #182022;
      --muted: #5d676a;
      --line: #d7dddf;
      --panel: #f6f8f8;
      --accent: #147a72;
      --danger: #9a2f35;
      --bg: #ffffff;
    }
    * { box-sizing: border-box; }
    body {
      margin: 0;
      font-family: system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
      background: var(--bg);
      color: var(--ink);
    }
    main {
      width: min(760px, calc(100vw - 28px));
      margin: 0 auto;
      padding: 24px 0 36px;
    }
    header {
      display: flex;
      justify-content: space-between;
      gap: 16px;
      align-items: flex-start;
      border-bottom: 1px solid var(--line);
      padding-bottom: 16px;
    }
    h1 { margin: 0; font-size: 1.8rem; letter-spacing: 0; }
    .status {
      min-width: 170px;
      padding: 10px 12px;
      background: var(--panel);
      border: 1px solid var(--line);
      border-radius: 8px;
      font-size: .95rem;
    }
    .status strong { display: block; margin-bottom: 2px; }
    section { padding-top: 22px; }
    h2 { margin: 0 0 12px; font-size: 1rem; }
    .grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
      gap: 10px;
    }
    button, select {
      min-height: 48px;
      border: 1px solid var(--line);
      border-radius: 8px;
      background: #fff;
      color: var(--ink);
      font: inherit;
    }
    button {
      padding: 10px 12px;
      cursor: pointer;
      text-align: left;
    }
    button:hover { border-color: var(--accent); }
    button.primary { background: var(--accent); color: white; border-color: var(--accent); }
    button.stop { background: var(--danger); color: white; border-color: var(--danger); text-align: center; }
    label { display: grid; gap: 6px; color: var(--muted); font-size: .9rem; }
    select { padding: 0 10px; }
    code {
      display: block;
      overflow-x: auto;
      padding: 12px;
      background: var(--panel);
      border: 1px solid var(--line);
      border-radius: 8px;
      color: var(--muted);
    }
    @media (max-width: 520px) {
      header { display: block; }
      .status { margin-top: 12px; }
    }
  </style>
</head>
<body>
  <main>
    <header>
      <div>
        <h1>SensePath</h1>
        <div>Wizard-of-Oz haptiekcontroller</div>
      </div>
      <div class="status">
        <strong id="pattern">...</strong>
        <span id="driver">DRV2605L: ...</span>
      </div>
    </header>

    <section>
      <h2>Routepatronen</h2>
      <div class="grid">
        <button onclick="play('m1')">M1 Route gestart</button>
        <button onclick="play('m2')">M2 Heartbeat</button>
        <button onclick="play('m4','left')" class="primary">M4 Bocht links</button>
        <button onclick="play('m4','right')" class="primary">M4 Bocht rechts</button>
        <button onclick="play('m5')">M5 Bocht correct</button>
        <button onclick="play('m6')">M6 Afwijking route</button>
        <button onclick="play('m7')">M7 Herorienteren</button>
        <button onclick="play('m8')">M8 Bestemming bereikt</button>
        <button onclick="play('m9')">M9 Batterij laag</button>
        <button onclick="stopAll()" class="stop">Stop</button>
      </div>
    </section>

    <section>
      <h2>Intensiteit</h2>
      <label>
        Niveau
        <select onchange="setIntensity(this.value)">
          <option value="low">Laag</option>
          <option value="medium" selected>Medium</option>
          <option value="high">Hoog</option>
        </select>
      </label>
    </section>

    <section>
      <h2>Status</h2>
      <code id="json">{}</code>
    </section>
  </main>

  <script>
    async function play(id, direction = '') {
      const params = new URLSearchParams({ name: id });
      if (direction) params.set('direction', direction);
      await fetch('/api/pattern?' + params.toString());
      refresh();
    }
    async function stopAll() {
      await fetch('/api/stop');
      refresh();
    }
    async function setIntensity(level) {
      await fetch('/api/intensity?level=' + encodeURIComponent(level));
      refresh();
    }
    async function refresh() {
      const data = await fetch('/api/status').then(r => r.json());
      document.getElementById('pattern').textContent = data.playing ? data.pattern : 'idle';
      document.getElementById('driver').textContent = 'DRV2605L: ' + (data.drv2605l ? 'gevonden' : 'niet gevonden');
      document.getElementById('json').textContent = JSON.stringify(data, null, 2);
    }
    setInterval(refresh, 1000);
    refresh();
  </script>
</body>
</html>
)HTML";
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", pageHtml());
}

void handleStatus() {
  server.send(200, "application/json", jsonStatus());
}

void handlePattern() {
  if (!server.hasArg("name")) {
    server.send(400, "application/json", "{\"error\":\"missing pattern name\"}");
    return;
  }

  const String name = server.arg("name");
  const String direction = server.hasArg("direction") ? server.arg("direction") : "";

  if (!startPatternById(name, direction)) {
    server.send(404, "application/json", "{\"error\":\"unknown pattern\"}");
    return;
  }

  Serial.print("Patroon gestart: ");
  Serial.println(pattern.name);
  server.send(200, "application/json", jsonStatus());
}

void handleStop() {
  stopPattern();
  Serial.println("Patroon gestopt");
  server.send(200, "application/json", jsonStatus());
}

void handleIntensity() {
  const String level = server.hasArg("level") ? server.arg("level") : "medium";

  if (level == "low") intensityScale = 0.65f;
  else if (level == "high") intensityScale = 1.15f;
  else intensityScale = 1.0f;

  Serial.print("Intensiteit: ");
  Serial.println(level);
  server.send(200, "application/json", jsonStatus());
}

void handleNotFound() {
  server.send(404, "application/json", "{\"error\":\"not found\"}");
}

void setupDrv2605() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  drvFound = drv.begin();

  if (drvFound) {
    drv.selectLibrary(6);
    drv.useLRA();
    drv.setMode(DRV2605_MODE_REALTIME);
    drv.setRealtimeValue(0);
    Serial.println("DRV2605L gevonden");
  } else {
    Serial.println("DRV2605L niet gevonden");
  }
}

void setupWifi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  Serial.print("AP gestart, IP: ");
  Serial.println(WiFi.softAPIP());
}

void setupServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/pattern", HTTP_GET, handlePattern);
  server.on("/api/stop", HTTP_GET, handleStop);
  server.on("/api/intensity", HTTP_GET, handleIntensity);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Webserver start");
}

}  // namespace

void setup() {
  Serial.begin(115200);
  delay(250);

  Serial.println();
  Serial.println("SensePath start");

  setupDrv2605();
  setupWifi();
  setupServer();
}

void loop() {
  server.handleClient();
  updatePattern();
  delay(1);
}
