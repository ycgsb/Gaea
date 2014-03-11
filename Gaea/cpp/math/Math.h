#ifndef MATH_H
#define MATH_H

#include <cmath>

namespace ycg {

namespace Math {
	const double E = 2.7182818284590452354;
	const double PI = 3.14159265358979323846;
    template <class T> static const T& max(const T &a, const T &b) {
    	return (a < b)? b : a;
    }
    template <class T> static const T& min(const T &a, const T &b) {
        return (a < b)? a : b;
    }
    template <class T> static const T& max(const T* array, int n);
    template <class T> static const T& min(const T* array, int n);
    static int abs(int x);
    static double abs(double x);
    template <class T> static T sqr(T x) { return x*x; }
    static double sqrt(double x) { return ::sqrt(x); }
    static int sum(const int *a, int length);
    static int power(int x, int p);

    inline double sin(double x) { return ::sin(x); }
    inline double cos(double x) { return ::cos(x); }

    template <class Iter> double mean(Iter begin, Iter end);
    template <class Iter> double var(Iter begin, Iter end);
    template <class Iter> double std(Iter begin, Iter end);

} //~ namespace math

template <class T>
const T& Math::max(const T* array, int n) {
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (array[index] < array[i]) {
            index = i;
        }
    }
    return array[index];
}

template <class T>
const T& Math::min(const T* array, int n) {
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (array[i] < array[index]) {
            index = i;
        }
    }
    return array[index];
}

inline int Math::abs(int x) {
	return (x >= 0) ? x : -x;
}

inline double Math::abs(double x) {
	return (x >= 0) ? x : -x;
}

//double average(const double* arr, int n) {
//    if (n <= 0) return 0.0;
//    double sum = 0.0;
//    for(int i = 0; i < n; i++) {
//         sum += arr[i];
//    }
//    double avg = sum / n;
//    return avg;
//}


template <class Iter>
double Math::mean(Iter begin, Iter end) {
	if (begin == end) { return 0.0; }
	int n = 0;
	double sum = 0.0;
	for (Iter it = begin; it != end; ++it) {
		n++;
		sum += *it;
	}
	double mean = sum / n;
	return mean;
}

template <class Iter>
double Math::var(Iter begin, Iter end) {
	if (begin == end) { return 0.0; }
	int n = 0;
	double sum = 0.0;
	double sqsum = 0.0;
	for (Iter it = begin; it != end; ++it) {
		sum += *it;
		sqsum += (*it)*(*it);
		++n;
	}
	double m1 = sqsum / n;
	double m2 = sum / n;
	double var = m1 - m2*m2;
	return var;
}

template <class Iter>
double Math::std(Iter begin, Iter end) {
	return sqrt(var(begin, end));
}

}  //~ namespace ycg
//const int OO = 2000000000;

//inline double angleToRadian(double angle) { return angle * PI / 180.0; }

//}  // namespace math





//inline bool isOdd(int x) {
//	return (x & 0x00000001);
//}

//inline bool isEven(int x) {
//	return (x & 0x00000001) == 0;
//}

//inline double round(double x) {
//	int temp = (x > 0) ? (int)(x+0.5) : (int)(x-0.5);
//	return (double)temp;
//}

#endif // MATH_H
