#pragma once
#include "raylib.h"
#include "../Tile/Tile.h"
#include <vector>


class Char {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void MoveTo(Vector2 direction, std::vector<std::vector<Tile>> &map) = 0;
	~Char() = default;
protected:
	Vector2 position;
	Texture2D texture;
	int frameCounter = 0;
	int thisFrame = 0;
	Rectangle activeFrame = { 0,0,16,16 };
private:

};