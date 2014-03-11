#include "Fibonacci.h"

namespace ycg {

BigInteger Fibonacci::fib(int n) {
	BigInteger f0 = 0, f1 = 1;
	for (int i = 2; i <= n; ++i) {
		BigInteger f2 = f0 + f1;
		f0 = f1;
		f1 = f2;
	}
	return f1;
}

} //~ namespace ycg
