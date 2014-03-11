#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Point2D.hpp"

namespace ycg {

class Triangle {
public:
	Triangle();
    Triangle(const Point2D64F &p0, const Point2D64F &p1, const Point2D64F &p2);
    Point2D64F computeExocenter() const;
public:
    Point2D64F p0, p1, p2;
};

Triangle::Triangle():p0(), p1(), p2() {
}

Triangle::Triangle(const Point2D64F &p0, const Point2D64F &p1, const Point2D64F &p2) {
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

Point2D64F Triangle::computeExocenter() const {
    Point2D64F v0 = p2 - p1;
    Point2D64F v1 = p2 - p0;
    Point2D64F v2 = p1 - p0;
    double p = v0.dotProduct(p0);
    double q = v1.dotProduct(p1);
    double r = v2.dotProduct(p2);
    Point2D64F pp1((p*v1.y-q*v0.y)/(v0.crossProduct(v1)), (v0.x*q-v1.x*p)/(v0.crossProduct(v1)));
    Point2D64F pp2((q*v2.y-r*v1.y)/(v1.crossProduct(v2)), (v1.x*r-v2.x*q)/(v1.crossProduct(v2)));
    Point2D64F pp3((p*v2.y-r*v0.y)/(v0.crossProduct(v2)), (v0.x*r-v2.x*p)/(v0.crossProduct(v2)));
    Point2D64F center = (pp1 + pp2 + pp3) / 3;
    if(center.length() < 1e-6) {
        center.x = 0.0;
        center.y = 0.0;
    }
    return center;
}

} //~ namespace ycg


#endif // TRIANGLE_HPP
