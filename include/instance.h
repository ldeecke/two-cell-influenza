// (c) 12/17/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef instance_h
#define instance_h

#include <vector>

#include "config.h"
#include "utilities/random_machine.h"
#include "utilities/vector_operations.h"

enum class drug_type_t
{
    ADM_WT,
    NAI_WT,
    ADM_MU,
    NAI_MU
};

class instance
{
public:
    instance(const config& config);

    ~instance();

    void step_forward();

    std::vector<double> V_wt()
    { return V_wt_; }

    std::vector<double> V_mu()
    { return V_mu_; }

    double efficacy(int t, drug_type_t drug_type);

private:
    utilities::random_machine rm_;

    int t_; // timestep

    int dpi_;
    int t_per_dpi_;
    double dt_;

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
    double b_wt_;
    double b_mu_;
    double p_wt_;
    double p_mu_;
    double t_E_;
    double t_I_;
    double c_;

    std::vector<double> T_d_;
    std::vector<double> T_s_;

    std::vector<double> E_d_wt_;
    std::vector<double> E_d_mu_;
    std::vector<double> E_s_wt_;
    std::vector<double> E_s_mu_;

    std::vector<double> I_d_wt_;
    std::vector<double> I_d_mu_;
    std::vector<double> I_s_wt_;
    std::vector<double> I_s_mu_;

    std::vector<double> V_wt_;
    std::vector<double> V_mu_;

    std::vector<double> D_d_;
    std::vector<double> D_s_;

    std::vector<double> m_wt_efficacy_;
    std::vector<double> n_wt_efficacy_;
    std::vector<double> m_mu_efficacy_;
    std::vector<double> n_mu_efficacy_;
};

inline instance::instance(const config& config)
        : rm_(),
          t_(-1)
{
    this->dpi_ = config.dpi();
    this->t_per_dpi_ = config.t_per_dpi();
    this->dt_ = 1.0 / static_cast<double>(t_per_dpi_);

    this->t_on_ = config.t_on();
    this->t_off_ = config.t_off();
    this->m_wt_ = config.m_wt();
    this->n_wt_ = config.n_wt();
    this->m_mu_ = config.m_mu();
    this->n_mu_ = config.n_mu();

    this->alpha_ = config.alpha();
    this->break_value_ = config.break_value();
    this->r_p_ = config.r_p();
    this->r_b_ = config.r_b();
    this->r_T_ = config.r_T();
    this->mu_nm_ = config.mu_nm();
    this->l_ = config.l();
    this->b_wt_ = config.b_wt();
    this->b_mu_ = config.b_wt() * config.b_fit();
    this->p_wt_ = config.p_wt();
    this->p_mu_ = config.p_wt() * config.p_fit();
    this->t_E_ = config.t_E();
    this->t_I_ = config.t_I();
    this->c_ = config.c();

    this->T_d_.push_back(config.T_0() * (1.0 - config.r_T()));
    this->T_s_.push_back(config.T_0() * config.r_T());

    this->E_d_wt_.push_back(config.E_0());
    this->E_d_mu_.push_back(config.E_0());
    this->E_s_wt_.push_back(config.E_0());
    this->E_s_mu_.push_back(config.E_0());

    this->I_d_wt_.push_back(config.I_0());
    this->I_d_mu_.push_back(config.I_0());
    this->I_s_wt_.push_back(config.I_0());
    this->I_s_mu_.push_back(config.I_0());

    this->D_d_.push_back(config.D_0());
    this->D_s_.push_back(config.D_0());

    this->V_wt_.push_back(config.V_0());
    this->V_mu_.push_back(0.0); // zero initial mutant virus

    this->m_wt_efficacy_ = utilities::periodic_efficacy(config.dpi(), config.t_per_dpi(), config.t_on(), config.t_off(),
                                                        config.m_wt(), 0.0);
    this->n_wt_efficacy_ = utilities::periodic_efficacy(config.dpi(), config.t_per_dpi(), config.t_on(), config.t_off(),
                                                        config.n_wt(), 0.0);
    this->m_mu_efficacy_ = utilities::periodic_efficacy(config.dpi(), config.t_per_dpi(), config.t_on(), config.t_off(),
                                                        config.m_mu(), 0.0);
    this->n_mu_efficacy_ = utilities::periodic_efficacy(config.dpi(), config.t_per_dpi(), config.t_on(), config.t_off(),
                                                        config.n_mu(), 0.0);
}

inline instance::~instance()
{
}

inline double instance::efficacy(int t, drug_type_t drug_type)
{
    if (drug_type == drug_type_t::ADM_WT) { return m_wt_efficacy_[t]; }
    else if (drug_type == drug_type_t::NAI_WT) { return n_wt_efficacy_[t]; }
    else if (drug_type == drug_type_t::ADM_MU) { return m_mu_efficacy_[t]; }
    else if (drug_type == drug_type_t::NAI_MU) { return n_mu_efficacy_[t]; }
    else { return -1.0; }
}


inline void instance::step_forward()
{
    t_ += 1;

    double T_d_in = rm_.discretize(l_ * D_d_.back() * dt_);
    double T_s_in = rm_.discretize(l_ * D_s_.back() * dt_);

    double V_wt_in = rm_.discretize((1 - efficacy(t_, drug_type_t::NAI_WT)) * (I_d_wt_.back() * p_wt_ * (1 - mu_nm_) +
                                                                               I_d_mu_.back() * p_wt_ * mu_nm_ + r_p_ * I_s_wt_.back() * p_wt_ * (1 - mu_nm_) + r_p_ * I_s_mu_.back() * p_wt_ * mu_nm_) * dt_);

    double V_wt_out = rm_.discretize(c_ * V_wt_.back() * dt_);
    double V_mu_in = rm_.discretize((1 - efficacy(t_, drug_type_t::NAI_MU)) * (I_d_wt_.back() * p_mu_ * mu_nm_ +
                                                                               I_d_mu_.back() * p_mu_ * (1 - mu_nm_) + I_s_wt_.back() * mu_nm_ * r_p_ * p_mu_ + I_s_mu_.back() * r_p_ * p_mu_ * (1 - mu_nm_)) * dt_);
    double V_mu_out = rm_.discretize(c_ * V_mu_.back() * dt_);

    double in_E_d_wt = rm_.discretize((1 - efficacy(t_, drug_type_t::ADM_WT)) * b_wt_ * V_wt_.back() * T_d_.back() * dt_);
    double in_E_d_mu = rm_.discretize((1 - efficacy(t_, drug_type_t::ADM_MU)) * b_mu_ * V_mu_.back() * T_d_.back() * dt_);
    double in_E_s_wt = rm_.discretize((1 - efficacy(t_, drug_type_t::ADM_WT)) * r_b_ * b_wt_ * V_wt_.back() * T_s_.back() * dt_);
    double in_E_s_mu = rm_.discretize((1 - efficacy(t_, drug_type_t::ADM_MU)) * r_b_ * b_mu_ * V_mu_.back() * T_s_.back() * dt_);

    double out_E_d_wt = rm_.discretize(E_d_wt_.back() / t_E_ * dt_);
    double out_E_d_mu = rm_.discretize(E_d_mu_.back() / t_E_ * dt_);
    double out_E_s_wt = rm_.discretize(E_s_wt_.back() / t_E_ * dt_);
    double out_E_s_mu = rm_.discretize(E_s_mu_.back() / t_E_ * dt_);

    double out_I_d_wt = rm_.discretize(I_d_wt_.back() / t_I_ * dt_);
    double out_I_d_mu = rm_.discretize(I_d_mu_.back() / t_I_ * dt_);
    double out_I_s_wt = rm_.discretize(I_s_wt_.back() / t_I_ * dt_);
    double out_I_s_mu = rm_.discretize(I_s_mu_.back() / t_I_ * dt_);

    T_d_.push_back(T_d_.back() - in_E_d_wt - in_E_d_mu + T_d_in);
    T_s_.push_back(T_s_.back() - in_E_s_wt - in_E_s_mu + T_s_in);

    E_d_wt_.push_back(E_d_wt_.back() + in_E_d_wt - out_E_d_wt);
    E_d_mu_.push_back(E_d_mu_.back() + in_E_d_mu - out_E_d_mu);
    E_s_wt_.push_back(E_s_wt_.back() + in_E_s_wt - out_E_s_wt);
    E_s_mu_.push_back(E_s_mu_.back() + in_E_s_mu - out_E_s_mu);

    I_d_wt_.push_back(I_d_wt_.back() + out_E_d_wt - out_I_d_wt);
    I_d_mu_.push_back(I_d_mu_.back() + out_E_d_mu - out_I_d_mu);
    I_s_wt_.push_back(I_s_wt_.back() + out_E_s_wt - out_I_s_wt);
    I_s_mu_.push_back(I_s_mu_.back() + out_E_s_mu - out_I_s_mu);

    V_wt_.push_back(V_wt_.back() + V_wt_in - V_wt_out);
    V_mu_.push_back(V_mu_.back() + V_mu_in - V_mu_out);

    D_d_.push_back(D_d_.back() + out_I_d_wt + out_I_d_mu - T_d_in);
    D_s_.push_back(D_s_.back() + out_I_s_wt + out_I_s_mu - T_s_in);
}

#endif //instance_h
