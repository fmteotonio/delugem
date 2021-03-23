#include "Animation.h"

#include <SDL.h>
#include <algorithm>

Animation::Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame) {
	firstFrame_ = firstFrame;
	lastFrame_ = lastFrame;
	frameRow_ = frameRow;
	msPerFrame_ = msPerFrame;
}

Animation::Animation(int onlyFrame, int frameRow) {
	firstFrame_ = onlyFrame;
	lastFrame_ = onlyFrame;
	frameRow_ = frameRow;
	msPerFrame_ = 0;
}

bool Animation::isPlaying() { return isPlaying_; }
int Animation::frameRow()   { return frameRow_; }

void Animation::Play() {
	timePassed_ = 0;
	isPlaying_ = true;
}

int Animation::getCurrentFrame() {
	if (isPlaying_ && msPerFrame_ > 0)
		return (timePassed_ / msPerFrame_) % (lastFrame_ - firstFrame_ + 1);
	else
		return firstFrame_;
}

bool Animation::PlayedOnce() {
	//returns true if last frame was reached once.
	if (isPlaying_ && msPerFrame_ > 0)
		return timePassed_ / msPerFrame_ >= (lastFrame_ - firstFrame_);
	else
		return false;
}

void Animation::Update(int deltaTime) {
	if (isPlaying_)
		timePassed_ += deltaTime;
}