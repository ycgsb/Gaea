#include "ConcentricDataGenerator.h"
#include "../../util/Random.h"
#include "../../math/Math.h"
#include <algorithm>

namespace ycg {

const std::string ConcentricDataGenerator::HOME_DIR = "E:\\Dataset";
const int ConcentricDataGenerator::SAMPLE_NUM = 150;

ConcentricDataGenerator::ConcentricDataGenerator() { }

ConcentricDataGenerator::~ConcentricDataGenerator() { }

void ConcentricDataGenerator::run() {
	std::ofstream osTrain(HOME_DIR + "\\con_train.txt");
	std::ofstream osTest(HOME_DIR + "\\con_test.txt");
	osTrain.precision(6);
	osTrain.setf(std::ios::fixed, std::ios::floatfield);
	osTest.precision(6);
	osTest.setf(std::ios::fixed, std::ios::floatfield);
	generateTrainFile(osTrain);
	generateTestFile(osTest);
}

void ConcentricDataGenerator::generateTrainFile(std::ostream& os) {
	std::vector<Vector> posSamples(SAMPLE_NUM);
	std::generate(posSamples.begin(), posSamples.end(),
			[this](){ return this->generatePositiveSample(); });
	std::for_each(posSamples.begin(), posSamples.end(),
			[&os](const Vector& sample){ os << sample << "," << 1 << std::endl; });
	std::vector<Vector> negSamples(SAMPLE_NUM);
	std::generate(negSamples.begin(), negSamples.end(),
			[this](){ return this->generateNegativeSample(); });
	std::for_each(negSamples.begin(), negSamples.end(),
			[&os](const Vector& sample){ os << sample << "," << 0 << std::endl; });
}

void ConcentricDataGenerator::generateTestFile(std::ostream& os) {
	generateTrainFile(os);
}

Vector ConcentricDataGenerator::generatePositiveSample() {
	Random& rnd = Random::instance();
	double theta = rnd.uniform(0.0, 2 * Math::PI);
	double radius = rnd.uniform(0.0, 1.0);
	double x = radius * Math::cos(theta);
	double y = radius * Math::sin(theta);
	Vector point(2);
	point[0] = x;
	point[1] = y;
	return point;
}

Vector ConcentricDataGenerator::generateNegativeSample() {
	Random& rnd = Random::instance();
	double theta = rnd.uniform(0.0, 2 * Math::PI);
	double radius = rnd.uniform(1.0, 2.0);
	double x = radius * Math::cos(theta);
	double y = radius * Math::sin(theta);
	Vector point(2);
	point[0] = x;
	point[1] = y;
	return point;
}

} //~ namespace ycg
