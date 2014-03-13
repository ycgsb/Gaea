#ifndef DATASETUNSUPERVISED_H
#define DATASETUNSUPERVISED_H

#include "../../lang/String.h"

namespace ycg {

class DatasetUnsupervised {
public:
	DatasetUnsupervised() { }
	DatasetUnsupervised(const String& filename) { }
	virtual ~DatasetUnsupervised();
};

} //~ namespace ycg

#endif /* DATASETUNSUPERVISED_H */
