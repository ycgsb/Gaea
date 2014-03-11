#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

namespace ycg {

class Stopwatch {
public:
	Stopwatch();
	Stopwatch& start();
	Stopwatch& stop();
	bool isRunning();
	int elapsedClocks();
	int elapsedMilliseconds();
private:
	static const int CLOCKS_PER_SECOND;
	static const int STATE_STOPPED = 0;
	static const int STATE_RUNNING = 1;
	int currentState;
	int elapsed;
	int baseTime;
};

inline bool Stopwatch::isRunning() {
	return (currentState == STATE_RUNNING);
}

inline int Stopwatch::elapsedClocks() {
	if (isRunning()) {
		elapsed = clock() - baseTime;
	}
	return elapsed;
}

inline int Stopwatch::elapsedMilliseconds() {
	return elapsedClocks() * 1000 / CLOCKS_PER_SECOND;
}

} // namespace ycg

#endif // STOPWATCH_H
