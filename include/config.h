// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef config_h
#define config_h

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

class config_error : public std::runtime_error {
public:
    config_error(const std::string &msg) : runtime_error("heom::config_error: " + msg) {};
};

class config {
public:
    config(const std::string& file_name, bool parse_config = true);

    virtual ~config() {};

    const int &dpi() const { return dpi_; }
    const int &t_per_dpi() const { return t_per_dpi_; }

    const double &t_on() const { return t_on_; }
    const double &t_off() const { return t_off_; }
    const double &m_wt() const { return m_wt_; }
    const double &n_wt() const { return n_wt_; }
    const double &m_mu() const { return m_mu_; }
    const double &n_mu() const { return n_mu_; }

    const double &alpha() const { return alpha_; }
    const double &break_value() const { return break_value_; }
    const double &r_p() const { return r_p_; }
    const double &r_b() const { return r_b_; }
    const double &r_T() const { return r_T_; }
    const double &mu_nm() const { return mu_nm_; }
    const double &l() const { return l_; }
    const double &p_fit() const { return p_fit_; }
    const double &b_fit() const { return b_fit_; }
    const double &b_wt() const { return b_wt_; }
    const double &p_wt() const { return p_wt_; }
    const double &t_E() const { return t_E_; }
    const double &t_I() const { return t_I_; }
    const double &c() const { return c_; }

    const double &T_0() const { return T_0_; }
    const double &E_0() const { return E_0_; }
    const double &I_0() const { return I_0_; }
    const double &D_0() const { return D_0_; }
    const double &V_0() const { return V_0_; }



protected:
    void parse(const std::string &file_name);
    boost::program_options::options_description desc_;

private:
    int dpi_;
    int t_per_dpi_;

    double t_on_;
    double t_off_;
    double m_wt_;
    double n_wt_;
    double m_mu_;
    double n_mu_;

    double alpha_;
    double break_value_;
    double r_p_;
    double r_b_;
    double r_T_;
    double mu_nm_;
    double l_;
    double p_fit_;
    double b_fit_;
    double b_wt_;
    double p_wt_;
    double t_E_;
    double t_I_;
    double c_;

    double T_0_;
    double E_0_;
    double I_0_;
    double D_0_;
    double V_0_;
};

#endif //config_h
