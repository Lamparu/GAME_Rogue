#pragma once
#ifndef _ConstThings_h_
#define _ConstThings_h_

#include <vector>
#include <map>
#include <utility>

//using namespace Prog4_Rogue;
using std::map;
using std::string;

namespace Prog4_Rogue {
	struct Coordinates
	{
		int x;
		int y;
	};
	const unsigned int MAX_FLOOR = 5;
	const unsigned int MAX_X = 5;
	const unsigned int MAX_Y = 5;
	const unsigned int MAXHP = 100;
	const unsigned int MAXSTAM = 100;
	const unsigned int INITCH = 5;
	const unsigned int INITPT = 2;

	static const char *NAME_DEFAULT = "IVAN";

	static const string shrt_char[] = { "AG", "BR","HP", "MAX HP",  "MAX STAM", "STAM", "STR"};
	static const string lng_char[] = { "Agility", "Breaking", "HealthPoint", "Max HealthPoint", "Max Stamina", "Stamina", "Strength" };
	static const map <string, string> chars = { {"AG", "Agility"}, {"BR", "Breaking"}, {"HP", "HealthPoint"}, {"MAX HP", "Max HealthPoint"}, {"MAX STAM", "Max Stamina"}, {"STAM", "Stamina"}, {"STR", "Strength"} };
	static const int Nchar = sizeof(shrt_char) / sizeof(shrt_char[0]);
	static const string enemy_types[] = { "Undead", "Goblin", "Wolf", "Golem", "Fireball" };
	static const int Nenemies = sizeof(enemy_types) / sizeof(enemy_types[0]);
	//почитать про герои меча и магии, про классы персов
	//static const map<string, string> bdprts_armr = { {"Head","Helmet"}, {"Legs","Boots"}, {"Arms","Gloves"}, {"Body","Armour"}, {"Neck","Pendant"} };
	static const map<string, string> bdprts_armr = { { "Gloves", "Arms" }, { "Armour", "Body" }, {"Helmet", "Head"}, { "Boots", "Legs" }, { "Pendant", "Neck" } };
	//static const pair<string, string> bdprts_armr[] = { { "Gloves", "Arms" }, { "Armour", "Body" }, {"Helmet", "Head"}, { "Boots", "Legs" }, { "Pendant", "Neck" } };
	//static const string objects[] = { "Weapon", "Armor", "MaterKey", "Potion" };
	//static const int Nobj = sizeof(objects) / sizeof(objects[0]);

	const enum objects { O_Weapon, O_Armor, O_MasterKey, O_Potion };
	const enum sqtypes { S_Floor, S_Wall, S_Door, S_Stair, S_Chest, S_Loot };
	const enum stair { downwards, upwards };
	const enum door { closed, opened };
	const enum weapons { WEAPON, ARTWEAPON };
	const enum armors { ARMOR, ARTARMOR };
	const enum potions { full, drunk };
}
#endif _ConstThings_h_