#ifndef ARIMA_WRAPPER
#define ARIMA_WRAPPER

#include "initializers.h"
#include "utils/utils.h"
#include "structural_model.h"
#include "xreg.h"

// defines the arima structure
struct arima_kind{
  arima_kind(){};
   arima_kind( int p, int d, int q, int P, int D, int Q, int s_period ){
     this->arma_p= p;
     this->diff_d = d;
     this->arma_q = q;
     this->sarma_P = P;
     this->seas_diff_D = D;
     this->sarma_Q = Q;
     this->s_period = s_period;
  }
  int p() const {
    return this->arma_p;
  }
  int d() const {
    return this->diff_d;
  }
  int q() const {
    return this->arma_q;
  }
  int P() const {
     return this->sarma_P;
  }
  int D() const {
    return this->seas_diff_D;
  }
  int Q() const {
    return this->sarma_P;
  }
  int period() const {
    return this->s_period;
  }
private:
  int arma_p, diff_d, arma_q, sarma_P, seas_diff_D, sarma_Q, s_period;
};

enum fitting_method{
  CSS = 1,
  CSSML = 2,
  ML = 3
};

template <typename U=double> class Arima {
public:
  Arima<U>(){};
  Arima( std::vector<U> & y,
         arima_kind kind,
         std::vector<std::vector<U>> xreg = {{}},
         bool intercept = true,
         bool transform_parameters = true,
         SSinit ss_init = Gardner,
         fitting_method method = ML,
         U kappa = 1000000 ){
    this->y = y;
    this->xreg = xreg;
    this->intercept = intercept;
    this->transform_parameters = transform_parameters;
    this->ss_init = ss_init;
    this->kind = kind;
    this->method = method;
  };
  void fit(){
    // this should just proceed with fitting, not do things which can be done in
    // the constructor
    // create deltas
    this->deltas = make_delta( this->kind.d(), this->kind.period(), this->kind.D());
    // get number of available observations
    int available_n = this->y.size();
    // take a copy so we do not modify the underlying data - maybe we
    // change this later
    std::vector<U> y_fit = this->y;
    // find na across y
    std::vector<int> na_cases = find_na(y);
    // fit xreg
    if( this->xreg.size() > 0 ) {
      std::vector<U> y_d;
      std::vector<std::vector<U>> xreg_d;
      // if we have any differences
      if( this->kind.d() > 0 ) {
        y_d = diff(this->y, 1, this->kind.d());
        xreg_d = diff(this->xreg, 1, this->kind.d());
      }
      // seasonal differences
      if( this->kind.period() > 1 && this->kind.D() > 0  ) {
        y_d = diff(this->y, this->kind.period(), this->kind.D());
        xreg_d = diff(this->xreg, this->kind.period(), this->kind.D());
      }
      lm_coef<U> reg_coef(xreg_d.size(), this->intercept);
      // fit coefficients and adjust y for fitted coefficients -
      // the original R code does this repeatedly, but it can be done only once
      // - the fitted effects from external regressors are never refitted
      if( this->y_d <= xreg_d.size() ) {
        reg_coef = xreg_coef(this->y, this->xreg, this->intercept);
        y_fit -= predict(reg_coef, xreg);
      }
      else {
        reg_coef = xreg_coef(y_d, xreg_d);
        y_fit -= predict(reg_coef, xreg);
      }
      this->reg_coef = reg_coef;
      // find na cases across xreg
      for( int i= 0; i < xreg.size(); i++  ) {
        na_cases = intersect( na_cases, find_na(xreg[i]));
      }
    }
    int missing_cases = na_cases.size();
    available_n -= (this->deltas.size() + missing_cases);
    // override method to ML if any cases are missing
    if(this->method == CSSML) {
      if(missing_cases > 0) {
        this->method = ML;
      }
    }
    // we have to include xreg in full parameter vector when optimizing -
    // as it can have an impact on the result, it has to be jointly optimized

    // ncond is the number of parameters we are effectively estimating thanks to
    // seasonal parameters
    int ncond = 0;
    if( method == CSS || method == CSSML ) {
      ncond += this->kind.d() + (this->kind.D() * this->kind.period());
      ncond += this->kind.p() + (this->kind.P() * this->kind.period());
    }
    if( ncond <= 0 ) {
      // too few non missing observations - alternatively we can throw
      return;
    }
    if( method == CSS ) {
      //         res <- optim(init[mask], armaCSS, method = "BFGS",
      //                      hessian = TRUE, control = optim.control)
      //         coef[mask] <- res$par
      //         trarma <- .Call(stats:::C_ARIMA_transPars, coef, arma, FALSE)
      //         mod <- stats:::makeARIMA(trarma[[1L]], trarma[[2L]], Delta, kappa,
      //                                  SSinit)
      //         if (ncxreg > 0) {
      //           x <- x - xreg %*% coef[narma + (1L:ncxreg)]
      //         }
      //         val <- .Call(stats:::C_ARIMA_CSS, x, arma, trarma[[1L]], trarma[[2L]],
      //                      as.integer(ncond), TRUE)
      //           sigma2 <- val[[1L]]
      //         var <- solve(res$hessian * n.used)
    }
    else {
      //         if (method == "CSS-ML") {
      //           res <- optim(init[mask], armaCSS, method = "BFGS",
      //                        hessian = FALSE, control = optim.control)
      //           if (res$convergence == 0)
      //             init[mask] <- res$par
      //             if (arma[1L] > 0)
      //               if (!arCheck(init[1L:arma[1L]]))
      //                 stop("non-stationary AR part from CSS")
      //                 if (arma[3L] > 0)
      //                   if (!arCheck(init[sum(arma[1L:2L]) + 1L:arma[3L]]))
      //                     stop("non-stationary seasonal AR part from CSS")
      //                     ncond <- 0L
      //         }
      //         if (transform.pars) {
      //           init <- .Call(stats:::C_ARIMA_Invtrans, init, arma)
      //           if (arma[2L] > 0) {
      //             ind <- arma[1L] + 1L:arma[2L]
      //             init[ind] <- maInvert(init[ind])
      //           }
      //           if (arma[4L] > 0) {
      //             ind <- sum(arma[1L:3L]) + 1L:arma[4L]
      //             init[ind] <- maInvert(init[ind])
      //           }
      //         }
      //         trarma <- .Call(stats:::C_ARIMA_transPars, init, arma, transform.pars)
      //           mod <- makeARIMA(trarma[[1L]], trarma[[2L]], Delta, kappa,
      //                            SSinit)
      //           res <- optim(init[mask], armafn, method = "BFGS",
      //                        hessian = TRUE, control = optim.control, trans = as.logical(transform.pars))
      //           if (res$convergence > 0)
      //             warning(gettextf("possible convergence problem: optim gave code = %d",
      //                              res$convergence), domain = NA)
      //             coef[mask] <- res$par
      //             if (transform.pars) {
      //               if (arma[2L] > 0L) {
      //                 ind <- arma[1L] + 1L:arma[2L]
      //                 if (all(mask[ind]))
      //                   coef[ind] <- maInvert(coef[ind])
      //               }
      //               if (arma[4L] > 0L) {
      //                 ind <- sum(arma[1L:3L]) + 1L:arma[4L]
      //                 if (all(mask[ind]))
      //                   coef[ind] <- maInvert(coef[ind])
      //               }
      //               if (any(coef[mask] != res$par)) {
      //                 oldcode <- res$convergence
      //                 res <- optim(coef[mask], armafn, method = "BFGS",
      //                              hessian = TRUE, control = list(maxit = 0L,
      //                                                             parscale = optim.control$parscale), trans = TRUE)
      //                 res$convergence <- oldcode
      //                 coef[mask] <- res$par
      //               }
      //               A <- .Call(stats:::C_ARIMA_Gradtrans, as.double(coef), arma)
      //                 A <- A[mask, mask]
      //               var <- crossprod(A, solve(res$hessian * n.used, A))
      //                 coef <- .Call(stats:::C_ARIMA_undoPars, coef, arma)
      //             }
      //             else var <- solve(res$hessian * n.used)
      //               trarma <- .Call(stats:::C_ARIMA_transPars, coef, arma, FALSE)
      //               mod <- makeARIMA(trarma[[1L]], trarma[[2L]], Delta, kappa,
      //                                SSinit)
      //               val <- if (ncxreg > 0L) {
      //                 arimaSS(x - xreg %*% coef[narma + (1L:ncxreg)], mod)
      //               } else arimaSS(x, mod)
      //                 sigma2 <- val[[1L]][1L]/n.used
    }
    //       value <- 2 * n.used * res$value + n.used + n.used * log(2 * pi)
    //         aic <- ifelse(method != "CSS", value + 2 * sum(mask) + 2, NA)
    //         resid <- val[[2L]]


  };
  forecast_result<U> predict(int h = 10, std::vector<std::vector<U>> newxreg = {{}}){
     // validate xreg length
     if( newxreg.size() != this->xreg.size() ) {
       return forecast_result<U>(0) ;
     }
     auto res = kalman_forecast(h, this-> structural_arma_model);
     auto xreg_adjusted = std::vector<U>(h);
     if( this->reg_coef.size() > 0 ) {
       // get the result of xreg regression
       xreg_adjusted = predict(this->reg_coef, newxreg);
     }
     res.forecast = xreg_adjusted + res.forecast;
     for( int i = 0; i < res.se.size(); i++ ) {
       res.se[i] = res.se[i] * this->sigma2;
     }
    return res;
  };
private:
  std::vector<U> y;
  std::vector<U> deltas;
  arima_kind kind;
  std::vector<U> residuals;
  std::vector<std::vector<U>> xreg;
  lm_coef<U> reg_coef;
  bool intercept;
  bool transform_parameters;
  SSinit ss_init;
  fitting_method method;
  U sigma2;
};

#endif
