#include "InventoryScreen.h"


InventoryScreen::InventoryScreen(SceneName sceneName, PlayerChar& player)
{
	activeScene = sceneName;
	invTexture = LoadTexture("assets/Inventory.png");
	playerTexture = LoadTexture("assets/Jeff.png");
	controlsTex = LoadTexture("assets/controls.png");
	
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

	EquipItem(player);

	UnequipThisItem(player);

	TossThisItem(player);

	ShowInfo(player); //this is just some quality of life stuff
}

void InventoryScreen::ShowInfo(PlayerChar& player)
{
	Rectangle infoRec = { 210, 53, 20, 10};
	if (CheckCollisionPointRec(virtualMouse, infoRec)) {
		showStrengthInfo = true;
	}
	else showStrengthInfo = false;

	infoRec = { 210, 87, 25, 10};
	if (CheckCollisionPointRec(virtualMouse, infoRec)) {
		showCarryInfo = true;
	}
	else showCarryInfo = false;

	if (activeScene != SceneName::Aufgabe2a && activeScene != SceneName::Aufgabe2b) {
		infoRec = { 252, 190, 20, 7};
		if (CheckCollisionPointRec(virtualMouse, infoRec)) {
			showNamePlusInfo = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				player.GetInventory()->SortByNameHighToLow();
			}
		}
		else showNamePlusInfo = false;

		infoRec = { 252, 198, 20, 7 };
		if (CheckCollisionPointRec(virtualMouse, infoRec)) {
			showNameMinusInfo = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				player.GetInventory()->SortByNameLowToHigh();
			}
		}
		else showNameMinusInfo = false;

		infoRec = { 252, 206, 20, 7 };
		if (CheckCollisionPointRec(virtualMouse, infoRec)) {
			showWeightPlusInfo = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				player.GetInventory()->SortByWeightHighToLow();
			}
		}
		else showWeightPlusInfo = false;

		infoRec = { 252, 214, 20, 7 };
		if (CheckCollisionPointRec(virtualMouse, infoRec)) {
			showWeightMinusInfo = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				player.GetInventory()->SortByWeightLowToHigh();
			}
		}
		else showWeightMinusInfo = false;

		infoRec = { 252, 222, 20, 7 };
		if (CheckCollisionPointRec(virtualMouse, infoRec)) {
			showValuePlusInfo = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				player.GetInventory()->SortByValueHighToLow();
			}
		}
		else showValuePlusInfo = false;

		infoRec = { 252, 230, 20, 7 };
		if (CheckCollisionPointRec(virtualMouse, infoRec)) {
			showValueMinusInfo = true;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				player.GetInventory()->SortByValueLowToHigh();
			}
		}
		else showValueMinusInfo = false;
	}
}

void InventoryScreen::TossThisItem(PlayerChar& player)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Rectangle itemHitbox = { 0,0, 16, 16 };
		int x = 0;
		int y = 0;
		for (int i = 0; i < slots; i++) {
			if (i % 5 == 0 && i != 0) y++, x = 0;
			itemHitbox.x = 61 + 40 * x;
			itemHitbox.y = 161 + 32 * y;

			if (player.GetInventory()->GetItem(i).GetType() != ItemType::Empty) {
				if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
					player.GetInventory()->TossItem(i);
					return;
				}
			}
			x++;
		}
	}
}

void InventoryScreen::UnequipThisItem(PlayerChar& player)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Rectangle itemHitbox;
		//for headgear
		if (player.GetInventory()->GetEquippedItem(ItemType::HeadGear).GetType() != ItemType::Empty) {
			itemHitbox = { 180, 53, 16, 16 };
			if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
				if (player.HasEmptyInventorySlots()) {
					player.GetInventory()->SetItem(player.GetInventory()->GetEquippedItem(ItemType::HeadGear), player.GetEmptyInventorySlot());
					player.GetInventory()->UnequipItem(ItemType::HeadGear);
				}
				return;
			}
		}
		//for bodygear
		if (player.GetInventory()->GetEquippedItem(ItemType::BodyGear).GetType() != ItemType::Empty) {
			itemHitbox = { 180, 87, 16, 16 };
			if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
				if (player.HasEmptyInventorySlots()) {
					player.GetInventory()->SetItem(player.GetInventory()->GetEquippedItem(ItemType::BodyGear), player.GetEmptyInventorySlot());
					player.GetInventory()->UnequipItem(ItemType::BodyGear);
				}
				return;
			}
		}
		//for weapon
		if (player.GetInventory()->GetEquippedItem(ItemType::Weapon).GetType() != ItemType::Empty) {
			itemHitbox = { 180, 121, 16, 16 };
			if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
				if (player.HasEmptyInventorySlots()) {
					player.GetInventory()->SetItem(player.GetInventory()->GetEquippedItem(ItemType::Weapon), player.GetEmptyInventorySlot());
					player.GetInventory()->UnequipItem(ItemType::Weapon);
				}
				return;
			}
		}
	}
}

void InventoryScreen::EquipItem(PlayerChar& player)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Rectangle itemHitbox = { 0,0, 16, 16 };
		int x = 0;
		int y = 0;
		for (int i = 0; i < slots; i++) {
			if (i % 5 == 0 && i != 0) y++, x = 0;
			itemHitbox.x = 61 + 40 * x;
			itemHitbox.y = 161 + 32 * y;

			if (player.GetInventory()->GetItem(i).GetType() != ItemType::Empty) {
				if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
					player.GetInventory()->SetEquippedItem(player.GetInventory()->GetItem(i).GetType(), i);
					return;
				}
			}
			x++;
		}
	}
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
				itemInfo->Update(player.GetInventory()->GetItem(i), {35,35});
				return;
			}
		}
		x++;
	}
	
	//mouse collision for equipped items
	if (player.GetInventory()->GetEquippedItem(ItemType::HeadGear).GetType() != ItemType::Empty) {
		itemHitbox = { 180, 53, 16, 16 };
		if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
			showInfo = true;
			itemInfo->Update(player.GetInventory()->GetEquippedItem(ItemType::HeadGear), { 35, 161 });
			return;
		}
	}
	if (player.GetInventory()->GetEquippedItem(ItemType::BodyGear).GetType() != ItemType::Empty) {
		itemHitbox = { 180, 87, 16, 16 };
		if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
			showInfo = true;
			itemInfo->Update(player.GetInventory()->GetEquippedItem(ItemType::BodyGear), { 35, 161 });
			return;
		}
	}
	if (player.GetInventory()->GetEquippedItem(ItemType::Weapon).GetType() != ItemType::Empty) {
		itemHitbox = { 180, 121, 16, 16 };
		if (CheckCollisionPointRec(virtualMouse, itemHitbox)) {
			showInfo = true;
			itemInfo->Update(player.GetInventory()->GetEquippedItem(ItemType::Weapon), { 35, 161 });
			return;
		}
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

	equippedHeadGear = player.GetInventory()->GetEquippedItem(ItemType::HeadGear);
	equippedBodyGear = player.GetInventory()->GetEquippedItem(ItemType::BodyGear);
	equippedWeapon = player.GetInventory()->GetEquippedItem(ItemType::Weapon);

	playerStrength = player.GetTotalStrengthStat();
	carryingPercentage = player.GetCarryWeight() / player.GetCarryingCapacity() * 100;
}

void InventoryScreen::Draw()
{
	DrawTexture(invTexture, position.x, position.y, WHITE);
	DrawTexturePro(playerTexture, playerFrame, { playerPosition.x, playerPosition.y, 64, 64 }, {0}, 0.0, WHITE);
	DrawTexture(controlsTex, position.x, 0, WHITE);

	DrawText("Equip/ Unequip", position.x + 30, 10, 5, BLACK);
	DrawText("Toss", position.x + 155, 10, 5, BLACK);

	//draw inventory items
	int y = 0;
	int x = 0;
	for (int i = 0; i < slots; i++) {
		if (i % 5 == 0 && i != 0) y++, x = 0;
		DrawTexture(invCont[i].GetTexture(), 61 + 40 * x, 161 + 32 * y, WHITE);
		x++;
	}

	//draw equipped items
	DrawTexture(equippedHeadGear.GetTexture(), 180, 53, WHITE);
	DrawTexture(equippedBodyGear.GetTexture(), 180, 87, WHITE);
	DrawTexture(equippedWeapon.GetTexture(), 180, 121, WHITE);

	//draw character stats
	if (activeScene != SceneName::Aufgabe2a) {
		DrawText(TextFormat("S: %i", playerStrength), 210, 53, 5, BLACK);
		DrawText(TextFormat("W: %.1f %%", carryingPercentage), 210, 87, 5, BLACK);
	}
	if (showStrengthInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 25, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 25, BLACK);
		DrawText("Strength determines", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
		DrawText("how much you can carry.", virtualMouse.x - 145, virtualMouse.y + 11, 5, BLACK);
	}
	if (showCarryInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 25, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 25, BLACK);
		DrawText("If your carrying capayity", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
		DrawText("is too high, you can't move.", virtualMouse.x - 145, virtualMouse.y + 11, 5, BLACK);
	}

	if (activeScene != SceneName::Aufgabe2a && activeScene != SceneName::Aufgabe2b) {
		DrawText("SORT", 250, 177, 5, BLACK);
		DrawText("N +", 252, 190, 5, BLACK);
		DrawText("N -", 252, 198, 5, BLACK);
		DrawText("W +", 252, 206, 5, BLACK);
		DrawText("W -", 252, 214, 5, BLACK);
		DrawText("V +", 252, 222, 5, BLACK);
		DrawText("V -", 252, 230, 5, BLACK);
	}
	if (showNamePlusInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 12, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 12, BLACK);
		DrawText("Sort by Name A-Z", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
	}
	else if (showNameMinusInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 12, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 12, BLACK);
		DrawText("Sort by Name Z-A", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
	}
	else if (showWeightPlusInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 12, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 12, BLACK);
		DrawText("Sort by Weight High-Low", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
	}
	else if (showWeightMinusInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 12, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 12, BLACK);
		DrawText("Sort by Weight Low-High", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
	}
	else if (showValuePlusInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 12, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 12, BLACK);
		DrawText("Sort by Value High-Low", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
	}
	else if (showValueMinusInfo) {
		DrawRectangle(virtualMouse.x - 150, virtualMouse.y, 150, 12, WHITE);
		DrawRectangleLines(virtualMouse.x - 150, virtualMouse.y, 150, 12, BLACK);
		DrawText("Sort by Value Low-High", virtualMouse.x - 145, virtualMouse.y + 1, 5, BLACK);
	}

	

	if (showInfo) {
		itemInfo->Draw();
	}
}