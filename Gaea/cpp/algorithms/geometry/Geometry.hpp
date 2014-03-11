#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include "Point2D.h"

namespace ycg {

class Geometry {
public:
    static int dblcmp(double x);
};



inline int Geometry::dblcmp(double x) {
    if(-1e-6 < x && x < 1e-6) return 0;
    return (x>0)? 1 : -1;
}

}  //~ namespace ycg


#endif // GEOMETRY_H
