#include "FIRFilter.h"

FIRFilter::FIRFilter(const std::vector<float>& coeffs)
    : coeffs_(coeffs), buffer_(coeffs.size(), 0.0f), index_(0) {}

float FIRFilter::process(float inputSample) {
    buffer_[index_] = inputSample;
    float output = 0.0f;
    size_t bufSize = buffer_.size();
    for (size_t i = 0; i < bufSize; ++i) {
        size_t bufIdx = (index_ + bufSize - i) % bufSize;
        output += coeffs_[i] * buffer_[bufIdx];
    }
    index_ = (index_ + 1) % bufSize;
    return output;
}


void FIRFilter::reset() {
    std::fill(buffer_.begin(), buffer_.end(), 0.0f);
    index_ = 0;
}

void FIRFilter::updateCoeffs(const std::vector<float>& newCoeffs) {
    coeffs_ = newCoeffs;
    buffer_.assign(coeffs_.size(), 0.0f);
    index_ = 0;
}
