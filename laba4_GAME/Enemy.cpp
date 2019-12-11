#include "stdafx.h"
#include "../RogueLib/Enemy.h"
#include "../RogueLib/Hero.h"
#include <ctime>

using namespace Prog4_Rogue;

//CONSTRUCTORS 
Enemy::Enemy(string str, int nhp = MAXHP, int nmhp = MAXHP, int nmaxd = 10, int nmind = 0, int nxp = 5)
{
	try {
		setType(str);
		setDmg(nmind, nmaxd);
		setXP(nxp);
		setMaxHP(nmhp);
		setCurHP(nhp);
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//SETTERS 
Enemy & Enemy::setCurHP(int n)
{
	if (n < 0 || n > maxhp)
		throw std::exception("Error. Wrong cur HP.");
	curhp = n;
	return *this;
}

Enemy & Enemy::setMaxHP(int n)
{
	if (n < 0)
		throw std::exception("Error. Negative max HP.");
	maxhp = n;
	return *this;
}

Enemy & Enemy::setType(string str)
{
	bool there = false;
	for (int i = 0; i < Nenemies; ++i)
		if (str == enemy_types[i])
			there = true;
	if (there == false)
	{
		throw std::exception("Error. Wrong enemy type.");
	}
	type = str;
	return *this;
}

Enemy & Enemy::setDmg(int min, int max)
{
	if (min < 0 || max < 0)
		throw std::exception("Error. Wrong damage numbers.");
	if (min < max)
	{
		maxdmg = max;
		mindmg = min;
	}
	else
	{
		maxdmg = min;
		mindmg = max;
	}
	return *this;
}

Enemy & Enemy::setMinDmg(int n)
{
	if (n < 0 || n > maxdmg)
		throw std::exception("Error. Wrong min DMG.");
	mindmg = n;
	return *this;
}

Enemy & Enemy::setMaxDmg(int n)
{
	if (n < 0 || n < mindmg)
		throw std::exception("Error. Wrong max DMG.");
	maxdmg = n;
	return *this;
}

Enemy & Enemy::setXP(int n)
{
	if (n < 0)
		throw std::exception("Error. Negative XP.");
	XP = n;
	return *this;
}

//GETTERS
int Enemy::getDmg() const
{
	srand(time(nullptr));
	int d = rand() % (maxdmg - mindmg - 1) + 1;
	return mindmg + d;
}


//OTHER FUNKS
Enemy & Enemy::hurted(const Hero &hero)
{
	int curhp = getCurHP();
	int dmg = hero.getDMG(); //дамаг от героя
	if (hero.getWeapon() != nullptr && hero.getWeapon()->getEnchant().size() != 0)
	{
		auto plusit = hero.getWeapon()->getEnchant().find(type);
		if (plusit != hero.getWeapon()->getEnchant().end())
			dmg += plusit->second;
	}
	if (curhp - dmg <= 0)
	{
		setCurHP(0);
		throw std::exception("DEAD");
	}
	setCurHP(curhp - dmg);

	return *this;
}

Enemy & Enemy::attack(Hero &hero)
{
	try { hero.hurted(*this); }
	catch (std::exception &ex) //если герой убит
	{
		std::cout << ex.what() << std::endl;
	}
	return *this;
}

Object* Enemy::genLoot()
{
	if (curhp >= 0)
		throw std::exception("Enemy still alive.");
	srand(time(nullptr));
	int randob = rand() % 4;
	if (randob == O_MasterKey)
	{
		Object *plt = new MasterKey(rand() % 3 + 1);
		return plt;
	}
	if (randob == O_Potion)
	{
		Object *plt = new Potion("HP Potion", { "HP",  10 }, 10); //выгрузка из файла или же из вектора с возможными зельями 
		return plt;
	}
	if (randob == O_Weapon)
	{
		int randwp = rand() % 4;
		if (randwp == 0) //usual
		{
			Object *plt = new Weapon;
			return plt;
		}
		if (randwp == 1) //usual ench
		{
			Object *plt = new Weapon("Enchanced usual", 10, 15, { "Wolf", 5 });
			return plt;
		}
		if (randwp == 2) //artifact
		{

			Object* plt = new ArtifactWeapon("Artifact", 12, 17, { "STAM",  4 });
			return plt;
		}
		if (randwp == 3) //artifact ench
		{
			Object* plt = new ArtifactWeapon("Enchanced artifact", 15, 19, { "STR", 3 }, { "Golem", 8 });
			return plt;
		}
	}
	if (randob == O_Armor)
	{
		int randar = rand() % 5;
		if (randar == 0) //helmet
		{
			int ifen = rand() % 2;
			if (ifen == 0)
			{
				Object *plt = new Armor("Test helmet", "Helmet", 10);
				return plt;
			}
			else
			{
				Object* plt = new ArtifactArmor("Art helmet", "Helmet", 11, { "HP",  6 });
				return plt;
			}
		}
		if (randar == 1) //boots
		{
			int ifen = rand() % 2;
			if (ifen == 0)
			{
				Object *plt = new Armor("Test boots", "Boots", 9);
				return plt;
			}
			else
			{
				Object* plt = new ArtifactArmor("Art boots", "Boots", 11, { "HP", 6 });
				return plt;
			}
		}if (randar == 2) //armour
		{
			int ifen = rand() % 2;
			if (ifen == 0)
			{
				Object *plt = new Armor("Test amour", "Armour", 8);
				return plt;
			}
			else
			{
				Object* plt = new ArtifactArmor("Art armour", "Armour", 11, { "HP",  6 });
				return plt;
			}
		}if (randar == 3) //gloves
		{
			int ifen = rand() % 2;
			if (ifen == 0)
			{
				Object *plt = new Armor("Test gloves", "Gloves", 7);
				return plt;
			}
			else
			{
				Object* plt = new ArtifactArmor("Art gloves", "Gloves", 11, { "HP", 6 });
				return plt;
			}
		}
		if (randar == 4) //pendant
		{
			int ifen = rand() % 2;
			if (ifen == 0)
			{
				Object *plt = new Armor("Test pendant", "Pendant", 6);
				return plt;
			}
			else
			{
				Object* plt = new ArtifactArmor("Art pendant", "Pendant", 11, { "HP", 6 });
				return plt;
			}
		}
	}
	return nullptr;
}
