#ifndef NUMBERTHEORY_H_
#define NUMBERTHEORY_H_

namespace ycg {

class NumberTheory {
public:
    static int gcd(int m, int n);
};

int NumberTheory::gcd(int m, int n) {
    if (m < n) {
        int tmp = m; m = n; n = tmp;
    }
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

//long long GCD(long long m, long long n) {
//	if (m < n) {
//		int tmp = m;
//		m = n;
//		n = tmp;
//	}
//	while (n != 0) {
//		int r = m % n;
//		m = n;
//		n = r;
//	}
//	return m;
//}

//long long LCM(long long m, long long n) {
//	return m * n / GCD(m,n);
//}

//int factorial(int n) {
//	int res = 1;
//	for (int i = 2; i <= n; ++i)
//		res *= i;
//	return res;
//}

//// 计算N！末尾零的个数
//int numberOfZerosAtEndOfFactorialN(int n) {
//	int zeros = 0;
//	while (n > 0) {
//		zeros += n / 5;
//		n /= 5;
//	}
//	return zeros;
//}

//// 使用欧拉函数，计算1，2，...，N-1这N-1个自然数中有多少个与N互质
//int numberOfPositiveIntegersLessThanAndRelativelyPrimeToN(int n) {
//	int count = n;
//	for(int i = 2; i*i <= n; i++) {
//		if (n%i == 0) {
//			count = (count/i)*(i-1);
//			while (n%i == 0)
//				n /= i;
//		}
//	}
//	if (n > 1)
//		count = (count/n)*(n-1);
//	return count;
//}

//// list[n]等于n！的最后一位非零数字，n=1,2,3,...MAX_N
//void lastNonZeroDigitListOfFactorialN(int list[], const int MAX_N) {
//	list[0] = list[1] = 1;
//	for(int n = 2; n <= MAX_N; ++n) {
//		int tmp = n;
//		list[n] = list[n-1];
//		while (tmp%5 == 0) {
//			tmp /= 5;
//			list[n] = (list[n] * 8) % 10;
//		}
//		list[n] = (list[n] * (tmp%10)) % 10;
//	}
//}

}  //~ namespace ycg


#endif /* NUMBERTHEORY_H_ */
