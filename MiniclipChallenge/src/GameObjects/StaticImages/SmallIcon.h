#pragma once

#include "StaticImage.h"

#include <string>

class SmallIcon : public StaticImage {
public:
	static const int cW;
	static const int cH;

	SmallIcon(float x, float y, std::string filename) : StaticImage(x, y, cW, cH, filename) {
	};
};