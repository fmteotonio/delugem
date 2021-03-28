#include "Animation.h"

Animation::Animation(int firstFrame, int lastFrame, int frameRow, int msPerFrame) {
	_firstFrame = firstFrame;
	_lastFrame = lastFrame;
	_frameRow = frameRow;
	_timePerFrame = msPerFrame;
	_currentFrame = _firstFrame;
}

Animation::Animation(int onlyFrame, int frameRow) {
	_firstFrame = onlyFrame;
	_lastFrame = onlyFrame;
	_frameRow = frameRow;
	_timePerFrame = 0;
	_currentFrame = _firstFrame;
}

bool Animation::isPlaying() { return _isPlaying; }
int Animation::GetFrameRow()   { return _frameRow; }

void Animation::Update(int deltaTime) {
	if (_isPlaying && _timePerFrame > 0) {
		_timePassed += deltaTime;
		_currentFrame = (_timePassed / _timePerFrame) % (_lastFrame - _firstFrame + 1);
	}
}

void Animation::Play() {
	_timePassed = 0;
	_isPlaying = true;
}

int Animation::GetCurrentFrame() {
	return _currentFrame;
}

void Animation::SetCurrentFrame(int frame) {
	_currentFrame = frame;
}

bool Animation::HasPlayedOnce() {
	//returns true if last frame was reached once.
	if (_isPlaying && _timePerFrame > 0)
		return _timePassed / _timePerFrame >= (_lastFrame - _firstFrame);
	else
		return false;
}

