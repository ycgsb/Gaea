#ifndef POLYNOMIALREGRESSION_H
#define POLYNOMIALREGRESSION_H

#include "../dataset/DatasetRegression.h"
#include "../../numerical/Vector.h"

namespace ycg {

class PolynomialRegressionConfig {
public:
	enum OptimizeMethod {
		CLOSED_FORM, GRADIENT_DESCENT
	};
	PolynomialRegressionConfig(int order, bool regNeeded = false,
			double regCoeff = 0.0, OptimizeMethod method = CLOSED_FORM);
public:
	int order;
	bool regNeeded;
	double regCoeff;
	OptimizeMethod method;
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
