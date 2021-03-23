#pragma once

#include <string>

class Animation {
public:
	Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame);
	Animation(int onlyFrame, int frameRow);

	bool isPlaying();
	int frameRow();

	void Play();
	int getCurrentFrame();
	bool PlayedOnce();
	
	void Update(int deltaTime);

private:
	int firstFrame_;
	int lastFrame_;
	int frameRow_;
	int msPerFrame_;

	bool isPlaying_ = false;
	int startTime_ = 0;

	int timePassed_ = 0;
};