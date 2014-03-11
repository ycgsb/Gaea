#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <cmath>

namespace ycg {

template <class T>
class Point2D {
public:
    Point2D();
    Point2D(T x, T y);
    Point2D<T> operator+ (const Point2D<T> &p1) const;
    Point2D<T> operator- (const Point2D<T> &p1) const;
    Point2D<T> operator* (T scale) const;
    Point2D<T> operator/ (T scale) const;
    T dotProduct(const Point2D<T> &p1) const;
    T crossProduct(const Point2D<T> &p1) const;
    double length() const;
    double distance(const Point2D<T> &p1) const;
public:
    T x, y;
};

template <class T>
inline Point2D<T>::Point2D() {
    x = y = 0;
}

template <class T>
inline Point2D<T>::Point2D(T x, T y) {
    this->x = x;
    this->y = y;
}

template <class T>
inline Point2D<T> Point2D<T>::operator+ (const Point2D<T> &p1) const {
    Point2D<T> result(x + p1.x, y + p1.y);
    return result;
}

template <class T>
inline Point2D<T> Point2D<T>::operator- (const Point2D<T> &p1) const {
    Point2D<T> result(x - p1.x, y - p1.y);
    return result;
}

template <class T>
inline Point2D<T> Point2D<T>::operator *(T scale) const {
    Point2D<T> result(x * scale, y * scale);
    return result;
}

template <class T>
inline Point2D<T> Point2D<T>::operator /(T scale) const {
    Point2D<T> result(x / scale, y / scale);
    return result;
}

template <class T>
inline T Point2D<T>::dotProduct(const Point2D<T> &p1) const {
    T result = x * p1.x + y * p1.y;
    return result;
}

template <class T>
inline T Point2D<T>::crossProduct(const Point2D<T> &p1) const {
    T result = x * p1.y - y * p1.x;
    return result;
}

template <class T>
inline double Point2D<T>::length() const {
    double result = sqrt(x * x + y * y);
    return result;
}

template <class T>
inline double Point2D<T>::distance(const Point2D<T> &p1) const {
    double dx = x - p1.x;
    double dy = y - p1.y;
    double result = sqrt(dx * dx + dy * dy);
    return result;
}

typedef Point2D<int> Point2D32I;
typedef Point2D<double>	Point2D64F;

typedef Point2D Vector2D;

}  //~ namespace ycg

#endif // POINT2D_HPP
