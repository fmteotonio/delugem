#pragma once

#include "GameObject.h"

class PlayButton : public GameObject {
public:
	PlayButton(float x, float y);

	bool clicked();

	void Update(int deltaTime);
	void HandleInput();
	void Render();

private:
	bool clicked_;
};