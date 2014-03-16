#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "../dataset/DatasetRegression.h"
#include "../../numerical/Vector.h"

namespace ycg {

class LinearRegressionConfig {
public:
	enum OptimizeMethod {
		CLOSED_FORM, GRADIENT_DESCENT
	};
	LinearRegressionConfig(bool regNeeded = false, double regCoeff = 0.0,
			OptimizeMethod method = CLOSED_FORM);
public:
	bool regNeeded;
	double regCoeff;
	OptimizeMethod method;
};

class LinearRegression {
public:
	LinearRegression(const LinearRegressionConfig& config, const DatasetRegression& dataset);
	virtual ~LinearRegression() {}
	void train();
	Vector getSolution() const;
	double predict(const Vector& feature);
private:
	double computeDataError(const Vector& coeff);
private:
	const LinearRegressionConfig& _config;
	const DatasetRegression& _dataset;

	Vector _coeff;
};

} //~ namespace ycg

#endif /* LINEARREGRESSION_H_ */
