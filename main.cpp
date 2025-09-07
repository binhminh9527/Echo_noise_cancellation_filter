
#include <iostream>
#include <string>
#include "WavFileHandler.h"


int main() {
    std::string filename1 = "input1.wav";
    std::string filename2 = "input2.wav";

    WavFileHandler wav1(filename1);
    WavFileHandler wav2(filename2);

    if (wav1.getNumChannels() == 0 || wav2.getNumChannels() == 0) {
        std::cerr << "Failed to read one or both WAV files." << std::endl;
        return 1;
    }

    // Example: Access channel buffers
    // int32_t* channel1_data = wav1.getChannelBuffers(0);
    // int32_t* channel2_data = wav2.getChannelBuffers(0);

    // Call echo noise cancellation function here
    // echoNoiseCancellation(channel1_data, channel2_data, ...);

    std::cout << "WAV files read successfully." << std::endl;
    return 0;
}
