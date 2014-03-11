#ifndef COMMON_H
#define COMMON_H

#include <cmath>

namespace ycg {

inline double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

} //~ namespace ycg

#endif // COMMON_H
