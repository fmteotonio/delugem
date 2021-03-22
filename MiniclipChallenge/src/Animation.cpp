#include "Animation.h"

#include <SDL.h>
#include <algorithm>

Animation::Animation(std::string id, int firstFrame, int lastFrame, int frameRow, int msPerFrame) {
	id_ = id;
	firstFrame_ = firstFrame;
	lastFrame_ = lastFrame;
	frameRow_ = frameRow;
	msPerFrame_ = msPerFrame;
	isPlaying_ = false;
}

Animation::Animation(std::string id, int onlyFrame, int frameRow) {
	id_ = id;
	firstFrame_ = onlyFrame;
	lastFrame_ = onlyFrame;
	frameRow_ = frameRow;
	msPerFrame_ = 0;
	isPlaying_ = false;
}

std::string Animation::id() {
	return id_;
}
int Animation::frameRow() {
	return frameRow_;
}

void Animation::Play() {
	startTime_ = SDL_GetTicks();
	isPlaying_ = true;
}

int Animation::getCurrentFrame() {
	if (isPlaying_ && msPerFrame_ > 0)
		return ((SDL_GetTicks() - startTime_) / msPerFrame_) % (lastFrame_ - firstFrame_ + 1);
	else
		return firstFrame_;
}

int Animation::PlayedOnce() {
	return (SDL_GetTicks() - startTime_) / msPerFrame_ >= (lastFrame_ - firstFrame_ + 1);
}