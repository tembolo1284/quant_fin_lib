#include <vector>
#include <stdexcept>
#include <cmath>
#include "yield_curve/interpolation.h"

// Linear Interpolation
double linear_interpolation(const std::vector<double>& x, const std::vector<double>& y, double target) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Invalid input data for interpolation.");
    }
    for (size_t i = 0; i < x.size() - 1; ++i) {
        if (target >= x[i] && target <= x[i + 1]) {
            double slope = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
            return y[i] + slope * (target - x[i]);
        }
    }
    throw std::out_of_range("Target value is outside the interpolation range.");
}

// Cubic Spline Interpolation
std::vector<double> cubic_spline_coefficients(const std::vector<double>& x, const std::vector<double>& y) {
    size_t n = x.size() - 1;
    std::vector<double> a(n), b(n), c(n + 1), d(n);
    std::vector<double> h(n);

    for (size_t i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    // Solve the system for cubic spline coefficients
    // (simplified implementation for demonstration purposes)

    return a; // Placeholder for actual coefficients
}

