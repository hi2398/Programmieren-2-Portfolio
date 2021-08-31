#include "Snorkel.h"

Snorkel::Snorkel(Vector2 spawnVector) : ItemBase(ItemType::HeadGear)
{
	weight = 3.0;
	name = "Mysterious Snorkel";
	description = "Great armor, but uncomfortable";
	description2 = "and makes breathing hard";
	value = 20.0;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/snorkel.png");
}

void Snorkel::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}