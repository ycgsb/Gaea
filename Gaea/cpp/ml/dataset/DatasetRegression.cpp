#include "DatasetRegression.h"
#include "../../lang/Double.h"

namespace ycg {

void DatasetRegression::clear() {
	_features.clear();
	_values.clear();
}

void DatasetRegression::addSample(const Vector& feature, double value) {
	assert(feature.size() == _dims);
	_features.push_back(feature);
	_values.push_back(value);
}

void DatasetRegression::processTarget(const String& item) {
	_values.push_back(Double::parseDouble(item));
}

} //~ namespace ycg
