#pragma once

#include "Char.h"
#include "../Inventory/Inventory.h"

class PlayerChar : public Char {
public:
	PlayerChar(Vector2 spawnVec);
	void Update() override;
	bool HasEmptyInventorySlots();
	int GetEmptyInventorySlot();
	void Draw() override;
	void MoveTo(Vector2 direction, std::vector<std::vector<Tile>>& map) override;

	void CheckTiles(Vector2& direction, std::vector<std::vector<Tile>>& map);

	void SetStrengthStat(int strength);

	float GetCarryingCapacity() const;
	int GetTotalStrengthStat() const;
	Vector2 GetPosition() const;
	Vector2 GetLastDirection() const;
	int GetIncreasedStrengthStat();
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
	static constexpr float startingStrengthStat = 5;
	int inventorySlots = 10;

	//player inventory
	std::shared_ptr<Inventory<ItemBase>> inventory;

	//player movement
	Vector2 checkTile{};
	Vector2 lastDirection{};
};