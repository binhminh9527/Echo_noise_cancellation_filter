#pragma once
#include <vector>
#include <cstdint>

class EcnrLib {
public:
    // Example echo noise cancellation function
    static void echoNoiseCancellation(std::vector<int16_t>& input1, std::vector<int16_t>& input2, std::vector<int16_t>& output);
};
