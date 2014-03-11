#ifndef TREEARRAY_H
#define TREEARRAY_H

namespace ycg {

class TreeArray {
public:
	TreeArray(int size);
	~TreeArray();
	int size() const;
	void modify(int i, int delta);
	int sum(int i);
private:
	int lowbit(int x);
private:
	int* data;
	int elemNum;
};

inline int TreeArray::lowbit(int x) {
	return x & (-x);
}

} // namespace ycg

#endif // TREEARRAY_H
