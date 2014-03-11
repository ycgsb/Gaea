#include "Random.h"

namespace ycg {

Random* Random::_instance = nullptr;

Random& Random::instance() {
    if (_instance == nullptr) {
        static Random rand;
        _instance = &rand;
    }
    return *_instance;
}

Random::Random() {
    _state = time(nullptr);
}

double Random::gauss() {
    static double v1, v2, s;
    static int phase = 0;
    double x;
    if (phase == 0) {
    	do {
            double U1 = nextDouble();
            double U2 = nextDouble();
            v1 = 2 * U1 - 1;
            v2 = 2 * U2 - 1;
            s = v1 * v1 + v2 * v2;
        } while(s >= 1 || s == 0);
        x = v1 * sqrt(-2 * log(s) / s);
    } else {
        x = v2 * sqrt(-2 * log(s) / s);
    }
    phase = 1 - phase;
    return x;
}

double Random::gauss(double mean, double std) {
	return mean + gauss() * std;
}

} //~ namespace ycg
