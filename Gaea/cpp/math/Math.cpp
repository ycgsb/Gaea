#include "Math.h"

namespace ycg {

int Math::sum(const int* a, int length) {
    int sum = a[0];
    for (int i = 1; i < length; ++i)
        sum += a[i];
    return sum;
}

int Math::power(int x, int p) {
	int result = 1;
	for (int j = 0; j < p; ++j) {
		result *= x;
	}
	return result;
}

} //~ namespace ycg



