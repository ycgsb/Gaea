#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include "IOException.h"
#include <cstdio>

namespace ycg {

class InputStream {
public:
	InputStream();
	InputStream(const char* fileName, const char* mode = "r");
	virtual ~InputStream();
	operator bool();
	friend InputStream& operator >> (InputStream& is, int& i);
protected:
	FILE* fp;
};

} //~ namespace ycg

#endif /* INPUTSTREAM_H */
