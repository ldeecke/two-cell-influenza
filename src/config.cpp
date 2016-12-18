// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#include "config.h"

namespace bpo = ::boost::program_options;

config::config(const std::string& file_name, bool parse_config)
    : desc_("influenza configuration")
{
    desc_.add_options()
            ("simulation.dpi", bpo::value(&dpi_)->required(), "simulation length [dpi]")
            ("simulation.t_per_dpi", bpo::value(&t_per_dpi_)->required(), "discretization steps per dpi [1/dpi]")

            ("medicine.t_on", bpo::value(&t_on_)->required(), "drug on duration [dpi]")
            ("medicine.t_off", bpo::value(&t_off_)->required(), "drug off duration [dpi]")
            ("medicine.m_wt", bpo::value(&m_wt_)->required(), "efficacy of adamantanes on wildtype virus")
            ("medicine.n_wt", bpo::value(&n_wt_)->required(), "efficacy of NAI on wildtype virus")
            ("medicine.m_mu", bpo::value(&m_mu_)->required(), "efficacy of adamantanes on mutant virus")
            ("medicine.n_mu", bpo::value(&n_mu_)->required(), "efficacy of NAI on mutant virus")

            ("biology.alpha", bpo::value(&alpha_)->required(), "conversion rate")
            ("biology.break_value", bpo::value(&break_value_)->required(), "infection breakthrough threshold")
            ("biology.r_p", bpo::value(&r_p_)->required(), "relative susceptibility")
            ("biology.r_b", bpo::value(&r_b_)->required(), "relative production rate")
            ("biology.r_T", bpo::value(&r_T_)->required(), "initial secondary target cells")
            ("biology.mu_nm", bpo::value(&mu_nm_)->required(), "mutation rate")
            ("biology.l", bpo::value(&l_)->required(), "regeneration rate")
            ("biology.p_fit", bpo::value(&p_fit_)->required(), "relation between p_wt and p_mu")
            ("biology.b_fit", bpo::value(&b_fit_)->required(), "relation between b_wt and b_mu")
            ("biology.b_wt", bpo::value(&b_wt_)->required(), "infection rate of wildtype virus")
            ("biology.p_wt", bpo::value(&p_wt_)->required(), "production rate rate of wildtype virus")
            ("biology.t_E", bpo::value(&t_E_)->required(), "transition time")
            ("biology.t_I", bpo::value(&t_I_)->required(), "time to cell death")
            ("biology.c", bpo::value(&c_)->required(), "viral clearance rate")

            ("boundary_condition.T_0", bpo::value(&T_0_)->required(), "initial number of target cells")
            ("boundary_condition.E_0", bpo::value(&E_0_)->required(), "initial number of eclipse cells")
            ("boundary_condition.I_0", bpo::value(&I_0_)->required(), "initial number of infected cells")
            ("boundary_condition.D_0", bpo::value(&D_0_)->required(), "initial number of dead cells")
            ("boundary_condition.V_0", bpo::value(&V_0_)->required(), "initial virus amount")
            ;

    if (parse_config)
        parse(file_name);
}


void config::parse(const std::string &file_name)
{
    std::cout << "parsing configuration file: " << file_name << std::endl;
    try {
        std::ifstream config_file(file_name);
        if (!config_file.is_open())
            throw (config_error("could not open config file: " + file_name));

        bpo::variables_map vm;
        bpo::store(bpo::parse_config_file(config_file, desc_, false), vm);
        notify(vm);

    } catch (const config_error& e) {
        throw(e);
    } catch (const bpo::invalid_option_value& e) {
        throw(config_error(std::string("faulty value: ") + e.what()));
    } catch (const std::exception& e) {
        throw(config_error(e.what()));
    }
}