#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_
#include <SDL.h>

class MyTimer {
private:
	bool started, paused;
	Uint32 startTicks, pausedTicks;
public:
	MyTimer();
	~MyTimer();
	void start();
	void stop();
	void pause();
	void unpause();
	bool isStarted();
	bool isPaused();
	Uint32 getTicks();

};

#endif // !_MY_TIMER_H_

