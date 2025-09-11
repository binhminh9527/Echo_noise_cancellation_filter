import numpy as np
import wave
import struct
import argparse

def db_to_amplitude(db):
    return 10 ** (db / 20)

def generate_sine_wave(filename, duration, frequency, db, sample_rate=48000):
    amplitude = db_to_amplitude(db)
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    signal = amplitude * np.sin(2 * np.pi * frequency * t)
    # Normalize to int16 range
    signal_int16 = np.int16(signal / np.max(np.abs(signal)) * 32767)
    with wave.open(filename, 'w') as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)
        wf.setframerate(sample_rate)
        wf.writeframes(signal_int16.tobytes())

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a sine wave and save as WAV file.")
    parser.add_argument("--filename", type=str, required=True, help="Output WAV file name")
    parser.add_argument("--duration", type=float, required=True, help="Duration in seconds")
    parser.add_argument("--frequency", type=float, required=True, help="Frequency in Hz")
    parser.add_argument("--db", type=float, default=-5.0, help="Amplitude in dB (default: -5dB)")
    args = parser.parse_args()
    generate_sine_wave(args.filename, args.duration, args.frequency, args.db)
