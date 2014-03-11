#include "VectorTest.h"
#include "../Vector.h"
#include <cstdio>

namespace ycg {

VectorTest::VectorTest() { }

VectorTest::~VectorTest() { }

void VectorTest::run() {
	Vector v1;
	Vector v2(3);
	Vector v3(3, 1.0);
	Vector v4(3, false);
	Vector v5 = v3;
	v1 = v2;
	print(v3);
	printf("Vector Test passed.\n");
}

} /* namespace ycg */
