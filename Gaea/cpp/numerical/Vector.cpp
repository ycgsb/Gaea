#include "Vector.h"
#include "../io/Writer.h"
#include <cmath>

namespace ycg {

Vector::Vector() :
	_size(0),
	_data(nullptr) { }

Vector::Vector(int size, double initValue) :
	_size(size),
	_data(new double[_size]) {
    for (int i = 0; i < _size; ++i) {
        _data[i] = initValue;
    }
}

Vector::Vector(int size, bool needInit, double initValue) :
	_size(size),
	_data(new double[_size]) {
    if (needInit) {
    	for (int i = 0; i < _size; ++i) {
    		_data[i] = initValue;
    	}
    }
}

Vector::Vector(const Vector& orig) {
    _size = orig._size;
    _data = new double[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = orig._data[i];
    }
}

Vector::Vector(Vector&& orig) {
	_size = orig._size;
	_data = orig._data;
	orig._data = nullptr;
}

Vector::~Vector() {
    freeData();
}

void Vector::freeData() {
	delete []_data;
    _data = nullptr;
}

Vector& Vector::operator = (const Vector& rhs) {
    if (this == &rhs) {
    	return *this;
    }
    freeData();
    _size = rhs._size;
    _data = new double[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = rhs._data[i];
    }
    return *this;
}

Vector& Vector::operator =  (Vector&& rhs) {
	if (this == &rhs) {
		return *this;
	}
	freeData();
	_size = rhs._size;
	_data = rhs._data;
	rhs._data = nullptr;
	return *this;
}

//Vector Vector::operator + (const Vector& rhs) const {
//    assert(this->size() == rhs.size());
//    Vector result(rhs.elemNum);
//    for (int i = 0; i < elemNum; ++i) {
//        result.data[i] = this->data[i] + rhs.data[i];
//    }
//    return result;
//}
//
//Vector& Vector::operator += (const Vector& rhs) {
//    assert(this->size() == rhs.size());
//    for (int i = 0; i < elemNum; ++i) {
//        this->data[i] += rhs.data[i];
//    }
//    return *this;
//}
//
//Vector Vector::operator -(const Vector& rhs) const {
//    assert(this->size() == rhs.size());
//    Vector result(rhs.elemNum);
//    for (int i = 0; i < elemNum; ++i) {
//        result.data[i] = this->data[i] - rhs.data[i];
//    }
//    return result;
//}
//
//Vector& Vector::operator -= (const Vector& rhs) {
//    assert(this->size() == rhs.size());
//    for (int i = 0; i < elemNum; ++i) {
//        this->data[i] -= rhs.data[i];
//    }
//    return *this;
//}
//
//Vector Vector::operator * (double k) const {
//    Vector result(elemNum);
//    for (int i = 0; i < elemNum; ++i) {
//        result.data[i] = this->data[i] * k;
//    }
//    return result;
//}
//
//Vector& Vector::operator *=(double k) {
//    for (int i = 0; i < elemNum; ++i) {
//        this->data[i] *= k;
//    }
//    return *this;
//}
//
//double Vector::dotProduct(const Vector& lhs, const Vector& rhs) {
//    assert(lhs.size() == rhs.size());
//    double result = 0.0;
//    for (int i = 0; i < lhs.elemNum; ++i) {
//        result += lhs.data[i] * rhs.data[i];
//    }
//    return result;
//}

double Vector::distanceL2(const Vector& lhs, const Vector& rhs) {
    assert(lhs.size() == rhs.size());
    double sum = 0.0;
    for (int i = 0; i < lhs._size; ++i) {
        double delta = lhs._data[i] - rhs._data[i];
        sum += delta * delta;
    }
    double distance = sqrt(sum);
    return distance;
}

//double Vector::normL1(const Vector &vec) {
//    double norm = 0.0;
//    for (int i = 0; i < vec.elemNum; ++i) {
//        norm += fabs(vec.data[i]);
//    }
//    return norm;
//}

std::ostream& operator << (std::ostream& os, const Vector& vec) {
	for (int i = 0; i < vec._size; ++i) {
		if (i > 0) { os << " "; }
		os << vec._data[i];
	}
	return os;
}

void print(const Vector& vec) {
	Writer writer;
	writer.print("Vector:").print(vec._size).println(" x 1:");
	for (int i = 0; i < vec._size; ++i) {
		writer.print('\t').println(vec._data[i]);
	}
}

} //~ namespace ycg
