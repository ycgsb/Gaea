#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "../dataset/DatasetRegression.h"
#include "../../numerical/Vector.h"

namespace ycg {

class LinearRegressionConfig {
public:
	enum OptimizeMethod {
		METHOD_CLOSED_FORM, METHOD_GRADIENT_DESCENT
	};
	LinearRegressionConfig(bool regNeeded, double regCoeff, OptimizeMethod method) {
		this->regNeeded = regNeeded;
		this->regCoeff = regCoeff;
		this->method = method;
	}
public:
	bool regNeeded;
	double regCoeff;
	OptimizeMethod method;
};

class LinearRegression {
public:
	LinearRegression(const DatasetRegression& dataset);
	LinearRegression(const DatasetRegression& dataset, const LinearRegressionConfig& config) :
		_dataset(dataset), _config(config) { }
	virtual ~LinearRegression() {}
	void train();
	Vector getW() const;
	double predict(const Vector& feature);
private:
	double computeDataError(const Vector& coeff);
private:
	static const LinearRegressionConfig _defaultConfig;
	const LinearRegressionConfig& _config;
	const DatasetRegression& _dataset;

	Vector _coeff;
};

} //~ namespace ycg

#endif /* LINEARREGRESSION_H_ */
