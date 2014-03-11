#ifndef SORTTEST_H
#define SORTTEST_H

#include "../../../test/Test.h"

namespace ycg {

class SorterTest : public Test {
public:
	void run();
private:
	void testQuickSorter();
	void testQuickSorterMT();
	void testMergeSorter();
	void testCountingSorter();
	void testRandomizedSelector();
private:
	static const int MAX_N = 200000000;
};

} //~ namespace ycg

#endif /* SORTTEST_H */
