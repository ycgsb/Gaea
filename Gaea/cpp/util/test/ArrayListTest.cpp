#include "ArrayListTest.h"
#include "../ArrayList.h"
#include "../../lang/String.h"
#include <cstdio>

namespace ycg {

ArrayListTest::ArrayListTest() {}

ArrayListTest::~ArrayListTest() { }

void ArrayListTest::run() {
	ArrayList<int> intList;
	for (int i = 0; i < 20; ++i) {
		intList.add(i);
	}
	for (int i = 0; i < intList.size(); ++i) {
		CHECK(intList.get(i) == i);
	}
	intList[1] = 42;

	ArrayList<String> stringList;
	for (int i = 0; i < 20; ++i) {
		stringList.add("abc");
	}
	for (int i = 0; i < intList.size(); ++i) {
		CHECK(stringList.get(i) == "abc");
	}
	stringList[0] = "def";
	printf("ArrayList Test Passed.\n");
}

}  //~ namespace ycg

