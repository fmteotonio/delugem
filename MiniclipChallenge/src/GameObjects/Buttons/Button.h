#pragma once

#include "../AnimatedGameObject.h"
#include "../GameObject.h"

#include <string>
#include <vector>

class Button : public AnimatedGameObject {
public:
	enum class ButtonState {
		DEFAULT, HOVERED, HOV_PRESSED, UNHOV_PRESSED, PRESS_ACTION, INACTIVE
	};

	Button(Position pos, int w, int h, std::string filename);

	void AddContent(GameObject* content);

	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	ButtonState GetButtonState();
	bool TransitState(ButtonState newButtonState);
	void OnlySetActiveIf(bool condition);

private:
	ButtonState buttonState_ = ButtonState::DEFAULT;

	std::vector<GameObject*> contents_;
};