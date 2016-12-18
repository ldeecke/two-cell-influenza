// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#include "utilities/vector_operations.h"

namespace utilities {

double sum_maximum(std::vector<double> &a,std::vector<double> &b)
{
    auto i1 = a.begin(), i2 = b.begin();
    double m = *i1++ + *i2++;

    for (; i1 != a.end(); ++i1, ++i2) {
        m = std::max(m, *i1 + *i2);
    }

    return m;
}

double sum_larger_than(std::vector<double> &a, std::vector<double> &b, double x)
{
    auto i1 = a.begin(), i2 = b.begin();
    int r = 0;

    for (; i1 != a.end(); i1++, i2++) {
        if (*i1 + *i2 > x) { r += 1; }
    }

    return static_cast<double>(r);
}

std::vector<double> linspace(double min, double max, int n)
{
    std::vector<double> ls;
    double increment = (max-min) / (n-1);

    while (min <= max) {
        ls.push_back(min);
        min += increment;
    }

    return ls;
}

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

            if (switch_count % (int)(t_on * steps_per_dpi) == 0)
            {
                b = false,
                switch_count = 0;
            }
        }
        else
        {
            efficacy.push_back(efficacy_off);

            if (switch_count % (int)(t_off * steps_per_dpi) == 0)
            {
                b = true;
                switch_count = 0;
            }
        }
    }
    return efficacy;
}

} // namespace utilities