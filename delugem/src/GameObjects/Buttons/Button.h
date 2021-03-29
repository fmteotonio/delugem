#pragma once

#include <string>
#include <vector>

#include "../AnimatedGameObject.h"

class Button : public AnimatedGameObject {
public:

	static const char* cAnimDefault;
	static const char* cAnimHovered;
	static const char* cAnimHovPressed;
	static const char* cAnimUnhovPressed;

	enum class ButtonState {
		DEFAULT, HOVERED, HOV_PRESSED, UNHOV_PRESSED, PRESS_ACTION, INACTIVE
	};

	Button(Position pos, Dimensions dim, std::string filename);

	ButtonState GetButtonState();

	void AddContent(GameObject* content);
	bool TransitState(ButtonState newButtonState);
	void OnlySetActiveIf(bool condition);

	void Update(int deltaTime);
	void Render();
	void Clean();

private:

	ButtonState _buttonState = ButtonState::DEFAULT;
	std::vector<GameObject*> _contents;

	void HandleInput();

};