#pragma once

class Animation {
public:

	Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame);
	Animation(int onlyFrame, int frameRow);

	bool isPlaying();
	int GetFrameRow();
	int GetLastFrame();
	int GetCurrentFrame();
	bool HasPlayedOnce();
	
	void SetCurrentFrame(int frame);
	void Play();
	
	void Update(int deltaTime);
	
private:

	int _firstFrame;
	int _lastFrame;
	int _frameRow;
	int _msPerFrame;
	
	int _currentFrame;
	int _timePassed = 0;
	bool _isPlaying = false;

};