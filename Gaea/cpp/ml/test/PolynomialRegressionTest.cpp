#include "PolynomialRegressionTest.h"
#include "../dataset/DatasetRegression.h"
#include "../regression/PolynomialRegression.h"

#include <iostream>

namespace ycg {

void PolynomialRegressionTest::run() {
	DatasetRegression dataset("E:\\Dataset\\sin_train.txt");
	PolynomialRegressionConfig config(3);
	PolynomialRegression regression(config, dataset);
	regression.train();
	std::cout << "best coeff:" << regression.getSolution() << std::endl;
}

} //~ namespace ycg

