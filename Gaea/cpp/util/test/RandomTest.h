#ifndef RANDOMTEST_H
#define RANDOMTEST_H

#include "../../test/Test.h"

namespace ycg {

class RandomTest : public Test {
public:
	void run();
private:
	void testUniformInt();
	void testUniformDouble();
	void testGaussStandard();
	void testGauss();
private:
	static const int BIG = 10000000;
};

} //~ namespace ycg

#endif /* RANDOMTEST_H */
