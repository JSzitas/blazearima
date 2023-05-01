#include <Rcpp.h>
using namespace Rcpp;
#include "arima/arima.h"
#include "string"

// [[Rcpp::plugins(cpp17)]]
class arima {
private:
  Arima<double, StandardScaler<double>> model;
public:
  arima( std::vector<double> y,
         std::vector<size_t> orders_period = {1,0,1,0,0,0,1},
         std::vector<std::vector<double>> xreg = {{}},
         std::string ss_init = std::string("Gardner"),
         std::string method = std::string("CSS"),
         std::vector<bool> intercept_drift_transform = {true, false, true},
         double kappa = 1000000) {

    const arima_kind kind = arima_kind(orders_period);
    // map is certainly nicer than if else statements and switches
    static std::map<std::string, SSinit> ss_method_map{
      {"Gardner", SSinit::Gardner},
      {"Rossignol", SSinit::Rossignol}
    };
    static std::map<std::string, fitting_method> fitting_method_map = {
      {"CSS", fitting_method::CSS},
      {"CSS-ML", fitting_method::CSSML},
      {"ML", fitting_method::ML},
      {"LASSO", fitting_method::LASSO}
    };

    this->model = Arima<double, StandardScaler<double>>(
      y, kind, xreg, intercept_drift_transform[0],
      intercept_drift_transform[1], intercept_drift_transform[2],
      ss_method_map[ss_init], fitting_method_map[method], kappa, true);
  }
  void fit() {
    this->model.fit();
  }
  std::vector<double> get_coef() const {
    return this->model.get_coef();
  }
  Rcpp::List get_structural_model() const {
    auto res = this->model.get_structural_model();
    return List::create(Named("phi") = res.phi,
                        Named("theta") = res.theta,
                        Named("Delta") = res.delta,
                        Named("Z") = res.Z,
                        Named("a") = res.a,
                        Named("P") = res.P,
                        Named("T") = res.T,
                        Named("V") = res.V,
                        Named("h") = res.h,
                        Named("Pn") = res.Pn);
  }
  Rcpp::List forecast( size_t h = 10, std::vector<std::vector<double>> newxreg = {{}} ){
    forecast_result<double> result = this->model.forecast(h, newxreg );
    return List::create(Named("forecast") = result.forecast, Named("std.err.") = result.std_err);
  };
  Rcpp::NumericVector residuals() const {
    return Rcpp::wrap(this->model.get_residuals());
  };
  Rcpp::NumericVector fitted() const {
    return Rcpp::wrap(this->model.get_fitted());
  };
};

RCPP_EXPOSED_CLASS_NODECL(arima)
RCPP_MODULE(blaze_arima) {
  // using namespace Rcpp;
  Rcpp::class_<arima>("blaze_arima")
  .constructor< std::vector<double>,
                std::vector<size_t>,
                std::vector<std::vector<double>>,
                std::string,
                std::string,
                std::vector<bool>,
                double>("basic contructor")
  .method("fit", &arima::fit,
                "fit arima model")
  .method("get_coef", &arima::get_coef,
                "get fitted arima coefficients")
  .method("forecast", &arima::forecast,
                "forecast from a fitted arima model")
  .method("get_structural_model", &arima::get_structural_model,
                "get structural model specification from arima model")
  .method("residuals", &arima::residuals,
                "get residuals from fitted model")
  .method("fitted", &arima::fitted,
                "get fitted values from fitted model");
}
