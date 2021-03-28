#pragma once

#include "StaticImage.h"

#include <string>

class SmallIcon : public StaticImage {
public:
	static const int cW;
	static const int cH;

	SmallIcon(Position pos, std::string filename) : StaticImage(pos, cW, cH, filename) {
	};
};