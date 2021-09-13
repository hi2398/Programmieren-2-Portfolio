#include "ArmFloats.h"

ArmFloats::ArmFloats(Vector2 spawnVector) : ItemBase(ItemType::BodyGear)
{
	weight = 1.0;
	strengthValue = 1;
	name = "Paladin's Arm Floats";
	description = "Even the mightiest knights would kill";
	description2 = "to wear these.";
	value = 15.5;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/arm_floats.png");
}

void ArmFloats::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}