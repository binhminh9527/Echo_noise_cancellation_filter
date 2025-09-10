#include "EcnrLib.h"

EcnrLib::EcnrLib(): fir_(std::vector<float>(3000, 0.0f)) //create a vector with length = 1/48000 * 0.15 * 48000 = 0.15 * 48000 = 7200
{
}

void EcnrLib::RLSFirUpdate(float out_fir, float micSample) {
    std::vector<float>* fir_coeef = fir_.getCoeffs();

}

float EcnrLib::process(float refSample, float micSample) {
    // Example: apply FIR filter to micSample - refSample
    float output = 0.0f;
    float out_fir = fir_.process(refSample);
    RLSFirUpdate(out_fir, micSample);
    return micSample - out_fir;
}

