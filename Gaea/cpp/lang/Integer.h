#ifndef INTEGER_HPP
#define INTEGER_HPP

#include "Character.h"
#include "String.h"
#include "Lang.h"

namespace ycg {

class Integer {
public:
    static int parseInt(const String& s);
    static String toString(int i);
public:
    Integer();
    Integer(int i);
private:
    int value;
};

} //~ namespace ycg

#endif // INTEGER_HPP
