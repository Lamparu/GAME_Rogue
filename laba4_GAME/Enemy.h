#pragma once
#ifndef _Enemy_h_
#define _Enemy_h_

#include "../RogueLib/Objects.h"

using namespace Prog4_Rogue;

namespace Prog4_Rogue {
	class Hero;

	class Enemy {
	private:
		string type;
		int curhp;
		int maxhp;
		int maxdmg;
		int mindmg;
		int XP;
	public:
		Enemy & setCurHP(int n);
		Enemy & setMaxHP(int n);
		Enemy & setType(string);
		Enemy & setDmg(int, int);
		Enemy & setMinDmg(int n);
		Enemy & setMaxDmg(int n);
		Enemy & setXP(int n);

		int getMinDmg() const { return mindmg; };
		int getMaxDmg() const { return maxdmg; };
		int getDmg() const; //дамаг из мин и макс
		int getMaxHP() const { return maxhp; };
		int getCurHP() const { return curhp; };
		int getXP() const { return XP; };
		string getType() const { return type; };

		Enemy & hurted(const Hero &);
		Enemy & attack(Hero &);
		Object* genLoot();

		Enemy() = delete;
		Enemy(string, int, int, int, int, int);
	};

}

#endif _ENemy_h_