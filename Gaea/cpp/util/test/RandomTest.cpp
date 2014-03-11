#include "RandomTest.h"
#include "../Random.h"
#include "../../math/Math.h"
#include <vector>

namespace ycg {

void RandomTest::run() {
	testUniform();
	testGauss();
}

void RandomTest::testUniform() {
	printf("test uniform random generator.\n");
	Random& rnd = Random::instance();
	int a = 10, b = 200;
	std::vector<int> numbers;
	for (int i = 0; i < BIG_NUM; ++i) {
		numbers.push_back(rnd.uniform(a, b));
	}
	double mean_gt = (a+b)/2;
	double mean = Math::mean(numbers.cbegin(), numbers.cend());
	double var_gt = Math::sqr(a-b)/12;
	double var = Math::var(numbers.cbegin(), numbers.cend());
	printf("mean_gt = %lf, mean = %lf\n",mean_gt, mean);
	printf("var_gt = %lf, var = %lf\n",var_gt, var);
}

void RandomTest::testGauss() {
	printf("test uniform random generator.\n");
	Random& rnd = Random::instance();
	int a = 10, b = 200;
	std::vector<int> numbers;
	for (int i = 0; i < BIG_NUM; ++i) {
		numbers.push_back(rnd.uniform(a, b));
	}
	double mean_gt = (a+b)/2;
	double mean = Math::mean(numbers.cbegin(), numbers.cend());
	double var_gt = Math::sqr(a-b)/12;
	double var = Math::var(numbers.cbegin(), numbers.cend());
	printf("mean_gt = %lf, mean = %lf\n",mean_gt, mean);
	printf("var_gt = %lf, var = %lf\n",var_gt, var);

}
} //~ namespace ycg

