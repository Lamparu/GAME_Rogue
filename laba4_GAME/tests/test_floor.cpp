#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

TEST(FloorConstructors, OnlySquares)
{
	Weapon loot_wp;
	vector<vector<Square*>> lvl1 = {
	{new Square(), new Square(&loot_wp), new Square()},
	{new Square(), new Square(S_Wall), new Door()},
	{new Chest(), new Square(S_Wall), new Square()} };

	Floor test(1, lvl1);

	ASSERT_EQ(test.getNumFloor(), 1);
	ASSERT_EQ(test.getEnemies().size(), 0);
	ASSERT_EQ(test.getSquares().size(), 3);

}

TEST(FloorConstructors, OneEnemy)
{

}