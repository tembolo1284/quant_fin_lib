#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

double binomial_tree_price(double spot, double strike, double rate, double time, double volatility, bool is_call, int steps);

#endif
