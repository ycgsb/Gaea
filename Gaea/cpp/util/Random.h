#ifndef RANDOM_H
#define RANDOM_H

#include "../lang/Types.h"
#include <cmath>
#include <ctime>

namespace ycg {

class Random {
public:
    static Random& instance();
public:
    void changeSeed(uint64 seed) {
    	_state = seed;
    }
    uint32 nextInt() {
        _state = (uint64)(unsigned)_state * 4164903690U + (_state >> 32);
        return (uint32)_state;
    }
    double nextDouble() {
    	return (double)nextInt() / 0xffffffff;
    }
    int uniform(int start, int end) {
    	return start + nextInt() % (end-start);
    }
	double uniform(double begin, double end) {
		return begin + nextDouble() * (end - begin);
	}
	double gauss();
	double gauss(double mean, double std);
    template <class T> void shuffle(T* array, int size);
protected:
    Random();
    Random(const Random&);
    Random(Random&&);
    Random& operator= (const Random&);
    Random& operator= (Random&&);
    ~Random() { };
private:
    static Random *_instance;
    uint64 _state;
};

template <class T>
void Random::shuffle(T *array, int size){
    for(int i = 0; i < size; ++i) {
        int p = uniform(i, size);
        T temp = array[i];
        array[i] = array[p];
        array[p] = temp;
    }
}

} //~ namespace ycg


//    operator uchar();
//    operator schar();
//    operator ushort();
//    operator short();
//    operator unsigned();
//    //! returns a random integer sampled uniformly from [0, N).
//    unsigned operator ()(unsigned N);
//    unsigned operator ()();
//    operator int();
//    operator float();
//    operator double();

//    //! returns uniformly distributed floating-point random number from [a,b) range
//    float uniform(float a, float b);
//    //! returns uniformly distributed double-precision floating-point random number from [a,b) range
//    double uniform(double a, double b);
//    void fill( InputOutputArray mat, int distType, InputArray a, InputArray b, bool saturateRange=false );
//    //! returns Gaussian random variate with mean zero.
//    double gaussian(double sigma);
//#include <stdlib.h>
//#include <math.h>
//
//
//　　这样生成的高斯分布随机数序列的期望为0.0，方差为1.0。若指定期望为E，方差为V，则只需增加：
//X = X * V + E;

//};

#endif // RANDOM_H
