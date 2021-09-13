#include "PoolNoodle.h"

PoolNoodle::PoolNoodle(Vector2 spawnVector) : ItemBase(ItemType::Weapon)
{
	weight = 5.0;
	strengthValue = 2;
	name = "ExcaliNoodle";
	description = "This pool noodle once belonged to ";
	description2 = "a long forgotten king...";
	value = 50.0;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/poolnoodle.png");
}

void PoolNoodle::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}
