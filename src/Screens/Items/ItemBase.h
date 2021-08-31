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
	~ItemBase() = default;
protected:
	float weight{};
	std::string name{};
	std::string description{};
	std::string description2{};
	float value{};
	Vector2 spawnVector{};
	Texture2D texture{};
	bool isVisible{ true };

	ItemType itemType{ItemType::Empty}; //added for Aufgabe2
private:
	
};