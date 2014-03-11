#include "TreeArray.h"

namespace ycg {

TreeArray::TreeArray(int size) {
	elemNum = size;
	data = new int[size];
	for(int i = 0; i < elemNum; ++i) {
		data[i] = 0;
	}
}

TreeArray::~TreeArray() {
	delete []data;
}

void TreeArray::modify(int i, int delta) {
	++i;
	for(int j = i; j <= elemNum; j += lowbit(j)) {
		data[j - 1] += delta;
	}
}

int TreeArray::sum(int i) {
	++i;
	int res = 0;
	for(int j = i; j >= 1; j -= lowbit(j)) {
		res += data[j - 1];
	}
	return res;
}

} //~ namespace ycg
