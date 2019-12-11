#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

TEST(TestMove, setPosition) {
	Weapon loot_weap_test;
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(&loot_weap_test), new Square()},
		{new Square(), new Square(S_Wall), new Door()},
		{new Chest(), new Square(S_Wall), new Stair(downwards, 2, 2)} };
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	//Coordinates wp1 = { 1, 0 }; //
	Coordinates fl1 = { 0, 1 }; //
	Coordinates st1 = { 2, 2 }; //
	Coordinates ch1 = { 0, 2 }; //
	Coordinates wl1 = { 1, 1 }; //
	Coordinates dr1 = { 2, 1 }; //

	play.setPosition(fl1, test_dg);
	ASSERT_EQ(play.getPosition().x, fl1.x);
	ASSERT_EQ(play.getPosition().y, fl1.y);
	ASSERT_ANY_THROW(play.setPosition(wl1, test_dg));
	ASSERT_EQ(play.getPosition().x, fl1.x);
	ASSERT_EQ(play.getPosition().y, fl1.y);
	play.setPosition(dr1, test_dg);
	ASSERT_EQ(play.getPosition().x, dr1.x);
	ASSERT_EQ(play.getPosition().y, dr1.y);
	/*play.setPosition(wp1, test_dg);
	ASSERT_EQ(play.getPosition().x, wp1.x);
	ASSERT_EQ(play.getPosition().y, wp1.y);*/
	play.setPosition(ch1, test_dg);
	ASSERT_EQ(play.getPosition().x, ch1.x);
	ASSERT_EQ(play.getPosition().y, ch1.y);
	ASSERT_ANY_THROW(play.setPosition(st1, test_dg));
}

TEST(TestGo, goLeft)
{
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(), new Square()},
		{new Square(), new Square(S_Wall), new Door()},
		{new Chest(), new Square(S_Wall), new Stair(downwards, 2, 2)} };
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	Coordinates test_c = { 1, 0 };

	ASSERT_ANY_THROW(play.goLeft(test_dg));
	play.setCoordinates(test_c);
	play.goLeft(test_dg);
	ASSERT_EQ(play.getPosition().x, 0);
	ASSERT_EQ(play.getPosition().y, 0);
}

TEST(TestGo, goRight)
{
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(), new Square()},
		{new Square(), new Square(S_Wall), new Door()},
		{new Chest(), new Square(S_Wall), new Stair(downwards, 2, 2)} };
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	Coordinates test_c = { 1, 0 };

	play.goRight(test_dg);
	ASSERT_EQ(play.getPosition().x, test_c.x);
	ASSERT_EQ(play.getPosition().y, test_c.y);
	play.setCoordinates(2, 0);
	ASSERT_ANY_THROW(play.goRight(test_dg));
}

TEST(TestGo, goUp)
{
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(), new Square()},
		{new Square(), new Square(S_Wall), new Door()},
		{new Chest(), new Square(S_Wall), new Stair(downwards, 2, 2)} };
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	Coordinates test_c = { 0, 1 };

	play.goUp(test_dg);
	ASSERT_EQ(play.getPosition().x, test_c.x);
	ASSERT_EQ(play.getPosition().y, test_c.y);
	play.setCoordinates(0, 2);
	ASSERT_ANY_THROW(play.goUp(test_dg));
}

TEST(TestGo, goDown)
{
	Weapon loot_weap_test;
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(&loot_weap_test), new Square()},
		{new Square(), new Square(S_Wall), new Door()},
		{new Chest(), new Square(S_Wall), new Stair(downwards, 2, 2)} };
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	Coordinates test_c = { 0, 0 };

	ASSERT_ANY_THROW(play.goDown(test_dg));
	play.setCoordinates(0, 1);
	play.goDown(test_dg);
	ASSERT_EQ(play.getPosition().x, test_c.x);
	ASSERT_EQ(play.getPosition().y, test_c.y);
}

TEST(TestMove, move)
{
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(), new Square()},
		{new Square(), new Square(S_Wall), new Door()},
		{new Chest(), new Square(S_Wall), new Stair(downwards, 2, 2)} };
	Hero play;
	Floor test_fl(1, lvl1);
	Dungeon test_dg(&play, test_fl);
	Coordinates y1 = { 0, 1 };
	Coordinates xy = { 0, 0 };
	Coordinates x1 = { 1, 0 };

	ASSERT_ANY_THROW(play.move(1, test_dg));
	ASSERT_ANY_THROW(play.move(37, test_dg));

	play.move(72, test_dg); //UP
	ASSERT_EQ(play.getPosition().x, y1.x);
	ASSERT_EQ(play.getPosition().y, y1.y);

	play.move(80, test_dg); //DOWN
	ASSERT_EQ(play.getPosition().x, xy.x);
	ASSERT_EQ(play.getPosition().y, xy.y);

	play.move(77, test_dg); //RIGHT
	ASSERT_EQ(play.getPosition().x, x1.x);
	ASSERT_EQ(play.getPosition().y, x1.y);

	play.move(75, test_dg); //LEFT
	ASSERT_EQ(play.getPosition().x, xy.x);
	ASSERT_EQ(play.getPosition().y, xy.y);
}