#ifndef CROSSVALIDATORCLASSIFICATION_H
#define CROSSVALIDATORCLASSIFICATION_H

#include "AbstractClassifier.h"
#include "../dataset/DatasetClassification.h"

namespace ycg {

class CrossValidatorParameter {
public:
	double testingDataRatio;
	static const int METHOD_FOLD = 0;
	static const int METHOD_LEAVE_ONE_OUT = 1;
};

class CrossValidatorClassification {
public:
	CrossValidatorClassification(AbstractClassifier *classifier,
			const DatasetClassification *dataset, const CrossValidatorParameter *parameter);
	virtual ~CrossValidatorClassification();
	void validate();
	double getTrainingError() const;
	double getTestingError() const;
private:
	AbstractClassifier *classifier;
	const DatasetClassification *dataset;
	const CrossValidatorParameter *parameter;
	double trainingError;
	double testingError;
};

} /* namespace ycg */

#endif /* CROSSVALIDATORCLASSIFICATION_H */
