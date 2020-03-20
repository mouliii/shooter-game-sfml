#include "ItemList.h"

ItemList& ItemList::Get()
{
	static ItemList instance;
	return instance;
}

void ItemList::AddWeapon(std::unique_ptr<Weapon> wep)
{
	Get().I_AddWeapon(std::move(wep));
}

void ItemList::RemoveWeapon(int index)
{
	Get().I_RemoveWeapon(index);
}

std::vector<std::unique_ptr<Weapon>>& ItemList::GetWeapons()
{
	return Get().I_GetWeapons();
}

void ItemList::I_RemoveWeapon(int index)
{
	if (index < weapons.size())
	{
		weapons.erase(weapons.begin() + index);
	}
}

void ItemList::I_AddWeapon(std::unique_ptr<Weapon> wep)
{
	weapons.push_back(std::move(wep));
}

std::vector<std::unique_ptr<Weapon>>& ItemList::I_GetWeapons()
{
	return weapons;
}
