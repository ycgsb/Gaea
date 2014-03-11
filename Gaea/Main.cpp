//#include "cpp/recsys/RecSysLauncher.h"
#include "cpp/util/test/RandomTest.h"
#include <cstdio>

int main(int argc, char **argv) {
	try {
//		ycg::RecSysLauncher().launch();
		ycg::RandomTest().run();
	} catch (...) {
		printf("Error Occured\n");
	}
	return 0;
}

