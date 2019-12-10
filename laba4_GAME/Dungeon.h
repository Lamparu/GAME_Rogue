
#pragma once
#ifndef _Dungeon_h_
#define _Dungeon_h_

#include "stdafx.h"
#include "../RogueLib/Enemy.h"
#include <vector>

using std::vector;
using namespace Prog4_Rogue;

namespace Prog4_Rogue {
	class Hero;

	class Square {
	private:
		sqtypes type;
		Object* fl_loot;
	public:

		Square & setType(sqtypes);
		Square & setLoot(Object *);

		sqtypes getType() const { return type; }
		Object* getLoot() const { return fl_loot; }
		virtual void actionWith() {};

		Square() :type(S_Floor) { fl_loot = nullptr; };
		Square(sqtypes name) :type(name) { fl_loot = nullptr; };
		Square(Object*);
	};

	class Floor {
	private:
		int floornum;
		//unsigned int xsquares;
		//unsigned int ysquares;
		vector<vector<Square*>> squares;
		vector<Enemy> enemypack;
	public:
		Floor & setNumFloor(int);
		Floor & setSquares(vector<vector<Square*>> &newsq) { squares = newsq; return *this; }
		Floor & setSquares(Square* nesq);
		//Floor & setXSquares(unsigned int n) { xsquares = n; return *this; }
		//Floor & setYSquares(unsigned int n) { ysquares = n; return *this; }
		Floor & setEnemypack(Enemy&);
		Floor & setEnemypack(vector<Enemy>&);

		int getNumFloor() const { return floornum; }
		//unsigned int getXSquares() const { return xsquares; }
		//unsigned int getYSquares() const { return ysquares; }
		//unsigned int getNumSquares() const { return xsquares * ysquares; }
		vector<vector<Square*>>& getSquares() { return squares; }
		vector<Enemy> getEnemies() const { return enemypack; }
		Square & getSChange(int, int);

		Floor() = delete;
		Floor(int, vector<vector<Square*>>&);
		Floor(int, vector<vector<Square*>>&, Enemy&);
		Floor(int, vector<vector<Square*>>&, vector<Enemy>&);
	};

	class Dungeon {
	private:
		//unsigned int nfloors;
		vector<Floor> floors;
		int curfl;
		Hero* player;
	public:

		//Dungeon & setNumFloors(int n) { nfloors = n; return *this; }
		Dungeon & setFloors(Floor&);
		Dungeon & setFloors(vector<Floor>&);
		Dungeon & setPlayer(Hero* you) { player = you; return *this; }
		Dungeon & setCurFloor(int);

		int getNumFloors() const { return floors.size(); }
		vector<Floor>& getFloors() { return floors; }
		Hero* getPlayer() const { return player; }
		int getCurFloor() const { return curfl; }

		Floor & getFChange() { return floors[curfl]; }

		Dungeon() = delete;
		Dungeon(Hero*, vector<Floor>&);
		Dungeon(Hero*, Floor&);
	};

	class Chest : public Square {
	private:
		int lvl;
		Object* loot;
	public:
		Chest & setLoot(Object*);
		Chest & setLvl(int n) {
			if (n < 0)
				throw std::exception("Wrong chest lvl.");
			lvl = n; return *this;
		}

		int getLvl() const { return lvl; }
		Object* getLoot() const { return loot; }

		Object* open_chest(Hero &);
		void actionWith(Hero &me) { open_chest(me); }


		Chest() :Square(S_Chest), lvl(0), loot(nullptr) {}
		Chest(int n, Object* drop = nullptr) :Square(S_Chest), loot(drop) {
			try { setLvl(n); }
			catch (std::exception & ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
	};

	class Door : public Square {
	private:
		int state;
	public:
		Door & setState(int n) {
			if (n < 0 || n > 1)
				throw std::exception("Wrong door state");
			state = n; return *this;
		}

		int getState() const { return state; }

		void actionWith() { open(); }
		Door & open() { state = opened; return *this; }
		Door & close() { state = closed; return *this; }

		Door() : Square(S_Door), state(closed) {}
		Door(unsigned int n) : Square(S_Door) {
			try { setState(n); }
			catch (std::exception & ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
	};

	class Stair : public Square {
	private:
		int state;
		int x;
		int y;
	public:
		Stair & setState(int n) {
			if (n < 0 || n > 1)
				throw std::exception("Wrong door state");
			state = n; return *this;
		}
		Stair & setX(int);
		Stair & setY(int);

		int getState() const { return state; }
		int getX() const { return x; }
		int getY() const { return y; }

		Square * go(Dungeon &);
		void actionWith(Dungeon & dg) { go(dg); }

		Stair(int nx, int ny) : Square(S_Stair), state(downwards) {
			try { setX(nx); setY(ny); }
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		Stair(int n, int nx, int ny) : Square(S_Stair) {
			try {
				setX(nx); setY(ny);
				setState(n);
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
	};

	class Wall : public Square {
		Wall() : Square(S_Wall) {}
	};
}

#endif _Dungeon_h_
