#ifndef CONCENTRICDATAGENERATOR_H
#define CONCENTRICDATAGENERATOR_H

#include "../../numerical/Vector.h"
namespace ycg {

class ConcentricDataGenerator {
public:
	void run();
private:
	Vector generatePositiveSample();
	Vector generateNegativeSample();
private:
	static const std::string HOME_DIR;
	static const int SAMPLE_NUM;
};

} //~ namespace ycg

#endif /* CONCENTRICDATAGENERATOR_H */
