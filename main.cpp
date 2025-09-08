
#include <iostream>
#include <string>
#include "WavFileHandler.h"


int main() {
    std::string RefSignalpath  = "/workspaces/Echo_noise_cancellation_filter/RefSignal.wav";
    std::string MicInputpath = "/workspaces/Echo_noise_cancellation_filter/MicInput.wav";

    WavFileHandler RefSignal_wav(RefSignalpath);
    WavFileHandler MicInput_wav(MicInputpath);

    if (RefSignal_wav.getNumChannels() == 0 || MicInput_wav.getNumChannels() == 0) {
        std::cerr << "Failed to read one or both WAV files." << std::endl;
        return 1;
    }

    AudioChannel* RefSignal = RefSignal_wav.getChannel(0);
    AudioChannel* MicInput = MicInput_wav.getChannel(0);

    // Call echo noise cancellation function here
    // echoNoiseCancellation(channel1_data, channel2_data, ...);

    std::cout << "WAV files read successfully." << std::endl;
    return 0;
}
