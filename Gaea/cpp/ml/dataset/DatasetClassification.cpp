#include "DatasetClassification.h"
#include "../../io/Scanner.h"
#include "../../io/Writer.h"
#include "../../lang/Double.h"
#include "../../lang/Integer.h"
#include <cstdio>

namespace ycg {

DatasetClassification::DatasetClassification()
	:numDim(0) {
}

DatasetClassification::DatasetClassification(const char *fileName) {
	load(fileName);
}

DatasetClassification::~DatasetClassification() {
	clear();
}

void DatasetClassification::clear() {
	numDim = 0;
	features.clear();
	labels.clear();
}

void DatasetClassification::load(const char *fileName) {
	clear();
	Scanner scanner(fileName);
	while (scanner.hasNext()) {
		String line = scanner.nextLine();
		ArrayList<String> items;
		line.split(',', &items);
		numDim = items.size() - 1;
		Vector data(numDim, false);
		for (int i = 0; i < numDim; ++i) {
			data[i] = Double::parseDouble(items[i]);
		}
        features.add(data);
        int label = Integer::parseInt(items[numDim]);
		labels.add(label);
	}
}

void DatasetClassification::save(const char *fileName) {
    Writer writer(fileName);
    for (int i = 0; i < features.size(); ++i) {
        const Vector& data = features[i];
        for (int j = 0; j < numDim; ++j) {
            writer.print(data[j]).print(',');
        }
        int label = labels[i];
        writer.println(label);
    }
    writer.close();
}

} /* namespace ycg */
