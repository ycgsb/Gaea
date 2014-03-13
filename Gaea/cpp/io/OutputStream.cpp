#include "OutputStream.h"

namespace ycg {

OutputStream::OutputStream() :
		fp(stdout) { }

OutputStream::OutputStream(const char* fileName, const char* mode) {
	fp = fopen(fileName, mode);
	if (fp == nullptr) {
		throw IOException();
	}
}

OutputStream::~OutputStream() {
	close();
}

void OutputStream::close() {
	if (fp != stdout) {
		fclose(fp);
	} else {
		fflush(fp);
	}
}

OutputStream& operator << (OutputStream& os, int32 i) {
	fprintf(os.fp, "%d", i);
	return os;
}

OutputStream& operator << (OutputStream& os, uint32 i) {
	fprintf(os.fp, "%u", i);
	return os;
}

OutputStream& operator << (OutputStream& os, double d) {
	fprintf(os.fp, "%lf", d);
	return os;
}

OutputStream& operator << (OutputStream& os, char ch) {
	fputc(ch, os.fp);
	return os;
}

OutputStream& operator << (OutputStream& os, const char* str) {
	fprintf(os.fp, "%s", str);
	return os;
}

} //~ namespace ycg
