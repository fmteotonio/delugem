#include "Timer.h"

Timer::Timer(int milliseconds, bool startNow) {
	_timeToPass = milliseconds;
	_isRunning = startNow;
}

bool Timer::IsRunning() {
	return _isRunning;
}

bool Timer::HasEnded() {
	return (_isRunning && _timePassed > _timeToPass);
}

/* Returns timer progress from 0 to 1 */
float Timer::HowMuchPassed() {
	return _timePassed / static_cast<float>(_timeToPass);
}

void Timer::StartTimer() {
	_isRunning = true;
}

void Timer::PauseTimer() {
	_isRunning = false;
}

void Timer::ResetTimer() {
	_timePassed = 0;
	_isRunning = true;
}

void Timer::ResetTimer(int milliseconds) {
	_timeToPass = milliseconds;
	_timePassed = 0;
	_isRunning = true;
}

void Timer::Update(int deltaTime) {
	if (_isRunning)
		_timePassed += deltaTime;
}