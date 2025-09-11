
#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include "AudioChannel.h"
#include "Logging/Logging.h"

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
    WavFileHandler(const std::vector<float>& data);
    ~WavFileHandler();
    const WAVHeader& getHeader() const { return header_; }
    AudioChannel* getChannel(int channel) const;
    size_t getSamplesPerChannel() const { return samplesPerChannel_; }
    size_t getNumChannels() const { return numChannels_; }
    bool saveWavFile(const std::string& filename) const;

private:
    WAVHeader header_;
    AudioChannel** channels_ = nullptr; // Array of pointers to AudioChannel
    size_t samplesPerChannel_ = 0;
    size_t numChannels_ = 0;
    bool readWavFile(const std::string& filename);
};
