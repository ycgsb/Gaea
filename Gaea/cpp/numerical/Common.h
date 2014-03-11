#ifndef COMMON_H
#define COMMON_H

#include <cmath>

namespace ycg {

inline bool dblzero(double x, double eps = 1e-10) {
    return fabs(x) < eps;
}

inline bool dblEqual(double a, double b, double eps = 1e-10) {
    return fabs(a - b) < eps;
}

inline bool dblNotEqual(double a, double b, double eps = 1e-10) {
	return fabs(a - b) >= eps;
}

inline int dblcmp(double x, double eps = 1e-10) {
    if (fabs(x) < eps) {
        return 0;
    } else if (x > 0) {
        return 1;
    } else {
        return -1;
    }
}

enum { DECOMP_LU = 0, DECOMP_CHOLESKY = 1, DECOMP_SVD = 2};
} //~ namespace ycg




#endif /* COMMON_H */
