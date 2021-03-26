#pragma once

#include "AnimatedGameObject.h"
#include "GameObject.h"

#include <string>
#include <vector>

class Button : public AnimatedGameObject {
public:
	enum class ButtonState {
		DEFAULT, HOVERED, HOV_PRESSED, UNHOV_PRESSED, PRESS_ACTION, INACTIVE
	};

	Button(float x, float y, int w, int h, std::string filename);

	void AddContent(GameObject* content);

	void Update(int deltaTime);
	void HandleInput();
	void Render();
	void Clean();

	ButtonState buttonState();
	bool TransitState(ButtonState newButtonState);

private:
	ButtonState buttonState_ = ButtonState::DEFAULT;

	std::vector<GameObject*> contents_;
};