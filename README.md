# Echo_noise_cancellation_filter
Real-time echo and noise cancellation library for speech applications, built with digital signal processing techniques to improve voice clarity in conferencing, VoIP, and smart assistant systems.

# Recursive Least Square Update Steps

This document describes the recursive steps for updating the adaptive filter using the Kalman filter approach.

---

### 1. Compute the filter output
$$
\hat{d}(n) = X_M^t(n) \, h_M(n-1)
$$

---

### 2. Compute the error
$$
e_M(n) = d(n) - \hat{d}(n)
$$

---

### 3. Compute the Kalman gain vector
$$
K_M(n) = \frac{P_M(n-1) \, X_M^*(n)}{w + X_M^t(n) \, P_M(n-1) \, X_M^*(n)}
$$

---

### 4. Update the inverse of the correlation matrix
$$
P_M(n) = \frac{1}{w} \Big[ P_M(n-1) - K_M(n) \, X_M^t(n) \, P_M(n-1) \Big]
$$

---

### 5. Update the coefficient vector of the filter
$$
h_M(n) = h_M(n-1) + K_M(n) \, e_M(n)
$$
