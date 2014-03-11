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
    static double V1, V2, S;
    static int phase = 0;
    double X;
    if ( phase == 0 ) {
    	do {
            double U1 = nextDouble();
            double U2 = nextDouble();
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);
        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);
    phase = 1 - phase;
    return X;
}

double Random::gauss(double mean, double std) {
	return mean + gauss() * std;
}

} //~ namespace ycg
