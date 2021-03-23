#include "Text.h"

#include "../Constants.h"
#include "../TextureManager.h"
#include "../InputHandler.h"

#include "../GameStates/TitleScreenState.h"

Text::Text(float x, float y, Align align, std::string font, int size, std::string text, int r, int g, int b) {
	SDL_Texture* objTexture = TextureManager::Instance()->LoadText(font, size, text, r, g, b);

	int w, h;
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);

	float xAux = 0;
	float yAux = 0;

	switch (align) {
		case Align::UPLEFT:		{ xAux = x;			yAux = y;			break; }
		case Align::UP:			{ xAux = x - w / 2; yAux = y;			break; }
		case Align::UPRIGHT:	{ xAux = x - w;		yAux = y;			break; }
		case Align::MIDLEFT:	{ xAux = x;			yAux = y - h / 2;	break; }
		case Align::MID:		{ xAux = x - w / 2; yAux = y - h / 2;	break; }
		case Align::MIDRIGHT:	{ xAux = x - w;		yAux = y - h / 2;	break; }
		case Align::DOWNLEFT:	{ xAux = x;			yAux = y - h;		break; }
		case Align::DOWN:		{ xAux = x - w / 2;	yAux = y - h;		break; }
		case Align::DOWNRIGHT:	{ xAux = x - w;		yAux = y - h;		break; }
	}

	//Specific Font Fixes
	if		(font == FNT_M6X11) { yAux += size/16; }
	else if (font == FNT_M3X6)	{ yAux -= 2*size / 16; }

	GameObject::Init(xAux, yAux, w, h, objTexture, new Animation(0, 0));
}

void Text::Update(int deltaTime) {
	GameObject::Update(deltaTime);
}

void Text::Render() {
	GameObject::Render();
}

void Text::Clean() {
	GameObject::Clean();
}

