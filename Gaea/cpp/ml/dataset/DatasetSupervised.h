#ifndef DATASETSUPERVISED_H
#define DATASETSUPERVISED_H

#include "../../numerical/Vector.h"
#include <vector>
#include <string>

namespace ycg {

class DatasetSupervised {
public:
	DatasetSupervised();
	DatasetSupervised(const char *filename);
	DatasetSupervised(const std::string& filename);
	virtual ~DatasetSupervised();
private:
	std::vector<Vector> features;
	int numDim;
};

} //~ namespace ycg

#endif /* DATASETSUPERVISED_H */
