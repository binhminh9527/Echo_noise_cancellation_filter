#include "EcnrLib.h"

EcnrLib::EcnrLib(const std::vector<float>& firCoeffs)
    : fir_(firCoeffs) {}

float EcnrLib::echoNoiseCancellation(float refSample, float micSample) {
    // Example: apply FIR filter to micSample - refSample
    float input = micSample - refSample;
    return fir_.process(input);
}
