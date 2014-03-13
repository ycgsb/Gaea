#ifndef WRITER_H
#define WRITER_H

#include "../lang/String.h"
#include "IOException.h"
#include <cstdio>

namespace ycg {

class WriterStrategy;

class Writer {
public:
    Writer();
    Writer(const char* filename);
    Writer(const String& filename);
    virtual ~Writer();
    Writer& println();
    Writer& print(int i);
    Writer& println(int i);
    Writer& print(const char *s);
    Writer& println(const char *s);
    Writer& print(const String& s);
    Writer& println(const String& s);
    Writer& print(char ch);
    Writer& println(char ch);
    Writer& print(double d);
    Writer& println(double d);
    void close();
private:
    WriterStrategy* strategy;
};

class WriterStrategy {
public:
	WriterStrategy();
	virtual ~WriterStrategy() = 0;
	virtual void println() = 0;
	virtual void print(int i) = 0;
	virtual void println(int i) = 0;
	virtual void print(const char *s) = 0;
	virtual void println(const char *s) = 0;
	virtual void print(const String& s) = 0;
	virtual void println(const String& s) = 0;
	virtual void print(char ch) = 0;
	virtual void println(char ch) = 0;
	virtual void print(double d) = 0;
	virtual void println(double d) = 0;
	virtual void close() = 0;
};

class WriterFile : public WriterStrategy {
public:
	WriterFile(const char* fileName);
	virtual ~WriterFile();
	void println();
	void print(int i);
	void println(int i);
	void print(const char *s);
	void println(const char *s);
	void print(const String& s);
	void println(const String& s);
	void print(char ch);
	void println(char ch);
	void print(double d);
	void println(double d);
	void close();
protected:
	WriterFile();
protected:
	FILE* fp;
};

class WriterConsole : public WriterFile {
public:
	WriterConsole();
	virtual ~WriterConsole();
	void close();
};

} //~ namespace ycg

#endif // PRINTWRITER_H
