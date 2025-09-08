
#pragma once
#include <vector>
#include <cstdint>
#include "FIRFilter/FIRFilter.h"

class EcnrLib {
public:
    EcnrLib(const std::vector<float>& firCoeffs);
    float echoNoiseCancellation(float refSample, float micSample);
private:
    FIRFilter fir_;
};
