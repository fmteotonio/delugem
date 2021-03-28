#include "Text.h"

#include "../../Constants.h"
#include "../../TextureManager.h"

Text::Text(Position pos, Align align, std::string font, int size, std::string text, SDL_Color color) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadText(font, size, text, color);

	int w, h;
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);

	float xAux = 0;
	float yAux = 0;

	switch (align) {
		case Align::UPLEFT:		{ xAux = pos.x;			yAux = pos.y;			break; }
		case Align::UP:			{ xAux = pos.x - w / 2; yAux = pos.y;			break; }
		case Align::UPRIGHT:	{ xAux = pos.x - w;		yAux = pos.y;			break; }
		case Align::MIDLEFT:	{ xAux = pos.x;			yAux = pos.y - h / 2;	break; }
		case Align::MID:		{ xAux = pos.x - w / 2; yAux = pos.y - h / 2;	break; }
		case Align::MIDRIGHT:	{ xAux = pos.x - w;		yAux = pos.y - h / 2;	break; }
		case Align::DOWNLEFT:	{ xAux = pos.x;			yAux = pos.y - h;		break; }
		case Align::DOWN:		{ xAux = pos.x - w / 2;	yAux = pos.y - h;		break; }
		case Align::DOWNRIGHT:	{ xAux = pos.x - w;		yAux = pos.y - h;		break; }
	}

	//Specific Font Fixes
	if		(font == FNT_M6X11) { yAux += size/16; }
	else if (font == FNT_M3X6)	{ yAux -= 2*size / 16; }

	AddAnimation("Default", new Animation(0, 0));

	AnimatedGameObject::Init({ xAux, yAux }, w, h, objTexture, "Default", false);
}