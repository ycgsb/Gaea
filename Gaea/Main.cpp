//#include "cpp/recsys/RecSysLauncher.h"
#include "cpp/recsys/dataprepare/OcnDataPreparation.h"
#include <cstdio>

int main(int argc, char **argv) {
	try {
//		ycg::RecSysLauncher().launch();
//		ycg::SinusoidalDataGenerator().run();
//		ycg::ConcentricDataGenerator().run();
		ycg::OcnDataPreparation().run();
	} catch (...) {
		printf("Error Occured\n");
	}
	return 0;
}

