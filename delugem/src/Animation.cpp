#include "Animation.h"

Animation::Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame) {
	_firstFrame = firstFrame;
	_lastFrame = lastFrame;
	_frameRow = frameRow;
	_msPerFrame = msPerFrame;
	_currentFrame = _firstFrame;
}

Animation::Animation(int onlyFrame, int frameRow) {
	_firstFrame = onlyFrame;
	_lastFrame = onlyFrame;
	_frameRow = frameRow;
	_msPerFrame = 0;
	_currentFrame = _firstFrame;
}

bool Animation::isPlaying() { 
	return _isPlaying; 
}

int Animation::GetFrameRow()   { 
	return _frameRow; 
}

int Animation::GetCurrentFrame() {
	return _currentFrame;
}

/* Returns true if last frame was reached at least once. */
bool Animation::HasPlayedOnce() {
	if (_isPlaying && _msPerFrame > 0)
		return _timePassed / _msPerFrame >= (_lastFrame - _firstFrame);
	else
		return false;
}

void Animation::SetCurrentFrame(int frame) {
	_currentFrame = frame;
}


void Animation::Play() {
	_timePassed = 0;
	_isPlaying = true;
}

void Animation::Update(int deltaTime) {
	if (_isPlaying && _msPerFrame > 0) {
		_timePassed += deltaTime;
		_currentFrame = (_timePassed / _msPerFrame) % (_lastFrame - _firstFrame + 1);
	}
}