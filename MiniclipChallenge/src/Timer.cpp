#include "Timer.h"

Timer::Timer(int milliseconds, bool startNow) {
	_timeToPass = milliseconds;
	_isRunning = startNow;
}

bool Timer::IsRunning() { return _isRunning; }

void Timer::ResetTimer() {
	_timePassed = 0;
	_isRunning = true;
}

void Timer::ResetTimer(int milliseconds) {
	_timeToPass = milliseconds;
	_timePassed = 0;
	_isRunning = true;
}

void Timer::StartTimer() {
	_isRunning = true;
}

void Timer::PauseTimer() {
	_isRunning = false;
}

bool Timer::HasRung() {
	return (_isRunning && _timePassed > _timeToPass);
}

float Timer::HowMuchPassed() {
	return _timePassed / (_timeToPass * 1.0f);
}

void Timer::Update(int deltaTime) {
	if (_isRunning)
		_timePassed += deltaTime;
}