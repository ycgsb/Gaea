#include "LinearRegression.h"
#include "../../math/Math.h"

namespace ycg {

LinearRegressionConfig::LinearRegressionConfig(bool regNeeded,
		double regCoeff, OptimizeMethod method) {
	this->regNeeded = regNeeded;
	this->regCoeff = regCoeff;
	this->method = method;
}

LinearRegression::LinearRegression(const LinearRegressionConfig& config,
		const DatasetRegression& dataset) :
	_config(config),
	_dataset(dataset) { }


void LinearRegression::train() {
	switch (_config.method) {
		case LinearRegressionConfig::CLOSED_FORM:
			computeSolutionByCloseForm();
			break;
		case LinearRegressionConfig::GRADIENT_DESCENT:
			computeSolutionByGradientDescent();
		default:
			break;
	}
}

void ycg::LinearRegression::computeSolutionByCloseForm() {
	Matrix X = _dataset.getDesignMatrix();
	Vector Y = _dataset.getTargetVector();
	inv(X.T()*X)*X.T()*t;

}

void ycg::LinearRegression::computeSolutionByGradientDescent() {
}

Vector LinearRegression::getSolution() const {
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

} //~ namespace ycg
