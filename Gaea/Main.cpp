//#include "cpp/recsys/RecSysLauncher.h"
#include "cpp/ml/dataprepare/ConcentricDataGenerator.h"
#include <cstdio>

int main(int argc, char **argv) {
	try {
//		ycg::RecSysLauncher().launch();
//		ycg::SinusoidalDataGenerator().run();
		ycg::ConcentricDataGenerator().run();
	} catch (...) {
		printf("Error Occured\n");
	}
	return 0;
}

