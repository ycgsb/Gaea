#ifndef RANDOMTEST_H
#define RANDOMTEST_H

#include "../../test/Test.h"

namespace ycg {

class RandomTest : public Test {
public:
	void run();
private:
	void testUniform();
	void testGauss();
private:
	static const int BIG_NUM = 10000000;
};

} //~ namespace ycg

#endif /* RANDOMTEST_H */
