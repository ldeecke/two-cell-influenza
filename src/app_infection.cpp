// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#include <iostream>

#include "config.h"
#include "instance.h"
#include "utilities/common.h"

int main(int argc, char *argv[]){
    std::string config_file_name = "config.ini";
    std::string observation_file_name = "out.dat";

    config config(config_file_name);
    instance instance(config);

    for (size_t t = 0; t < config.dpi() * config.t_per_dpi(); ++t) { instance.step_forward(); }

    std::ofstream observation_file;
    observation_file.open(observation_file_name);
    if (!observation_file.is_open())
    {
        std::cerr << "Error: could not open output file: " << observation_file_name << std::endl;
        return -1;
    }

    observation_file << "V_wt,V_mu" << std::endl;
    utilities::write_result(instance.V_wt(), instance.V_mu(), observation_file);

    observation_file.close();

    return 0;
}
