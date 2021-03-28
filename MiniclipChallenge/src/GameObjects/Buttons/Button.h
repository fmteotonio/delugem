#pragma once

#include <string>
#include <vector>

#include "../AnimatedGameObject.h"

class Button : public AnimatedGameObject {
public:
	enum class ButtonState {
		DEFAULT, HOVERED, HOV_PRESSED, UNHOV_PRESSED, PRESS_ACTION, INACTIVE
	};

	Button(Position pos, Dimensions dim, std::string filename);

	void AddContent(GameObject* content);

	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	ButtonState GetButtonState();
	bool TransitState(ButtonState newButtonState);
	void OnlySetActiveIf(bool condition);

private:
	ButtonState _buttonState = ButtonState::DEFAULT;

	std::vector<GameObject*> _contents;
};