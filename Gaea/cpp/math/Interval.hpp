#ifndef INTERVAL_HPP
#define INTERVAL_HPP

namespace ycg {

template <class T>
class Interval {
public:
    Interval();
    Interval(T begin, T end);
    T begin;
    T end;
};

template <class T>
inline Interval<T>::Interval() {
    begin = 0;
    end = 0;
}

template <class T>
inline Interval<T>::Interval(T begin, T end) {
    this->begin = begin;
    this->end = end;
}

} //~ namespace ycg

#endif /* INTERVAL_HPP */
