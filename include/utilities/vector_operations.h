// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef vector_operations_h
#define vector_operations_h

#include <vector>

namespace utilities {

double sum_maximum(std::vector<double> &a, std::vector<double> &b);

double sum_larger_than(std::vector<double> &a, std::vector<double> &b, double input);

std::vector<double> linspace(double min, double max, int n);

std::vector<double> periodic_efficacy(int max_dpi, int t_per_dpi, double t_on, double t_off,
                                      double efficacy_on, double efficacy_off);

} // namespace utilities

#endif //vector_operations_h
