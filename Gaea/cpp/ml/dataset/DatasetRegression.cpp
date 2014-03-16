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

Vector DatasetRegression::getTargetVector() {
	int n = _values.size();
	Vector target(n);
	for (int i = 0; i < n; ++i) {
		target[i] = _values[i];
	}
	return target;
}

void DatasetRegression::readTarget(const String& item) {
	_values.push_back(Double::parseDouble(item));
}

void DatasetRegression::writeTarget(int i, Writer& writer) {
	writer.print(_values[i]);
}

} //~ namespace ycg
