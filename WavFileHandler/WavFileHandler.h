#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "../EcnrLib/EcnrLib.h"


struct WAVHeader {
    char riff[4];
    uint32_t chunkSize;
    char wave[4];
    char fmt[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char data[4];
    uint32_t dataSize;
};

class WavFileHandler {
public:
    WavFileHandler(const std::string& filename);
    ~WavFileHandler();
    const WAVHeader& getHeader() const { return header_; }
    int32_t** getChannelBuffers() const { return channelBuffers_; }
    size_t getSamplesPerChannel() const { return samplesPerChannel_; }
    size_t getNumChannels() const { return numChannels_; }

private:
    WAVHeader header_;
    int32_t** channelBuffers_ = nullptr; // Array of pointers to int32_t buffers
    size_t samplesPerChannel_ = 0;
    size_t numChannels_ = 0;
    bool readWavFile(const std::string& filename);
};
