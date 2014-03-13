//#include "cpp/recsys/RecSysLauncher.h"
#include "cpp/recsys/dataprepare/OcnDataPreparation.h"
#include "cpp/lang/test/StringTest.h"
#include <cstdio>

int main(int argc, char **argv) {
	try {
//		ycg::RecSysLauncher().launch();
//		ycg::SinusoidalDataGenerator().run();
//		ycg::ConcentricDataGenerator().run();
		ycg::OcnDataPreparation().run();
//		ycg::StringTest().run();
	} catch (...) {
		printf("Error Occured\n");
	}
	return 0;
}

