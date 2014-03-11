#ifndef VECTOR_H
#define VECTOR_H

#include "Common.h"
#include <cassert>

namespace ycg {

class Vector {
public:
	Vector();
	Vector(int size, double initValue = 0.0);
	Vector(int size, bool needInit, double initValue = 0.0);
    Vector(const Vector& orig);
    Vector(Vector&& orig);
	~Vector();
	int size() const;
	double& operator [] (int index);
    const double& operator [] (int index) const;
    double& operator () (int index);
    const double& operator () (int index) const;
	Vector& operator = (const Vector& rhs);



//
//    Vector operator + (const Vector& rhs) const;
//    Vector& operator += (const Vector& rhs);
//    Vector operator - (const Vector& rhs) const;
//    Vector& operator -= (const Vector& rhs);
//    Vector operator * (double k) const;
//    Vector& operator *= (double k);
public:
    static double distanceL2(const Vector& lhs, const Vector& rhs);
//    static double dotProduct(const Vector& lhs, const Vector& rhs);
//    static double normL0(const Vector& vec);
//    static double normL1(const Vector& vec);
//    static double normL2(const Vector& vec);
//    static double normLP(const Vector& vec, double p);
//    static double normINF(const Vector& vec);
	friend void print(const Vector& vec);
private:
    void freeData();
private:
    int _size;
	double* _data;
};

inline int Vector::size() const {
    return _size;
}

inline double& Vector::operator [] (int index) {
    return _data[index];
}

inline const double& Vector::operator [] (int index) const {
    return _data[index];
}

inline double& Vector::operator () (int index) {
    return _data[index];
}

inline const double& Vector::operator () (int index) const {
    return _data[index];
}

//inline Vector operator * (double k, const Vector& vec) {
//    return vec * k;
//}

} //~ namespace ycg
#endif // VECTOR_H
