#pragma once

class Timer {
public:
	Timer(int milliseconds, bool startNow);
	void ResetTimer();
	void ResetTimer(int milliseconds);
	void StartTimer();
	void PauseTimer();
	bool hasRung();

	void Update(int deltaTime);
private:
	bool isRunning_ = false;
	int timeToPass_;
	int timePassed_ = 0;
};