#pragma once

#include <string>

class Animation {
public:
	Animation(std::string id, int firstFrame, int lastFrame, int frameRow, int msPerFrame);
	Animation(std::string id, int onlyFrame, int frameRow);

	std::string id();
	int frameRow();

	void Play();
	int getCurrentFrame();
	int PlayedOnce();
	
private:
	std::string id_;
	int firstFrame_;
	int lastFrame_;
	int frameRow_;
	int msPerFrame_;

	bool isPlaying_ = false;
	int startTime_ = 0;
};