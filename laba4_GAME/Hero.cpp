#include "stdafx.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
#include <string>
#include <map>
#include <algorithm>
#include <conio.h>
using namespace Prog4_Rogue;
using std::map;

//SETTERS
Hero & Hero::setPlayName(string nname)
{
	play_name = nname;
	return *this;
}

Hero & Hero::setCharacter(map<string, pair<string, int>> charcs)
{
	charac = charcs;
	return *this;
}

Hero & Hero::changeCharac(string str, int n)
{
	if (n < 0)
		throw std::exception("Negative num for characteristic.");
	auto it = charac.find(str);
	if (it == charac.end())
		throw std::exception("No such characteristic.");
	if (it->first == "HP")
	{
		auto maxit = charac.find("MAX HP");
		int mxhp = maxit->second.second;
		if (n > mxhp)
			throw std::exception("MAX HP is less.");
	}
	if (it->first == "STAM")
	{
		auto maxit = charac.find("MAX STAM");
		int mxst = maxit->second.second;
		if (n > mxst)
			throw std::exception("MAX STAM is less.");
	}
	it->second.second = n;
	return *this;
}

Hero & Hero::setHP(int n)
{
	if (n < 0)
		throw std::exception("Negative HP.");
	auto it = charac.find("MAX HP");
	if (it->second.second < n)
		throw std::exception("MAX HP is less.");
	charac.find("HP")->second.second = n;
	return *this;
}

Hero & Hero::setMaxHp(int n)
{
	if (n < 0)
		throw std::exception("Negative Max HP.");
	auto maxHPp = charac.find("MAX HP");
	int maxHPn = maxHPp->second.second;
	auto HPp = charac.find("HP");
	int HPn = HPp->second.second;
	float perc = (float)HPn / (float)maxHPn;
	perc = n * perc;
	charac.find("HP")->second.second = (int)perc;
	charac.find("MAX HP")->second.second = n;
	return *this;
}

Hero & Hero::setMaxPt(int n)
{
	if (n < 0)
		throw std::exception("Negative amount of potions.");
	maxpt = n;
	return *this;
}

Hero & Hero::setWeapon(Weapon* wpnew)
{
	if (wpnew == nullptr)
	{
		wp = nullptr;
		return *this;
	}
	if (wpnew->IAm() == ARTWEAPON)
	{
		ArtifactWeapon* artnwp = dynamic_cast<ArtifactWeapon*>(wpnew);
		wp = artnwp;
	}
	if (wpnew->IAm() == WEAPON)
		wp = wpnew; //прописать = ?
	return *this;
}

Hero & Hero::setXP(int n)
{
	if (n < 0)
		throw std::exception("Negative XP.");
	XP = n;
	return *this;
}

Hero & Hero::setPotion(Potion ptnew)
{
	if (getCurPt() >= getMaxPt())
		throw std::exception("You have max amount of potions");
	pt.push_back(ptnew);
	return *this;
}

Hero & Hero::setPotion(vector<Potion> ptnew)
{
	if (getCurPt() + ptnew.size() > getMaxPt())
		throw std::exception("Too many potions to add");
	std::for_each(ptnew.begin(), ptnew.end(), [this](Potion cur)
	{
		pt.push_back(cur);
	});
	return *this;
}

Hero & Hero::setMasterKey(MasterKey n)
{
	masterkey.setAmount(n.getAmount());
	return *this;
}

Hero & Hero::setArmor(map<string, Armor*> arnew)
{
	for (auto it = arnew.begin(); it != arnew.end(); ++it)
	{
		setArmor(it->second);
	}
	/*
	std::for_each(arnew.begin(), arnew.end(), [this](pair<string, Armor*> cur)
	{
		setArmor(cur.second);
	});*/
	return *this;
}

Hero & Hero::setArmor(Armor* arnew)
{
	string typear = arnew->getType();
	auto itnew = bdprts_armr.find(typear);
	auto it = ar.find(itnew->second);
	if (arnew->IAm() == ARTARMOR)
	{
		ArtifactArmor* artnar = dynamic_cast<ArtifactArmor*>(arnew);
		it->second = artnar;
	}
	if (arnew->IAm() == ARMOR)
		it->second = arnew;
	return *this;
}

Hero & Hero::setCoordinates(int nx, int ny)
{
	if (nx < 0 || ny < 0 || nx >= MAX_X || ny >= MAX_Y)
		throw std::exception("Out of map");
	position.x = nx;
	position.y = ny;
	return *this;
}

Hero & Hero::setCoordinates(Coordinates ncoord)
{
	if (ncoord.x < 0 || ncoord.y < 0 || ncoord.x >= MAX_X || ncoord.y >= MAX_Y)
		throw std::exception("Out of map");
	position.x = ncoord.x;
	position.y = ncoord.y;
	return *this;
}

Hero & Hero::getItem(Object *loot) //можно переделать под массив функций 
{
	if (loot != nullptr) {
		objects wat = loot->getID();
		if (wat == O_Weapon)
		{
			Weapon *lwp = dynamic_cast<Weapon*>(loot);
			compare(lwp, getWeapon());
			if (chooseWpArm())
			{
				setWeapon(lwp);
				std::cout << "You got new weapon!" << std::endl;
			}
			else
				loot = nullptr;
		}
		if (wat == O_Armor)
		{
			Armor *lwp = dynamic_cast<Armor*>(loot);
			compare(lwp, getArmor());
			if (chooseWpArm())
			{
				setArmor(lwp);
				std::cout << "You got new armor!" << std::endl;
			}
			else
				loot = nullptr;
		}
		if (wat == O_MasterKey)
		{
			MasterKey *lwp = dynamic_cast<MasterKey*>(loot);
			setMasterKey(*lwp);
		}
		if (wat == O_Potion)
		{
			Potion *lwp = dynamic_cast<Potion*>(loot);
			setPotion(*lwp);
		}
	}
	return *this;
}


//GETTERS
int Hero::getOneCharac(string nm) const
{
	auto pt1 = charac.find(nm);
	if (pt1 == charac.end())
	{
		throw std::exception("Such characteristic doesn't exist.");
	}
	return pt1->second.second;
}

int Hero::getCharNum() const
{
	return charac.size();
}

int Hero::getHP() const
{
	auto pt1 = charac.find("HP");
	auto pt2 = pt1->second;
	return pt2.second;
}

int Hero::getMaxHP() const
{
	auto pt1 = charac.find("MAX HP");
	auto pt2 = pt1->second;
	return pt2.second;
}

int Hero::getCurPt() const
{
	return pt.size();
}

int Hero::getDMG() const
{
	if (wp == nullptr)
		return 5;
	int str = charac.find("STR")->second.second;
	int stam = charac.find("STAM")->second.second;
	if (wp->IAm() == ARTWEAPON)
	{
		ArtifactWeapon* nwp = dynamic_cast<ArtifactWeapon*>(wp);
		auto stats = nwp->getCharac();
		auto it = stats.find("STR");
		if (it != stats.end())
			str += it->second;
		it = stats.find("STAM");
		if (it != stats.end())
			stam += it->second;
	}
	float bonusstam = stam * 0.2; //чета с флоат сделать 
	float bonusstr = str * 0.5;
	float d = wp->getDmg()*0.8;
	d = (int)d + (int)bonusstr + (int)bonusstam;
	if (d > wp->getMaxDmg())
		return wp->getMaxDmg();
	return d;
}

int Hero::getDEF() const
{
	float res = 0;
	int n = 0;
	for (auto it = ar.begin(); it != ar.end(); ++it)
	{
		if (it->second != nullptr)
		{
			++n;
			res += it->second->getDef();
		}
	}
	if (n != 0)
		res = res / n;
	res += charac.find("AG")->second.second * 0.2;
	res += charac.find("STR")->second.second * 0.2;
	res += charac.find("STAM")->second.second*0.2;
	return res;
}

int Hero::getMasterKey() const
{
	return masterkey.getAmount();
}

//OTHER FUNKS
Hero & Hero::drink(Potion &newpt)
{
	newpt.setState(drunk);
	auto np = newpt.getCharac();
	for (auto it = np.begin(); it != np.end(); ++it)
	{
		auto cur = charac.find(it->first);
		try { changeCharac(it->first, it->second + cur->second.second); }
		catch (std::exception & ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	/*
	std::for_each(np.begin(), np.end(), [&np, this](pair<string, int> curpt) {
		auto it = charac.find(curpt.first);
		it->second.second += curpt.second;
	});*/
	return *this;
}

Hero & Hero::hurted(const Enemy &en)
{
	int curhp = getHP();
	int dmg = en.getDmg(); //дамаг от врага
	int def = getDEF();
	int stam = getOneCharac("STAM");
	if (stam - 10 <= 0)
		changeCharac("STAM", 0);
	else
		changeCharac("STAM", stam - 10);
	if (curhp - dmg + def < 0)
	{
		setHP(0);
		throw std::exception("DEAD");
	}
	if (curhp - dmg + def >= getHP())
		setHP(curhp - 4);
	else
		setHP(curhp - dmg + def);
	return *this;
}

Hero & Hero::attack(Enemy &en)
{
	try { en.hurted(*this); }
	catch (std::exception &ex) //если враг убит
	{
		std::cout << ex.what() << std::endl;
		setXP(getXP() + en.getXP());
	}
	return *this;
}

Hero & Hero::setCharbyXP(string str, int delxp) // 1:100
{
	int curxp = getXP();
	if (delxp > curxp)
		throw std::exception("Not enough XP.");
	auto it = charac.find(str);
	if (it == charac.end())
		throw std::exception("Characteristic not found.");
	setXP(curxp - delxp / 100 * 100);
	it->second.second += delxp / 100;
	return *this;
}


void Hero::compare(const Weapon* new_, const Weapon* old_)
{
	if (old_ != nullptr)
	{
		std::cout << "Your weapon: " << old_->getName() << std::endl;
		old_->printWeapon();
	}
	std::cout << "Weapon you can choose: " << new_->getName() << std::endl;
	new_->printWeapon();
}

void Hero::compare(const Armor* new_, const map<string, Armor*>& old_)
{
	auto i = old_.find(new_->getType());
	if (i != old_.end())
	{
		Armor* ar = i->second;
		std::cout << "Your " << ar->getType() << ": " << ar->getName() << std::endl;
		std::cout << "DEF = " << ar->getDef() << std::endl;
	}
	if (new_ != nullptr)
	{
		std::cout << "Armor you can choose: " << new_->getName() << std::endl;
		std::cout << "DEF = " << new_->getDef() << std::endl;
	}
}

bool Hero::chooseWpArm()
{
	string pch = "";
	std::cout << "Do you want to change? y/n" << std::endl;
	do {
		std::cout << pch;
		char i = _getch();
		if (i == 'y')
			return true;
		if (i == 'n')
			return false;
		pch = "Wrong letter, try again";
	} while (true);
}

//CONSTRUCTORS
Hero::Hero()
{
	for (auto itp = chars.begin(); itp != chars.end(); ++itp)
	{
		pair<string, int> puck = { itp->second, INITCH };
		charac.insert({ itp->first, puck });
	}
	/*
	for (auto i = 0; i < Nchar; ++i)
	{
		pair<string, int> puck = { lng_char[i], INITCH };
		pair<string, pair<string, int>> inpk = { shrt_char[i], puck };
		charac.insert(inpk);
	}*/
	auto it = charac.find("HP");
	it->second.second = MAXHP;
	it = charac.find("MAX HP");
	it->second.second = MAXHP;
	it = charac.find("STAM");
	it->second.second = MAXSTAM;
	it = charac.find("MAX STAM");
	it->second.second = MAXSTAM;
	for (auto j = bdprts_armr.begin(); j != bdprts_armr.end(); ++j)
	{
		pair<string, Armor*> pu = { j->second, nullptr };
		ar.insert(pu);
	}
	wp = nullptr;
	XP = 0;
	masterkey.setAmount(0);
	maxpt = INITPT;
	position.x = 0;
	position.y = 0;
	play_name = NAME_DEFAULT;
}
Hero::Hero(string nname)
{
	for (auto itp = chars.begin(); itp != chars.end(); ++itp)
	{
		pair<string, int> puck = { itp->second, INITCH };
		charac.insert({ itp->first, puck });
	}
	/*
	for (auto i = 0; i < Nchar; ++i)
	{
		pair<string, int> puck = { lng_char[i], INITCH };
		pair<string, pair<string, int>> inpk = { shrt_char[i], puck };
		charac.insert(inpk);
	}*/
	auto it = charac.find("HP");
	it->second.second = MAXHP;
	it = charac.find("MAX HP");
	it->second.second = MAXHP;
	it = charac.find("STAM");
	it->second.second = MAXSTAM;
	it = charac.find("MAX STAM");
	it->second.second = MAXSTAM;
	for (auto j = bdprts_armr.begin(); j != bdprts_armr.end(); ++j)
	{
		pair<string, Armor*> pu = { j->second, nullptr };
		ar.insert(pu);
	}
	wp = nullptr;
	XP = 0;
	masterkey.setAmount(0);
	maxpt = INITPT;
	position.x = 0;
	position.y = 0;
	play_name = nname;
}

Hero::Hero(string nname, map<string, pair<string, int>> newchar, map<string, Armor*> newar, int mpt, vector<Potion> newpt, Weapon* newwp = nullptr, int xp = 0, int numkey = 0, int x_ = 0, int y_ = 0)
{
	for (auto j = bdprts_armr.begin(); j != bdprts_armr.end(); ++j)
	{
		pair<string, Armor*> pu = { j->second, nullptr };
		ar.insert(pu);
	}
	try {
		setMaxPt(mpt);
		setCharacter(newchar);
		setArmor(newar);
		setWeapon(newwp);
		setPotion(newpt);
		setXP(xp);
		masterkey.setAmount(numkey);
		setCoordinates(x_, y_);
		setPlayName(nname);
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//FRIENDS
std::ostream & Prog4_Rogue::operator <<(std::ostream &s, const Hero & hero)
{
	s << "*** HERO ***" << std::endl;
	s << "XP: " << hero.getXP() << std::endl;
	auto stats = hero.getAllCharacter();
	for (auto it = stats.begin(); it != stats.end(); ++it)
	{
		s << it->second.first << ": " << it->second.second << std::endl;
	}
	if (hero.getWeapon() != nullptr) //написать для артефакта
	{
		Weapon* hero_wp = hero.getWeapon();
		s << hero_wp->getName() << ": " << std::endl;
		s << "DMG: max = " << hero_wp->getMaxDmg() << " min = " << hero_wp->getMinDmg() << std::endl;
		auto ench = hero_wp->getEnchant();
		if (ench.size() != 0)
		{
			s << "Enchantments: ";
			for (auto i = ench.begin(); i != ench.end(); i++)
				s << i->first << ": " << i->second;
		}
		s << std::endl;
	}
	else
		s << "Weapon: empty" << std::endl;
	auto armors = hero.getArmor();
	for (auto it = armors.begin(); it != armors.end(); ++it) //написать для артефакта
	{
		s << it->first;
		if (it->second != nullptr)
		{
			s << " " << it->second->getName() << std::endl;
			s << "Defence: " << it->second->getDef() << std::endl;
		}
		else
			s << ": empty" << std::endl;
	}
	s << "MasterKeys: " << hero.getMasterKey() << std::endl;
	s << "POTIONS: " << std::endl;
	s << "Places for potions: " << hero.getMaxPt() << std::endl;
	auto potions = hero.getPotion();
	if (potions.size() != 0)
	{
		for (auto it = potions.begin(); it != potions.end(); ++it)
		{
			s << it->getName() << std::endl;
			s << "Time: " << it->getTime() << std::endl;
			auto stpt = it->getCharac();
			s << "Bonus to characteristics: " << std::endl;
			for (auto itp = stpt.begin(); itp != stpt.end(); ++itp)
				s << itp->first << ": " << itp->second;
		}
	}
	return s;
}

//MOVEMENT


Hero & Hero::setPosition(Coordinates ncoord, Dungeon& dung)
{
	if (ncoord.x < 0 || ncoord.y < 0 || ncoord.x >= dung.getFloors()[dung.getCurFloor()].getSquares().size() || ncoord.y >= dung.getFloors()[dung.getCurFloor()].getSquares().size())
		throw std::exception("Out of map");
	int cfl = dung.getCurFloor();
	//Square *nsq = &(dung.getFloors()[cfl].getSquares()[ncoord.y][ncoord.x]);
	
	//Floor cflf = cflfl[cfl];
	//vector<vector<Square>> csq = cflf.getSquares();
	//auto sqd = dung.getFloors()[cfl].getSquares()[ncoord.y][ncoord.x];
	//vector<vector<Square*>> cqs = dung.getFloors()[cfl].getSquares();
	//Square* nsq = cqs[ncoord.y][ncoord.x];
	//Square npsq = cqs[ncoord.y][ncoord.x];
	Square* nsq = dung.getFloors()[dung.getCurFloor()].getSquares()[ncoord.y][ncoord.x];
	if (nsq->getType() == S_Wall)
		throw std::exception("There is wall.");
	if (nsq->getType() == S_Door)
	{
		//dung.getFloors()[cfl].getSquares()[ncoord.y][ncoord.x]->actionWith();
		//nsq->actionWith();
		Door* check = dynamic_cast<Door*>(nsq); //?
		if (check->getState() == closed)
		{
			check->open();
			std::cout << "The door was opened" << std::endl;
			//throw std::exception("The door was opened.");
		}
	}
	if (nsq->getType() == S_Chest)
	{
		Chest* check = dynamic_cast<Chest*>(nsq);
		try { 
			Object *LootFromChest = check->open_chest(*this); 
			std::cout << "The chest was opened" << std::endl;
			getItem(LootFromChest);
		}
		catch (std::exception & ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	if (nsq->getType() == S_Stair)
	{
		Stair* check = dynamic_cast<Stair*>(nsq);
		nsq = check->go(dung);
		if (check->getState() == downwards)
			std::cout << "Went down the stairs." << std::endl;
		if (check->getState() == upwards)
			std::cout << "Went up the stairs." << std::endl;
	}
	if (nsq->getType() == S_Loot)
	{
		if (nsq->getLoot() != nullptr)
			getItem(nsq->getLoot());
		//nsq->setType(S_Floor);
		dung.getFChange().getSChange(ncoord.x, ncoord.y).setType(S_Floor);
	}
	setCoordinates(ncoord);
	return *this;
}

Hero & Hero::updatePotion()
{
	for (auto it = pt.begin(); it != pt.end(); ++it)
	{
		if (it->getState() == drunk)
		{
			if (it->getTime() - 1 <= 0)
				it->setTime(0);
			else
				it->setTime(it->getTime() - 1);
		}
	}
	for (auto pcur = pt.begin(); pcur != pt.end(); ++pcur)
		if (pcur->getTime() == 0)
		{
			for (auto potion_ch = pcur->getCharac().begin(); potion_ch != pcur->getCharac().end(); ++potion_ch)
				charac.find(potion_ch->first)->second.second -= potion_ch->second;
			pt.erase(pcur);
		}
	return *this;
}

Square * Hero::goLeft(Dungeon& dg)
{
	Coordinates newc = getPosition();
	newc.x = newc.x - 1;
	if (newc.x < 0)
		throw std::exception("End of map.");
	setPosition(newc, dg);
	updatePotion();
	return dg.getFloors()[dg.getCurFloor()].getSquares()[newc.x][newc.y];
}

Square * Hero::goRight(Dungeon& dg)
{
	Coordinates newc = getPosition();
	newc.x = newc.x + 1;
	if (newc.x >= MAX_X)
		throw std::exception("End of map.");
	setPosition(newc, dg);
	updatePotion();
	return dg.getFloors()[dg.getCurFloor()].getSquares()[newc.x][newc.y];
}

Square * Hero::goUp(Dungeon& dg)
{
	Coordinates newc = getPosition();
	newc.y = newc.y + 1;
	if (newc.y >= MAX_Y)
		throw std::exception("End of map.");
	setPosition(newc, dg);
	updatePotion();
	return dg.getFloors()[dg.getCurFloor()].getSquares()[newc.x][newc.y];
}

Square * Hero::goDown(Dungeon& dg)
{
	Coordinates newc = getPosition();
	newc.y = newc.y - 1;
	if (newc.y < 0)
		throw std::exception("End of map.");
	setPosition(newc, dg);
	updatePotion();
	return dg.getFloors()[dg.getCurFloor()].getSquares()[newc.x][newc.y];
}

Square * Hero::move(int ins, Dungeon &dg)
{
	if (ins == 75)
		return goLeft(dg);
	if (ins == 72)
		return goUp(dg);
	if (ins == 77)
		return goRight(dg);
	if (ins == 80)
		return goDown(dg);
	if (ins == 105)
		std::cout << *(dg.getPlayer()) << std::endl;
	else
	{
		throw std::exception("Wrong way");
	}
}
