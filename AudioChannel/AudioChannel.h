#pragma once
#include <cstddef>
#include <memory>
class AudioChannel {
public:
    AudioChannel(size_t numSamples);
    ~AudioChannel();
    float* data();
    const float* data() const;
    size_t numSamples() const;
private:
    float* samples_;
    size_t numSamples_;
};
