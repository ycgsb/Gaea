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
	PolynomialRegressionConfig() : order(0), regNeeded(false), regCoeff(0.0), method(CLOSED_FORM) { }
	PolynomialRegressionConfig(int order, bool regNeeded, double regCoeff, OptimizeMethod method) {
		this->order = order;
		this->regNeeded = regNeeded;
		this->regCoeff = regCoeff;
		this->method = method;
	}
public:
	int order;
	bool regNeeded;
	double regCoeff;
	OptimizeMethod method;
};

class PolynomialRegression {
public:
	PolynomialRegression(const DatasetRegression& dataset);
	PolynomialRegression(const DatasetRegression& dataset, const PolynomialRegressionConfig& config);
	virtual ~PolynomialRegression();
	void train();
	Vector getCoefficient() const;
	double predict();
private:
	DatasetRegression generateLinearRegressionDataset();
private:
	static const PolynomialRegressionConfig defaultConfig;
	const PolynomialRegressionConfig& _config;
	const DatasetRegression& _dataset;
	Vector _w;
};

} //~ namespace ycg

#endif /* POLYNOMIALREGRESSION_H */
