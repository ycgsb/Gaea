#include "PolynomialRegressionTest.h"
#include "../dataset/DatasetRegression.h"
#include "../regression/PolynomialRegression.h"

#include <iostream>

namespace ycg {

void PolynomialRegressionTest::run() {
	DatasetRegression dataset("E:\\Dataset\\sin_train.txt");
	PolynomialRegressionConfig config;
	PolynomialRegression regression(dataset);
	regression.train();
	std::cout << "best coeff:" << regression.getCoefficient() << std::endl;
}

} //~ namespace ycg

