#include "DatasetClassificationTest.h"
#include "../dataset/DatasetClassification.h"

namespace ycg {

DatasetClassificationTest::DatasetClassificationTest() { }

DatasetClassificationTest::~DatasetClassificationTest() { }

void DatasetClassificationTest::run() {
	DatasetClassification dataset;
	dataset.load("/ml/test/dating.txt");

}

} //~ namespace ycg
