#!/usr/bin/env python3
# Zet 16 kHz mono 16-bit PCM WAV-bestanden om naar een C-header met int16-arrays
# voor afspelen via I2S op de ESP32-S3.
#   python tools/wav2header.py eta=handle/audio/eta.wav locatie=handle/audio/locatie.wav > handle/audio_clips.h
import sys, wave

def load(path):
    with wave.open(path, "rb") as w:
        assert w.getsampwidth() == 2, f"{path}: verwacht 16-bit"
        assert w.getnchannels() == 1, f"{path}: verwacht mono"
        rate = w.getframerate()
        frames = w.readframes(w.getnframes())
    # int16 little-endian samples
    import struct
    n = len(frames) // 2
    samples = struct.unpack("<%dh" % n, frames[: n * 2])
    return rate, samples

print("// Auto-gegenereerd door tools/wav2header.py — niet handmatig bewerken.")
print("#pragma once")
print("#include <stdint.h>")
print()
for arg in sys.argv[1:]:
    name, path = arg.split("=", 1)
    rate, samples = load(path)
    print(f"// {name}: {path}  ({len(samples)} samples @ {rate} Hz, {len(samples)/rate:.2f}s)")
    print(f"constexpr uint32_t {name}_rate = {rate};")
    print(f"constexpr uint32_t {name}_len = {len(samples)};")
    print(f"const int16_t {name}_pcm[] = {{")
    for i in range(0, len(samples), 16):
        chunk = samples[i : i + 16]
        print("  " + ",".join(str(s) for s in chunk) + ",")
    print("};")
    print()
