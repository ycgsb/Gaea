#include "FileUtil.h"

namespace ycg {

FileUtil::FileUtil() { }

FileUtil::~FileUtil() { }

FileCompareResult FileUtil::fileCompare(const char* fileName1, const char* fileName2) {
	FILE* file1 = fopen(fileName1, "r");
	FILE* file2 = fopen(fileName2, "r");
	while (true) {
		int ch1 = fgetc(file1);
		int ch2 = fgetc(file2);
		if (ch1 != ch2) {
			fclose(file1);
			fclose(file2);
			return FileCompareResult::FILE_DIFFERENT;
		}
		if (ch1 == EOF) {
			fclose(file1);
			fclose(file2);
			return FileCompareResult::FILE_SAME;
		}
	}
	return FileCompareResult::FILE_SAME;
}

void filecopy(FILE *ifp, FILE* ofp) {
	int c;
	while ((c=getc(ifp))!=EOF) {
		putc(c, ofp);
	}
}
} //~ namespace ycg
