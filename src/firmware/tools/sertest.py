#!/usr/bin/env python3
# Lokaal dev-hulpje: stuur 1 commando naar het handvat en lees de respons.
#   python tools/sertest.py <COM> <commando> [leestijd_s]
# Voorbeeld: python tools/sertest.py COM7 1 4
# Opent de poort met DTR hoog (nodig voor USB-CDC output op de ESP32-S3)
# en RTS laag (vermijdt een reset-puls). Output is ascii-veilig.
import sys, time, serial

port = sys.argv[1] if len(sys.argv) > 1 else "COM7"
cmd  = sys.argv[2] if len(sys.argv) > 2 else "?"
secs = float(sys.argv[3]) if len(sys.argv) > 3 else 3.0

s = serial.Serial()
s.port = port
s.baudrate = 115200
s.timeout = 0.3
s.dtr = True
s.rts = False
s.open()
time.sleep(0.8)
s.reset_input_buffer()
s.write(cmd.encode())
t = time.time()
while time.time() - t < secs:
    line = s.readline().decode("utf-8", errors="replace").rstrip()
    if line:
        print(line.encode("ascii", "replace").decode("ascii"))
s.close()
