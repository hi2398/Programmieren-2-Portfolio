#include "ItemInfo.h"

#include <string>


ItemInfo::ItemInfo(ItemBase& item)
{
	texture = LoadTexture("assets/iteminfo.png");
}

void ItemInfo::Update(ItemBase& item)
{
	auto pItem = item; //keep the item reference alive

	sName = pItem.GetName(); //get item name as string
	name = sName.c_str(); //convert string to const char

	sDescription = pItem.GetDescription(); //same procedure as for name
	description = sDescription.c_str();

	sDescription2 = pItem.GetDescription2();
	description2 = sDescription2.c_str();

	value = pItem.GetValue();
	weight = pItem.GetWeight();

	switch (pItem.GetType())
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
	this->position = { 50,55 };
}

void ItemInfo::Draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawTexture(itemTex, position.x + 10, position.y + 20, WHITE);
	DrawText(name, position.x + 10, position.y + 5, 5,BLACK);
	DrawText(type, position.x + 160, position.y + 5, 5, BLACK);
	DrawText(description, position.x + 10, position.y + 40, 5, BLACK);
	DrawText(description2, position.x + 10, position.y + 50, 5, BLACK);
	DrawText(TextFormat("Value: %.2f $", value), position.x + 10, position.y + 60, 5, BLACK);
	DrawText(TextFormat("Weight: %.2f", weight), position.x + 100, position.y + 60, 5, BLACK);
}