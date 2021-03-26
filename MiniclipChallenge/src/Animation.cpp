#include "Animation.h"

Animation::Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame) {
	firstFrame_ = firstFrame;
	lastFrame_ = lastFrame;
	frameRow_ = frameRow;
	timePerFrame = msPerFrame;
	currentFrame_ = firstFrame_;
}

Animation::Animation(int onlyFrame, int frameRow) {
	firstFrame_ = onlyFrame;
	lastFrame_ = onlyFrame;
	frameRow_ = frameRow;
	timePerFrame = 0;
	currentFrame_ = firstFrame_;
}

bool Animation::isPlaying() { return isPlaying_; }
int Animation::GetFrameRow()   { return frameRow_; }

void Animation::Update(int deltaTime) {
	if (isPlaying_ && timePerFrame > 0) {
		timePassed_ += deltaTime;
		currentFrame_ = (timePassed_ / timePerFrame) % (lastFrame_ - firstFrame_ + 1);
	}
}

void Animation::Play() {
	timePassed_ = 0;
	isPlaying_ = true;
}

int Animation::GetCurrentFrame() {
	return currentFrame_;
}

void Animation::SetCurrentFrame(int frame) {
	currentFrame_ = frame;
}

bool Animation::HasPlayedOnce() {
	//returns true if last frame was reached once.
	if (isPlaying_ && timePerFrame > 0)
		return timePassed_ / timePerFrame >= (lastFrame_ - firstFrame_);
	else
		return false;
}

