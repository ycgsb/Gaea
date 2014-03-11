#include "RandomTest.h"
#include "../Random.h"
#include "../../math/Math.h"
#include <vector>

namespace ycg {

void RandomTest::run() {
	testUniformInt();
	testUniformDouble();
	testGaussStandard();
	testGauss();
}

void RandomTest::testUniformInt() {
	printf("test uniform int:\n");
	Random& rnd = Random::instance();
	int a = 10, b = 200;
	double mean = (a+b)/2;
	double var = Math::sqr(a-b)/12;
	std::vector<int> numbers;
	for (int i = 0; i < BIG; ++i) {
		numbers.push_back(rnd.uniform(a, b));
	}
	double meanData = Math::mean(numbers.cbegin(), numbers.cend());
	double varData = Math::var(numbers.cbegin(), numbers.cend());
	printf("mean = %lf, meanData = %lf\n", mean, meanData);
	printf("var = %lf, varData = %lf\n", var, varData);
}

void RandomTest::testUniformDouble() {
	printf("test uniform double:\n");
	Random& rnd = Random::instance();
	double a = 1.0, b = 20.0;
	double mean = (a + b) / 2;
	double var = Math::sqr(a - b) / 12;
	std::vector<double> numbers;
	for (int i = 0; i < BIG; ++i) {
		numbers.push_back(rnd.uniform(a, b));
	}
	double meanData = Math::mean(numbers.cbegin(), numbers.cend());
	double varData = Math::var(numbers.cbegin(), numbers.cend());
	printf("mean = %lf, meanData = %lf\n", mean, meanData);
	printf("var = %lf, varData = %lf\n", var, varData);
}

void RandomTest::testGaussStandard() {
	printf("test uniform random generator.\n");
	Random& rnd = Random::instance();
	std::vector<double> numbers;
	for (int i = 0; i < BIG; ++i) {
		numbers.push_back(rnd.gauss());
	}
	double meanData = Math::mean(numbers.cbegin(), numbers.cend());
	double stdData = Math::std(numbers.cbegin(), numbers.cend());
	printf("mean = %lf, meanData = %lf\n", 0.0, meanData);
	printf("std = %lf, stdData = %lf\n", 1.0, stdData);

}

void RandomTest::testGauss() {
	printf("test uniform random generator.\n");
	Random& rnd = Random::instance();
	double mean = 10.0;
	double std = 2.0;
	std::vector<double> numbers;
	for (int i = 0; i < BIG; ++i) {
		numbers.push_back(rnd.gauss(mean, std));
	}
	double meanData = Math::mean(numbers.cbegin(), numbers.cend());
	double stdData = Math::std(numbers.cbegin(), numbers.cend());
	printf("mean = %lf, meanData = %lf\n", mean, meanData);
	printf("std = %lf, stdData = %lf\n", std, stdData);

}
} //~ namespace ycg

