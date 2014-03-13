#ifndef STRING_H
#define STRING_H

#include "../io/OutputStream.h"
#include "../util/List.h"
#include <string>
#include <vector>
#include <iostream>

namespace ycg {

class String {
public:
    String();
    String(const char* chars);
    String(const char* charArray, int len);
    String(const std::string& str);
    String(const String& str);
    String(String&& orig);
    ~String();
    String& operator = (const char* rhs);
    String& operator = (const std::string& rhs);
    String& operator = (const String &rhs);
    String& operator = (String &&rhs);
    int length() const { return _len; }
    int size() const { return _len; }
    const char* toChars() const { return _str; }
    bool equals(const String &rhs) const;
    String substring(int beginIndex) const;
    String substring(int beginIndex, int endIndex) const;
    String replace(char oldChar, char newChar) const;
    int indexOf(char ch, int fromIndex = 0) const;
    int lastIndexOf(int ch, int fromIndex) const;
    bool startsWith(const char* prefix) const;
    String trim() const;
    std::vector<String> split2vector(char ch) const;
    friend void swap(String& lhs, String& rhs);

    friend bool operator < (const String &lhs, const String &rhs);


    char& operator [] (int index) { return _str[index]; }
    const char& operator [] (int index) const  { return _str[index]; }
    String& operator += (const String &rhs);
    String& operator += (char rhs);
    friend bool operator == (const String &lhs, const String &rhs);
    friend String operator + (const String &lhs, const String &rhs);
    friend String operator + (const String &lhs, int rhs);
    friend String operator + (const String &lhs, char rhs);
    friend OutputStream& operator << (OutputStream& os, const String& str);
    friend std::ostream& operator << (std::ostream& os, const String& str);
    operator std::string () const;

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
    int _len;
    char *_str;
};

void swap(String& lhs, String& rhs);
bool operator < (const String &lhs, const String &rhs);
bool operator == (const String &lhs, const String &rhs);
std::ostream& operator << (std::ostream& os, const String& str);
OutputStream& operator << (OutputStream& os, const String& str);

} //~ namespace ycg

#endif // STRING_H
