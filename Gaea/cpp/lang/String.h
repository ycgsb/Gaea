#ifndef STRING_H
#define STRING_H

#include "../util/List.h"

namespace ycg {

class String {
public:
    String();
    String(const char *chars);
    String(const char *charArray, int len);
    String(const String &str);
    ~String();
    const char* toChars() const;
    int length() const { return len; };
    bool equals(const String &anString) const;
    String substring(int beginIndex, int endIndex) const;
    String substring(int beginIndex) const;
    void split(char ch, List<String> *items);

    String& operator = (const String &rhs);
    bool operator == (const String &rhs) const;
    char& operator [] (int index);
    const char& operator [] (int index) const;
    String& operator += (const String &rhs);
    String& operator += (char rhs);
    friend String operator + (const String &lhs, const String &rhs);
    friend String operator + (const String &lhs, int rhs);
    friend String operator + (const String &lhs, char rhs);
    class Iterator;
    friend class Iterator;
    class Iterator {
    public:
    	Iterator(String& str, int index);
    	bool operator ==(const Iterator& iter) const;
    	bool operator !=(const Iterator& iter) const;
    	Iterator& operator ++ ();
    	char& operator * ();
    private:
    	String& string;
    	int currentIndex;
    };

    Iterator begin();
    Iterator end();
private:
    char *str;
    int len;
};

inline const char* String::toChars() const {
    return str;
}

inline bool String::operator == (const String &rhs) const {
    return this->equals(rhs);
}

inline char& String::operator [] (int index) {
    return str[index];
}

inline const char& String::operator [] (int index) const {
    return str[index];
}

} //~ namespace ycg

#endif // STRING_H
