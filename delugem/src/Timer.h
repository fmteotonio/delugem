#pragma once

class Timer {
public:

	Timer(int milliseconds, bool startNow);

	bool IsRunning();
	bool HasEnded();
	float HowMuchPassed();

	void StartTimer();
	void PauseTimer();
	void ResetTimer();
	void ResetTimer(int milliseconds);

	void Update(int deltaTime);

private:

	bool _isRunning = false;
	int _timePassed = 0;
	int _timeToPass;

};