#include "String.h"
#include "Integer.h"
#include "Character.h"
#include <cassert>
#include <cstdio>

namespace ycg {

String::String():
	_len(0),
	_str(nullptr) {
	_str = new char[1];
	_str[0] = '\0';
}

String::String(const char *chars):
	_len(0),
	_str(nullptr) {
    while (chars[_len] != '\0') ++_len;
    _str = new char[_len + 1];
    for (int i = 0; i < _len; ++i) {
        _str[i] = chars[i];
    }
    _str[_len] = '\0';
}

String::String(const char *charArray, int len):
	_len(len),
	_str(new char[len + 1]) {
    for (int i = 0; i < len; ++i) {
        _str[i] = charArray[i];
    }
    _str[len] = '\0';
}

String::String(const std::string& str) :
	_len(str.length()),
	_str(new char[_len + 1]) {
	for (int i = 0; i < _len; ++i) {
		_str[i] = str[i];
	}
	_str[_len] = '\0';
}

String::String(const String& orig):
	_len(orig._len),
	_str(new char[_len+1]) {
    for (int i = 0; i < _len; ++i) {
        _str[i] = orig._str[i];
    }
    _str[_len] = '\0';
}

String::String(String&& orig):
	_len(orig._len),
	_str(orig._str) {
	orig._str = nullptr;
}

String::~String() {
    delete []_str;
}

String& String::operator = (const char* rhs) {
	if (_str == rhs) return *this;
	delete []_str;
	_len = 0;
	while (rhs[_len] != '\0') ++_len;
	_str = new char[_len + 1];
	for (int i = 0; i < _len; ++i) {
		_str[i] = rhs[i];
	}
	_str[_len] = '\0';
	return *this;
}

String& String::operator = (const std::string& rhs) {
	delete []_str;
	_len = rhs.length();
	_str = new char[_len + 1];
	for (int i = 0; i < _len; ++i) {
		_str[i] = rhs[i];
	}
	_str[_len] = '\0';
	return *this;
}

String& String::operator = (const String &rhs) {
	if (&rhs == this) return *this;
	delete []_str;
    _len = rhs._len;
    _str = new char[_len + 1];
    for (int i = 0; i < _len; ++i) {
        _str[i] = rhs._str[i];
    }
    _str[_len] = '\0';
    return *this;
}

String& String::operator = (String&& rhs) {
	if (&rhs == this) return *this;
	delete []_str;
	_len = rhs._len;
	_str = rhs._str;
	rhs._str = nullptr;
	return *this;
}

bool String::equals(const String &rhs) const {
    if (_len != rhs._len) return false;
    for (int i = 0; i < _len; ++i) {
    	if (_str[i] != rhs._str[i]) {
    		return false;
    	}
    }
    return true;
}

String String::substring(int beginIndex) const {
    return substring(beginIndex, _len);
}

String String::substring(int beginIndex, int endIndex) const {
    assert(0 <= beginIndex && beginIndex <= _len);
    assert(beginIndex <= endIndex && endIndex <= _len);
    return String(_str + beginIndex, endIndex - beginIndex);
}

String String::replace(char oldChar, char newChar) const {
	String res(*this);
	for (int i = 0; i < res._len; ++i) {
		if (res._str[i] == oldChar) {
			res._str[i] = newChar;
		}
	}
	return res;
}

int String::indexOf(char ch, int fromIndex) const {
	assert(0 <= fromIndex);
	for (int pos = fromIndex; pos < _len; ++pos) {
		if (_str[pos] == ch) {
			return pos;
		}
	}
	return -1;
}

int String::lastIndexOf(int ch, int fromIndex) const {
	assert(fromIndex < _len);
	for (int pos = fromIndex; pos >= 0; --pos) {
		if (_str[pos] == ch) {
			return pos;
		}
	}
	return -1;
}

bool String::startsWith(const char* prefix) const {
	for (int i = 0; prefix[i] != '\0'; ++i) {
		if (_str[i] != prefix[i]) {
			return false;
		}
	}
	return true;
}

String String::trim() const {
	int i = 0;
	while (i < _len && Character::isWhitespace(_str[i])) ++i;
	int j = _len - 1;
	while (j > i &&Character::isWhitespace(_str[j])) --j;
	return substring(i, j + 1);
}

std::vector<String> String::split2vector(char ch) const {
	std::vector<String> items;
	int pos1 = 0, pos2 = 0;
	while ((pos2 = indexOf(ch, pos1)) != -1) {
		items.push_back(substring(pos1, pos2));
		pos1 = pos2 + 1;
	}
	items.push_back(substring(pos1));
	return items;
}

void swap(String& lhs, String& rhs) {
	int tmp1 = lhs._len;
	lhs._len = rhs._len;
	rhs._len = tmp1;
	char* tmp2 = lhs._str;
	lhs._str = rhs._str;
	rhs._str = tmp2;
}

bool operator < (const String &lhs, const String &rhs) {
	for (int i = 0; lhs._str[i] && rhs._str[i]; ++i) {
		if (lhs._str[i] != rhs._str[i]) {
			return lhs._str[i] < rhs._str[i];
		}
	}
	return lhs._len < rhs._len;
}

String operator + (const String& lhs, const String& rhs) {
    String res;
    res._len = lhs._len + rhs._len;
    res._str = new char[res._len + 1];
    for (int i = 0; i < lhs._len; ++i) {
        res._str[i] = lhs._str[i];
    }
    for (int i = lhs._len, j = 0; j < rhs._len; ++i, ++j) {
        res._str[i] = rhs._str[j];
    }
    res._str[res._len] = '\0';
    return res;
}

String operator + (const String& lhs, int rhs) {
	return lhs + Integer::toString(rhs);
}

String operator + (const String& lhs, char rhs) {
    String res;
    res._len = lhs._len + 1;
    res._str = new char[res._len + 1];
    for (int i = 0; i < lhs._len; ++i) {
        res._str[i] = lhs._str[i];
    }
    res._str[lhs._len] = rhs;
    res._str[res._len] = '\0';
    return res;
}

String& String::operator += (const String &rhs) {
	int len_new = _len + rhs._len;
	char *str_new = new char[len_new + 1];
    for (int i = 0; i < _len; ++i) {
        str_new[i] = _str[i];
    }
    for (int i = _len, j = 0; j < rhs._len; ++i, ++j) {
        str_new[i] = rhs._str[j];
    }
    str_new[len_new] = '\0';
    delete []_str;
    _len = len_new;
    _str = str_new;
    return *this;
}

String& String::operator += (char rhs) {
    char *str_new = new char[_len + 2];
    for (int i = 0; i < _len; ++i) {
        str_new[i] = _str[i];
    }
    str_new[_len++] = rhs;
    str_new[_len] = '\0';
    delete []_str;
    _str = str_new;
    return *this;
}

String::Iterator String::begin() {
	return Iterator(*this, 0);
}

String::operator std::string() const {
	return std::string(_str);
}

String::Iterator String::end() {
	return Iterator(*this, _len);
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
	return string._str[currentIndex];
}

std::ostream& operator <<(std::ostream& os, const String& str) {
	os << str._str;
	return os;
}

OutputStream& operator <<(OutputStream& os, const String& str) {
	os << str._str;
	return os;
}

bool operator == (const String& lhs, const String& rhs) {
	return lhs.equals(rhs);
}

} //~ namespace ycg
