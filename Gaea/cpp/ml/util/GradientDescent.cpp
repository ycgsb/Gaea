#include "GradientDescent.h"

namespace ycg {

GradientDescentConfig::GradientDescentConfig(double learningRate,
		int maxIteration, double convergeEps, bool showProcess) {
	this->learningRate = learningRate;
	this->maxIteration = maxIteration;
	this->convergeEps = convergeEps;
	this->showProcess = showProcess;
}

} //~ namespace ycg
