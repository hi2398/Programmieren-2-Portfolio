#pragma once
#include "Screen.h"

#include "raylib.h"
#include <vector>

class StartScreen : public Screen {
public:
	StartScreen();
	void Input() override;
	void Update() override;
	void Draw() override;
	~StartScreen() {};
	
protected:

private:
	Vector2 mouse{};

	Rectangle select1a = {40, 50, 30, 30};
	Rectangle select1b = { 80, 50, 30, 30 };
	Rectangle select1c = { 120, 50, 30, 30 };
	Rectangle select2a = { 40, 100, 30, 30 };
	Rectangle select2b = { 80, 100, 30, 30 };
	Rectangle select3a = { 40, 150, 30, 30 };
	Rectangle select3b = { 80, 150, 30, 30 };
	Rectangle select4a = { 40, 200, 30, 30 };
	Rectangle select5a = { 40, 250, 30, 30 };
};