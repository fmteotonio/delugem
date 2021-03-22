#pragma once

#include "GameObject.h"

class PlayButtonText : public GameObject {
public:
	PlayButtonText(float x, float y);

	void Update(int deltaTime);
	void Render();
	void Clean();
};