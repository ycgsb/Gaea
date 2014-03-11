#ifndef CONCENTRICDATAGENERATOR_H
#define CONCENTRICDATAGENERATOR_H

#include "../../numerical/Vector.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace ycg {

class ConcentricDataGenerator {
public:
	ConcentricDataGenerator();
	virtual ~ConcentricDataGenerator();
	void run();
private:
	void generateTrainFile(std::ostream& os);
	void generateTestFile(std::ostream& os);
	Vector generatePositiveSample();
	Vector generateNegativeSample();
private:
	static const std::string HOME_DIR;
	static const int SAMPLE_NUM;
};

} //~ namespace ycg

#endif /* CONCENTRICDATAGENERATOR_H */
