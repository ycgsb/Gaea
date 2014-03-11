#include "BinarySearchTest.h"
#include "../BinarySearch.h"
#include "../../../util/Pair.h"
#include <cstdio>

namespace ycg {

void BinarySearchTest::run() {
	int n = 1000;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		array[i] = i*2;
	}
	BinarySearch bsearch;
	for (int i = 0; i < n; ++i) {
		int pos1 = bsearch(i*2, array, n);
		CHECK(pos1 == i);
		int pos2 = bsearch(i*2+1, array, n);
		CHECK(pos2 == -1);
	}
	delete []array;
	IntPair *brray = new IntPair[n];
	for (int i = 0; i < n; ++i) {
		brray[i].setFirst(i*3);
		brray[i].setSecond(i*3+1);
	}
	for (int i = 0; i< n; ++i) {
		int pos = bsearch(i*3, brray, n, [&](const int& lhs, const IntPair& rhs) { return lhs - rhs.first();});
		CHECK(pos == i);
	}
	printf("cpp/algorithms/search/BinarySearch---pass.\n");
}

} //~ namespace ycg

