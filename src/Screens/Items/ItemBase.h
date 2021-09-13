#pragma once
#include <iostream>
#include "raylib.h"

enum class ItemType {HeadGear, BodyGear, Weapon, Empty};
class ItemBase {
public:
	explicit ItemBase(ItemType itemType);
	ItemBase() {};
	virtual void Draw() {};
	virtual Texture2D GetTexture();
	virtual Vector2 GetPosition();
	virtual std::string GetName();
	virtual std::string GetDescription();
	virtual std::string GetDescription2();
	virtual float GetValue();
	virtual float GetWeight();
	virtual ItemType GetType();
	virtual bool IsVisible();
	virtual void SetIsVisible(bool visible);
	virtual int GetStrengthStat();
	~ItemBase() = default;
protected:
	float weight{100}; //set to high value, so that the sort algorithm places empty slots last
	std::string name{};
	std::string description{};
	std::string description2{};
	float value{1000}; //same as for weight
	Vector2 spawnVector{};
	Texture2D texture{};
	bool isVisible{ true };
	int strengthValue = 0;

	ItemType itemType{ItemType::Empty}; //added for Aufgabe2
private:
	
};