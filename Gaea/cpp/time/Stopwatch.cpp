#include "Stopwatch.h"
#include <ctime>

namespace ycg {

const int Stopwatch::CLOCKS_PER_SECOND = CLOCKS_PER_SEC;

Stopwatch::Stopwatch() {
	currentState = STATE_STOPPED;
	baseTime = 0;
	elapsed = 0;
}

Stopwatch& Stopwatch::start() {
	switch (currentState) {
		case STATE_STOPPED:
			currentState = STATE_RUNNING;
			baseTime = clock();
			break;
		case STATE_RUNNING:
			break;
		default:
			break;
	}
	return *this;
}

Stopwatch& Stopwatch::stop() {
	switch (currentState) {
		case STATE_STOPPED:
			break;
		case STATE_RUNNING:
			currentState = STATE_STOPPED;
			elapsed = clock() - baseTime;
			break;
		default:
			break;
	}
	return *this;
}

} //~ namespace ycg
