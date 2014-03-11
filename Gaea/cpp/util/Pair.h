#ifndef PAIR_H
#define PAIR_H

namespace ycg {

template <class T1, class T2>
class Pair {
public:
    Pair() : _first(), _second() { }
    Pair(const T1& first, const T2& second) :
    	_first(first), _second(second) { }
    const T1& first() const { return _first; }
    const T2& second() const { return _second; }
    void setFirst(const T1& first) { _first = first; }
    void setSecond(const T2& second) { _second = second; }
    bool operator < (const Pair<T1, T2>& rhs) {
    	if (_first < rhs._first) {
    		return true;
    	} else if (rhs._first < _first) {
    		return false;
    	} else {
    		return _second < rhs._second;
    	}
    }
private:
    T1 _first;
    T2 _second;
};

typedef Pair<int, int> IntPair;
typedef Pair<int, double> IntDoublePair;
typedef Pair<double, int> DoubleIntPair;

} //~ namespace ycg

#endif // PAIR_HPP
