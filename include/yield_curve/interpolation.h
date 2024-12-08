#ifndef INTERPOLATION_H
#define INTERPOLATION_H

double linear_interpolation(const std::vector<double>& x, const std::vector<double>& y, double target);
std::vector<double> cubic_spline_coefficients(const std::vector<double>& x, const std::vector<double>& y);

#endif
