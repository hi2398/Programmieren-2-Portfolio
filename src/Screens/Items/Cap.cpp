#include "Cap.h"

Cap::Cap(Vector2 spawnVector) : ItemBase(ItemType::HeadGear)
{
	weight = 1.0;
	name = "Heroic Cap";
	description = "You can wear it to protect your head.";
	description2 = "It makes you feel heroic!";
	value = 10.5;
	this->spawnVector = spawnVector;
	texture = LoadTexture("assets/cap.png");
}

void Cap::Draw()
{
	DrawTexture(texture, spawnVector.x, spawnVector.y, WHITE);
}
