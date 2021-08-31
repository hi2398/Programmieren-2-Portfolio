#pragma once
#include <vector>
#include <iostream>
#include "Screen.h"
#include "Tile/Tile.h"

class Aufgabe1b : public Screen {
public:
	Aufgabe1b();
	void Input() override;
	void Update() override;
	void Draw() override;
	~Aufgabe1b() {};
protected:

private:
	//2-dimensionaler Vector mit Tile-Struct befüllt
	std::vector<std::vector<Tile>> map;

	//alle Tile-Texturen
	Texture2D sand;
	Texture2D water;
	Texture2D castle;
	Texture2D crab;
	Texture2D towel;
	Texture2D icecream;

	//Tile Vector
	Vector2 tileVec{};


	//frame Handling
	int frameCounter = 0;
	int thisFrame = 0;
	Rectangle activeFrame{};
};