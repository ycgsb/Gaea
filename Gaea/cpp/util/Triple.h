#ifndef TRIPLE_H
#define TRIPLE_H

namespace ycg {

template <class T1, class T2, class T3>
class Triple {
public:
    Triple() : _first(), _second(), _third() { }
    Triple(const T1& first, const T2& second, const T3& third) :
    	_first(first), _second(second), _third(third) { }
    const T1& first() const { return _first; }
    const T2& second() const { return _second; }
    const T3& third() const { return _third; }
    Triple& setFirst(const T1& first) {
    	_first = first;
    	return *this;
    }
    Triple& setSecond(const T2& second) {
    	_second = second;
    	return *this;
    }
    Triple& setThird(const T3& third) {
    	_third = third;
    	return *this;
    }
private:
    T1 _first;
    T2 _second;
    T3 _third;
};

}  //~ namespace ycg

#endif /* TRIPLE_H */
