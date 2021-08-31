#pragma once

#include "Screen.h"
#include "Inventory/Inventory.h"
#include "Actor/PlayerChar.h"
#include "../global.h"
#include "Items/ItemInfo.h"
#include <vector>

class InventoryScreen {
public:
	InventoryScreen(SceneName sceneName, PlayerChar& player); //aufgabe2b and onwards
	InventoryScreen(SceneName sceneName);// aufgabe 2a
	void Input(PlayerChar& player);
	void CheckMouseItemCollision(PlayerChar& player);
	void Update(PlayerChar& player);
	void Draw();
	~InventoryScreen() = default;
protected:

private:
	SceneName activeScene;
	Texture2D invTexture;
	Vector2 position{35, 35};
	Texture2D playerTexture;
	Vector2 playerPosition{63, 63};
	Rectangle playerFrame = { 0,0,16,16 };
	int frameCounter = 0;
	int thisFrame = 0;
	int slots = 0;
	
	std::vector<ItemBase> invCont;
	std::unique_ptr<ItemInfo> itemInfo;
	bool showInfo{ false };
};