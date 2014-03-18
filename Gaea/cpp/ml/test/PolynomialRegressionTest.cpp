#include "PolynomialRegressionTest.h"
#include "../../math/Math.h"
#include <iostream>

namespace ycg {

void PolynomialRegressionTest::run() {
	DatasetRegression dataset("E:\\Dataset\\sin_train.txt");
	PolynomialRegressionConfig config(9, LinearRegressionConfig(true,
			0.0001, LinearRegressionConfig::CLOSED_FORM));
	PolynomialRegression regression(config, dataset);
	regression.train();
	std::cout << "model: " << regression.getSolution() << std::endl;
	DatasetRegression testset("E:\\Dataset\\sin_test.txt");
	double trainError = computeRMSE(dataset, regression);
	double testError = computeRMSE(testset, regression);
	std::cout << "training error in RMSE = " << trainError << std::endl;
	std::cout << "testing error in RMSE = " << testError << std::endl;
}

double PolynomialRegressionTest::computeRMSE(const DatasetRegression& dataset,
		PolynomialRegression& regression) {
	int n = dataset.samples();
	double error = 0.0;
	for (int i = 0; i < n; ++i) {
		double real = dataset.value(i);
		double pred = regression.predict(dataset.feature(i)(0));
		error += Math::sqr(pred-real);
	}
	error = Math::sqrt(error / n);
	return error;
}

} //~ namespace ycg
