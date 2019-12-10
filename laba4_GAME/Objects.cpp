#include "stdafx.h"
#include "../RogueLib/Objects.h"
#include "../RogueLib/Hero.h"
#include <string>
#include <algorithm>
#include <ctime>

using namespace Prog4_Rogue;

//WEAPON
int Weapon::getDmg() const
{
	srand(time(nullptr));
	int d = rand() % (dmgmax - dmgmin - 1) + 1;
	return d + dmgmin;
}

void Weapon::printWeapon() const
{
	if (this == nullptr)
		std::cout << "Empty" << std::endl;
	else
	{
		std::cout << "DMG: max = " << getMaxDmg() << " min = " << getMinDmg() << std::endl;
		auto ench = getEnchant();
		if (ench.size() != 0)
		{
			std::cout << "Enchantments: ";
			for (auto i = ench.begin(); i != ench.end(); i++)
				std::cout << i->first << ": " << i->second;
		}
	}
}

Weapon & Weapon::setEnchant(map<string, int> nch)
{
	int i = 0;
	std::for_each(nch.begin(), nch.end(), [this](pair<string, int> cur) {
		try { setEnchant(cur); }
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
	});
	return *this;
}

Weapon & Weapon::setEnchant(pair<string, int> nch)
{
	bool there = false;
	for (auto i = 0; i < Nenemies; ++i)
		if (nch.first == enemy_types[i])
			there = true;
	enchant.insert(nch);
	return *this;
}

Weapon & Weapon::setDmg(int min, int max)
{
	if (min < 0 || max < 0)
		throw std::exception("Error. Wrong damage number.");
	if (min < max)
	{
		dmgmin = min;
		dmgmax = max;
	}
	else
	{
		dmgmax = min;
		dmgmin = max;
	}
	return *this;
}

Weapon::Weapon()
{
	setID(O_Weapon);
	dmgmin = 0;
	dmgmax = 10;
	name = "Wooden sword";
}

Weapon::Weapon(string str, int min, int max)
{
	setID(O_Weapon);
	name = str;
	try { setDmg(min, max); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

Weapon::Weapon(string str, int min, int max, map<string, int> magic)
{
	setID(O_Weapon);
	name = str;
	try { setDmg(min, max); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

Weapon::Weapon(string str, int min, int max, pair<string, int> magic)
{
	setID(O_Weapon);
	name = str;
	try { setDmg(min, max); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	try { setEnchant(magic); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//ARMOR
Armor::Armor(string n_name, string n_type, int n_def)
{
	setID(O_Armor);
	name = n_name;
	if (n_def > 0)
		def = n_def;
	else
		throw std::exception("Error. Wrong defence number.");
	bool there = false;
	std::for_each(bdprts_armr.begin(), bdprts_armr.end(), [this, n_type, &there](pair<string, string> cur) {
		if (cur.first == n_type) there = true; });
	if (there == false)
		throw std::exception("Error. Wrong type of armor.");
	type = n_type;
}

//POTION
Potion & Potion::setCharac(map<string, int> newch)
{
	std::for_each(newch.begin(), newch.end(), [this](pair<string, int> cur) {
		try { setCharac(cur); }
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
	});
	return *this;
}

Potion & Potion::setCharac(pair<string, int> newch)
{
	bool there = false;
	for (auto i = 0; i < Nchar; ++i)
	{
		if (newch.first == shrt_char[i])
			there = true;
	}
	if (there == false)
		throw std::exception("Error. Wrong characteristic's name.");
	chchar.insert(newch);
	return *this;
}

Potion & Potion::setTime(int n)
{
	if (n < 0)
		throw std::exception("Wrong amount of time.");
	time = n;
	return *this;
}

Potion::Potion(string str, map<string, int> nchars, int nt) //for many characteristics
{
	setState(full);
	setID(O_Potion);
	try { 
		setCharac(nchars); 
		setTime(nt);
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	name = str;
}

Potion::Potion(string str, pair<string, int> nch, int nt) //for 1 characteristic
{
	setState(full);
	setID(O_Potion);
	try { 
		setCharac(nch); 
		setTime(nt);
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	name = str;
}

//MASTERKEY
MasterKey & MasterKey::setAmount(int n)
{
	if (n < 0)
		throw std::exception("Negative amount of MasterKey.");
	amount = n;
	return *this;
}

MasterKey::MasterKey(int num) 
{ 
	setID(O_MasterKey); 
	try { setAmount(num); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//ARTIFACT 
Artifact & Artifact::setCharac(map<string, int> newch)
{
	if (artchar.size() != 0)
		artchar.clear();
	artchar = newch;
	return *this;
}

Artifact & Artifact::setCharac(pair<string, int> newch)
{
	if (artchar.size() != 0)
		artchar.clear();
	artchar.insert(newch);
	return *this;
}

int Artifact::getIntCharac(string checktype)
{
	for (auto it = artchar.begin(); it != artchar.end(); ++it)
		if (it->first == checktype)
			return it->second;
	return 0;
}
/*
void Artifact::bonus(Hero &player)
{
	auto curh = player.getAllCharacter();
	std::for_each(artchar.begin(), artchar.end(), [&curh, this](pair<string, int> cur) {
		auto it = curh.find(cur.first);
		it->second.second += cur.second;
	});
	player.setCharacter(curh);
}
*/
//ARTIFACT ARMOR
/*
ArtifactArmor* Armor::changeClass()
{
	if (IAm() == ARTARMOR)
		throw std::exception("Already is ArtifactArmor");
	ArtifactArmor* newar = dynamic_cast<ArtifactArmor*>(this);
	return newar;
}
*/
ArtifactArmor::ArtifactArmor(string n_name, string n_type, int n_def, map<string, int> ch) : Armor(n_name, n_type, n_def)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}
ArtifactArmor::ArtifactArmor(string n_name, string n_type, int n_def, pair<string, int> ch) : Armor(n_name, n_type, n_def)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//ARTIFACT WEAPON
/*
ArtifactWeapon* Weapon::changeClass()
{
	if (IAm() == ARTWEAPON)
		throw std::exception("Already is ArtifactWeapon");
	ArtifactWeapon* newar = dynamic_cast<ArtifactWeapon*>(this);
	return newar;
}
*/
ArtifactWeapon::ArtifactWeapon(string n_name, int min, int max, map<string, int> ch) : Weapon(n_name, min, max)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

ArtifactWeapon::ArtifactWeapon(string n_name, int min, int max, map<string, int> ch, map<string, int> en) : Weapon(n_name, min, max, en)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

ArtifactWeapon::ArtifactWeapon(string n_name, int min, int max, map<string, int> ch, pair<string, int> en) : Weapon(n_name, min, max, en)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

ArtifactWeapon::ArtifactWeapon(string n_name, int min, int max, pair<string, int> ch) : Weapon(n_name, min, max)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

ArtifactWeapon::ArtifactWeapon(string n_name, int min, int max, pair<string, int> ch, map<string, int> en) : Weapon(n_name, min, max, en)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

ArtifactWeapon::ArtifactWeapon(string n_name, int min, int max, pair<string, int> ch, pair<string, int> en) : Weapon(n_name, min, max, en)
{
	try { setCharac(ch); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}