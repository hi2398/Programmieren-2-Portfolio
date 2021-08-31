#include "ItemBase.h"

ItemBase::ItemBase(ItemType itemType)
{
	this->itemType = itemType;
}

Texture2D ItemBase::GetTexture()
{
	return texture;
}

Vector2 ItemBase::GetPosition()
{
	return spawnVector;
}

std::string ItemBase::GetName()
{
	return name;
}

std::string ItemBase::GetDescription()
{
	return description;
}

std::string ItemBase::GetDescription2()
{
	return description2;
}

float ItemBase::GetValue()
{
	return value;
}

float ItemBase::GetWeight()
{
	return weight;
}

ItemType ItemBase::GetType()
{
	return itemType;
}

bool ItemBase::IsVisible()
{
	return isVisible;
}

void ItemBase::SetIsVisible(bool visible)
{
	this->isVisible = visible;
}
