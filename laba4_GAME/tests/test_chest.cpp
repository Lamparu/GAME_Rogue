#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

TEST(ChestConstructors, ConstructorDef)
{
	Chest test;

	ASSERT_EQ(test.getLvl(), 0);
	ASSERT_EQ(test.getType(), S_Chest);
	EXPECT_EQ(test.getLoot(), nullptr);
}

TEST(ChestConstructors, ConstructorPartlyFull)
{
	Weapon wp;
	Chest test(3);

	ASSERT_EQ(test.getLvl(), 3);
	ASSERT_EQ(test.getType(), S_Chest);
	EXPECT_EQ(test.getLoot(), nullptr);
}

TEST(ChestConstructors, ConstructorFull)
{
	Weapon wp;
	Chest test(3, &wp);

	ASSERT_EQ(test.getLvl(), 3);
	ASSERT_EQ(test.getType(), S_Chest);
	EXPECT_EQ(test.getLoot()->getID(), O_Weapon);
}

TEST(ChestSetters, setLvl)
{
	Chest test;

	ASSERT_ANY_THROW(test.setLvl(-1));
	test.setLvl(5);
	ASSERT_EQ(test.getLvl(), 5);
}

TEST(ChestSetters, setLoot)
{
	Chest test;
	Weapon wp;

	ASSERT_ANY_THROW(test.setLoot(nullptr));
	test.setLoot(&wp);
	ASSERT_EQ(test.getLoot()->getID(), O_Weapon);
}

TEST(ChestGetters, getLvl)
{
	Chest test;
	ASSERT_EQ(test.getLvl(), 0);
	test.setLvl(3);
	ASSERT_EQ(test.getLvl(), 3);
	Chest test1(5);
	ASSERT_EQ(test1.getLvl(), 5);
}

TEST(ChestGetters, getLoot)
{
	Chest test;
	EXPECT_EQ(test.getLoot(), nullptr);
	
	Weapon wp;
	Chest test1(3, &wp);
	ASSERT_EQ(test1.getLoot()->getID(), O_Weapon);
}

TEST(ChestFunks, open_chest)
{
	Weapon wp;
	Chest test(2, &wp);
	Hero player;

	ASSERT_ANY_THROW(test.open_chest(player));
	player.changeCharac("BR", 65);
	ASSERT_EQ(test.open_chest(player)->getID(), O_Weapon);

	Chest test1;
	EXPECT_EQ(test1.open_chest(player), nullptr);
}