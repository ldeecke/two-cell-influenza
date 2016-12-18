// (c) 12/18/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef common_h
#define common_h

#include <fstream>
#include <string>
#include <vector>

namespace utilities {

void write_result(const std::vector<double>& V_wt, const std::vector<double>& V_mu, std::ofstream& stream);

} // namespace utilities

#endif //common_h
