#include "InputStream.h"

namespace ycg {

InputStream::InputStream() :
		fp(stdin) {
}

InputStream::~InputStream() {
	if (fp != stdin) {
		fclose(fp);
	}
}

InputStream::InputStream(const char* fileName, const char* mode) {
	fp = fopen(fileName,mode);
	if (fp == nullptr) {
		throw IOException();
	}
}

InputStream::operator bool() {
	int ch = fgetc(fp);
	if (ch != EOF) {
		ungetc(ch, fp);
		return true;
	} else {
		return false;
	}
}

InputStream& operator >> (InputStream& is, int& i) {
	fscanf(is.fp, "%d", &i);
	return is;
}

} //~ namespace ycg
