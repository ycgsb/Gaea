#ifndef TEST_H
#define TEST_H

#include "TestExceptions.h"

namespace ycg {

#define CHECK(exper) checkCondition((exper), #exper, __LINE__, __FILE__);

class Test {
public:
	Test();
	virtual ~Test();
	virtual void run() = 0;
protected:
	void checkCondition(bool requirement, const char *exper, int lineNo = -1, const char *filename = nullptr);
};

} //~ namespace ycg

#endif // TEST_H
