#include "Animation.h"

Animation::Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame) {
	firstFrame_ = firstFrame;
	lastFrame_ = lastFrame;
	frameRow_ = frameRow;
	timePerFrame = msPerFrame;
}

Animation::Animation(int onlyFrame, int frameRow) {
	firstFrame_ = onlyFrame;
	lastFrame_ = onlyFrame;
	frameRow_ = frameRow;
	timePerFrame = 0;
}

bool Animation::isPlaying() { return isPlaying_; }
int Animation::frameRow()   { return frameRow_; }

void Animation::Update(int deltaTime) {
	if (isPlaying_)
		timePassed_ += deltaTime;
}

void Animation::Play() {
	timePassed_ = 0;
	isPlaying_ = true;
}

int Animation::GetCurrentFrame() {
	if (isPlaying_ && timePerFrame > 0)
		return (timePassed_ / timePerFrame) % (lastFrame_ - firstFrame_ + 1);
	else
		return firstFrame_;
}

bool Animation::HasPlayedOnce() {
	//returns true if last frame was reached once.
	if (isPlaying_ && timePerFrame > 0)
		return timePassed_ / timePerFrame >= (lastFrame_ - firstFrame_);
	else
		return false;
}

