#include "StartScreen.h"
#include "Aufgabe1a.h"
#include "Aufgabe1b.h"
#include "Aufgabe1c.h"
#include "Aufgabe2a.h"
#include "Aufgabe2b.h"
#include "raylib.h"
#include "../global.h"

StartScreen::StartScreen() : Screen(SceneName::Other)
{
	
}

void StartScreen::Input() 
{
	if (CheckCollisionPointRec(virtualMouse, select1a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextScreen = std::make_shared<Aufgabe1a>();
	if (CheckCollisionPointRec(virtualMouse, select1b) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextScreen = std::make_shared<Aufgabe1b>();
	if (CheckCollisionPointRec(virtualMouse, select1c) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextScreen = std::make_shared<Aufgabe1c>();
	if (CheckCollisionPointRec(virtualMouse, select2a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextScreen = std::make_shared<Aufgabe2a>();
	if (CheckCollisionPointRec(virtualMouse, select2b) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) nextScreen = std::make_shared<Aufgabe2b>();
	if (CheckCollisionPointRec(virtualMouse, select3a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
	if (CheckCollisionPointRec(virtualMouse, select3b) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
	if (CheckCollisionPointRec(virtualMouse, select4a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
	if (CheckCollisionPointRec(virtualMouse, select5a) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

void StartScreen::Update()
{
	
}

void StartScreen::Draw()
{
	ClearBackground(GRAY);
	DrawText("CHOOSE PORTFOLIO EXERCISE", 50, 10, 15, BLACK);

	for (int i = 1; i < 4; i++) {
		DrawRectangle(40 * i, 50 , 30, 30, BLACK);
	}
	for (int i = 1; i < 3; i++) {
		DrawRectangle(40 * i, 100, 30, 30, BLACK);
	}
	for (int i = 1; i < 3; i++) {
		DrawRectangle(40 * i, 150, 30, 30, BLACK);
	}
    DrawRectangle(40, 200, 30, 30, BLACK);
	DrawRectangle(40, 250, 30, 30, BLACK);

	DrawText("1a", 45, 55, 20, WHITE);
	DrawText("1b", 85, 55, 20, WHITE);
	DrawText("1c", 125, 55, 20, WHITE);
	DrawText("2a", 45, 105, 20, WHITE);
	DrawText("2b", 85, 105, 20, WHITE);
	DrawText("3a", 45, 155, 20, WHITE);
	DrawText("3b", 85, 155, 20, WHITE);
	DrawText("4a", 45, 205, 20, WHITE);
	DrawText("5a", 45, 255, 20, WHITE);
}
