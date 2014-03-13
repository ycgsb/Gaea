#include "cpp/recsys/dataprepare/OcnDataPreparation.h"
#include "cpp/ml/test/PolynomialRegressionTest.h"
#include "cpp/ml/test/GradientDescentTest.h"
#include <cstdio>

int main(int argc, char **argv) {
	try {
//		ycg::RecSysLauncher().launch();
//		ycg::OcnDataPreparation().run();
//		ycg::PolynomialRegressionTest().run();
		ycg::GradientDescentTest().run();
	} catch (...) {
		printf("Error Occured\n");
	}
	return 0;
}

