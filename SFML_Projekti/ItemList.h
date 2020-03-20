#pragma once
#include <vector>
#include "Weapon.h"


// singleton
class ItemList
{
public:
	ItemList(const ItemList&) = delete;
	static ItemList& Get();
	static void AddWeapon(std::unique_ptr<Weapon> wep);
	static void RemoveWeapon(int index);
	static std::vector<std::unique_ptr<Weapon>>& GetWeapons();
private:
	ItemList() {};
	void I_RemoveWeapon(int index);
	void I_AddWeapon(std::unique_ptr<Weapon> wep);
	std::vector<std::unique_ptr<Weapon>>& I_GetWeapons();
	std::vector<std::unique_ptr<Weapon>> weapons;
};