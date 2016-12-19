// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef vector_operations_h
#define vector_operations_h

#include <vector>

namespace utilities {

std::vector<double> periodic_efficacy(int max_dpi, int t_per_dpi, double t_on, double t_off,
                                      double efficacy_on, double efficacy_off);

} // namespace utilities

#endif //vector_operations_h
