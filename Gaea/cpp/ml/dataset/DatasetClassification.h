#ifndef DATASETCLASSIFICATION_H
#define DATASETCLASSIFICATION_H

#include "../../numerical/Vector.h"
#include "../../util/ArrayList.h"
#include <cassert>

namespace ycg {

class DatasetClassification {
public:
	DatasetClassification();
	DatasetClassification(const char *fileName);
	virtual ~DatasetClassification();
    int size() const;
	int dimension() const;
    const Vector& getFeature(int i) const;
    int getLabel(int i) const;
    void addData(const Vector& feature, int label);
    void clear();
    void load(const char *fileName);
	void save(const char *fileName);


//public:
//	class Iterator {
//	public:
//		Iterator(DatasetClassification& dataset);
//	private:
//		DatasetClassification& dataset;
//	};
//	Iterator begin();
//	Iterator end();
private:

private:
	ArrayList<Vector> features;
    ArrayList<int> labels;
	int numDim;
};

inline int DatasetClassification::size() const {
    return features.size();
}

inline int DatasetClassification::dimension() const {
    return numDim;
}

inline const Vector& DatasetClassification::getFeature(int i) const {
    assert(i>=0 && i<features.size());
    return features[i];
}

inline int DatasetClassification::getLabel(int i) const {
    assert(i>=0 && i<labels.size());
    return labels[i];
}

inline void DatasetClassification::addData(const Vector& feature, int label) {
	features.add(feature);
	labels.add(label);
}

} //~ namespace ycg

#endif /* DATASETCLASSIFICATION_H */
