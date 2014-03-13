#include "LinearRegressionTest.h"
#include "../regression/LinearRegression.h"

namespace ycg {

void LinearRegressionTest::run() {
	DatasetRegression dataset(3);
	LinearRegressionConfig config;
	LinearRegression lr(dataset, config);
	lr.train();
	lr.getW();
}

} //~ namespace ycg

