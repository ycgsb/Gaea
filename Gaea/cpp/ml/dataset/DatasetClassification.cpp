#include "DatasetClassification.h"
#include "../../lang/Integer.h"
#include <cstdio>

namespace ycg {

void DatasetClassification::clear() {
	_dims = 0;
	_features.clear();
	_labels.clear();
}

void DatasetClassification::addSample(const Vector& feature, int label) {
	_features.push_back(feature);
	_labels.push_back(label);
}

void DatasetClassification::processTarget(const String& item) {
	_labels.push_back(Integer::parseInt(item));
}

} //~ namespace ycg
