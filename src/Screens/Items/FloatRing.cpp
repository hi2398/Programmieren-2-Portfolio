#include "FloatRing.h"

FloatRing::FloatRing(Vector2 spawnVector) : ItemBase(ItemType::BodyGear)
{
	weight = 1.0;
	strengthValue = 3;
	name = "Incredibly Round Float";
	description = "Perfectly fit for a hero.";
	description2 = "Don't get stuck in it!";
	value = 5.0;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/floating_ring.png");
}

void FloatRing::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}