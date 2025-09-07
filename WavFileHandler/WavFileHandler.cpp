

#include "WavFileHandler.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdint>

WavFileHandler::WavFileHandler(const std::string& filename) {
    if (!readWavFile(filename)) {
        std::cerr << "Failed to read WAV file: " << filename << std::endl;
    }
}

WavFileHandler::~WavFileHandler() {
    if (channelBuffers_) {
        for (size_t ch = 0; ch < numChannels_; ++ch) {
            delete[] channelBuffers_[ch];
        }
        delete[] channelBuffers_;
    }
}

bool WavFileHandler::readWavFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }
    file.read(reinterpret_cast<char*>(&header_), sizeof(WAVHeader));
    if (std::string(header_.riff, 4) != "RIFF" || std::string(header_.wave, 4) != "WAVE") {
        std::cerr << "Invalid WAV file: " << filename << std::endl;
        return false;
    }

    numChannels_ = header_.numChannels;
    samplesPerChannel_ = (header_.dataSize / (header_.bitsPerSample / 8)) / numChannels_;
    size_t numSamples = samplesPerChannel_ * numChannels_;

    channelBuffers_ = new int32_t*[numChannels_];
    for (size_t ch = 0; ch < numChannels_; ++ch) {
        channelBuffers_[ch] = new int32_t[samplesPerChannel_];
    }

    if (header_.bitsPerSample == 16) {
        int16_t* allSamples = new int16_t[numSamples];
        file.read(reinterpret_cast<char*>(allSamples), header_.dataSize);
        // Deinterleave and convert to int32_t
        for (size_t ch = 0; ch < numChannels_; ++ch) {
            for (size_t i = 0; i < samplesPerChannel_; ++i) {
                channelBuffers_[ch][i] = static_cast<int32_t>(allSamples[i * numChannels_ + ch]);
            }
        }
        delete[] allSamples;
    } else if (header_.bitsPerSample == 32) {
        int32_t* allSamples = new int32_t[numSamples];
        file.read(reinterpret_cast<char*>(allSamples), header_.dataSize);
        // Deinterleave
        for (size_t ch = 0; ch < numChannels_; ++ch) {
            for (size_t i = 0; i < samplesPerChannel_; ++i) {
                channelBuffers_[ch][i] = allSamples[i * numChannels_ + ch];
            }
        }
        delete[] allSamples;
    } else {
        std::cerr << "Only 16-bit and 32-bit PCM WAV files are supported." << std::endl;
        return false;
    }
    return true;
}
