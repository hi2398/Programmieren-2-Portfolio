#include "PlayerChar.h"

PlayerChar::PlayerChar(Vector2 spawnVec, int inventorySlots)
{
	startPos = spawnVec;
	position = spawnVec;
	SetStrengthStat(startingStrengthStat);
	inventory = std::make_shared<Inventory<ItemBase>>(inventorySlots);
	texture = LoadTexture("assets/Jeff.png");
}

void PlayerChar::Update()
{
	carryingCapacity = strength * 2;  //for example with 10 strength -> can carry 20 kg

	if (GetCarryWeight() > carryingCapacity) tooHeavy = true; //disable movement when carrying too much
	else tooHeavy = false;

	SetStrengthStat(startingStrengthStat + GetIncreasedStrengthStat()); //increase strength based on equipped items


	frameCounter++; //frame handling
	if (frameCounter >= 30) {
		thisFrame++;
		frameCounter = 0;
	}
	activeFrame.y = 16 * thisFrame;
}

bool PlayerChar::HasEmptyInventorySlots()
{
	for (int i = 0; i < GetInventory()->GetSlots(); i++) {
		if (GetInventory()->GetItem(i).GetType() == ItemType::Empty) {
			return true;
		}
	}

	return false;
}

int PlayerChar::GetEmptyInventorySlot()
{
	for (int i = 0; i < GetInventory()->GetSlots(); i++) {
		if (GetInventory()->GetItem(i).GetType() == ItemType::Empty) {
			return i;
		}
	}
}

void PlayerChar::Draw()
{
	DrawTextureRec(texture, activeFrame, position, WHITE);
	if (tooHeavy) DrawText("TOO HEAVY!", 30, 20, 35, RED);
}

float PlayerChar::GetCarryingCapacity() const
{
	return carryingCapacity;
}

int PlayerChar::GetTotalStrengthStat() const
{
	return strength;
}

Vector2 PlayerChar::GetPosition() const
{
	return position;
}

Vector2 PlayerChar::GetLastDirection() const
{
	return lastDirection;
}

int PlayerChar::GetIncreasedStrengthStat()
{
	int increasedStrengthStat;
	increasedStrengthStat = inventory->GetEquippedItem(ItemType::HeadGear).GetStrengthStat() + inventory->GetEquippedItem(ItemType::BodyGear).GetStrengthStat() + inventory->GetEquippedItem(ItemType::Weapon).GetStrengthStat();
	return increasedStrengthStat;
}

std::shared_ptr<Inventory<ItemBase>> PlayerChar::GetInventory() const
{
	return inventory;
}

float PlayerChar::GetCarryWeight()
{
	carryWeight = 0.0;
	for (int i = 0; i < GetInventory()->GetSlots(); i++) {
		if (GetInventory()->GetItem(i).GetType() != ItemType::Empty) carryWeight += GetInventory()->GetItem(i).GetWeight();
	}
	if (GetInventory()->GetEquippedItem(ItemType::HeadGear).GetType() != ItemType::Empty)
		carryWeight += GetInventory()->GetEquippedItem(ItemType::HeadGear).GetWeight();

	if (GetInventory()->GetEquippedItem(ItemType::BodyGear).GetType() != ItemType::Empty)
		carryWeight += GetInventory()->GetEquippedItem(ItemType::BodyGear).GetWeight();

	if (GetInventory()->GetEquippedItem(ItemType::Weapon).GetType() != ItemType::Empty)
		carryWeight += GetInventory()->GetEquippedItem(ItemType::Weapon).GetWeight();

	return carryWeight;
}

void PlayerChar::MoveTo(Vector2 direction, std::vector<std::vector<Tile>>& map)
{
	if (!tooHeavy) {
		CheckTiles(direction, map);
		if (playerCanMove) {
			position.x += direction.x;
			position.y += direction.y;
		}
	}

}

void PlayerChar::CheckTiles(Vector2& direction, std::vector<std::vector<Tile>>& map)
{
	checkTile = { position.x + direction.x, position.y + direction.y };
	for (const auto& row : map) {
		for (const auto& element : row) {
			if (element.position.x == checkTile.x && element.position.y == checkTile.y) {
				switch (element.type)
				{
				case TileType::PASSABLE:
					playerCanMove = true;
					break;
				case TileType::START:
					playerCanMove = true;
					break;
				case TileType::RESET:
					position = startPos;
					playerCanMove = false;
					break;
				case TileType::SLIPPERY:
					lastDirection = direction;
					playerCanMove = true;
					break;
				default:
					playerCanMove = false;
					break;
				}
				return;
			}
		}
	}

	playerCanMove = false;
	return;
}

void PlayerChar::SetStrengthStat(int strength)
{
	this->strength = strength;
}
