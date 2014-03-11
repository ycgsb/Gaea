#include "BigInteger.h"
#include "Math.h"
#include <cstdio>
#include <cassert>

namespace ycg {

BigInteger::BigInteger() {
	length = 1;
	numbers = new uint32[1];
    numbers[0] = 0;
}

BigInteger::BigInteger(int val) {
	assert(val >= 0);
	uint32 temp[4];
	int count = 0;
	while (val > 0) {
		temp[count] = val % RADIX;
		val /= RADIX;
		count++;
	}
	length = count;
	numbers = new uint32[length];
    for (int i = 0; i < length; ++i) {
    	numbers[i] = temp[i];
    }
}

BigInteger::BigInteger(const BigInteger& big) {
    length = big.length;
	numbers = new uint32[length];
	for(int i = 0; i < length; ++i) {
		numbers[i] = big.numbers[i];
	}
}

BigInteger::BigInteger(BigInteger&& orig) {
	length = orig.length;
	numbers = orig.numbers;
	orig.numbers = nullptr;
}

BigInteger::BigInteger(uint32* numbers, int length) {
	this->length = length;
	this->numbers = numbers;
}

BigInteger::~BigInteger(){
    freeNumbers(numbers);
}

void BigInteger::freeNumbers(uint32*& numbers) {
	delete []numbers;
	numbers = nullptr;
}

BigInteger& BigInteger::operator = (const BigInteger& big) {
	if (this == &big) {
		return *this;
	}
	freeNumbers(numbers);
	length = big.length;
	numbers = new uint32[length];
	for(int i = 0; i < length; ++i) {
		numbers[i] = big.numbers[i];
	}
	return *this;
}

BigInteger operator + (const BigInteger& lhs, const BigInteger& rhs) {
	int maxLength = Math::max(lhs.length, rhs.length);
	int minLength = Math::min(lhs.length, rhs.length);
	uint32* sum = new uint32[maxLength + 1];
	uint32 carry = 0;
	for(int i = 0; i < minLength; ++i) {
		sum[i] = lhs.numbers[i] + rhs.numbers[i] + carry;
		carry = sum[i] / BigInteger::RADIX;
		sum[i] %= BigInteger::RADIX;
	}
	if (minLength < maxLength) {
		uint32* remain = (lhs.length > minLength) ? lhs.numbers: rhs.numbers;
		for(int i = minLength; i < maxLength; ++i)	{
			sum[i] = remain[i] + carry;
			carry = sum[i] / BigInteger::RADIX;
			sum[i] %= BigInteger::RADIX;
		}
	}
	int length = maxLength;
	if (carry != 0) {
		sum[maxLength] = carry;
		length++;
	}
	return BigInteger(sum, length);
}

BigInteger operator * (const BigInteger& lhs, int rhs) {
//	assert(rhs >= 0 && rhs < BigInteger::RADIX);
	int length = lhs.length;
	uint32* prod = new uint32[length + 1];
	uint32 carry = 0;
	for(int i = 0; i < length; ++i) {
		prod[i] = lhs.numbers[i] * rhs + carry;
		carry = prod[i] / BigInteger::RADIX;
		prod[i] %= BigInteger::RADIX;
	}
	if (carry != 0) {
		prod[length] = carry;
		length++;
	}
	return BigInteger(prod, length);
}

BigInteger operator * (int lhs, const BigInteger& rhs) {
	return rhs * lhs;
}

BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs) {
	return BigInteger::ONE;
}

OutputStream& operator<< (OutputStream& os, const BigInteger& big) {
	int length = big.length;
	os << big.numbers[length - 1];
	for(int i = length - 2; i >= 0; --i) {
		for(uint32 r = BigInteger::RADIX / 10; r >= 10; r /= 10) {
			if(big.numbers[i] < r) {
				os << '0';
			}
		}
		os << big.numbers[i];
	}
	return os;
}

BigInteger BigInteger::ZERO = BigInteger(0);
BigInteger BigInteger::ONE = BigInteger(1);


//BigInteger::BigInteger(const string& Str) {
//    int n = Str.length();
//	digits = new uint32[(n + NUMLEN - 1) / NUMLEN];
//	digitNum = 0;
//    for(int i = n - 1; i >= 0;)
//    {
//        int weight = 1, temp = 0;
//        while(weight < RADIX && i >= 0)
//		{
//			temp += (Str[i] - '0') * weight;
//			weight *= 10;
//			--i;
//		}
//		digits[digitNum++] = temp;
//    }
//	while(digits[digitNum - 1] == 0)--digitNum;
//}

} //~ namespace ycg
