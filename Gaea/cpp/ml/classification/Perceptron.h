#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "../dataset/DatasetClassification.h"

namespace ycg {

class Perceptron {
public:
	Perceptron(const DatasetClassification& dataSet);
	virtual ~Perceptron();
	void train();
//	double predict(const Vector&);
private:
	const DatasetClassification& dataSet;
};


} //~ namespace ycg

#endif /* PERCEPTRON_H */
