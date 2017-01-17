// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef random_machine_h
#define random_machine_h

#include <random>
#include <math.h>

namespace utilities {

class random_machine
{
public:
    random_machine();
    double discretize(double input);

private:
    std::random_device random_device;
    std::mt19937 number_generator;
    std::uniform_real_distribution<> uniform_distribution;
};

random_machine::random_machine()
    : number_generator(random_device()),
      uniform_distribution(0., 1.)
{
}

double random_machine::discretize(double input)
{
    if (input <= 0.0) { return 0.0; }
    else
    {
        double c = input - floor(input);
        auto r = uniform_distribution(number_generator);
        if (r <= c) { return ceil(input); } else { return floor(input); }
    }
}

} // namespace utilities

#endif //random_machine_h

