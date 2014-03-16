#ifndef DATASETSUPERVISED_H
#define DATASETSUPERVISED_H

#include "../../lang/String.h"
#include "../../io/Writer.h"
#include "../../numerical/Vector.h"
#include "../../numerical/Matrix.h"
#include <vector>

namespace ycg {

class DatasetSupervised {
public:
	DatasetSupervised(int dims) : _dims(dims) { }
	virtual ~DatasetSupervised() { }
	void load(const String& filename);
	void save(const String& filename);
	virtual void clear() = 0;
	int samples() const { return _features.size(); }
	int dims() const { return _dims; }
	const Vector& feature(int i) const { return _features[i]; }
	Matrix getDesignMatrix() const;
protected:
	virtual void readTarget(const String& item) = 0;
	virtual void writeTarget(int i, Writer& writer) = 0;
protected:
	int _dims;
	std::vector<Vector> _features;
};

} //~ namespace ycg

#endif /* DATASETSUPERVISED_H */
