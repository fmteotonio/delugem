#pragma once

#include "GameObject.h"

class ForegroundStrip : public GameObject {
public:
	ForegroundStrip(float x, float y);

	void Update(int deltaTime);
	void Render();
};