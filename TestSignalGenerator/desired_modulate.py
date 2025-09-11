import numpy as np
import wave

def read_wav(filename):
    with wave.open(filename, 'rb') as wf:
        n_channels = wf.getnchannels()
        sampwidth = wf.getsampwidth()
        framerate = wf.getframerate()
        n_frames = wf.getnframes()
        audio = wf.readframes(n_frames)
        data = np.frombuffer(audio, dtype=np.int16)
        return data, framerate

def write_wav(filename, data, framerate):
    data_int16 = np.int16(data)
    with wave.open(filename, 'w') as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)
        wf.setframerate(framerate)
        wf.writeframes(data_int16.tobytes())

def modulate_desired(input_file, output_file):
    data, sr = read_wav(input_file)
    t = np.arange(len(data)) / sr
    modulator = 0.2 + np.sin(2 * np.pi * 10 * t)
    modulated = data * modulator
    # Normalize to int16 range
    modulated = modulated / np.max(np.abs(modulated)) * 32767
    write_wav(output_file, modulated, sr)

if __name__ == "__main__":
    modulate_desired('desired.wav', 'desired_modulated.wav')
