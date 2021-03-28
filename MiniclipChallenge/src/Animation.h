#pragma once

class Animation {
public:
	Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame);
	Animation(int onlyFrame, int frameRow);

	bool isPlaying();
	int GetFrameRow();

	void Update(int deltaTime);

	void Play();
	int GetCurrentFrame();
	void SetCurrentFrame(int frame);
	bool HasPlayedOnce();
	
private:
	int _firstFrame;
	int _lastFrame;
	int _frameRow;

	int _timePassed = 0;
	int _timePerFrame;

	int _currentFrame;

	bool _isPlaying = false;
};