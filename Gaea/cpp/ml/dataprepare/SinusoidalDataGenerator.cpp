#include "SinusoidalDataGenerator.h"
#include "../../math/Math.h"
#include "../../util/Random.h"
#include <vector>

namespace ycg {

const std::string SinusoidalDataGenerator::HOME_DIR = "E:\\Dataset";
const int SinusoidalDataGenerator::TRAIN_SAMPLE_NUM = 10;
const int SinusoidalDataGenerator::TEST_SAMPLE_NUM = 100;
const double SinusoidalDataGenerator::NOISE_STD = 0.05;

SinusoidalDataGenerator::SinusoidalDataGenerator() {}

SinusoidalDataGenerator::~SinusoidalDataGenerator() {}

void SinusoidalDataGenerator::run() {
	std::ofstream foutTrain(HOME_DIR + "\\sin_train.txt");
	std::ofstream foutTest(HOME_DIR + "\\sin_test.txt");
	foutTrain.precision(6);
	foutTrain.setf(std::ios::fixed, std::ios::floatfield);
	foutTest.precision(6);
	foutTest.setf(std::ios::fixed, std::ios::floatfield);
	generateTrainFile(foutTrain);
	generateTestFile(foutTest);
}

void SinusoidalDataGenerator::generateTrainFile(std::ostream& os) {
	Random& rnd = Random::instance();
	for (int i = 0; i < TRAIN_SAMPLE_NUM; ++i) {
		double x = 1.0 / (TRAIN_SAMPLE_NUM - 1)*i;
		double y = sinFun(x) + rnd.gauss(0.0, NOISE_STD);
		os << x << " " << y << std::endl;
	}
}

void SinusoidalDataGenerator::generateTestFile(std::ostream& os) {
	Random& rnd = Random::instance();
	for (int i = 0; i < TEST_SAMPLE_NUM; ++i) {
		double x = rnd.uniform(0.0, 1.0);
		double y = sinFun(x);
		os << x << " " << y << std::endl;
	}
}

double SinusoidalDataGenerator::sinFun(double x) {
	return Math::sin(2.0*Math::PI*x);
}

} //~ namespace ycg
