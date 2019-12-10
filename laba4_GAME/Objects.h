#pragma once
#pragma once
#ifndef _Objects_h_
#define _Objects_h_

#include <iostream>
#include <vector>
#include <utility>
#include "../RogueLib/ConstThings.h"

using std::string;
using std::pair;

using namespace Prog4_Rogue;

namespace Prog4_Rogue {
	class Hero;
	//class ArtifatArmor;
	//class ArtifactWeapon;

	class Object {
	protected:
		objects id;
	public:
		virtual Object & setID(objects nm) { id = nm; return *this; }

		virtual objects getID() const { return id; }

		Object* clone()const { return new Object(*this); }
		//Object(objects str) :name(str) {};

		virtual ~Object() {}
	};

	class Weapon : public Object {
	protected:
		string name;
		int dmgmin;
		int dmgmax;
		map<string, int> enchant; //<enemy type, +/- dmg>
	public:
		Weapon & setDmg(int min, int max);
		Weapon & setMaxDmg(int n) { dmgmax = n; return *this; };
		Weapon & setMinDmg(int n) { dmgmin = n; return *this; };
		Weapon & setName(string str) { name = str; return *this; }
		Weapon & setEnchant(map<string, int>);
		Weapon & setEnchant(pair<string, int>);

		int getDmg() const;
		int getMinDmg() const { return dmgmin; };
		int getMaxDmg() const { return dmgmax; };
		map<string, int> getEnchant() const { return enchant; }
		string getName() const { return name; };

		void printWeapon() const;
		virtual weapons IAm() { return WEAPON; };

		//ArtifactWeapon* changeClass();

		Weapon();
		Weapon(string, int, int);
		Weapon(string, int, int, map<string, int>);
		Weapon(string, int, int, pair<string, int>);
	};

	class Armor : public Object { //добавить =
	protected:
		string name;
		string type; //helmet, boots, ...
		int def;
	public:
		Armor & setDef(int n) { def = n; return *this; }
		Armor & setType(string str) { type = str; return *this; }
		Armor & setName(string str) { name = str; return *this; }

		int getDef() const { return def; };
		string getType() const { return type; };
		virtual armors IAm() { return ARMOR; };
		string getName() const { return name; };

		//ArtifactArmor* changeClass();

		Armor() = delete;
		Armor(string, string, int); //name, type, def
	};

	class MasterKey : public Object {
	private:
		int amount;
	public:
		MasterKey & setAmount(int);

		int getAmount() const { return amount; };

		MasterKey() : amount(0) { setID(O_MasterKey); }
		MasterKey(int);
	};

	class Potion : public Object {
	private:
		string name;
		potions state;
		map<string, int> chchar; //shrt_charac
		int time; //кол-во клеток
	public:
		Potion & setCharac(map<string, int>);
		Potion & setCharac(pair<string, int>);
		Potion & setTime(int n);
		Potion & setState(potions n) { state = n; return *this; }
		Potion & setName(string str) { name = str; return*this; }

		map<string, int> getCharac() const { return chchar; }
		int getTime() const { return time; }
		string getName() const { return name; }
		potions getState() const { return state; }

		Potion() = delete;
		Potion(string, map<string, int>, int); //for many characteristics
		Potion(string, pair<string, int>, int);//Characteristic); //for 1 characteristic
	};

	class Artifact {
	protected:
		map<string, int> artchar; //bonus to characteristics

		virtual Artifact & setCharac(map<string, int>);
		virtual Artifact & setCharac(pair<string, int>);
	public:
		//virtual void bonus(Hero &);
		virtual int getIntCharac(string);
		virtual map<string, int> getCharac() const { return artchar; };

		virtual ~Artifact() {};
	};

	class ArtifactWeapon :public Weapon, public Artifact {
	public:

		virtual weapons IAm() { return ARTWEAPON; }

		//virtual void bonus(Hero &);

		ArtifactWeapon() = delete;
		ArtifactWeapon(string, int, int, map<string, int>);
		ArtifactWeapon(string, int, int, map<string, int>, map<string, int>);
		ArtifactWeapon(string, int, int, map<string, int>, pair<string, int>);
		ArtifactWeapon(string, int, int, pair<string, int>);
		ArtifactWeapon(string, int, int, pair<string, int>, map<string, int>);
		ArtifactWeapon(string, int, int, pair<string, int>, pair<string, int>);

		~ArtifactWeapon() {};
	};

	class ArtifactArmor :public Armor, public Artifact {
	public:

		virtual armors IAm() { return ARTARMOR; }

		ArtifactArmor() = delete;
		ArtifactArmor(string, string, int, map<string, int>);
		ArtifactArmor(string, string, int, pair<string, int>);

		~ArtifactArmor() {};
	};
	//подумать над зачарованием 
	/*
	class Enchanced {
	protected:
		map<string, int> ench;

		Enchanced & setEnchance(std::string, int);

		map<string, int> getEnchance() const { return ench; }

		Enchanced bonus() const;
	};
	*/
}

#endif _Objects_h_