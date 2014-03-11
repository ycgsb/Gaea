#include "BinaryHeapTest.h"
#include "../BinaryHeap.h"
#include "../../../util/Random.h"
#include <cstdio>

namespace ycg {

void BinaryHeapTest::run() {
	int n = 1234;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		array[i] = i;
	}
	Random::instance().shuffle(array, n);
	MaxBinaryHeap<int> heap1(n);
	for (int i = 0; i < n; ++i) {
		heap1.add(array[i]);
	}
	CHECK(heap1.size() == n);
	CHECK(heap1.max() == n-1);
	for (int i = n-1; i >= 0; --i) {
		CHECK(heap1.extract() == i);
	}
	CHECK(heap1.size() == 0);
	MinBinaryHeap<int> heap2(2*n, array, n);
	CHECK(heap2.min() == 0);
	for (int i = 0; i < n; ++i) {
		CHECK(heap2.extract() == i);
		heap2.add(n);
	}
	CHECK(heap2.top()==n);
	delete []array;
	printf("BinaryHeapTest pass.\n");
}

} //~ namespace ycg
