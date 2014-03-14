#include <iostream>
#include <sstream>
#include <string>
#include <list>
using namespace std;

int __main() {
	int caseNo;
	cin >> caseNo;
	string text;
	getline(cin, text);
	for (int caseID = 1; caseID <= caseNo; ++caseID) {
		getline(cin, text);
		istringstream iss(text);
		istream_iterator<string> is_iter(iss), is_eof;
		list<string> lwords;
		while(is_iter != is_eof) {
			lwords.push_back(*is_iter++);
		}
		lwords.reverse();
		cout << "Case #" << caseID << ":";
		for (auto& w : lwords) {
			cout << " " << w;
		}
		cout << endl;
	}
	return 0;
}
