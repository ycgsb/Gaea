#ifndef INTERVAL_H
#define INTERVAL_H

namespace ycg {

template <class T>
class Interval {
public:
    Interval():_begin(), _end() {}
    Interval(T begin, T end): _begin(begin), _end(end) { }
    T begin() const { return _begin; }
    T end() const { return _end; }
    Interval& setBegin(T begin) {
    	_begin = begin;
    	return *this;
    }
    Interval& setEnd(T end) {
    	_end = end;
    	return *this;
    }
private:
    T _begin;
    T _end;
};

} //~ namespace ycg

#endif /* INTERVAL_H*/
