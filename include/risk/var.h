#ifndef VAR_H
#define VAR_H

double approximate_erfinv(double x);
double historical_var(const std::vector<double>& returns, double confidence_level);
double parametric_var(double mean, double std_dev, double confidence_level);

#endif
