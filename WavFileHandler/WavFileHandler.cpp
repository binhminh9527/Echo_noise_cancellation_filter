

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
    if (channels_) {
        for (size_t ch = 0; ch < numChannels_; ++ch) {
            delete channels_[ch];
        }
        delete[] channels_;
    }
}

// Removed getChannelBuffers; use getChannel instead


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

    channels_ = new AudioChannel*[numChannels_];
    for (size_t ch = 0; ch < numChannels_; ++ch) {
        channels_[ch] = new AudioChannel(samplesPerChannel_);
    }

    if (header_.bitsPerSample == 16) {
        int16_t* allSamples = new int16_t[numSamples];
        file.read(reinterpret_cast<char*>(allSamples), header_.dataSize);
        // Deinterleave and convert to float
        for (size_t ch = 0; ch < numChannels_; ++ch) {
            float* channelData = channels_[ch]->data();
            for (size_t i = 0; i < samplesPerChannel_; ++i) {
                channelData[i] = static_cast<float>(allSamples[i * numChannels_ + ch]) / 32768.0f;
            }
        }
        delete[] allSamples;
    } else if (header_.bitsPerSample == 32) {
        int32_t* allSamples = new int32_t[numSamples];
        file.read(reinterpret_cast<char*>(allSamples), header_.dataSize);
        // Deinterleave and convert to float
        for (size_t ch = 0; ch < numChannels_; ++ch) {
            float* channelData = channels_[ch]->data();
            for (size_t i = 0; i < samplesPerChannel_; ++i) {
                channelData[i] = static_cast<float>(allSamples[i * numChannels_ + ch]) / 2147483648.0f;
            }
        }
        delete[] allSamples;
    } else {
        std::cerr << "Only 16-bit and 32-bit PCM WAV files are supported." << std::endl;
        return false;
    }
    return true;
}
AudioChannel* WavFileHandler::getChannel(int channel) const {
    if (channel < 0 || static_cast<size_t>(channel) >= numChannels_) return nullptr;
    return channels_[channel];
}
bool WavFileHandler::saveWavFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file for writing: " << filename << std::endl;
        return false;
    }
    // Write header
    file.write(reinterpret_cast<const char*>(&header_), sizeof(WAVHeader));

    // Interleave and convert float data back to PCM
    if (header_.bitsPerSample == 16) {
        for (size_t i = 0; i < samplesPerChannel_; ++i) {
            for (size_t ch = 0; ch < numChannels_; ++ch) {
                float sample = channels_[ch]->data()[i];
                int16_t pcm = static_cast<int16_t>(std::max(-32768.0f, std::min(32767.0f, sample * 32768.0f)));
                file.write(reinterpret_cast<const char*>(&pcm), sizeof(int16_t));
            }
        }
    } else if (header_.bitsPerSample == 32) {
        for (size_t i = 0; i < samplesPerChannel_; ++i) {
            for (size_t ch = 0; ch < numChannels_; ++ch) {
                float sample = channels_[ch]->data()[i];
                int32_t pcm = static_cast<int32_t>(std::max(-2147483648.0f, std::min(2147483647.0f, sample * 2147483648.0f)));
                file.write(reinterpret_cast<const char*>(&pcm), sizeof(int32_t));
            }
        }
    } else {
        std::cerr << "Only 16-bit and 32-bit PCM WAV files are supported for saving." << std::endl;
        return false;
    }
    return true;
}
    