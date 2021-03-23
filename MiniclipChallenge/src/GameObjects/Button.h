#pragma once

#include "GameObject.h"

#include <string>
#include <vector>

class Button : public GameObject {
public:
	enum class ButtonState {
		DEFAULT, PRESSED, PRESS_ACTION
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

	Animation* defaultAnimation_;
	Animation* pressedAnimation_;

	std::vector<GameObject*> contents_;
};