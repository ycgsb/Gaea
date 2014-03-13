#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include "../../numerical/Vector.h"
#include <iostream>

namespace ycg {

class GradientDescentConfig {
public:
	GradientDescentConfig(double learningRate, int maxIteration = 10000000,
			double changeEps = 1e-14, bool showProcess = false) {
		this->learningRate = learningRate;
		this->maxIteration = maxIteration;
		this->changeEps = changeEps;
		this->showProcess = showProcess;
	}
public:
	double learningRate;
	int maxIteration;
	double changeEps;
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
		if (countIter > _config.maxIteration || normL2(delta) < _config.changeEps) {
			break;
		}
	}
	if (_config.showProcess) {
		if (countIter <= _config.maxIteration) {
			std::cout << "gradient descent converges at " << countIter << "iteration.\n";
		} else {
			std::cout << "max iteration exceeded, gradient descent not converges.\n";
		}
	}
	return var;
}

} //~ namespace ycg

#endif /* GRADIENTDESCENT_H */
