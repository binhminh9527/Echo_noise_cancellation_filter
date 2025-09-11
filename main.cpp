
#include <iostream>
#include <string>
#include "WavFileHandler.h"
#include "EcnrLib.h"

int main() {
    EcnrLib ecnr;
    std::string RefSignalpath  = "TestSignalGenerator/desired_modulated.wav";
    std::string MicInputpath = "TestSignalGenerator/ref_from_speaker.wav";

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
    std::vector<float> output_vec;
    float* refData = RefSignal->data();
    float* micData = MicInput->data();
    size_t numSamples = std::min(RefSignal->numSamples(), MicInput->numSamples());
    for (size_t i = 0; i < 8000/*numSamples*/; ++i) {
        LOG_INTERVAL(i, numSamples, 1);
        float outputSample = ecnr.process(refData[i], micData[i]);
        output_vec.push_back(outputSample);
    }
    
    // Save output_vec to test_result.wav
    WavFileHandler result_wav(output_vec);
    result_wav.saveWavFile("test_result.wav");
    std::cout << "WAV files read successfully and result saved to test_result.wav." << std::endl;
    return 0;
}
