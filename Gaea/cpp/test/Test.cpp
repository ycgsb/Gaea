#include "Test.h"
#include <cstdio>
#include <cstdlib>

namespace ycg {

Test::Test() { }

Test::~Test() { }

void Test::checkCondition(bool requirement, const char* exper, int lineNo, const char *filename) {
	if (!requirement) {
		fprintf(stderr, "Test failed at condition: %s", exper);
		if (filename != nullptr) {
			fprintf(stderr, ", file %s", filename);
		}
		if (lineNo >= 0) {
			fprintf(stderr, ", line %d", lineNo);
		}
		fprintf(stderr, "\n");
		exit(1);
	}
}

} /* namespace ycg */
