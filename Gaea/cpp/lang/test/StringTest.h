#ifndef STRINGTEST_H
#define STRINGTEST_H

#include "../../test/Test.h"
#include "../String.h"
#include "../../io/OutputStream.h"

namespace ycg {

class StringTest : public Test {
public:
	void run();
private:
	OutputStream cos;
};

} //~ namespace ycg

#endif /* STRINGTEST_H */
