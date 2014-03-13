#include "PolynomialRegression.h"
#include "LinearRegression.h"

namespace ycg {

const PolynomialRegressionConfig PolynomialRegression::defaultConfig(1, false, 0.0,
		PolynomialRegressionConfig::CLOSED_FORM);

PolynomialRegression::PolynomialRegression(const DatasetRegression& dataset) :
	_dataset(dataset),
	_config(defaultConfig) { }

PolynomialRegression::PolynomialRegression(const DatasetRegression& dataset,
		const PolynomialRegressionConfig& config) :
	_dataset(dataset),
	_config(config) { }

PolynomialRegression::~PolynomialRegression() { }

void PolynomialRegression::train() {
	int dims = _config.order + 1;
	DatasetRegression datasetLR(dims);
	for (int i = 0; i < _dataset.samples(); ++i) {
		double x = _dataset.feature(i)[0];
		double y = _dataset.value(i);
		Vector feature(dims);
		feature[0] = 1.0;
		for (int p = 1; p < dims; ++p) {
			feature[p] = feature[p - 1] * x;
		}

	}
	_w = Vector(_config.order, 21.0);
}

Vector PolynomialRegression::getCoefficient() const {
	return _w;
}

double PolynomialRegression::predict() {
	return 0.0;
}

} //~ namespace ycg
