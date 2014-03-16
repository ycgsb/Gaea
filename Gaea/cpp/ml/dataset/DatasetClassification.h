#ifndef DATASETCLASSIFICATION_H
#define DATASETCLASSIFICATION_H

#include "DatasetSupervised.h"
#include "../../numerical/Vector.h"
#include "../../util/ArrayList.h"
#include <string>
#include <cassert>

namespace ycg {

class DatasetClassification : public DatasetSupervised {
public:
	DatasetClassification(int dims) : DatasetSupervised(dims) { }
	DatasetClassification(const String& fileName) : DatasetSupervised(0) { load(fileName); }
	virtual ~DatasetClassification() { }
	virtual void clear();
	int label(int i) const { return _labels[i]; }
    void addSample(const Vector& feature, int label);
protected:
	virtual void readTarget(const String& item);
	virtual void writeTarget(int i, Writer& writer);
protected:
    std::vector<int> _labels;
};

} //~ namespace ycg

#endif /* DATASETCLASSIFICATION_H */
