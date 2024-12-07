#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

// Inverse error function implementation
double approximate_erfinv(double x) {
    // Approximation for inverse error function
    double a = 0.147; // Constant for the approximation
    double ln1mx2 = std::log(1 - x * x);
    double part1 = 2 / (M_PI * a) + ln1mx2 / 2;
    double part2 = ln1mx2 / a;
    return std::copysign(std::sqrt(std::sqrt(part1 * part1 - part2) - part1), x);
}

// Historical Value-at-Risk
double historical_var(const std::vector<double>& returns, double confidence_level) {
    if (returns.empty()) {
        throw std::invalid_argument("Returns cannot be empty.");
    }
    std::vector<double> sorted_returns = returns;
    std::sort(sorted_returns.begin(), sorted_returns.end());
    size_t index = static_cast<size_t>((1.0 - confidence_level) * sorted_returns.size());
    return sorted_returns[index];
}

// Parametric Value-at-Risk
double parametric_var(double mean, double std_dev, double confidence_level) {
    double z_score = std::sqrt(2.0) * approximate_erfinv(2.0 * confidence_level - 1.0);
    return mean - z_score * std_dev;
}

