#ifndef DATASETREGRESSION_H
#define DATASETREGRESSION_H

#include "DatasetSupervised.h"
#include "../../io/Writer.h"

namespace ycg {

class DatasetRegression : public DatasetSupervised {
public:
	DatasetRegression(int dims) : DatasetSupervised(dims) { }
	DatasetRegression(const String& filename) : DatasetSupervised(0) { load(filename); }
	virtual ~DatasetRegression() { }
	virtual void clear();
	double value(int i) const { return _values[i]; }
	void addSample(const Vector& feature, double value);
	Vector getTargetVector();
protected:
	virtual void readTarget(const String& item);
	virtual void writeTarget(int i, Writer& writer);
protected:
	std::vector<double> _values;
};

} //~ namespace ycg

#endif /* DATASETREGRESSION_H */
