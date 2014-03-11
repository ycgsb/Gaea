#ifndef SCANNER_H
#define SCANNER_H

#include "IOException.h"
#include "../lang/String.h"
#include <cstdio>

namespace ycg {

class ScannerStrategy;

class Scanner {
public:
    Scanner();
    Scanner(const char* fileName);
    Scanner(const String& fileName);
    virtual ~Scanner();
    bool hasNext();
    int nextInt();
    char nextChar(bool skipWhitespace = true);
    double nextDouble();
    String nextLine();
    Scanner& skip(char ch);
    Scanner& skipWhitespace();
private:
    ScannerStrategy* strategy;
};

class ScannerStrategy {
public:
	ScannerStrategy();
	virtual ~ScannerStrategy() = 0;
	virtual bool hasNext() = 0;
	virtual int nextInt() = 0;
	virtual char nextChar(bool skipWhitespace) = 0;
	virtual double nextDouble() = 0;
	virtual String nextLine() = 0;
	virtual void skip(char ch) = 0;
	virtual void skipWhitespace() = 0;
};

class ScannerFile : public ScannerStrategy {
public:
	ScannerFile(const char* fileName);
	virtual ~ScannerFile();
	bool hasNext();
	int nextInt();
	char nextChar(bool skipWhitespace);
	double nextDouble();
	String nextLine();
	void skip(char ch);
	void skipWhitespace();
protected:
	ScannerFile();
protected:
	static const int BUFFER_SIZE = 1024;
	static char Buffer[BUFFER_SIZE];
	FILE* fp;
};

class ScannerConsole : public ScannerFile {
public:
	ScannerConsole();
	virtual ~ScannerConsole();
};

} //~ namespace ycg

#endif // SCANNER_HPP
