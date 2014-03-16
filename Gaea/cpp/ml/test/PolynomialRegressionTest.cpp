#include "PolynomialRegressionTest.h"
#include <iostream>

namespace ycg {

void PolynomialRegressionTest::run() {
	DatasetRegression dataset("E:\\Dataset\\sin_train.txt");
	PolynomialRegressionConfig config(3, LinearRegressionConfig(false, 0.0, LinearRegressionConfig::CLOSED_FORM));
	PolynomialRegression regression(config, dataset);
	regression.train();
	std::cout << "model: " << regression.getSolution() << std::endl;
	DatasetRegression testset("E:\\Dataset\\sin_test.txt");
	double trainRMSE = computeRMSE(dataset, regression);
	double testRMSE = computeRMSE(testset, regression);
	std::cout << ""
}

double PolynomialRegressionTest::computeRMSE(const DatasetRegression& dataset,
		PolynomialRegression& regression) {
	double error = 0.0;
	for (int i = 0; i < dataset.samples(); ++i) {
	double real = dataset.value(i);
	double pred = regression.predict(dataset.feature(i)(0));
	trainRMSE
}

}

} //~ namespace ycg

