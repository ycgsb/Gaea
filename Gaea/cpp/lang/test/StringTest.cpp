#include "StringTest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>

namespace ycg {

void StringTest::run() {
	String str1;
	CHECK(str1.length() == 0);
	String str2("construct from const char*");
	std::cout << str2 << std::endl;
	char chArr[6] = {'A','r','r','a','y'};
	String str3(chArr, 5);
	CHECK(str3.size() == 5);
	printf("%s\n", str3.toChars());
	std::string ss("STL string object");
	String str4(ss);
	cos << str4 << "\n";
	String str5 = "copy construct";
	String str6 = str5;
	CHECK(str6 == str5);
	String str7 = String("Hello, ") + String("world.");
	CHECK(str7.equals("Hello, world."));
	str1 = str7;
	str2 = ss;
	str3 = "some text";
	str4 = str1 + "test.";
	CHECK(str7.substring(7) == "world.");
	CHECK(str7.substring(1, 5) == "ello");
	CHECK(str7.indexOf(',') == 5);
	CHECK(str7.indexOf(',', 6) == -1);
	str1 = "  test trim.  \t";
	CHECK(str1.trim() == "test trim.");
	str1 = "11|22|ab|cd";
	auto items = str1.split2vector('|');
	CHECK(items.size() == 4);
	str1 = "123";
	str2 = "1245";
	CHECK(str1 < str2);
	str2 = "1234";
	CHECK(str1 < str2);

	printf("String Test Passed.\n");
}

} //~ namespace ycg

