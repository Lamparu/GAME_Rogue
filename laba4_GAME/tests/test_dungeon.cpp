#include "pch.h"
#include "../RogueLib/Dungeon.h"
#include "../RogueLib/Hero.h"

using namespace Prog4_Rogue;
//test lvl

Weapon loot_wp("Enchanced usual", 10, 15, { "Wolf", 5 });
vector<vector<Square>> lvl1 = {
	{Square(),Square(&loot_wp), Square()},
	{Square(), Square(S_Wall), Door()},
	{Chest(), Square(S_Wall), Square()} };

vector<vector<Square>> lvl2 = {
	{Square(),Square(), Stair(downwards, 2, 0)},
	{Square(), Square(), Square()},
	{Square(), Square(), Square(&loot_wp)} };

vector<vector<Square>> lvl3 = {
	{Square(),Square(), Stair(upwards, 2, 0)},
	{Square(S_Wall), Door(),  Square(S_Wall)},
	{Square(), Chest(), Square()} };


TEST(DungeonConstructors, ConstructorOne) {
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getCurFloor(), 0);
	ASSERT_EQ(test_dg.getNumFloors(), 1);
	EXPECT_EQ(test_dg.getPlayer()->getPlayName(), play.getPlayName());
	ASSERT_EQ(test_dg.getFloors()[0].getNumFloor(), 1);
}

TEST(DungeonConstructors, ConstructorMany) {
	Hero play;
	Floor test_fl1(1, lvl2);
	Floor test_fl2(2, lvl3);
	vector<Floor> test_fl = { test_fl1, test_fl2 };
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getCurFloor(), 0);
	ASSERT_EQ(test_dg.getNumFloors(), 2);
	EXPECT_EQ(test_dg.getPlayer()->getPlayName(), play.getPlayName());
	ASSERT_EQ(test_dg.getFloors()[0].getNumFloor(), 1);
	ASSERT_EQ(test_dg.getFloors()[1].getNumFloor(), 2);
}

TEST(DungeonSetters, setFloorsOne)
{
	Hero play;
	Floor test_fl1(1, lvl1);
	Floor test_fl2(1, lvl2);
	Dungeon test_dg(&play, test_fl1);

	test_dg.setFloors(test_fl2);
	ASSERT_EQ(test_dg.getNumFloors(), 1);
	//ASSERT_EQ(test_dg.getFloors()[0], test_fl2);
}

TEST(DungeonSetters, setFloorsMany)
{
	Hero play;
	Floor test_fl1(1, lvl1);
	Floor test_fl2(1, lvl2);
	Floor test_fl3(2, lvl3);
	vector<Floor> test_fl = { test_fl2, test_fl3 };
	Dungeon test_dg(&play, test_fl1);

	test_dg.setFloors(test_fl);
	ASSERT_EQ(test_dg.getNumFloors(), 2);
	ASSERT_EQ(test_dg.getFloors()[0].getNumFloor(), 1);
	ASSERT_EQ(test_dg.getFloors()[1].getNumFloor(), 2);
}

TEST(DungeonSetters, setPlayer)
{
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	Hero play_test;

	play_test.setXP(90);
	test_dg.setPlayer(&play_test);
	ASSERT_EQ(test_dg.getPlayer()->getXP(), 90);
}

TEST(DungeonSetters, setCurFloor)
{
	Hero play;
	Floor test_fl1(1, lvl2);
	Floor test_fl2(2, lvl3);
	vector<Floor> test_fl = { test_fl1, test_fl2 };
	Dungeon test_dg(&play, test_fl);

	test_dg.setCurFloor(2);
	ASSERT_EQ(test_dg.getCurFloor(), 2);
}

TEST(DungeonSetters, setCurFloorExc)
{
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);

	ASSERT_ANY_THROW(test_dg.setCurFloor(2));
}

TEST(DungeonGetters, getNumFloorsOne)
{
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getNumFloors(), 1);
}

TEST(DungeonGetters, getNumFloorsMany)
{
	Hero play;
	Floor test_fl1(1, lvl2);
	Floor test_fl2(2, lvl3);
	vector<Floor> test_fl = { test_fl1, test_fl2 };
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getNumFloors(), 2);
}

TEST(DungeonGetters, getPlayer)
{
	Hero play("GENA");
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);

	Hero* fromdung = test_dg.getPlayer();
	string testname = fromdung->getPlayName();
	EXPECT_EQ(testname, "GENA");
}

TEST(DungeonGetters, getFloorsOne)
{
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getFloors()[0].getNumFloor(), 1);
}

TEST(DungeonGetters, getFloorsMany)
{
	Hero play;
	Floor test_fl1(1, lvl2);
	Floor test_fl2(2, lvl3);
	vector<Floor> test_fl = { test_fl1, test_fl2 };
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getFloors()[0].getNumFloor(), 1);
	ASSERT_EQ(test_dg.getFloors()[1].getNumFloor(), 2);
}

TEST(DungeonGetters, getCurFloorOne)
{
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);

	ASSERT_EQ(test_dg.getCurFloor(), 0);
}

TEST(DungeonGetters, getCurFloorMany)
{
	Hero play;
	Floor test_fl1(1, lvl2);
	Floor test_fl2(2, lvl3);
	vector<Floor> test_fl = { test_fl1, test_fl2 };
	Dungeon test_dg(&play, test_fl);

	test_dg.setCurFloor(2);
	ASSERT_EQ(test_dg.getCurFloor(), 2);
}