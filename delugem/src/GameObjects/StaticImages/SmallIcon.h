#pragma once

#include <string>

#include "StaticImage.h"

class SmallIcon : public StaticImage {
public:

	static const Dimensions cDim;

	SmallIcon(Position pos, std::string filename) : StaticImage(pos, cDim, filename) {
	};

};