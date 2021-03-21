#pragma once

#include "GameObject.h"

class Background : public GameObject {
public:
	Background(float x, float y);

	void Update(int deltaTime);
	void Render();
};