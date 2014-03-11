#include "Integer.h"

namespace ycg {

int Integer::parseInt(const String &s) {
    int i = 0;
    while (Character::isWhitespace(s[i])) {
        ++i;
    }
    int sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        ++i;
    }
    int num = 0;
    while (Character::isDigit(s[i])) {
        num = 10 * num + (s[i] - '0');
        ++i;
    }
    int result = sign * num;
    return result;
}

String Integer::toString(int num) {
	int sign = num;
    if (sign < 0) {
    	num = -num;
    }
    char buff[16];
    int len = 0;
    while (num > 0) {
        buff[len++] = num % 10 + '0';
        num /= 10;
    }
    if (sign < 0) {
        buff[len++] = '-';
    }
    reverse(buff, len);
    return String(buff, len);
}

} //~ namespace ycg
