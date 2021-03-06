#pragma once

#include "ItemBase.h"

class ItemInfo {
public:
	ItemInfo(ItemBase& item);
	~ItemInfo() {};

	void Update(ItemBase& item, Vector2 drawPos);
	void Draw();
private:
	Texture2D texture{};
	Texture2D itemTex{};
	Vector2 position{};
	const char* name{};
	const char* description{};
	const char* description2{};
	const char* type{};

	std::string sName;
	std::string sDescription;
	std::string sDescription2;
	int strengthPlus;

	float value;
	float weight;
};

