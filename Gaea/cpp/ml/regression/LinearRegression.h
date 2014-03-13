#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "../dataset/DatasetRegression.h"
#include "../../numerical/Vector.h"

namespace ycg {

class LinearRegressionConfig {
public:

public:
	bool regNeeded;
	double regCoeff;
	enum OptimizeMethod {
		CLOSED_FORM, GRADIENT_DESCENT
	};
	OptimizeMethod method;
};

class LinearRegression {
public:
	LinearRegression(const DatasetRegression& dataset) : _dataset(dataset) { }
	LinearRegression(const DatasetRegression& dataset, const LinearRegressionConfig& config) :
		_dataset(dataset), _config(config) { }
	virtual ~LinearRegression();
	void train();
	Vector getW() const;
	double predict(const Vector& feature);
private:
	double computeDataError(const Vector& coeff);
private:
	const DatasetRegression& _dataset;
	const LinearRegressionConfig& _config;
	Vector _coeff;
};

} //~ namespace ycg

#endif /* LINEARREGRESSION_H_ */
