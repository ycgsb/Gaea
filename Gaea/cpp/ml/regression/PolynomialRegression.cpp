#include "PolynomialRegression.h"
#include "LinearRegression.h"
#include <cassert>

namespace ycg {

PolynomialRegressionConfig::PolynomialRegressionConfig(int order,
		bool regNeeded, double regCoeff, OptimizeMethod method) {
	this->order = order;
	this->regNeeded = regNeeded;
	this->regCoeff = regCoeff;
	this->method = method;
}

PolynomialRegression::PolynomialRegression(const PolynomialRegressionConfig& config,
		const DatasetRegression& dataset) :
	_config(config),
	_dataset(dataset) {
	assert(_dataset.dims() == 1); // feature vector must be a single variable
}

PolynomialRegression::~PolynomialRegression() { }

void PolynomialRegression::train() {
	int dims = _config.order + 1;
	DatasetRegression datasetLR(dims);
	for (int i = 0; i < _dataset.samples(); ++i) {
		double x = _dataset.feature(i)(0);
		double y = _dataset.value(i);
		Vector feature(dims);
		feature[0] = 1.0;
		for (int p = 1; p < dims; ++p) {
			feature[p] = feature[p - 1] * x;
		}
		datasetLR.addSample(feature, y);
	}
	LinearRegressionConfig configLR(_config.regNeeded, _config.regCoeff, _config.method);
	LinearRegression LR(configLR, datasetLR);
	LR.train();
	_coeff = LR.getSolution();
}

Vector PolynomialRegression::getSolution() const {
	return _coeff;
}

double PolynomialRegression::predict(double x) {
	int dims = _config.order + 1;
	Vector feature(dims);
	feature[0] = 1.0;
	for (int p = 1; p < dims; ++p) {
		feature[p] = feature[p - 1] * x;
	}
	double predVal = _coeff.dotProd(feature);
	return predVal;
}

} //~ namespace ycg
