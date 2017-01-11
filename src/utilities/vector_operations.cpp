// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#include "utilities/vector_operations.h"

namespace utilities {

std::vector<double> periodic_efficacy(int total_dpi, int steps_per_dpi, double t_on, double t_off, double efficacy_on, double efficacy_off)
{
    bool b = true;
    int switch_count = 1;
    std::vector<double> efficacy;

    for (int t = 0; t < (total_dpi * steps_per_dpi); t++, switch_count++)
    {
        if (b)
        {
            efficacy.push_back(efficacy_on);

            if (switch_count % static_cast<int>(t_on * steps_per_dpi) == 0)
            {
                b = false,
                switch_count = 0;
            }
        }
        else
        {
            efficacy.push_back(efficacy_off);

            if (switch_count % static_cast<int>(t_off * steps_per_dpi) == 0)
            {
                b = true;
                switch_count = 0;
            }
        }
    }
    return efficacy;
}

} // namespace utilities