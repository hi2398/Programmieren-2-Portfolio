#include "ItemInfo.h"

#include <string>


ItemInfo::ItemInfo(ItemBase& item)
{
	texture = LoadTexture("assets/iteminfo.png");
}

void ItemInfo::Update(ItemBase& item, Vector2 drawPos)
{
	sName = item.GetName(); //get item name as string

	strengthPlus = item.GetStrengthStat();

	sDescription = item.GetDescription(); //same procedure as for name

	sDescription2 = item.GetDescription2();


	value = item.GetValue();
	weight = item.GetWeight();

	switch (item.GetType())
	{
	case ItemType::BodyGear:
		type = "Body Gear";
		break;
	case ItemType::HeadGear:
		type = "Head Gear";
		break;
	case ItemType::Weapon:
		type = "Weapon";
		break;
	default:
		break;
	}

	itemTex = item.GetTexture();
	this->position = drawPos;
}

void ItemInfo::Draw()
{
	DrawTexturePro(texture, { 0,0,(float)texture.width, (float)texture.height }, { position.x, position.y, 250, 115 }, {0}, 0.0, WHITE);
	DrawTexture(itemTex, position.x + 10, position.y + 20, WHITE);
	DrawText(sName.c_str(), position.x + 10, position.y + 5, 5,BLACK);
	DrawText(type, position.x + 160, position.y + 5, 5, BLACK);
	DrawText(sDescription.c_str(), position.x + 10, position.y + 40, 5, BLACK);
	DrawText(sDescription2.c_str(), position.x + 10, position.y + 50, 5, BLACK);
	DrawText(TextFormat("Value: %.2f $", value), position.x + 10, position.y + 70, 5, BLACK);
	DrawText(TextFormat("Weight: %.2f", weight), position.x + 100, position.y + 70, 5, BLACK);
	DrawText(TextFormat("Strength+: %i", strengthPlus), position.x + 10, position.y + 90, 5, BLACK);
}