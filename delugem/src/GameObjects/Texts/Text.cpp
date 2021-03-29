#include "Text.h"

#include "../../Constants.h"
#include "../../TextureManager.h"

const char* Text::cAnimDefault = "Default";

Text::Text(Position pos, Align align, std::string font, int size, std::string text, SDL_Color color) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadText(font, size, text, color);

	int w, h;
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);

	float x = 0;
	float y = 0;

	//Offset real position from arguments to align text
	switch (align) {
		case Align::UPLEFT:		{ x = pos.x;			y = pos.y;			break; }
		case Align::UP:			{ x = pos.x - w / 2;	y = pos.y;			break; }
		case Align::UPRIGHT:	{ x = pos.x - w;		y = pos.y;			break; }
		case Align::MIDLEFT:	{ x = pos.x;			y = pos.y - h / 2;	break; }
		case Align::MID:		{ x = pos.x - w / 2;	y = pos.y - h / 2;	break; }
		case Align::MIDRIGHT:	{ x = pos.x - w;		y = pos.y - h / 2;	break; }
		case Align::DOWNLEFT:	{ x = pos.x;			y = pos.y - h;		break; }
		case Align::DOWN:		{ x = pos.x - w / 2;	y = pos.y - h;		break; }
		case Align::DOWNRIGHT:	{ x = pos.x - w;		y = pos.y - h;		break; }
	}

	//Specific Font Fixes
	if		(font == FNT_M6X11) { y += size/16; }
	else if (font == FNT_M3X6)	{ y -= 2*size / 16; }

	AddAnimation(cAnimDefault, new Animation(0, 0));

	AnimatedGameObject::Init({ x, y }, { w, h }, objTexture, cAnimDefault, false);
}