#include "SoakerGun.h"

SoakerGun::SoakerGun(Vector2 spawnVector) : ItemBase(ItemType::Weapon)
{
	weight = 5.0;
	strengthValue = 2;
	name = "Holy Soaker Gun";
	description = "It looks like a normal squirt gun,";
	description2 = "but it is loaded with holy water.";
	value = 30.0;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/soaker_gun.png");
}

void SoakerGun::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}