#include "SorterTest.h"
#include "../QuickSorter.h"
#include "../QuickSorterMT.h"
#include "../MergeSorter.h"
#include "../CountingSorter.h"
#include "../../../util/Pair.h"
#include "../Comparator.h"
#include "../RandomizedSelector.h"
#include "../../../util/Random.h"
#include "../../../time/Stopwatch.h"
#include <cstdio>
#include <cassert>
#include <algorithm>

namespace ycg {

void SorterTest::run() {
//	testQuickSorter();
	testQuickSorterMT();
//	testMergeSorter();
//	testCountingSorter();
//	testRandomizedSelector();
}

void SorterTest::testQuickSorter() {
	QuickSorter qsort;
	Random& rnd = Random::instance();
	int n = MAX_N;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		array[i] = i;
	}
	rnd.shuffle(array, n);
	Stopwatch sw;
	sw.start();
	qsort(array, n);
	printf("quicksort %d ints, time = %dms.\n", n, sw.stop().elapsedMilliseconds());
	for (int i = 1; i < n; ++i) {
		CHECK(array[i-1] <= array[i]);
	}
	rnd.shuffle(array, n);
	sw.start();
	qsort(array, n, [=](int a, int b){return b-a;});
	printf("quicksort %d ints, time = %dms.\n", n, sw.stop().elapsedMilliseconds());
	for (int i = 1; i < n; ++i) {
		CHECK(array[i-1] >= array[i]);
	}
	delete []array;
	printf("cpp/algorithms/sort/QuickSorter---pass.\n");
}

void SorterTest::testQuickSorterMT() {
	QuickSorterMT qsort;
	Random& rnd = Random::instance();
	int n = MAX_N;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		array[i] = i;
	}
	rnd.shuffle(array, n);
	Stopwatch sw;
	sw.start();
	qsort(array, n);
	printf("quicksort MT %d ints, time = %dms.\n", n, sw.stop().elapsedMilliseconds());
	for (int i = 1; i < n; ++i) {
		CHECK(array[i-1] <= array[i]);
	}
	rnd.shuffle(array, n);
	sw.start();
	qsort(array, n, [=](int a, int b){return b-a;});
	printf("quicksort MT %d ints, time = %dms.\n", n, sw.stop().elapsedMilliseconds());
	for (int i = 1; i < n; ++i) {
		CHECK(array[i-1] >= array[i]);
	}
	delete []array;
	printf("cpp/algorithms/sort/QuickSorterMT---pass.\n");
}

void SorterTest::testMergeSorter() {
	MergeSorter msort;
	Random& rnd = Random::instance();
	int n = 5000000;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		array[i] = i;
	}
	rnd.shuffle(array, n);
	Stopwatch sw;
	sw.start();
	msort(array, n);
	printf("merge sort %d ints, time = %dms.\n", n, sw.stop().elapsedMilliseconds());
	for (int i = 1; i < n; ++i) {
		CHECK(array[i-1] <= array[i]);
	}
	rnd.shuffle(array, n);
	sw.start();
	msort(array, n, [=](int a, int b){return b-a;});
	printf("merge sort %d ints, time = %dms.\n", n, sw.stop().elapsedMilliseconds());
	for (int i = 1; i < n; ++i) {
		CHECK(array[i-1] >= array[i]);
	}
	delete []array;
	printf("cpp/algorithms/sort/MergeSorter---pass.\n");
}

void SorterTest::testCountingSorter() {
	int size = 100;
	IntPair *array = new IntPair[size];
	for (int i = 0, k = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			array[k].setFirst(i);
			array[k].setSecond(j);
			++k;
		}
	}
	Random::instance().shuffle(array, size);
	CountingSorter<IntPair> sort;
	sort(array, size, [&](const IntPair& p)->int{ return p.second(); }, 20);
	sort(array, size, [&](const IntPair& p)->int{ return p.first(); }, 20);
	for (int i = 0, k = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			CHECK(array[k].first() == i);
			CHECK(array[k].second() == j);
			++k;
		}
	}
	delete []array;
	printf("cpp/algorithms/sort/CountingSorter---pass.\n");
}

void SorterTest::testRandomizedSelector() {
	int n = 1000;
	int k = 32;
	int *array = new int[n];
	for (int i = 0; i < n; ++i) {
		array[i] = i;
	}
	RandomizedSelector<int> select;
	Random::instance().shuffle(array, n);
	select(array, n, k);
	CHECK(array[k] == k);
	for (int i = 0; i < k; ++i) {
		CHECK(array[i] < array[k]);
	}
	Random::instance().shuffle(array, n);
	select(array, n, k, ComparatorGreater<int>());
	CHECK(array[k] == n-k-1);
	for (int i = 0; i < k; ++i) {
		CHECK(array[i] > array[k]);
	}
	delete []array;
	printf("cpp/algorithms/sort/RandomizedSelector---pass.\n");
}
} //~ namespace ycg
