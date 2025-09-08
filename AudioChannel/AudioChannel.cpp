#include "AudioChannel.h"

AudioChannel::AudioChannel(size_t numSamples) : numSamples_(numSamples) {
    samples_ = new float[numSamples_];
}

AudioChannel::~AudioChannel() {
    delete[] samples_;
}

float* AudioChannel::data() {
    return samples_;
}

size_t AudioChannel::numSamples() const {
    return numSamples_;
}
