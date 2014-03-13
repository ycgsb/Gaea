#include "DatasetSupervised.h"
#include "../../io/Scanner.h"
#include "../../io/Writer.h"
#include "../../lang/Double.h"

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
        processTarget(items[_dims]);
	}

}

void DatasetSupervised::save(const String& filename) {
    Writer writer(filename);
//    for (int i = 0; i < _features.size(); ++i) {
//        const Vector& data = features[i];
//        for (int j = 0; j < numDim; ++j) {
//            writer.print(data[j]).print(',');
//        }
//        int label = _labels[i];
//        writer.println(label);
//    }
    writer.close();
}
} //~ namespace ycg
