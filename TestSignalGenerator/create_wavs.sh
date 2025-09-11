#!/bin/bash
set -e
# Change to the directory where this script is located
cd "$(dirname "$0")"
python3 sine_wave_generator.py --filename desired.wav --duration 5 --frequency 1000 --db -5
python3 sine_wave_generator.py --filename ref_from_speaker.wav --duration 5 --frequency 10000 --db -5
python3 Create_ecnr_test.py
