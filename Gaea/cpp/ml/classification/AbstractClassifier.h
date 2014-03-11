#ifndef ABSTRACTCLASSIFIER_H
#define ABSTRACTCLASSIFIER_H

#include "../dataset/DatasetClassification.h"

namespace ycg {

class AbstractClassifier {
public:
	AbstractClassifier();
	virtual ~AbstractClassifier();
	virtual void train(const DatasetClassification *trainingData) = 0;
	virtual int predict(const Vector &feature) = 0;
};

} //~ namespace ycg

#endif /* ABSTRACTCLASSIFIER_H */
