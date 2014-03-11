#ifndef RANDOMSTRINGGENERATOR_H
#define RANDOMSTRINGGENERATOR_H

#include "../../lang/String.h"

namespace ycg {

class RandomStringGenerator {
public:
	RandomStringGenerator(int length, bool containUpper, bool containLower, bool containDigit);
    String generate();
private:
    int length;
    bool containUpper;
    bool containLower;
    bool containDigit;
};

}//~ namespace ycg


#endif // RANDOMSTRINGGENERATOR_H
