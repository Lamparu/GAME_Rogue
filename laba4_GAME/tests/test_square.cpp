#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

TEST(SquareConstructors, ConstructorDef)
{
	Square test;
	ASSERT_EQ(test.getType(), S_Floor);
}

TEST(SquareConstructors, ConstructorSq)
{
	Square test1(S_Floor);
	Square test2(S_Door);
	Square test3(S_Chest);
	Square test4(S_Stair);
	Square test5(S_Wall);

	ASSERT_EQ(test1.getType(), S_Floor);
	ASSERT_EQ(test2.getType(), S_Door);
	ASSERT_EQ(test3.getType(), S_Chest);
	ASSERT_EQ(test4.getType(), S_Stair);
	ASSERT_EQ(test5.getType(), S_Wall);
}

TEST(SquareConstructors, ConstructorObject)
{
	Weapon wpt;
	Square test(&wpt);

	ASSERT_EQ(test.getType(), S_Loot);
	Object *tob = test.getLoot();
	ASSERT_EQ(tob->getID(), O_Weapon);
}

TEST(SquareSetters, setType)
{
	Weapon wp;
	sqtypes test_type = S_Door;
	Square test;
	Square test1(&wp);

	test.setType(test_type);
	ASSERT_EQ(test.getType(), test_type);
	test1.setType(S_Wall);
	ASSERT_EQ(test1.getType(), S_Wall);
	EXPECT_EQ(test1.getLoot(), nullptr);
}

TEST(SquareSetters, setLoot)
{
	Weapon wpt;
	MasterKey mkt(2);
	Armor art("Test gloves", "Gloves", 10);
	Potion ptt("HP potion", {"HP", 20}, 5);
	ArtifactArmor artart("Art helmet", "Helmet", 11, { "HP",  6 });
	ArtifactWeapon artwpt("Enchanced artifact", 15, 19, { "STR", 3 }, { "Golem", 8 });

	Square test;
	Square test1(S_Wall);
	test.setLoot(&wpt);
	ASSERT_EQ(test.getType(), S_Loot);
	Object *lt = test.getLoot();
	ASSERT_EQ(test.getLoot()->getID(), O_Weapon);
	test.setLoot(&mkt);
	ASSERT_EQ(test.getType(), S_Loot);
	lt = test.getLoot();
	ASSERT_EQ(test.getLoot()->getID(), O_MasterKey);
	test.setLoot(&art);
	ASSERT_EQ(test.getType(), S_Loot);
	lt = test.getLoot();
	ASSERT_EQ(test.getLoot()->getID(), O_Armor);
	test.setLoot(&ptt);
	ASSERT_EQ(test.getType(), S_Loot);
	lt = test.getLoot();
	ASSERT_EQ(test.getLoot()->getID(), O_Potion);
	test.setLoot(&artart);
	ASSERT_EQ(test.getType(), S_Loot);
	lt = test.getLoot();
	ASSERT_EQ(test.getLoot()->getID(), O_Armor);
	test.setLoot(&artwpt);
	ASSERT_EQ(test.getType(), S_Loot);
	lt = test.getLoot();
	ASSERT_EQ(test.getLoot()->getID(), O_Weapon);

	ASSERT_ANY_THROW(test.setLoot(nullptr));
	ASSERT_ANY_THROW(test1.setLoot(&wpt));
}

TEST(SquareGetters, getType)
{
	Weapon wp;
	Square test1;
	Square test2(S_Chest);
	Square test3(&wp);

	ASSERT_EQ(test1.getType(), S_Floor);
	ASSERT_EQ(test2.getType(), S_Chest);
	ASSERT_EQ(test3.getType(), S_Loot);
}

TEST(SquareGetters, getLoot)
{
	Weapon wpt;
	MasterKey mkt(2);
	Armor art("Test gloves", "Gloves", 10);
	Potion ptt("HP potion", { "HP", 20 }, 5);
	ArtifactArmor artart("Art helmet", "Helmet", 11, { "HP",  6 });
	ArtifactWeapon artwpt("Enchanced artifact", 15, 19, { "STR", 3 }, { "Golem", 8 });

	Square swp(&wpt);
	Square smk(&mkt);
	Square sar(&art);
	Square spt(&ptt);
	Square sartar(&artart);
	Square sartwp(&artwpt);
	Square sempty;

	ASSERT_EQ(swp.getLoot()->getID(), O_Weapon);
	ASSERT_EQ(smk.getLoot()->getID(), O_MasterKey);
	ASSERT_EQ(sar.getLoot()->getID(), O_Armor);
	ASSERT_EQ(spt.getLoot()->getID(), O_Potion);
	ASSERT_EQ(sartar.getLoot()->getID(), O_Armor);
	ASSERT_EQ(sartwp.getLoot()->getID(), O_Weapon);
	EXPECT_EQ(sempty.getLoot(), nullptr);
}