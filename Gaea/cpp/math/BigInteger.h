#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "../lang/Types.h"
#include "../io/OutputStream.h"

namespace ycg {

class BigInteger {
public:
	BigInteger();
	BigInteger(int val);
	BigInteger(const BigInteger& orig);
	BigInteger(BigInteger&& orig);
    virtual ~BigInteger();
    BigInteger& operator = (const BigInteger& big);
	friend BigInteger operator + (const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger operator * (const BigInteger& lhs, int rhs);
	friend BigInteger operator * (int lhs, const BigInteger& rhs);
	friend BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs);
	friend OutputStream& operator<< (OutputStream& os, const BigInteger& big);
public:
	static BigInteger ZERO;
	static BigInteger ONE;
private:
	BigInteger(uint32* numbers, int length);
	static void freeNumbers(uint32*& numbers);
private:
	static const int DIGIT_PER_NUMBER = 4;
	static const uint32 RADIX = 10000;
    int length;
	uint32* numbers;
};

} //~ namespace ycg

#endif /* BIGINTEGER_H_ */
