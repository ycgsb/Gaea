#include "CrossValidatorClassification.h"
#include <cstdio>

namespace ycg {

CrossValidatorClassification::CrossValidatorClassification(AbstractClassifier *classifier,
		const DatasetClassification *dataset, const CrossValidatorParameter *parameter) {
	this->classifier = classifier;
	this->dataset = dataset;
	this->parameter = parameter;
}

CrossValidatorClassification::~CrossValidatorClassification() { }

void CrossValidatorClassification::validate() {
	assert(parameter->testingDataRatio > 0.0 && parameter->testingDataRatio < 1.0);
	int boundary = static_cast<int>(dataset->size()*parameter->testingDataRatio);
	DatasetClassification trainingData;
	for (int i = boundary; i < dataset->size(); ++i) {
		trainingData.addData(dataset->getFeature(i), dataset->getLabel(i));
	}
	classifier->train(&trainingData);
	int wrong = 0;
	for (int i = 0; i < boundary; ++i) {
		int predicted = classifier->predict(dataset->getFeature(i));
		int groundTruth = dataset->getLabel(i);
		if (predicted != groundTruth) {
			++wrong;
		}
	}
	testingError = static_cast<double>(wrong) / (boundary);
}

double CrossValidatorClassification::getTrainingError() const {
	return trainingError;
}

double CrossValidatorClassification::getTestingError() const {
	return testingError;
}

} //~ namespace ycg
