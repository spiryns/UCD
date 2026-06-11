# SensePath source code

## Firmware

De huidige werkende prototypefirmware staat in:

- [`firmware/sensepath_esp32`](firmware/sensepath_esp32)

Deze ESP32-sketch start een eigen wifi-accesspoint, bedient de DRV2605L haptiekdriver en biedt een kleine webcontroller voor de SensePath M-patronen.

Korte flow:

1. Upload `firmware/sensepath_esp32/sensepath_esp32.ino` naar een ESP32.
2. Verbind met wifi `SensePath` met wachtwoord `sensepath`.
3. Open `http://192.168.4.1/`.

Zie de README in de firmwaremap voor pinnen, libraries en API-routes.
