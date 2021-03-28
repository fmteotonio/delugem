#pragma once

class Timer {
public:
	Timer(int milliseconds, bool startNow);
	bool IsRunning();
	void ResetTimer();
	void ResetTimer(int milliseconds);
	void StartTimer();
	void PauseTimer();
	bool HasRung();
	float HowMuchPassed();

	void Update(int deltaTime);
private:
	bool _isRunning = false;
	int _timeToPass;
	int _timePassed = 0;
};