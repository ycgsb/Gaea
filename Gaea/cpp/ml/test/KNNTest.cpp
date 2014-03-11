#include "KNNTest.h"
#include "../../io/Scanner.h"
#include "../../io/Writer.h"
#include "../../io/FileUtil.h"
#include "../dataset/DatasetClassification.h"
#include "../classification/KNN.h"
#include "../classification/CrossValidatorClassification.h"
#include <cstdio>

namespace ycg {

KNNTest::KNNTest() { }

KNNTest::~KNNTest() { }

void KNNTest::run() {
	Scanner scanner("cpp/ml/test/TestKNNInput.txt");
	Writer writer("cpp/ml/test/TestKNNOutput.txt");
	KNN kNN(3);
	DatasetClassification dataset("cpp/ml/test/TestKNNData.txt");
    CrossValidatorParameter parameter;
    while (scanner.hasNext()) {
    	parameter.testingDataRatio = scanner.nextDouble();
    	CrossValidatorClassification validator(&kNN, &dataset, &parameter);
    	validator.validate();
    	double testingErr = validator.getTestingError();
    	writer.println(testingErr);
    }
    writer.close();
}

} //~ namespace ycg
