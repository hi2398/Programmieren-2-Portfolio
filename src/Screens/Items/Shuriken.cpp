#include "Shuriken.h"

Shuriken::Shuriken(Vector2 spawnVector) : ItemBase(ItemType::Weapon)
{
	weight = 3.0;
	strengthValue = 3;
	name = "Starfish Shuriken";
	description = "You sense immense bloodlust";
	description2 = "coming from this.";
	value = 15.0;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/shuriken.png");
}

void Shuriken::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}