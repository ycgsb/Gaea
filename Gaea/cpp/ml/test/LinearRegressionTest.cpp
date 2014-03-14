#include "LinearRegressionTest.h"
#include "../regression/LinearRegression.h"

namespace ycg {

void LinearRegressionTest::run() {
	DatasetRegression dataset(3);
//	LinearRegressionConfig config;
	LinearRegression lr(dataset);
	lr.train();
	lr.getW();
}

} //~ namespace ycg

