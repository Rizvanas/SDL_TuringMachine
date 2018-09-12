#include "MyTimer.h"

MyTimer::MyTimer() 
	: started{ false }, paused{ false }, startTicks{ 0 }, pausedTicks{ 0 } {
}

MyTimer::~MyTimer() {
}

void MyTimer::start() {
	if (!started) {
		started = true;
		paused = false;
		startTicks = SDL_GetTicks();
		pausedTicks = 0;
	}
}

void MyTimer::stop() {
	if (started) {
		started = false;
		paused = false;
		startTicks = 0;
		pausedTicks = 0;
	}
}

void MyTimer::pause() {
	if (started && !paused) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}

}

void MyTimer::unpause() {
	if (started && paused) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

bool MyTimer::isStarted() {
	return started;
}

bool MyTimer::isPaused() {
	return paused;
}

Uint32 MyTimer::getTicks() {
	if (started) {
		if (paused) {
			return pausedTicks;
		} else {
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}
