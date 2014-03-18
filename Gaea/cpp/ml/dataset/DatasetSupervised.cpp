#include "DatasetSupervised.h"
#include "../../io/Scanner.h"
#include "../../lang/Double.h"
#include <iostream>

namespace ycg {

void DatasetSupervised::load(const String& filename) {
	clear();
	Scanner scanner(filename);
	while (scanner.hasNext()) {
		String line = scanner.nextLine();
		std::vector<String> items = line.split2vector(',');
		_dims = items.size() - 1;
		Vector data(_dims, false);
		for (int i = 0; i < _dims; ++i) {
			data[i] = Double::parseDouble(items[i]);
		}
        _features.push_back(data);
        readTarget(items[_dims]);
	}

}

void DatasetSupervised::save(const String& filename) {
    Writer writer(filename);
    for (int i = 0; i < _features.size(); ++i) {
        const Vector& data = _features[i];
        for (int j = 0; j < _dims; ++j) {
            writer.print(data[j]).print(',');
        }
        writeTarget(i, writer);
    }
    writer.close();
}

Matrix ycg::DatasetSupervised::getDesignMatrix() const {
	int n = _features.size();
	int m = _dims;
	Matrix X(n, m, false);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			X[i][j] = _features[i][j];
		}
	}
	return X;
}

} //~ namespace ycg

