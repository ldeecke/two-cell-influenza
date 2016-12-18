// (c) 12/18/16 Lucas Deecke (ldeecke@gmail.com)

#include "utilities/common.h"

namespace utilities {

const char default_separator = ',';

void write_result(const std::vector<double>& V_wt, const std::vector<double>& V_mu, std::ofstream& stream)
{
    for (size_t i = 0; i < V_wt.size(); ++i)
    {
        stream << std::to_string(V_wt[i]);
        stream << ",";
        stream << std::to_string(V_mu[i]);
        stream << std::endl;
    }
}

} // namespace utilities