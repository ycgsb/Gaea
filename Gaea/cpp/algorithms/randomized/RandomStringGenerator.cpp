#include "RandomStringGenerator.h"
#include "../../util/Random.h"
#include <cassert>

namespace ycg {

RandomStringGenerator::RandomStringGenerator(int length, bool containUpper, bool containLower, bool containDigit) {
	assert(length > 0);
	assert(containUpper || containLower || containDigit);
	this->length = length;
	this->containUpper = containUpper;
	this->containLower = containLower;
	this->containDigit = containDigit;
}

String RandomStringGenerator::generate() {
    char *randStr = new char[length+1];
    int type[3];
    int ntype = 0;
    if (containUpper) type[ntype++] = 0;
    if (containLower) type[ntype++] = 1;
    if (containDigit) type[ntype++] = 2;
    Random& rnd = Random::instance();
    for (int i = 0; i < length; ++i) {
        rnd.shuffle(type, ntype);
        switch (type[0]) {
        case 0:
            randStr[i] = 'A' + rnd.uniform(0,26);
            break;
        case 1:
            randStr[i] = 'a' + rnd.uniform(0,26);
            break;
        case 2:
            randStr[i] = '0' + rnd.uniform(0,10);
            break;
        default:
            break;
        }
    }
    randStr[length] = '\0';
    String res(randStr);
    delete []randStr;
    return res;
}

}//~ namespace ycg
