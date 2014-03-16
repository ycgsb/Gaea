#ifndef POLYNOMIALREGRESSIONTEST_H
#define POLYNOMIALREGRESSIONTEST_H

#include "../dataset/DatasetRegression.h"
#include "../regression/PolynomialRegression.h"
#include "../../test/Test.h"

namespace ycg {

class PolynomialRegressionTest : public Test {
public:
	void run();
private:
	double computeRMSE(const DatasetRegression& dataset, PolynomialRegression& regression);
};

} //~ namespace ycg

#endif /* POLYNOMIALREGRESSIONTEST_H_ */
