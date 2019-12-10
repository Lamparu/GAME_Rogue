#include "pch.h"
#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
using namespace Prog4_Rogue;

/*
* setArmor
* setPotions
* getItem
*** ALL GETTERS
*/

TEST(HeroConstructors, ConstructorDefault)
{
	Hero test;

	auto stats = test.getAllCharacter();
	auto hero_ar = test.getArmor();

	EXPECT_EQ(test.getPlayName(), NAME_DEFAULT);
	ASSERT_EQ(test.getXP(), 0);
	ASSERT_EQ(stats.size(), Nchar);
	auto nit = chars.begin();
	for (auto it = stats.begin(); it != stats.end(); ++it)
	{
		EXPECT_EQ(it->first, nit->first);
		EXPECT_EQ(it->second.first, nit->second);
		if (it->first == "STAM" || it->first == "MAX STAM")
			ASSERT_EQ(it->second.second,MAXSTAM);
		if (it->first == "HP" || it->first == "MAX HP")
			ASSERT_EQ(it->second.second, MAXHP);
		if (it->first != "STAM" && it->first != "HP" && it->first != "MAX HP" && it->first != "MAX STAM")
			ASSERT_EQ(it->second.second, INITCH);
		++nit;
	}
	ASSERT_EQ(test.getMasterKey(), 0);
	ASSERT_EQ(test.getMaxPt(), INITPT);
	ASSERT_EQ(test.getCurPt(), 0);
	EXPECT_EQ(test.getWeapon(), nullptr);
	//for (auto it = hero_ar.begin(); it != hero_ar.end(); ++it)
	//{
		//auto dit = bdprts_armr.find(it->first);
		//EXPECT_EQ(it->first, plit->second);
		//EXPECT_EQ(it->second, nullptr);
	//}
	ASSERT_EQ(test.getPosition().x, 0);
	ASSERT_EQ(test.getPosition().y, 0);
}

TEST(HeroConstructors, ConstructorName)
{
	Hero test("GLEB");

	auto stats = test.getAllCharacter();
	EXPECT_EQ(test.getPlayName(),"GLEB");
	ASSERT_EQ(test.getXP(), 0);
	ASSERT_EQ(stats.size(), Nchar);
	auto nit = chars.begin();
	for (auto it = stats.begin(); it != stats.end(); ++it)
	{
		EXPECT_EQ(it->first, nit->first);
		EXPECT_EQ(it->second.first, nit->second);
		if (it->first == "STAM")
			ASSERT_EQ(it->second.second, MAXSTAM);
		if (it->first == "STAM" || it->first == "MAX STAM")
			ASSERT_EQ(it->second.second, MAXSTAM);
		if (it->first == "HP" || it->first == "MAX HP")
			ASSERT_EQ(it->second.second, MAXHP);
		if (it->first != "STAM" && it->first != "HP" && it->first != "MAX HP" && it->first != "MAX STAM")
			ASSERT_EQ(it->second.second, INITCH);
		++nit;
	}
	ASSERT_EQ(test.getMasterKey(), 0);
	ASSERT_EQ(test.getMaxPt(), INITPT);
	ASSERT_EQ(test.getCurPt(), 0);
	EXPECT_EQ(test.getWeapon(), nullptr);
	/*auto plar = test.getArmor();
	auto plit = bdprts_armr.begin();
	for (auto it = plar.begin(); it != plar.end(); ++it)
	{
		EXPECT_EQ(it->first, plit->second);
		EXPECT_EQ(it->second, nullptr);
		++plit;
	}*/
	ASSERT_EQ(test.getPosition().x, 0);
	ASSERT_EQ(test.getPosition().y, 0);
}


TEST(HeroConstructors, ConstructorFull)
{
	map<string, pair<string, int>> nstats = { {"HP", {"HealthPoint", 70}}, {"MAX HP", {"Max HealthPoint", 100}}, {"STAM", {"Stamina", 55}}, {"MAX STAM", {"Max Stamina", 100}}, {"STR", {"Strength", 11}}, {"AG", {"Agility", 7}}, {"BR", {"Breaking",33}} };
	Armor defhelmet("Default Helmet", "Helmet", 7);
	map<string, Armor*> nar = { { "Head", &defhelmet } };
	vector<Potion> npt;
	Weapon nwp("Enchanced usual", 10, 15, { "Wolf", 5 });
	Hero test("GLEB", nstats, nar,2 , npt, &nwp, 10, 2, 1, 2);

	auto stats = test.getAllCharacter();
	auto plar = test.getArmor();

	EXPECT_EQ(test.getPlayName(), "GLEB");
	ASSERT_EQ(test.getXP(), 10);
	ASSERT_EQ(stats.size(), Nchar);
	auto nit = nstats.begin();
	for (auto it = stats.begin(); it != stats.end(); ++it)
	{
		EXPECT_EQ(it->first, nit->first);
		EXPECT_EQ(it->second.first, nit->second.first);
		ASSERT_EQ(it->second.second, nit->second.second);
		++nit;
	}
	ASSERT_EQ(test.getMasterKey(), 2);
	ASSERT_EQ(test.getMaxPt(), 2);
	ASSERT_EQ(test.getCurPt(), 0);

	Weapon *twp = test.getWeapon();
	EXPECT_EQ(nwp.getName(), twp->getName());

	auto plit = plar.find("Head");
	EXPECT_EQ(plit->second->getName(), defhelmet.getName());
	ASSERT_EQ(test.getPosition().x, 1);
	ASSERT_EQ(test.getPosition().y, 2);
}

TEST(HeroSetters, setCharacter)
{
	map<string, pair<string, int>> nstats = { {"HP", {"HealthPoint", 70}}, {"MAX HP", {"Max HealthPoint", 100}}, {"STAM", {"Stamina", 55}}, {"MAX STAM", {"Max Stamina", 100}}, {"STR", {"Strength", 11}}, {"AG", {"Agility", 7}}, {"BR", {"Breaking",33}} };
	Hero test;
	test.setCharacter(nstats);
	int i = 0;
	auto nit = nstats.begin();
	auto stats = test.getAllCharacter();
	for (auto it = stats.begin(); it != stats.end(); ++it)
	{
		EXPECT_EQ(it->first, nit->first);
		EXPECT_EQ(it->second.first, nit->second.first);
		ASSERT_EQ(it->second.second, nit->second.second);
		++nit;
		++i;
	}
}

TEST(HeroSetters, changeCharac)
{
	Hero test;
	ASSERT_ANY_THROW(test.changeCharac("BE", 99));
	ASSERT_ANY_THROW(test.changeCharac("HP", MAXHP+100));
	ASSERT_ANY_THROW(test.changeCharac("HP", -3));
	ASSERT_ANY_THROW(test.changeCharac("STAM", MAXSTAM+200));
	test.changeCharac("STAM", 88);
	ASSERT_EQ(test.getOneCharac("STAM"), 88);
}

TEST(HeroSetters, setHP)
{
	Hero test;
	ASSERT_ANY_THROW(test.setHP(-1));
	ASSERT_ANY_THROW(test.setHP(MAXHP + 100));
	test.setHP(MAXHP - 50);
	ASSERT_EQ(test.getHP(), MAXHP - 50);
}

TEST(HeroSetters, setMaxHP)
{
	Hero test;
	ASSERT_ANY_THROW(test.setMaxHp(-1));
	test.setMaxHp(999);
	ASSERT_EQ(test.getMaxHP(), 999);
	test.setMaxHp(80);
	ASSERT_EQ(test.getMaxHP(), 80);
	ASSERT_EQ(test.getHP(), 80);
	test.setMaxHp(100);
	ASSERT_EQ(test.getMaxHP(), 100);
	test.setHP(50);
	ASSERT_EQ(test.getHP(), 50);
	test.setMaxHp(1000);
	ASSERT_EQ(test.getMaxHP(), 1000);
	ASSERT_EQ(test.getHP(), 500);

}

TEST(HeroSetters, setWeapon)
{
	Weapon sword("Enchanced usual", 10, 15, { "Wolf", 5 });
	Weapon arms;
	Hero test;
	
	test.setWeapon(&sword);
	Weapon* nwp = test.getWeapon();
	EXPECT_EQ(nwp->getName(), sword.getName());
	test.setWeapon(&arms);
	nwp = test.getWeapon();
	EXPECT_EQ(nwp->getName(), arms.getName());
}

TEST(HeroSetters, setMaxPt)
{
	Hero test;
	test.setMaxPt(3);
	ASSERT_EQ(test.getMaxPt(), 3);
	ASSERT_ANY_THROW(test.setMaxPt(-5));
}

TEST(HeroSetters, setMasterKey)
{
	Hero test;
	MasterKey mk(5);

	test.setMasterKey(mk);
	ASSERT_EQ(mk.getAmount(), test.getMasterKey());
}

TEST(HeroSetters, setXP)
{
	Hero test;

	ASSERT_ANY_THROW(test.setXP(-1));
	test.setXP(88);
	ASSERT_EQ(test.getXP(), 88);
}

TEST(HeroSetters, setPlayName)
{
	string newname = "Polya";
	Hero test;

	test.setPlayName(newname);
	EXPECT_EQ(test.getPlayName(), newname);
}

TEST(HeroSetters, setCoordinates)
{
	Hero test;
	ASSERT_ANY_THROW(test.setCoordinates(MAX_X+1, MAX_Y-1));
	ASSERT_ANY_THROW(test.setCoordinates(MAX_X-1, MAX_Y+1));
	test.setCoordinates(MAX_X - 1, MAX_Y - 1);
	ASSERT_EQ(test.getPosition().x, MAX_X - 1);
	ASSERT_EQ(test.getPosition().y, MAX_Y - 1);

	Coordinates tcord = { 1, 2 };
	test.setCoordinates(tcord);
	ASSERT_EQ(test.getPosition().x, 1);
	ASSERT_EQ(test.getPosition().y, 2);
	ASSERT_ANY_THROW(test.setCoordinates({ MAX_X + 1, MAX_Y - 1 }));
	ASSERT_ANY_THROW(test.setCoordinates({ MAX_X - 1, MAX_Y + 1 }));
}

TEST(HeroGetters, getPartArmor)
{
	Hero test;

	EXPECT_EQ(test.getPartArmor("Head"), nullptr);

}