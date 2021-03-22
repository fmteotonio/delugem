#pragma once

#include "GameObject.h"

class PlayButton : public GameObject {
public:
	PlayButton(float x, float y);

	bool clicked();

	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

private:

	GameObject* playText_;
	bool clicked_;
};