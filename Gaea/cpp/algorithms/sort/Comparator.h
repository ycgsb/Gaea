#ifndef COMPARATOR_H
#define COMPARATOR_H

namespace ycg {

template <class T>
class Comparator {
public:
    int operator() (const T &lhs, const T &rhs) {
        if (lhs == rhs) return 0;
    	return (lhs < rhs)? -1 : 1;
    }
};

template <class T>
class ComparatorLess {
public:
    int operator() (const T &lhs, const T &rhs) {
        return (lhs < rhs)? -1 : 1;
    }
};

template <class T>
class ComparatorGreater {
public:
	int operator() (const T &lhs, const T &rhs) {
		return (lhs < rhs)? 1 : -1;
	}
};
} //~ namespace ycg

#endif // COMPARATOR_H
