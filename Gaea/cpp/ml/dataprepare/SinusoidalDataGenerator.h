#ifndef SINUSOIDALDATAGENERATOR_H
#define SINUSOIDALDATAGENERATOR_H

#include <iostream>
#include <fstream>
#include <string>

namespace ycg {

class SinusoidalDataGenerator {
public:
	void run();
private:
	void generateTrainFile(std::ostream& os);
	void generateTestFile(std::ostream& os);
	double sinFun(double x);
private:
	static const std::string HOME_DIR;
	static const int TRAIN_SAMPLE_NUM;
	static const int TEST_SAMPLE_NUM;
	static const double NOISE_STD;
};


} //~ namespace ycg

#endif /* SINUSOIDALDATAGENERATOR_H */
