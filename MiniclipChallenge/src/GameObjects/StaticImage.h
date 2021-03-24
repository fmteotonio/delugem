#pragma once

#include "GameObject.h"

#include <string>

class StaticImage : public GameObject {
public:
	StaticImage(float x, float y, int w, int h, std::string filename);

	void Update(int deltaTime);
	void Render();
};