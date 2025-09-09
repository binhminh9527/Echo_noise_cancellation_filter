
#pragma once
#include <vector>
#include <cstdint>
#include "FIRFilter.h"

class EcnrLib {
public:
    EcnrLib();
    float process(float refSample, float micSample);
    void RLSFirUpdate(float out_fir, float micSample);
private:
    FIRFilter fir_;
};
