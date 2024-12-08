#ifndef VAR_H
#define VAR_H
#include "quant_fin_lib.h"

#include <vector>

double approximate_erfinv(double x);
QF_API double historical_var(const std::vector<double>& returns, double confidence_level);
QF_API double parametric_var(double mean, double std_dev, double confidence_level);

#endif
