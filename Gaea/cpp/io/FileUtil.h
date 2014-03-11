#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <cstdio>

namespace ycg {

enum FileCompareResult {
	FILE_SAME, FILE_DIFFERENT
};

class FileUtil {
public:
	FileUtil();
	virtual ~FileUtil();
public:
	static FileCompareResult fileCompare(const char* fileName1, const char* fileName2);
};

} //~ namespace ycg

#endif /* FILEUTIL_H_ */
