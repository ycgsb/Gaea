#ifndef POLYNOMIALREGRESSION_H
#define POLYNOMIALREGRESSION_H

#include "LinearRegression.h"

namespace ycg {

class PolynomialRegressionConfig {
public:
	PolynomialRegressionConfig(int order, LinearRegressionConfig configLR);
public:
	int order;
	LinearRegressionConfig configLR;
};

class PolynomialRegression {
public:
	PolynomialRegression(const PolynomialRegressionConfig& config, const DatasetRegression& dataset);
	virtual ~PolynomialRegression();
	void train();
	Vector getSolution() const;
	double predict(double x);
private:
	DatasetRegression generateLinearRegressionDataset();
private:
	const PolynomialRegressionConfig& _config;
	const DatasetRegression& _dataset;
	Vector _coeff;
};

} //~ namespace ycg

#endif /* POLYNOMIALREGRESSION_H */
