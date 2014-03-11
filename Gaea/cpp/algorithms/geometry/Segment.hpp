#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "Point2D.h"

namespace ycg {

template <class T>
class Segment {
public:
	double length() const;
private:
	Point2D<T> start;
	Point2D<T> end;

};

} //~ namespace ycg


#endif
