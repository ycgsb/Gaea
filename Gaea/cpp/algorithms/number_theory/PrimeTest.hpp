#ifndef PRIME_TEST_HPP
#define PRIME_TEST_HPP

namespace ycg {

class PrimeTest {
public:
	bool isPrime(int num) {
		if(num <= 1) return false;
		if(num == 2) return true;
		if((num & 1) == 0) return false;
		int sqrtNum = (int)sqrt(num);
		for(int t = 3; t <= sqrtNum; t += 2)
			if(num % t == 0) {
				return false;
			}
		return true;
	}
};

} //~ namespace ycg

#endif // PRIME_TEST_HPP
