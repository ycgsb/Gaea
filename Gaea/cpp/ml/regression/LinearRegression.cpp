#include "LinearRegression.h"
#include "../util/GradientDescent.h"
#include "../../numerical/Exception.h"
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
			break;
		default:
			throw UnsupportMethodException();
	}
}

void LinearRegression::computeSolutionByCloseForm() {
	Matrix X = _dataset.getDesignMatrix();
	Vector t = _dataset.getTargetVector();
	if (!_config.regNeeded) {
		_coeff = (X.T()*X).inv()*X.T()*t;
	} else {
		double lambda = _config.regCoeff;
		_coeff = (X.T()*X + lambda*Matrix::eye(X.rows()))
				.inv()*X.T()*t;
	}
}

void LinearRegression::computeSolutionByGradientDescent() {
	GradientDescentConfig config(0.05, 1000000, 0.00001, true);
	GradientDescent gd(config);
	Vector init(_dataset.dims(), 0.0);
	Matrix X = _dataset.getDesignMatrix();
	Vector t = _dataset.getTargetVector();
	if (!_config.regNeeded) {
		_coeff = gd.compute(init,
			[&X, &t](const Vector& w) -> double {
				double eng = normL2Sqr(t-X*w) / (2.0*X.rows());
				return eng;
			},
			[&X, &t](const Vector& w) -> Vector{
				Matrix residual(t-X*w);
				Vector grad = -residual.T()*X;
				return grad;
			});
	} else {
		double lambda = _config.regCoeff;
		_coeff = gd.compute(init,
			[=, &X, &t](const Vector& w) -> double {
				double eng = normL2Sqr(t-X*w) / (2.0*X.rows())
						+ lambda / 2.0 *normL2Sqr(w);
				return eng;
			},
			[=, &X, &t](const Vector& w) -> Vector {
				Matrix residual(t-X*w);
				Vector grad = -residual.T()*X + lambda*w;
				return grad;
			});
	}
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
