#include "PlayerChar.h"

PlayerChar::PlayerChar(Vector2 spawnVec)
{
	startPos = spawnVec;
	position = spawnVec;
	SetStrengthStat(5);
	inventory = std::make_shared<Inventory<ItemBase>>(20);
	texture = LoadTexture("assets/Jeff.png");
}

void PlayerChar::Update()
{
	carryingCapacity = strength * 2;  //for example with 10 strength -> can carry 20 kg

	if (GetCarryWeight() > carryingCapacity) tooHeavy = true; //disable movement when carrying too much
	else tooHeavy = false;

	frameCounter++; //frame handling
	if (frameCounter >= 30) {
		thisFrame++;
		frameCounter = 0;
	}
	activeFrame.y = 16 * thisFrame;
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

Vector2 PlayerChar::GetPosition() const
{
	return position;
}

Vector2 PlayerChar::GetLastDirection() const
{
	return lastDirection;
}

std::shared_ptr<Inventory<ItemBase>> PlayerChar::GetInventory() const
{
	return inventory;
}

float PlayerChar::GetCarryWeight()
{
	carryWeight = 0.0;
	for (int i = 0; i < GetInventory()->GetSlots(); i++) {
		carryWeight += GetInventory()->GetItem(i).GetWeight();
	}
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
