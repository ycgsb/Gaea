#ifndef DATASETREGRESSION_H
#define DATASETREGRESSION_H

#include "DatasetSupervised.h"

namespace ycg {

class DatasetRegression : public DatasetSupervised {
public:
	DatasetRegression() : DatasetSupervised() { }
	DatasetRegression(const String& filename) : DatasetSupervised(filename) { }
	virtual ~DatasetRegression() { }
	virtual void clear();
	int value(int i) const { return _values[i]; }
	void addSample(const Vector& feature, double value);
protected:
	virtual void processTarget(const String& item);
protected:
	std::vector<double> _values;
};

} //~ namespace ycg

#endif /* DATASETREGRESSION_H */
