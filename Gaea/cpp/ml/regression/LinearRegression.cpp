#include "LinearRegression.h"
#include "../../math/Math.h"

namespace ycg {

const LinearRegressionConfig LinearRegression::_defaultConfig(false, 0.0, LinearRegressionConfig::METHOD_CLOSED_FORM);

LinearRegression::LinearRegression(const DatasetRegression& dataset) :
	_dataset(dataset),
	_config(_defaultConfig) { }

void ycg::LinearRegression::train() {

}

Vector ycg::LinearRegression::getW() const {
	return _coeff;
}

double ycg::LinearRegression::predict(const Vector& feature) {
	return 0.0;
}


double LinearRegression::computeDataError(const Vector& coeff) {
	int N = _dataset.samples();
	double error = 0.0;
	for (int i = 0; i < N; ++i) {
		double yp = coeff.dotProd(_dataset.feature(i));
		error += Math::sqr(yp-_dataset.value(i));
	}
	error /= N;
	return error;
}

} /* namespace ycg */
