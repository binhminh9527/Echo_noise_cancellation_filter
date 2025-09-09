#pragma once
#include <vector>

class FIRFilter {
public:
    FIRFilter(const std::vector<float>& coeffs);
    float process(float inputSample);
    void reset();
    void updateCoeffs(const std::vector<float>& newCoeffs);
    std::vector<float>* getCoeffs();
private:
    std::vector<float> coeffs_;
    std::vector<float> buffer_;
    size_t index_;
};
