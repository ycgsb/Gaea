#include "Scanner.h"
#include "../lang/Character.h"

namespace ycg {

Scanner::Scanner() {
	strategy = new ScannerConsole();
}

Scanner::Scanner(const char* fileName) {
	strategy = new ScannerFile(fileName);
}

Scanner::Scanner(const String& fileName) {
	strategy = new ScannerFile(fileName.toChars());
}

Scanner::~Scanner() {
	delete strategy;
}

bool Scanner::hasNext() {
	return strategy->hasNext();
}

int Scanner::nextInt() {
	return strategy->nextInt();
}

char Scanner::nextChar(bool skipWhitespace) {
	return strategy->nextChar(skipWhitespace);
}

double Scanner::nextDouble() {
	return strategy->nextDouble();
}

String Scanner::nextLine() {
	return strategy->nextLine();
}

Scanner& Scanner::skip(char ch) {
	strategy->skip(ch);
	return *this;
}

Scanner& Scanner::skipWhitespace() {
	strategy->skipWhitespace();
	return *this;
}

ScannerStrategy::ScannerStrategy() { }

ScannerStrategy::~ScannerStrategy() { }

char ScannerFile::Buffer[ScannerFile::BUFFER_SIZE];

ScannerFile::ScannerFile() :
	fp(nullptr) {
}

ScannerFile::ScannerFile(const char* fileName) {
	fp = fopen(fileName, "r");
	if (!fp) {
		throw IOException();
	}
}

ScannerFile::~ScannerFile() {
	fclose(fp);
}

bool ScannerFile::hasNext() {
	int ch = fgetc(fp);
	if (ch != EOF) {
		ungetc(ch, fp);
		return true;
	} else {
		return false;
	}
}

int ScannerFile::nextInt() {
	int i;
	fscanf(fp, "%d", &i);
	return i;
}

char ScannerFile::nextChar(bool skipWhitespace) {
	char ch = getc(fp);
	if (skipWhitespace) {
		while(Character::isWhitespace(ch)) {
			ch = getc(fp);
		}
	}
	return ch;
}

double ScannerFile::nextDouble() {
	double d;
	fscanf(fp, "%lf", &d);
	return d;
}

String ScannerFile::nextLine() {
	int len = 0, ch;
	while (len < BUFFER_SIZE && (ch = getc(fp)) != EOF && ch != '\n') {
		Buffer[len++] = ch;
	}
	return String(Buffer, len);
}

void ScannerFile::skip(char ch) {
	char next = getc(fp);
	while (next != ch) {
		next = getc(fp);
	}
}

void ScannerFile::skipWhitespace() {
	char next = getc(fp);
	while (Character::isWhitespace(next)) {
		next = getc(fp);
	}
	ungetc(next, fp);
}

ScannerConsole::ScannerConsole() {
	fp = stdin;
}

ScannerConsole::~ScannerConsole() {
}

} //~ namespace ycg
