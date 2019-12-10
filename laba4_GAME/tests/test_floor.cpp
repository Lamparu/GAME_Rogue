#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

TEST(FloorConstructors, OnlySquares)
{
	Weapon loot_wp;
	vector<vector<Square>> lvl1 = {
	{Square(),Square(&loot_wp), Square()},
	{Square(), Square(S_Wall), Door()},
	{Chest(), Square(S_Wall), Square()} };

	Floor test(1, lvl1);

	ASSERT_EQ(test.getNumFloor(), 1);
	ASSERT_EQ(test.getEnemies().size(), 0);
	ASSERT_EQ(test.getSquares().size(), 3);

}

TEST(FloorConstructors, OneEnemy)
{

}