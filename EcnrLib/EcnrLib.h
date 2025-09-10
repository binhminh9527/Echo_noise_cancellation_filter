
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
    std::vector<float> K;
    std::vector<std::vector<float>> P; // Covariance matrix
    std::vector<float>* fir_buffer_ = nullptr; // State vector      
    size_t* fir_index_ = 0;         
};
