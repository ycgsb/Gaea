#ifndef DATASETREGRESSION_H
#define DATASETREGRESSION_H

#include "DatasetSupervised.h"

namespace ycg {

class DatasetRegression : public DatasetSupervised {
public:
	DatasetRegression(int dims) : DatasetSupervised(dims) { }
	DatasetRegression(const String& filename) : DatasetSupervised(0) { load(filename); }
	virtual ~DatasetRegression() { }
	virtual void clear();
	double value(int i) const { return _values[i]; }
	void addSample(const Vector& feature, double value);
protected:
	virtual void processTarget(const String& item);
protected:
	std::vector<double> _values;
};

} //~ namespace ycg

#endif /* DATASETREGRESSION_H */
