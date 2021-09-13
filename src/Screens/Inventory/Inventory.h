#pragma once
#include "../Items/ItemBase.h"
#include "InvContainer.h"
#include <iostream>
#include <vector>

template <typename T, typename S = InvContainer<T>>
class Inventory {
public:
	Inventory(int slots);
	~Inventory() = default;

	T GetItem(int slot);
	void SetItem(T saidItem, int slot);
	int GetSlots() const;
	void SetEquippedItem(ItemType itemType, int slot);
	T GetEquippedItem(ItemType itemType) const;
	bool UnequipItem(ItemType itemType);
	bool TossItem(int slot);
	void SortByNameLowToHigh();
	void SortByNameHighToLow();
	void SortByWeightLowToHigh();
	void SortByWeightHighToLow();
	void SortByValueLowToHigh();
	void SortByValueHighToLow();

protected:

private:
	std::shared_ptr<S> inventory;
	int slots;
	static constexpr int MAX_SLOTS{ 20 };

	//equipped items
	T slot1;
	T slot2;
	T slot3;

	T emptySlot; //set slots to this, if item gets unequipped
	std::vector<int> emptySlotCounter;
};

template <typename T, typename S>
Inventory<T, S>::Inventory(int slots) { //set amount of slots
	if (slots > MAX_SLOTS) this->slots = MAX_SLOTS; //cannot exceed maximum slots 
	else if (slots < 0) this->slots = 0; //cannot be below zero
	else this->slots = slots;
	inventory = std::make_shared<S>(slots);
}

template <typename T, typename S>
T Inventory<T, S>::GetItem(int slot) {//get slot specific item
	return inventory->GetItem(slot);
};

template <typename T, typename S>
void Inventory<T, S>::SetItem(T saidItem, int slot) {//set item in specific slot
	inventory->SetItem(saidItem, slot);
	return;
}


template<typename T, typename S>
inline int Inventory<T, S>::GetSlots() const
{
	return slots; //returns number of slots
}

template<typename T, typename S>
inline void Inventory<T, S>::SetEquippedItem(ItemType itemType, int slot)
{
	switch (itemType)
	{
	case ItemType::HeadGear:
		if (slot1.GetType() == ItemType::Empty) { //if equipped slot is empty
		slot1 = inventory->GetItem(slot); //set equipped slot
		inventory->PopItem(slot); //erase item from container: item gets basically transferred
		}
		else { // if slot is not empty, swap items
			T savedItem;
			savedItem = slot1;
			slot1 = inventory->GetItem(slot);
			inventory->PopItem(slot);
			inventory->InsertItem(savedItem, slot);
		}
		break;
	case ItemType::BodyGear:
		if (slot2.GetType() == ItemType::Empty) {
			slot2 = inventory->GetItem(slot);
			inventory->PopItem(slot);
		}
		else {
			T savedItem;
			savedItem = slot2;
			slot2 = inventory->GetItem(slot);
			inventory->PopItem(slot);
			inventory->InsertItem(savedItem, slot);
		}
		break;
	case ItemType::Weapon:
		if (slot3.GetType() == ItemType::Empty) {
			slot3 = inventory->GetItem(slot);
			inventory->PopItem(slot);
		}
		else {
			T savedItem;
			savedItem = slot3;
			slot3 = inventory->GetItem(slot);
			inventory->PopItem(slot);
			inventory->InsertItem(savedItem, slot);
		}
		break;
	default:
		return;
		break;
	}
	return; 
}
template<typename T, typename S>
inline T Inventory<T, S>::GetEquippedItem(ItemType itemType) const
{
	switch (itemType) //returns equipped items
	{
	case ItemType::HeadGear:
		return slot1;
		break;
	case ItemType::BodyGear:
		return slot2;
		break;
	case ItemType::Weapon:
		return slot3;
		break;
	}
}

template<typename T, typename S>
inline bool Inventory<T, S>::UnequipItem(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::HeadGear:
		slot1 = emptySlot;
		break;
	case ItemType::BodyGear:
		slot2 = emptySlot;
		break;
	case ItemType::Weapon:
		slot3 = emptySlot;
		break;
	default:
		return false;
		break;
	}
	return true;
}

template<typename T, typename S>
inline bool Inventory<T, S>::TossItem(int slot)
{
	inventory->PopItem(slot);
	return false;
}

//All Functions below this line were added for 3a) and onwards
template<typename T, typename S>
inline void Inventory<T, S>::SortByNameLowToHigh()
{
	T temp;
	int i;
	for (int j = 1; j < slots; j++) {
		temp = inventory->GetItem(j);
		i = j - 1;
		while (i >= 0 && inventory->GetItem(i).GetName() < temp.GetName()) {
			inventory->SetItem(inventory->GetItem(i), i + 1);
			i = i - 1;
		}
		inventory->SetItem(temp, i + 1);
	}
	while (inventory->GetItem(0).GetType() == ItemType::Empty) {
		inventory->PopItem(0);
	}
	
	return;
}

template<typename T, typename S>
inline void Inventory<T, S>::SortByNameHighToLow()
{
	T temp;
	int i;
	for (int j = 1; j < slots; j++) {
		temp = inventory->GetItem(j);
		i = j - 1;
		while (i >= 0 && inventory->GetItem(i).GetName() > temp.GetName()) {
			inventory->SetItem(inventory->GetItem(i), i + 1);
			i = i - 1;
		}
		inventory->SetItem(temp, i + 1);
	}

	while (inventory->GetItem(0).GetType() == ItemType::Empty) {
		inventory->PopItem(0);
	}
	return;
}

template<typename T, typename S>
inline void Inventory<T, S>::SortByWeightLowToHigh()
{
	T temp;
	int i;
	for (int j = 1; j < slots; j++) {
		temp = inventory->GetItem(j);
		i = j - 1;
		while (i >= 0 && inventory->GetItem(i).GetWeight() > temp.GetWeight()) {
			inventory->SetItem(inventory->GetItem(i), i+1);
			i = i - 1;
		}
		inventory->SetItem(temp, i + 1);
	}

	while (inventory->GetItem(0).GetType() == ItemType::Empty) {
		inventory->PopItem(0);
	}
	return;
}

template<typename T, typename S>
inline void Inventory<T, S>::SortByWeightHighToLow()
{
	T temp;
	int i;
	for (int j = 1; j < slots; j++) {
		temp = inventory->GetItem(j);
		i = j - 1;
		while (i >= 0 && inventory->GetItem(i).GetWeight() < temp.GetWeight()) {
			inventory->SetItem(inventory->GetItem(i), i + 1);
			i = i - 1;
		}
		inventory->SetItem(temp, i + 1);
	}

	while (inventory->GetItem(0).GetType() == ItemType::Empty) {
		inventory->PopItem(0);
	}
	return;
}

template<typename T, typename S>
inline void Inventory<T, S>::SortByValueLowToHigh()
{
	T temp;
	int i;
	for (int j = 1; j < slots; j++) {
		temp = inventory->GetItem(j);
		i = j - 1;
		while (i >= 0 && inventory->GetItem(i).GetValue() > temp.GetValue()) {
			inventory->SetItem(inventory->GetItem(i), i + 1);
			i = i - 1;
		}
		inventory->SetItem(temp, i + 1);
	}

	while (inventory->GetItem(0).GetType() == ItemType::Empty) {
		inventory->PopItem(0);
	};
	return;
}

template<typename T, typename S>
inline void Inventory<T, S>::SortByValueHighToLow()
{
	T temp;
	int i;
	for (int j = 1; j < slots; j++) {
		temp = inventory->GetItem(j);
		i = j - 1;
		while (i >= 0 && inventory->GetItem(i).GetValue() < temp.GetValue()) {
			inventory->SetItem(inventory->GetItem(i), i + 1);
			i = i - 1;
		}
		inventory->SetItem(temp, i + 1);
	}

	while (inventory->GetItem(0).GetType() == ItemType::Empty) {
		inventory->PopItem(0);
	}
	return;
}
