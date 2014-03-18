#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include "../../numerical/Vector.h"
#include <iostream>

namespace ycg {

class GradientDescentConfig {
public:
	GradientDescentConfig(double learningRate, int maxIteration = 10000000,
			double convergeEps = 1e-12, bool showProcess = false);
public:
	double learningRate;
	int maxIteration;
	double convergeEps;
	bool showProcess;
};

class GradientDescent {
public:
	GradientDescent(const GradientDescentConfig& config) : _config(config) { }
	virtual ~GradientDescent() { }
	template <class Func, class Grad>
	Vector compute(const Vector& init, Func function, Grad gradient);
private:
	const GradientDescentConfig& _config;
};

template<class Func, class Grad>
Vector GradientDescent::compute(const Vector& init, Func function, Grad gradient) {
	if (_config.showProcess) {
		std::cout << "gradient descent start.\n";
	}
	Vector var = init;
	int countIter = 0;
	while (true) {
		++countIter;
		if (_config.showProcess) {
			std::cout << "iteration " << countIter << ", var = ("
					  << var << "), fun = " << function(var) << ".\n";
		}
		Vector delta = _config.learningRate * gradient(var);
		var -= delta;
		if (countIter >= _config.maxIteration || normL2(delta) < _config.convergeEps) {
			break;
		}
	}
	if (_config.showProcess) {
		if (countIter < _config.maxIteration) {
			std::cout << "gradient descent converges at " << countIter << "iteration.\n";
		} else {
			std::cout << "max iteration exceeded, gradient descent not converges.\n";
		}
	}
	return var;
}

} //~ namespace ycg

#endif /* GRADIENTDESCENT_H */
