#include "String.h"
#include "Integer.h"
#include <cstdio>

namespace ycg {

String::String() {
    str = 0;
    len = 0;
}

String::String(const char *chars) {
	int i = 0;
    while (chars[i] != '\0') ++i;
    len = i;
    if (len == 0) {
        str = 0;
        return;
    }
    str = new char[len + 1];
    for (int i = 0; i < len; ++i) {
        str[i] = chars[i];
    }
    str[len] = '\0';
}

String::String(const char *charArray, int len) {
    if (len == 0) {
        str = nullptr;
        return;
    }
    str = new char[len+1];
    for (int i = 0; i < len; ++i) {
        str[i] = charArray[i];
    }
    str[len] = '\0';
    this->len = len;
}

String::String(const String& string) {
    if (string.len == 0) {
        str = 0;
        len = 0;
        return;
    }
    len = string.len;
    str = new char[len+1];
    for (int i = 0; i < len; ++i) {
        str[i] = string.str[i];
    }
    str[len] = '\0';
}

String::~String() {
    delete []str;
    str = 0;
}

String& String::operator = (const String &rhs) {
	if (&rhs == this) return *this;
    if (rhs.len == 0) {
        str = 0;
        len = 0;
        return *this;
    }
    len = rhs.len;
    delete []str;
    str = new char[len+1];
    for (int i = 0; i < len; ++i) {
        str[i] =rhs.str[i];
    }
    str[len] = '\0';
    return *this;
}

String operator + (const String& lhs, const String& rhs) {
    String res;
    res.len = lhs.len + rhs.len;
    res.str = new char[res.len + 1];
    for (int i = 0; i < lhs.len; ++i) {
        res.str[i] = lhs.str[i];
    }
    for (int i = lhs.len, j = 0; j < rhs.len; ++i, ++j) {
        res.str[i] = rhs.str[j];
    }
    res.str[res.len] = '\0';
    return res;
}

String operator + (const String& lhs, int rhs) {
	return lhs + Integer::toString(rhs);
}

String operator + (const String& lhs, char rhs) {
    String res;
    res.len = lhs.len + 1;
    res.str = new char[res.len + 1];
    for (int i = 0; i < lhs.len; ++i) {
        res.str[i] = lhs.str[i];
    }
    res.str[lhs.len] = rhs;
    res.str[res.len] = '\0';
    return res;
}

String& String::operator += (const String &rhs) {
	int len_new = len + rhs.len;
	char *str_new = new char[len_new + 1];
    for (int i = 0; i < len; ++i) {
        str_new[i] = str[i];
    }
    for (int i = len, j = 0; j < rhs.len; ++i, ++j) {
        str_new[i] = rhs.str[j];
    }
    str_new[len_new] = '\0';
    delete []str;
    len = len_new;
    str = str_new;
    return *this;
}

String& String::operator += (char rhs) {
    char *str_new = new char[len + 2];
    for (int i = 0; i < len; ++i) {
        str_new[i] = str[i];
    }
    str_new[len++] = rhs;
    str_new[len] = '\0';
    delete []str;
    str = str_new;
    return *this;
}

String::Iterator String::begin() {
	return Iterator(*this, 0);
}

String::Iterator String::end() {
	return Iterator(*this, len);
}

String::Iterator::Iterator(String& str, int index) :
		string(str), currentIndex(index) {
}

bool String::Iterator::operator == (const Iterator& iter) const {
	return (this->currentIndex == iter.currentIndex);
}

bool String::Iterator::operator != (const Iterator& iter) const {
	return (this->currentIndex != iter.currentIndex);
}

String::Iterator& String::Iterator::operator ++() {
	++currentIndex;
	return *this;
}

char& String::Iterator::operator * () {
	return string.str[currentIndex];
}

bool String::equals(const String &anString) const {
    if (this->len != anString.len)
        return false;
    for (int i = 0; i < len; ++i) {
        if (this->str[i] != anString.str[i])
            return false;
    }
    return true;
}

String String::substring(int beginIndex, int endIndex) const {
    String sub;
    int len = endIndex - beginIndex;
    sub.str = new char[len + 1];
    for (int i = beginIndex, j = 0; i < endIndex; ++i, ++j) {
        sub.str[j] = str[i];
    }
    sub.str[len] = '\0';
    sub.len = len;
    return sub;
}

String String::substring(int beginIndex) const {
    int endIndex = len;
    return substring(beginIndex, endIndex);
}

void String::split(char ch, List<String> *items) {
	static const int BUFFER_SIZE = 1024;
	static char Buff[BUFFER_SIZE];
	int itemLen = 0;
	for (int i = 0; i < len; ++i) {
		if (str[i] != ch) {
			Buff[itemLen++] = str[i];
		} else {
			items->add(String(Buff, itemLen));
			itemLen = 0;
		}
	}
	items->add(String(Buff, itemLen));
}


} //~ namespace ycg
