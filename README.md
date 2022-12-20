
<!-- README.md is generated from README.Rmd. Please edit that file -->

# blazearima

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![R-CMD-check](https://github.com/JSzitas/fasttbats/workflows/R-CMD-check/badge.svg)](https://github.com/JSzitas/fasttbats/actions)
<!-- badges: end -->

An intentionally very fast (S)ARIMA(X) implementation. Any major
difference as compared to the **R** `arima()` function may be considered
a bug.

# Thanks, recognition

This package really follows the ‘I stand on the shoulders of giants’
idea. It would have never been possible without all the careful work put
into R’s `arima()` implementation done by many member of the R Core Team
and others over the years. I do believe professor Ripley is of
particular note here, and deserves recognition for being one of the
driving forces behind such an awesome project.

I further want to thank the authors of the awesome **Eigen** C++
template library. This library is one of the silent drivers of much of
this computation, particularly the handling of external variables.

Finally, last but not least, I believe the many people who contributed
to the great **CppNumericalSolvers** library deserve recognition. This
is the library used for optimization in this package, and it’s
relatively straightforward implementation has been a huge boon.
