#pragma once
#pragma once
#ifndef _Hero_h_
#define _Hero_h_

#include "../RogueLib/Objects.h"
#include "../RogueLib/Enemy.h"
//#include "../RogueLib/Vector.h"
#include <map>
#include <utility>
#include <vector>

using namespace Prog4_Rogue;

using std::map;
using std::pair;
using std::string;
using std::vector;

namespace Prog4_Rogue {
	class Dungeon;
	class Square;

	class Hero {
	private:
		string play_name;
		int XP;
		map<string, pair<string, int>> charac;
		MasterKey masterkey;
		int maxpt;
		vector<Potion> pt;
		Weapon* wp;
		map<string, Armor*> ar; //часть тела и броня
		Coordinates position;

	public:
		Hero & setCharacter(map<string, pair<string, int>>);
		Hero & changeCharac(string, int);
		Hero & setHP(int);
		Hero & setMaxHp(int);
		Hero & setWeapon(Weapon*);
		Hero & setPotion(Potion);
		Hero & setPotion(vector<Potion>);
		Hero & setMaxPt(int);
		Hero & setMasterKey(MasterKey);
		Hero & setArmor(map<string, Armor*>);
		Hero & setArmor(Armor*);
		Hero & setXP(int);
		Hero & getItem(Object*);
		Hero & setPosition(Coordinates, Dungeon &);
		Hero & setCoordinates(int, int);
		Hero & setCoordinates(Coordinates);
		Hero & setPlayName(string);

		map<string, pair<string, int>> getAllCharacter() const { return charac; };
		int getOneCharac(string) const;
		int getCharNum() const;
		int getHP() const;
		int getXP() const { return XP; };
		int getMaxHP() const;
		int getDMG() const; //from min and max DMG + stats
		int getDEF() const; //from armor + stats
		map<string, Armor*> getArmor() const { return ar; };
		Armor* getPartArmor(string tp) const { return ar.find(tp)->second; };
		Weapon* getWeapon() const { return wp; };
		vector<Potion> getPotion() const { return pt; };
		int getCurPt() const;
		int getMaxPt() const { return maxpt; };
		int getMasterKey() const;
		Coordinates getPosition() const { return position; };
		string getPlayName() const { return play_name; };

		Hero & updatePotion();
		Hero & drink(Potion &);
		Hero & hurted(const Enemy &);
		Hero & attack(Enemy &); //?
		Hero & setCharbyXP(string, int);//Characteristic &, int);
		void compare(const Weapon*, const Weapon*);
		void compare(const Armor*, const map<string, Armor*>&);
		bool chooseWpArm();
		friend std::ostream & operator <<(std::ostream &, const Hero &);
		Square * goLeft(Dungeon&);
		Square * goRight(Dungeon&);
		Square * goUp(Dungeon&);
		Square * goDown(Dungeon&);
		Square * move(int, Dungeon&);

		Hero();
		Hero(string);
		Hero(string, map<string, pair<string, int>>, map<string, Armor*>, int, vector<Potion>, Weapon*, int, int, int, int);
	};
}
#endif _Hero_h_
