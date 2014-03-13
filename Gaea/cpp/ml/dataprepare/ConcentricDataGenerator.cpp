#include "ConcentricDataGenerator.h"
#include "../../util/Random.h"
#include "../../math/Math.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

namespace ycg {

const std::string ConcentricDataGenerator::HOME_DIR = "E:\\Dataset";
const int ConcentricDataGenerator::SAMPLE_NUM = 300;

void ConcentricDataGenerator::run() {
	std::ofstream osTrain(HOME_DIR + "\\concentric.txt");
	osTrain.precision(6);
	osTrain.setf(std::ios::fixed, std::ios::floatfield);
	std::vector<Vector> posSamples(SAMPLE_NUM);
	std::vector<Vector> negSamples(SAMPLE_NUM);
	std::generate(posSamples.begin(), posSamples.end(),
			[this](){ return this->generatePositiveSample(); });
	std::generate(negSamples.begin(), negSamples.end(),
			[this](){ return this->generateNegativeSample(); });
	for (int i = 0; i < SAMPLE_NUM; ++i) {
		osTrain << posSamples[i] << "," << 1 << "\n";
		osTrain << negSamples[i] << "," << 0 << "\n";
	}
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
