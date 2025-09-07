#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

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

bool readWavFile(const std::string& filename, std::vector<int16_t>& buffer, WAVHeader& header) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    if (std::string(header.riff, 4) != "RIFF" || std::string(header.wave, 4) != "WAVE") {
        std::cerr << "Invalid WAV file: " << filename << std::endl;
        return false;
    }

    buffer.resize(header.dataSize / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(buffer.data()), header.dataSize);

    return true;
}

int main() {
    std::string filename1 = "input1.wav";
    std::string filename2 = "input2.wav";
    std::vector<int16_t> buffer1, buffer2;
    WAVHeader header1, header2;

    if (!readWavFile(filename1, buffer1, header1)) {
        std::cerr << "Failed to read " << filename1 << std::endl;
        return 1;
    }
    if (!readWavFile(filename2, buffer2, header2)) {
        std::cerr << "Failed to read " << filename2 << std::endl;
        return 1;
    }

    // Call echo noise cancellation function here
    // echoNoiseCancellation(buffer1, buffer2, ...);

    std::cout << "WAV files read successfully." << std::endl;
    return 0;
}
