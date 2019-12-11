#include "stdafx.h"
#include "../RogueLib/Dungeon.h"
#include "../RogueLib/Hero.h"
#include <algorithm>
#include <ctime>
using namespace Prog4_Rogue;

//DUNGEON 
Dungeon & Dungeon::setFloors(Floor &nfl) { floors.clear(); floors.push_back(nfl); return *this; }

Dungeon & Dungeon::setFloors(vector<Floor> &newfloors)
{
	if (newfloors.size() == 0)
		throw std::exception("Error. 0 floors.");
	floors.clear();
	floors = newfloors;
	return *this;
}

Dungeon & Dungeon::setCurFloor(int newfl)
{
	if (newfl < 0 || newfl >= getFloors().size())
		throw std::exception("Num floor out of range");
	curfl = newfl;
	return *this;
}

Dungeon::Dungeon(Hero* you, vector<Floor> & newfloors)
{
	player = you;
	curfl = 0;
	try { setFloors(newfloors); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

Dungeon::Dungeon(Hero* you, Floor & onefloor)
{
	curfl = 0;
	floors.clear();
	setFloors(onefloor);
	player = you;
}

//FLOOR

Square & Floor::getSChange(int x, int y)
{
	if (x < 0 || y < 0 || x >= squares.size() || y >= squares.size())
		throw std::exception("Out of map");
	return *squares[y][x];
}

Floor & Floor::setSquares(Square *nesq)
{
	squares.clear();
	squares.push_back(vector<Square*>());
	squares[squares.size() - 1].push_back(nesq);
	return *this;
}

Floor & Floor::setEnemypack(vector<Enemy>& n_en)
{
	std::for_each(n_en.begin(), n_en.end(), [this](Enemy cur) {
		try { setEnemypack(cur); }
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
	});
	return *this;
}

Floor & Floor::setEnemypack(Enemy& n_en)
{
	bool there = false;
	for (int i = 0; i < Nenemies; ++i)
		if (n_en.getType() == enemy_types[i])
			there = true;
	if (there == false)
		throw std::exception("Error. Wrong enemy type.");
	enemypack.push_back(n_en);
	return *this;
}

Floor & Floor::setNumFloor(int n)
{
	if (n < 0 || n > MAX_FLOOR)
		throw std::exception("Out of floor num range.");
	floornum = n;
	return *this;
}

Floor::Floor(int nfl, vector<vector<Square*>>& newsq)
{
	try { setNumFloor(nfl); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	setSquares(newsq);
}

Floor::Floor(int nfl, vector<vector<Square*>>& newsq, Enemy& newen)
{
	//xsquares = xsq;
	//ysquares = ysq;
	try { setNumFloor(nfl); }
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	setSquares(newsq);
	enemypack.insert(enemypack.begin(), newen);
}

Floor::Floor(int nfl, vector<vector<Square*>> &newsq, vector<Enemy>& newen)
{
	//xsquares = xsq;
	//ysquares = ysq;
	setSquares(newsq);
	try {
		setEnemypack(newen);
		setNumFloor(nfl);
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

//SQUARE

Square & Square::setType(sqtypes names)
{
	if ((names == S_Chest) || (names == S_Stair) || (names == S_Door) || (names == S_Wall) || (names == S_Floor))
	{
		fl_loot = nullptr;
	}
	type = names;
	return *this;
}

Square & Square::setLoot(Object *nloot)
{
	if (nloot == nullptr)
		throw std::exception("Loot is nullptr.");
	if (getType() == S_Chest || getType() == S_Stair || getType() == S_Door || getType() == S_Wall)
		throw std::exception("Square is busy.");
	setType(S_Loot);
	objects wat = nloot->getID();
	if (wat == O_Weapon)
	{
		Weapon *lwp = dynamic_cast<Weapon*>(nloot);
		fl_loot = lwp;
	}
	if (wat == O_Armor)
	{
		Armor *lwp = dynamic_cast<Armor*>(nloot);
		fl_loot = lwp;
	}
	if (wat == O_MasterKey)
	{
		MasterKey *lwp = dynamic_cast<MasterKey*>(nloot);
		fl_loot = lwp;
	}
	if (wat == O_Potion)
	{
		Potion *lwp = dynamic_cast<Potion*>(nloot);
		fl_loot = lwp;
	}
	return *this;
}

Square::Square(Object* lt)
{
	type = S_Loot;
	setLoot(lt);
}

//CHEST
Chest & Chest::setLoot(Object* nloot)
{
	if (nloot == nullptr)
	{
		loot = nullptr;
		throw std::exception("Loot is nullptr.");
	}
	objects wat = nloot->getID();
	if (wat == O_Weapon)
	{
		Weapon *lwp = dynamic_cast<Weapon*>(nloot);
		loot = lwp;
	}
	if (wat == O_Armor)
	{
		Armor *lwp = dynamic_cast<Armor*>(nloot);
		loot = lwp;
	}
	if (wat == O_MasterKey)
	{
		MasterKey *lwp = dynamic_cast<MasterKey*>(nloot);
		loot = lwp;
	}
	if (wat == O_Potion)
	{
		Potion *lwp = dynamic_cast<Potion*>(nloot);
		loot = lwp;
	}
	return *this;
}

Object* Chest::open_chest(Hero &you)
{
	int br = you.getOneCharac("BR");
	Armor* brgloves = you.getPartArmor("Arms");
	if (brgloves != nullptr)
	{
		if (brgloves->IAm() == ARTARMOR)
		{
			ArtifactArmor *brg = dynamic_cast<ArtifactArmor*>(brgloves);
			br += brg->getIntCharac("BR");
		}
	}
	Armor* brpendant = you.getPartArmor("Neck");
	if (brpendant != nullptr)
	{
		if (brgloves->IAm() == ARTARMOR)
		{
			ArtifactArmor *brp = dynamic_cast<ArtifactArmor*>(brpendant);
			br += brp->getIntCharac("BR");
		}
	}
	if (br < lvl * 30)
		throw std::exception("Hero's breaking lvl is too low");
	srand(time(nullptr));
	int randob = rand() % 10;
	if (randob == 1)
		throw std::exception("Not successful to open.");
	if (loot != nullptr)
	{
		Object* take = loot->clone();
		setType(S_Floor);
		return take;
	}
	setType(S_Floor);
	//что делать, если нужно из сундука сделать клетку?
	return nullptr;
}

//STAIR

Square * Stair::go(Dungeon &dg)
{
	int X, Y;
	if (getState() == downwards)
	{
		if (dg.getNumFloors() < dg.getCurFloor() + 1)
			throw std::exception("No more floors down");
		dg.setCurFloor(dg.getCurFloor() + 1);
		X = getX();
		Y = getY();
	}
	if (getState() == upwards)
	{
		if (dg.getCurFloor() - 1 < 0)
			throw std::exception("No more floors up");
		dg.setCurFloor(dg.getCurFloor() - 1);
		X = getX();
		Y = getY();
	}
	return dg.getFloors()[dg.getCurFloor()].getSquares()[Y][X];
}

Stair & Stair::setX(int i)
{
	if (i < 0)
		throw std::exception("Wrong x index.");
	x = i;
	return *this;
}

Stair & Stair::setY(int i)
{
	if (i < 0)
		throw std::exception("Wrong y index.");
	y = i;
	return *this;
}