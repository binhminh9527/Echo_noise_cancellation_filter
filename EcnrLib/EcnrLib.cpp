#include "EcnrLib.h"

void EcnrLib::echoNoiseCancellation(std::vector<int16_t>& input1, std::vector<int16_t>& input2, std::vector<int16_t>& output) {
    // Simple subtraction for demonstration
    size_t size = std::min(input1.size(), input2.size());
    output.resize(size);
    for (size_t i = 0; i < size; ++i) {
        output[i] = input1[i] - input2[i];
    }
}
