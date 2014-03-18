#ifndef VECTOR_H
#define VECTOR_H

#include "Common.h"
#include <iostream>
#include <cassert>

namespace ycg {

class Matrix;

class Vector {
public:
	Vector();
	Vector(int size, double initValue = 0.0);
	Vector(int size, bool needInit, double initValue = 0.0);
    Vector(const Vector& orig);
    Vector(Vector&& orig);
	~Vector();
	Vector& operator = (const Vector& rhs);
	Vector& operator = (Vector&& rhs);
	int size() const { return _size; };
	double* data() { return _data; }
	const double* data() const { return _data; }
	double dotProd(const Vector& rhs) const;
	double& operator [] (int index) { return _data[index]; }
    const double& operator [] (int index) const { return _data[index]; }
    double& operator () (int index) { return _data[index]; }
    const double& operator () (int index) const { return _data[index]; }
    Vector& operator += (const Vector& rhs);
    Vector& operator -= (const Vector& rhs);
    friend Vector operator + (const Vector& lhs, const Vector& rhs);
    friend Vector operator - (const Vector& lhs, const Vector& rhs);
    friend Vector operator * (double k, const Vector& rhs);
    friend Vector operator * (const Vector& lhs, double k);
    friend std::ostream& operator << (std::ostream& os, const Vector& vec);
    friend double dotProd(const Vector& lhs, const Vector& rhs);
    friend double normL2(const Vector& vec);
    friend double normL2Sqr(const Vector& vec);
    friend class Matrix;
//    Vector operator + (const Vector& rhs) const;


//    Vector& operator *= (double k);
public:
    static Vector rand(int size);
    static double distanceL2(const Vector& lhs, const Vector& rhs);

//    static double dotProduct(const Vector& lhs, const Vector& rhs);
//    static double normL0(const Vector& vec);
//    static double normL1(const Vector& vec);

//    static double normLP(const Vector& vec, double p);
//    static double normINF(const Vector& vec);
	friend void print(const Vector& vec);
private:
    int _size;
	double* _data;
};

Vector operator + (const Vector& lhs, const Vector& rhs);
Vector operator - (const Vector& lhs, const Vector& rhs);
Vector operator * (double k, const Vector& rhs);
Vector operator * (const Vector& lhs, double k);
std::ostream& operator << (std::ostream& os, const Vector& vec);
inline double dotProd(const Vector& lhs, const Vector& rhs) { return lhs.dotProd(rhs); }
double normL2(const Vector& vec);
double normL2Sqr(const Vector& vec);

} //~ namespace ycg
#endif // VECTOR_H
