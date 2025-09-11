import numpy as np
import wave
import argparse

def db_to_amplitude(db):
    return 10 ** (db / 20)

def create_white_noise(length, amplitude=1.0):
    return np.random.normal(0, amplitude, length)

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

def main():
    # Read both files
    desired, sr = read_wav('desired.wav')
    ref, sr_ref = read_wav('ref_from_speaker.wav')
    assert sr == sr_ref, "Sample rates must match"

    # Create delayed, attenuated, and noisy version of ref_from_speaker
    delay_ms = 5
    delay_samples = int(sr * delay_ms / 1000)
    gain = db_to_amplitude(-4)
    ref_delayed = np.concatenate((np.zeros(delay_samples), ref[:-delay_samples]))
    ref_delayed = ref_delayed * gain

    # Add white noise
    noise = create_white_noise(len(ref_delayed), amplitude=0.05 * np.max(np.abs(ref_delayed)))
    ref_noisy = ref_delayed + noise
    # Add desired signal to the noisy reference (simulating mic recording with echo and noise)
    mic_record = ref_noisy + desired[:len(ref_noisy)]
    ref_noisy = mic_record
    # Save the new file
    write_wav('Mic_record_with_EchoNoise.wav', mic_record, sr)

if __name__ == "__main__":
    main()
