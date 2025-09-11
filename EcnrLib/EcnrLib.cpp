#include "EcnrLib.h"

EcnrLib::EcnrLib(): fir_(std::vector<float>(3000, 0.0f)) //create a vector with length = 1/48000 * 0.15 * 48000 = 0.15 * 48000 = 7200
{
    int fir_length = fir_.getCoeffs()->size();
    //Initialize Kalman gain vector
    K = std::vector<float>(fir_length, 0.0f);

    //Initialize Covariance matrix P
    P = std::vector<std::vector<float>>(fir_length, std::vector<float>(fir_length, 0.0f));
    for (size_t i = 0; i < fir_length; ++i) {
        P[i][i] = 0.5f ; // Initialize diagonal elements to 0.5
    }
    fir_buffer_ = fir_.getBuffer();
    fir_index_ = fir_.getindex();
}

void EcnrLib::RLSFirUpdate(float out_fir, float micSample) {
    std::vector<float>* fir_coeef = fir_.getCoeffs();
// 1 Compute Filter Output

// 2 Compute Error Signal
    float error = micSample - out_fir;

// 3. Compute the Kalman gain vector
    // K_M(n) = P_M(n-1) X*_M(n) / (w + X^t_M(n) P_M(n-1) X*_M(n))
    // X_M(n) is the state vector (fir_buffer_)
    // P_M(n-1) is the covariance matrix (P)
    // w is a regularization parameter, e.g., 0.01
    float w = 0.01f;
    size_t N = fir_coeef->size();
    std::vector<float> X(N);
    // Get X_M(n) from fir_buffer_ (current state)
    for (size_t i = 0; i < N; ++i) {
        // X[0] is the latest sample, X[N-1] is the oldest
        size_t idx = ((*fir_index_) + N - 1 - i + N) % N;
        X[i] = (*fir_buffer_)[idx];
    }

    // Compute P_M(n-1) X*_M(n)
    std::vector<float> numerator(N, 0.0f);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            numerator[i] += P[i][j] * X[j];
        }
    }
    // Compute denominator: w + X^t_M(n) P_M(n-1) X*_M(n)
    float denom = w;
    for (size_t i = 0; i < N; ++i) {
        denom += X[i] * numerator[i];
    }
    // Compute Kalman gain vector
    for (size_t i = 0; i < N; ++i) {
        K[i] = numerator[i] / denom;
    }

// 4. Update the inverse correlation matrix
    // P_M(n) = (1/w) [P_M(n-1) - K_M(n) X^t_M(n) P_M(n-1)]
    // Compute X^t_M(n) P_M(n-1): this is a row vector
    std::vector<float> XtP(N, 0.0f);
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            XtP[j] += X[i] * P[i][j];
        }
    }
    // Compute K_M(n) X^t_M(n) P_M(n-1): this is an NxN matrix
    std::vector<std::vector<float>> KXtP(N, std::vector<float>(N, 0.0f));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            KXtP[i][j] = K[i] * XtP[j];
        }
    }
    // Update P
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            P[i][j] = (P[i][j] - KXtP[i][j]) / w;
        }
    }

// 5. Update the filter coefficients
    // hM(n) = hM(n − 1) + KM(n)eM(n)
    for (size_t i = 0; i < fir_coeef->size(); ++i) {
        (*fir_coeef)[i] += K[i]*error;
    }

}

float EcnrLib::process(float refSample, float micSample) {
    // Example: apply FIR filter to micSample - refSample
    float output = 0.0f;
    float out_fir = fir_.process(refSample);

    
    RLSFirUpdate(out_fir, micSample);

    return micSample - out_fir;
}


