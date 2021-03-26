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
	bool HasPlayedOnce();
	
private:
	int firstFrame_;
	int lastFrame_;
	int frameRow_;

	int startTime_ = 0;
	int timePassed_ = 0;
	int timePerFrame;

	bool isPlaying_ = false;
};