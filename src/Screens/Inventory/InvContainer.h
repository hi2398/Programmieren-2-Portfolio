#pragma once
#include <vector>

template <typename T>
class InvContainer {
public:
	InvContainer(int slots);
	~InvContainer() {};
	T GetItem(int slot);
	bool SetItem(T saidItem, int slot);
	void PopItem(int slot);
	void InsertItem(T saidItem, int slot);
private:
	std::vector<T> invCont;
};

template <typename T>
InvContainer<T>::InvContainer(int slots) {
	for (int i = 0; i < slots; i++) {
		invCont.emplace_back();
	}
}

template <typename T>
T InvContainer<T>::GetItem(int slot) {
	return invCont[slot];
}

template <typename T>
bool InvContainer<T>::SetItem(T saidItem, int slot) {
	this->invCont[slot] = saidItem;
	return true;
}

template<typename T>
inline void InvContainer<T>::PopItem(int slot)
{
	invCont.erase(invCont.begin() + slot);
	invCont.emplace_back();
	return;
}

template<typename T>
inline void InvContainer<T>::InsertItem(T saidItem, int slot)
{
	auto it = invCont.begin() + slot;
	invCont.insert(it, saidItem);
}
