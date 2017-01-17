// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#include "config.h"

namespace bpo = ::boost::program_options;

config::config(const std::string& file_name, bool parse_config)
    : desc_("influenza configuration")
{
    desc_.add_options()
            ("simulation.dpi", bpo::value(&dpi_)->required(), "simulation length [dpi]")
            ("simulation.t_per_dpi", bpo::value(&t_per_dpi_)->required(), "discretization steps per dpi [1/dpi]")

            ("treatment.t_on", bpo::value(&t_on_)->required(), "drug on duration [dpi]")
            ("treatment.t_off", bpo::value(&t_off_)->required(), "drug off duration [dpi]")
            ("treatment.m_wt", bpo::value(&m_wt_)->required(), "efficacy of adamantanes on wildtype virus")
            ("treatment.n_wt", bpo::value(&n_wt_)->required(), "efficacy of NAI on wildtype virus")
            ("treatment.m_mu", bpo::value(&m_mu_)->required(), "efficacy of adamantanes on mutant virus")
            ("treatment.n_mu", bpo::value(&n_mu_)->required(), "efficacy of NAI on mutant virus")

            ("biology.alpha", bpo::value(&alpha_)->required(), "conversion rate")
            ("biology.break_value", bpo::value(&break_value_)->required(), "infection breakthrough threshold")
            ("biology.r_p", bpo::value(&r_p_)->required(), "relative susceptibility")
            ("biology.r_b", bpo::value(&r_b_)->required(), "relative production rate")
            ("biology.r_T", bpo::value(&r_T_)->required(), "initial secondary target cells")
            ("biology.mu_nm", bpo::value(&mu_nm_)->required(), "mutation rate")
            ("biology.l", bpo::value(&l_)->required(), "regeneration rate")
            ("biology.p_fit", bpo::value(&p_fit_)->required(), "relation between p_wt and p_mu")
            ("biology.b_fit", bpo::value(&b_fit_)->required(), "relation between b_wt and b_mu")
            ("biology.p_wt", bpo::value(&p_wt_)->required(), "production rate rate of wildtype virus")
            ("biology.b_wt", bpo::value(&b_wt_)->required(), "infection rate of wildtype virus")
            ("biology.t_E", bpo::value(&t_E_)->required(), "transition time")
            ("biology.t_I", bpo::value(&t_I_)->required(), "time to cell death")
            ("biology.c", bpo::value(&c_)->required(), "viral clearance rate")

            ("boundary_conditions.T_0", bpo::value(&T_0_)->required(), "initial number of target cells")
            ("boundary_conditions.E_0", bpo::value(&E_0_)->required(), "initial number of eclipse cells")
            ("boundary_conditions.I_0", bpo::value(&I_0_)->required(), "initial number of infected cells")
            ("boundary_conditions.D_0", bpo::value(&D_0_)->required(), "initial number of dead cells")
            ("boundary_conditions.V_0", bpo::value(&V_0_)->required(), "initial virus amount")
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

    check();
}

void config::check()
{
    if (!(dpi_ > 0))
        throw(config_error("simulation.bpi must be > 0"));
    if (!(t_per_dpi_ > 0))
        throw(config_error("simulation.t_per_bpi must be > 0"));

    if (!(t_on_ > 0.))
        throw(config_error("treatment.t_on must be > 0"));
    if (!(t_off_ > 0.))
        throw(config_error("treatment.t_off must be > 0"));
    if (m_wt_ < 0. or  m_wt_ > 1.)
        throw(config_error("treatment.m_wt must be between 0 and 1."));
    if (n_wt_ < 0. or  n_wt_ > 1.)
        throw(config_error("treatment.n_wt must be between 0 and 1"));
    if (m_mu_ < 0. or  m_mu_ > 1.)
        throw(config_error("treatment.m_mu must be between 0 and 1"));
    if (n_mu_ < 0. or  n_mu_ > 1.)
        throw(config_error("treatment.n_mu must be between 0 and 1"));

    if (!(alpha_ > 0.))
        throw(config_error("biology.alpha must be > 0"));
    if (!(break_value_ > 0.))
        throw(config_error("biology.break_value must be > 0"));
    if (!(r_p_ > 0.))
        throw(config_error("biology.r_p must be > 0"));
    if (!(r_b_ > 0.))
        throw(config_error("biology.r_b must be > 0"));
    if (r_T_ < 0. or r_T_ > 1.)
        throw(config_error("biology.r_T must be between 0 and 1"));
    if (mu_nm_ < 0. or mu_nm_ > 1.)
        throw(config_error("biology.mu_nu must be between 0 and 1"));
    if (!(l_ >= 0.))
        throw(config_error("biology.l must be >= 0"));
    if (!(p_fit_ > 0.))
        throw(config_error("biology.p_fit must be > 0"));
    if (!(b_fit_ > 0.))
        throw(config_error("biology.b_fit must be > 0"));
    if (!(p_wt_ > 0.))
        throw(config_error("biology.p_wt must be > 0"));
    if (!(b_wt_ > 0.))
        throw(config_error("biology.b_wt must be > 0"));
    if (!(t_E_ > 0.))
        throw(config_error("biology.t_E must be > 0"));
    if (!(t_I_ > 0.))
        throw(config_error("biology.t_I must be > 0"));
    if (!(c_ > 0.))
        throw(config_error("biology.c must be > 0"));

    if (!(T_0_ > 0.))
        throw(config_error("boundary_conditions.T_0 must be > 0"));
    if (!(E_0_ >= 0.))
        throw(config_error("boundary_conditions.E_0 must be >= 0"));
    if (!(I_0_ >= 0.))
        throw(config_error("boundary_conditions.I_0 must be >= 0"));
    if (!(D_0_ >= 0.))
        throw(config_error("boundary_conditions.D_0 must be >= 0"));
    if (!(V_0_ > 0.))
        throw(config_error("boundary_conditions.V_0 must be > 0"));
}