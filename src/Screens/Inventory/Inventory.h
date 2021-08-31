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

protected:

private:
	std::shared_ptr<S> inventory;
	T* slot1;
	T* slot2;
	int slots;
	static constexpr int MAX_SLOTS{ 20 };

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
	return slots;
}

template<typename T, typename S>
inline void Inventory<T, S>::SetEquippedItem(ItemType itemType, int slot)
{
	switch (itemType)
	{
	case ItemType::HeadGear:
		slot1 = inventory->GetItem(slot);
		break;
	default:
		break;
	}
}
;