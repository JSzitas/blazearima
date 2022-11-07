// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// parameter_transform
std::vector<double> parameter_transform(std::vector<double>& coef);
RcppExport SEXP _blazearima_parameter_transform(SEXP coefSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type coef(coefSEXP);
    rcpp_result_gen = Rcpp::wrap(parameter_transform(coef));
    return rcpp_result_gen;
END_RCPP
}
// inv_parameter_transform
std::vector<double> inv_parameter_transform(std::vector<double>& phi);
RcppExport SEXP _blazearima_inv_parameter_transform(SEXP phiSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type phi(phiSEXP);
    rcpp_result_gen = Rcpp::wrap(inv_parameter_transform(phi));
    return rcpp_result_gen;
END_RCPP
}
// ts_conv
std::vector<double> ts_conv(std::vector<double>& a, std::vector<double>& b);
RcppExport SEXP _blazearima_ts_conv(SEXP aSEXP, SEXP bSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type a(aSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type b(bSEXP);
    rcpp_result_gen = Rcpp::wrap(ts_conv(a, b));
    return rcpp_result_gen;
END_RCPP
}
// arima_transform_parameters
std::vector<double> arima_transform_parameters(std::vector<double> coef, std::vector<int> arma, bool transform);
RcppExport SEXP _blazearima_arima_transform_parameters(SEXP coefSEXP, SEXP armaSEXP, SEXP transformSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type coef(coefSEXP);
    Rcpp::traits::input_parameter< std::vector<int> >::type arma(armaSEXP);
    Rcpp::traits::input_parameter< bool >::type transform(transformSEXP);
    rcpp_result_gen = Rcpp::wrap(arima_transform_parameters(coef, arma, transform));
    return rcpp_result_gen;
END_RCPP
}
// arima_inverse_transform_parameters
std::vector<double> arima_inverse_transform_parameters(std::vector<double> coef, std::vector<int>& arma);
RcppExport SEXP _blazearima_arima_inverse_transform_parameters(SEXP coefSEXP, SEXP armaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type coef(coefSEXP);
    Rcpp::traits::input_parameter< std::vector<int>& >::type arma(armaSEXP);
    rcpp_result_gen = Rcpp::wrap(arima_inverse_transform_parameters(coef, arma));
    return rcpp_result_gen;
END_RCPP
}
// arima_grad_transform
std::vector<double> arima_grad_transform(std::vector<double>& coef, std::vector<int>& arma, double eps);
RcppExport SEXP _blazearima_arima_grad_transform(SEXP coefSEXP, SEXP armaSEXP, SEXP epsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type coef(coefSEXP);
    Rcpp::traits::input_parameter< std::vector<int>& >::type arma(armaSEXP);
    Rcpp::traits::input_parameter< double >::type eps(epsSEXP);
    rcpp_result_gen = Rcpp::wrap(arima_grad_transform(coef, arma, eps));
    return rcpp_result_gen;
END_RCPP
}
// some_fun
double some_fun(std::vector<double>& x, double lambda, int period);
RcppExport SEXP _blazearima_some_fun(SEXP xSEXP, SEXP lambdaSEXP, SEXP periodSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< int >::type period(periodSEXP);
    rcpp_result_gen = Rcpp::wrap(some_fun(x, lambda, period));
    return rcpp_result_gen;
END_RCPP
}
// particle_solver_bc
double particle_solver_bc(std::vector<double> x, double lower, double upper, int n_particles);
RcppExport SEXP _blazearima_particle_solver_bc(SEXP xSEXP, SEXP lowerSEXP, SEXP upperSEXP, SEXP n_particlesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double> >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type lower(lowerSEXP);
    Rcpp::traits::input_parameter< double >::type upper(upperSEXP);
    Rcpp::traits::input_parameter< int >::type n_particles(n_particlesSEXP);
    rcpp_result_gen = Rcpp::wrap(particle_solver_bc(x, lower, upper, n_particles));
    return rcpp_result_gen;
END_RCPP
}
// test_polyroot_abs
std::vector<double> test_polyroot_abs(std::vector<double>& x);
RcppExport SEXP _blazearima_test_polyroot_abs(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_polyroot_abs(x));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_blazearima_parameter_transform", (DL_FUNC) &_blazearima_parameter_transform, 1},
    {"_blazearima_inv_parameter_transform", (DL_FUNC) &_blazearima_inv_parameter_transform, 1},
    {"_blazearima_ts_conv", (DL_FUNC) &_blazearima_ts_conv, 2},
    {"_blazearima_arima_transform_parameters", (DL_FUNC) &_blazearima_arima_transform_parameters, 3},
    {"_blazearima_arima_inverse_transform_parameters", (DL_FUNC) &_blazearima_arima_inverse_transform_parameters, 2},
    {"_blazearima_arima_grad_transform", (DL_FUNC) &_blazearima_arima_grad_transform, 3},
    {"_blazearima_some_fun", (DL_FUNC) &_blazearima_some_fun, 3},
    {"_blazearima_particle_solver_bc", (DL_FUNC) &_blazearima_particle_solver_bc, 4},
    {"_blazearima_test_polyroot_abs", (DL_FUNC) &_blazearima_test_polyroot_abs, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_blazearima(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
