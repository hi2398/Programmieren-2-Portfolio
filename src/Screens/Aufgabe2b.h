#pragma once
#include <vector>
#include <iostream>
#include "Screen.h"
#include "Tile/Tile.h"
#include "Items/ItemBase.h"
#include "InventoryScreen.h"
#include "Actor/PlayerChar.h"

class Aufgabe2b : public Screen {
public:
	Aufgabe2b();
	void Input() override;
	void Update() override;
	int GetFreeInventorySlot();
	void Draw() override;
	~Aufgabe2b() {};
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

	//container for item
	std::vector<std::unique_ptr<ItemBase>> item;
	bool itemPlaced{ false };
	std::vector<Vector2> emptySpace;

	//inventory interface
	std::unique_ptr<InventoryScreen> invInterface;
	bool inventoryIsOpen{ false };

	//player initialization
	std::shared_ptr<PlayerChar> player;
};