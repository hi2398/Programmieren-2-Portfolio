#include "InventoryScreen.h"


InventoryScreen::InventoryScreen(SceneName sceneName, PlayerChar& player)
{
	activeScene = sceneName;
	invTexture = LoadTexture("assets/Inventory.png");
	playerTexture = LoadTexture("assets/Jeff.png");
	
	//fill inventory screen with inventory elements
	slots = player.GetInventory()->GetSlots();
	for (int i = 0; i < slots; i++) {
		invCont.emplace_back(player.GetInventory()->GetItem(i));
	}

	itemInfo = std::make_unique<ItemInfo>(player.GetInventory()->GetItem(0));
}

InventoryScreen::InventoryScreen(SceneName sceneName)
{
	activeScene = sceneName;
	invTexture = LoadTexture("assets/Inventory.png");
	playerTexture = LoadTexture("assets/Jeff.png");

}

void InventoryScreen::Input(PlayerChar& player)
{
	CheckMouseItemCollision(player);
}

void InventoryScreen::CheckMouseItemCollision(PlayerChar& player)
{
	Rectangle itemHitbox = { 0,0, 16, 16 };
	int x = 0;
	int y = 0;
	for (int i = 0; i < slots; i++) {
		if (i % 5 == 0 && i != 0) y++, x = 0;
		itemHitbox.x = 61 + 40 * x;
		itemHitbox.y = 161 + 32 * y;

		if (player.GetInventory()->GetItem(i).GetType() != ItemType::Empty) {
			if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
				showInfo = true;
				itemInfo->Update(player.GetInventory()->GetItem(i));
				return;
			}
		}
		x++;
	}
	showInfo = false;
	return;
}

void InventoryScreen::Update(PlayerChar& player)
{
	frameCounter++;
	if (frameCounter >= 30) {
		thisFrame++;
		frameCounter = 0;
	}
	playerFrame.y = 16 * thisFrame;

	//update inventory
	for (int i = 0; i < slots; i++) {
		invCont[i] = player.GetInventory()->GetItem(i);
	}
}

void InventoryScreen::Draw()
{
	DrawTexture(invTexture, position.x, position.y, WHITE);
	DrawTexturePro(playerTexture, playerFrame, { playerPosition.x, playerPosition.y, 64, 64 }, {0}, 0.0, WHITE);

	//draw inventory items
	int y = 0;
	int x = 0;
	for (int i = 0; i < slots; i++) {
		if (i % 5 == 0 && i!= 0) y++, x = 0;
		DrawTexture(invCont[i].GetTexture(), 61 + 40 * x, 161 + 32 * y, WHITE);
		x++;
	}
	
	if (showInfo) {
		itemInfo->Draw();
	}
}