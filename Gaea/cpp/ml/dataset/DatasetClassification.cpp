#include "DatasetClassification.h"
#include "../../lang/Integer.h"
#include <cassert>
#include <cstdio>

namespace ycg {

void DatasetClassification::clear() {
	_features.clear();
	_labels.clear();
}

void DatasetClassification::addSample(const Vector& feature, int label) {
	assert(feature.size() == _dims);
	_features.push_back(feature);
	_labels.push_back(label);
}

void DatasetClassification::readTarget(const String& item) {
	_labels.push_back(Integer::parseInt(item));
}

void DatasetClassification::writeTarget(int i, Writer& writer) {
	writer.print(_labels[i]);
}

} //~ namespace ycg
