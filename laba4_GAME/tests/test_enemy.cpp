#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

TEST(EnemyConstructor, OnlyConstructor)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	EXPECT_EQ(test.getType(), "Undead");
	ASSERT_EQ(test.getCurHP(), 90);
	ASSERT_EQ(test.getMaxHP(), 100);
	ASSERT_EQ(test.getMaxDmg(), 20);
	ASSERT_EQ(test.getMinDmg(),15);
	ASSERT_EQ(test.getXP(), 50);
}

TEST(EnemyGettetrs, getType)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	EXPECT_EQ(test.getType(), "Undead");
}

TEST(EnemyGettetrs, getCurHP)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	ASSERT_EQ(test.getCurHP(), 90);
}

TEST(EnemyGettetrs, getMaxHP)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	ASSERT_EQ(test.getMaxHP(), 100);
}

TEST(EnemyGettetrs, getMaxDmg)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	ASSERT_EQ(test.getMaxDmg(), 20);
}

TEST(EnemyGettetrs, getMinDmg)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	ASSERT_EQ(test.getMinDmg(), 15);
}

TEST(EnemyGettetrs, getXP)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	ASSERT_EQ(test.getXP(), 50);
}

TEST(EnemySetters, setType)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);
	
	ASSERT_ANY_THROW(test.setType("Boo"));
	test.setType("Wolf");
	EXPECT_EQ(test.getType(), "Wolf");
}

TEST(EnemySetters, setCurHP)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.setCurHP(-1));
	ASSERT_ANY_THROW(test.setCurHP(200));
	test.setCurHP(30);
	ASSERT_EQ(test.getCurHP(), 30);
	test.setCurHP(100);
	ASSERT_EQ(test.getCurHP(), 100);
	test.setCurHP(0);
	ASSERT_EQ(test.getCurHP(), 0);
}

TEST(EnemySetters, setMaxHP)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.setMaxHP(-1));
	test.setMaxHP(200);
	ASSERT_EQ(test.getMaxHP(), 200);
}

TEST(EnemySetters, setMaxDmg)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.setMaxDmg(-1));
	ASSERT_ANY_THROW(test.setMaxDmg(10));

	test.setMaxDmg(30);
	ASSERT_EQ(test.getMaxDmg(), 30);
}

TEST(EnemySetters, setMinDmg)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.setMinDmg(-1));
	ASSERT_ANY_THROW(test.setMinDmg(25));

	test.setMinDmg(10);
	ASSERT_EQ(test.getMinDmg(), 10);
}

TEST(EnemySetters, setDmg)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.setDmg(-1, 5));
	ASSERT_ANY_THROW(test.setDmg(1, -5));
	ASSERT_ANY_THROW(test.setDmg(-1, -5));
	ASSERT_ANY_THROW(test.setDmg(-5, -1));

	test.setDmg(10, 30);
	ASSERT_EQ(test.getMinDmg(), 10);
	ASSERT_EQ(test.getMaxDmg(), 30);

	test.setDmg(30, 10);
	ASSERT_EQ(test.getMinDmg(), 10);
	ASSERT_EQ(test.getMaxDmg(), 30);
}

TEST(EnemySetters, setXP)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.setXP(-1));

	test.setXP(7);
	ASSERT_EQ(test.getXP(), 7);
}

TEST(EnemyFunks, getDmg)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_LE(test.getDmg(), test.getMaxDmg());
	ASSERT_GE(test.getDmg(), test.getMinDmg());
}

TEST(EnemyFunks, hurted)
{
	Hero hero;
	Enemy test("Undead", 90, 100, 20, 15, 50);
	Weapon weapon;

	test.hurted(hero);
	ASSERT_LE(test.getCurHP(), 90);

	weapon.setMaxDmg(200);
	weapon.setMinDmg(200);
	hero.setWeapon(&weapon);
	ASSERT_ANY_THROW(test.hurted(hero));
}

TEST(EnemyFunks, attack)
{
	Hero hero;
	Enemy test("Undead", 90, 100, 20, 15, 50);

	test.attack(hero);
	ASSERT_LE(hero.getHP(), 100);

	test.setDmg(200,200);
	test.attack(hero);
	ASSERT_EQ(hero.getHP(), 0);
}

TEST(EnemyFunks, genLoot)
{
	Enemy test("Undead", 90, 100, 20, 15, 50);

	ASSERT_ANY_THROW(test.genLoot());
}