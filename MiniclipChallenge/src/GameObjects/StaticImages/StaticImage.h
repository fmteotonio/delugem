#pragma once

#include "../AnimatedGameObject.h"

#include <string>

class StaticImage : public AnimatedGameObject {
public:
	StaticImage(float x, float y, int w, int h, std::string filename);
};