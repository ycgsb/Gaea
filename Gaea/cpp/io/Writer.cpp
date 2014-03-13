#include "Writer.h"

namespace ycg {

Writer::Writer() {
	strategy = new WriterConsole();
}

Writer::Writer(const char* filename) {
	strategy = new WriterFile(filename);
}

Writer::Writer(const String& filename) {
	strategy = new WriterFile(filename.toChars());
}

Writer::~Writer() {
	delete strategy;
}

Writer& Writer::println() {
    strategy->println();
    return *this;
}

Writer& Writer::print(int i) {
    strategy->print(i);
    return *this;
}

Writer& Writer::println(int i) {
    strategy->println(i);
    return *this;
}

Writer& Writer::print(const char *s) {
    strategy->print(s);
    return *this;
}

Writer& Writer::println(const char *s) {
	strategy->println(s);
    return *this;
}

Writer& Writer::print(const String &s) {
	strategy->print(s);
    return *this;
}

Writer& Writer::println(const String &s) {
	strategy->println(s);
    return *this;
}

Writer& Writer::print(char ch) {
    strategy->print(ch);
    return *this;
}

Writer& Writer::println(char ch) {
	strategy->println(ch);
	return *this;
}

Writer& Writer::print(double d) {
	strategy->print(d);
	return *this;
}

Writer& Writer::println(double d) {
	strategy->println(d);
	return *this;
}

void Writer::close() {
	strategy->close();
}

WriterStrategy::WriterStrategy() { }

WriterStrategy::~WriterStrategy() { }

WriterFile::WriterFile() :
	fp(nullptr) {
}

WriterFile::WriterFile(const char* fileName) {
	fp = fopen(fileName, "w");
	if (fp == nullptr) {
		throw IOException();
	}
}

WriterFile::~WriterFile() {
    close();
}

void WriterFile::println() {
	putc('\n', fp);
}

void WriterFile::print(int i) {
	fprintf(fp, "%d", i);
}

void WriterFile::println(int i) {
	fprintf(fp, "%d\n", i);
}

void WriterFile::print(const char *s) {
	fprintf(fp, "%s", s);
}

void WriterFile::println(const char *s) {
	fprintf(fp, "%s\n", s);
}

void WriterFile::print(const String& s) {
	fprintf(fp, "%s", s.toChars());
}

void WriterFile::println(const String& s) {
	fprintf(fp, "%s\n", s.toChars());
}

void WriterFile::print(char ch) {
	putc(ch, fp);
}

void WriterFile::println(char ch) {
	putc(ch, fp);
	putc('\n', fp);
}

void WriterFile::print(double d) {
	fprintf(fp, "%lf", d);
}

void WriterFile::println(double d) {
	fprintf(fp, "%lf\n", d);
}

void WriterFile::close() {
    if (fp != nullptr) {
        fclose(fp);
        fp = nullptr;
    }
}

WriterConsole::WriterConsole() {
	fp = stdout;
}

WriterConsole::~WriterConsole() {
	fflush(fp);
}

void WriterConsole::close() {
	fflush(fp);
	fp = nullptr;
}

} //~ namespace ycg
