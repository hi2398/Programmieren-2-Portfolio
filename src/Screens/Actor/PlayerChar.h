#pragma once

#include "Char.h"
#include "../Inventory/Inventory.h"

class PlayerChar : public Char {
public:
	PlayerChar(Vector2 spawnVec);
	void Update() override;
	void Draw() override;
	void MoveTo(Vector2 direction, std::vector<std::vector<Tile>>& map) override;

	void CheckTiles(Vector2& direction, std::vector<std::vector<Tile>>& map);

	void SetStrengthStat(int strength);
	float GetCarryingCapacity() const;
	Vector2 GetPosition() const;
	Vector2 GetLastDirection() const;
	std::shared_ptr<Inventory<ItemBase>> GetInventory() const;
	float GetCarryWeight();
	~PlayerChar() = default;
private:
	//player attributes
	int strength = 0;
	float carryingCapacity = 0;
	bool playerCanMove{ true };
	bool tooHeavy{ false };
	Vector2 startPos{};
	float carryWeight = 0.0;


	//player inventory
	std::shared_ptr<Inventory<ItemBase>> inventory;

	//player movement
	Vector2 checkTile{};
	Vector2 lastDirection{};
};