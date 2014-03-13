#include "LinearRegression.h"

namespace ycg {

void ycg::LinearRegression::train() {

}

Vector ycg::LinearRegression::getW() const {
	return _coeff;
}

double ycg::LinearRegression::predict(const Vector& feature) {
	return 0.0;
}

double LinearRegression::computeDataError(const Vector& coeff) {
	for (int i = 0; i < _dataset.samples(); ++i) {
		double yp = coeff.dotProd(_dataset.feature(i));
		double error = Math::sqr(yp-_dataset.value(i));
	}
}

} /* namespace ycg */
