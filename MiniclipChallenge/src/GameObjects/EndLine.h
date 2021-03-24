#pragma once

#include "GameObject.h"

class EndLine : public GameObject {
public:
	EndLine(float x, float y);

	void Update(int deltaTime);
	void Render();
};