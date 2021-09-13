#pragma once
#include <vector>
#include <iostream>
#include "Screen.h"
#include "Tile/Tile.h"
#include "Items/ItemBase.h"
#include "InventoryScreen.h"
#include "Actor/PlayerChar.h"

class Aufgabe3b : public Screen {
public:
	Aufgabe3b();
	void Input() override;
	void Update() override;
	int GetFreeInventorySlot();
	void Draw() override;
	~Aufgabe3b() {};
protected:

private:
	//2-dimensionaler Vector mit Tile-Struct befüllt
	std::vector<std::vector<Tile>> map;

	//alle Tile-Texturen
	Texture2D sand;
	Texture2D water;
	Texture2D towel;
	Texture2D chest;

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

	//only for 3b: three random inventories
	std::shared_ptr<Inventory<ItemBase>> generatedInventory;
	std::vector<std::unique_ptr<ItemBase>> itemCont;

	Vector2 invVec1{ 9 * 16, 3 * 16 };
};