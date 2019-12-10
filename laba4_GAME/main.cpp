#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
#include <conio.h>

int main() {
	Hero me;
	
	Weapon loot_wp;
	MasterKey loot_mk(4);
	Armor loot_ar("Test amour", "Armour", 8);
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(), new Square(), new Square(), new Stair(downwards, 4, 0)},
		{new Square(), new Square(), new Square(&loot_ar), new Square(), new Square() },
		{new Square(), new Square(), new Square(S_Wall), new Door(), new Square(S_Wall) },
		{new Square(&loot_wp), new Square(), new Square(S_Wall), new Square(), new Square() },
		{new Square(), new Square(&loot_mk), new Square(S_Wall), new Chest(), new Square()}
	};
	Weapon loot_wp_ench("Enchanced usual", 10, 15, { "Wolf", 5 });
	Armor loot_ar_h("Test helmet", "Helmet", 10);
	Armor loot_ar_p("Test pendant", "Pendant", 6);
	Armor loot_ar_g("Test gloves", "Gloves", 7);
	Potion loot_pt("Health max potion", { "MAX HP", 100 }, 10);
	vector<vector<Square*>> lvl2 = {
		{new Square(), new Square(), new Square(&loot_wp_ench), new Square(), new Stair(upwards, 4, 0)},
		{new Square(&loot_ar_h), new Square(), new Square(), new Square(), new Square() },
		{new Square(S_Wall), new Square(S_Wall), new Square(S_Wall), new Square(S_Wall), new Door() },
		{new Square(), new Square(), new Square(S_Wall), new Square(), new Square() },
		{new Square(), new Chest(1, &loot_ar_p), new Square(), new Square(&loot_pt), new Square(&loot_ar_g)}
	};
	Floor fl1(1, lvl1);
	Floor fl2(2, lvl2);
	vector<Floor> fl_dung= { fl1, fl2 };
	Dungeon dg(&me, fl_dung);
	/*
	Weapon loot_weap_test;
	vector<vector<Square*>> lvl1 = {
		{new Square(), new Square(),new Square()},
		{new Square(&loot_weap_test),new Square(S_Wall),new Door()},
		{new Square(),new Square(S_Wall),new Chest()} };
	Floor fl(1, lvl1);
	Dungeon dg(&me, fl);
	*/
	std::cout << me << std::endl;
	int c = 0;

	while (c != 13) // 13- код Enter
	{
		system("pause");
		system("cls");
		std::cout << "Max floors: " << dg.getNumFloors() << std::endl;
		std::cout << "Current floo: " << dg.getCurFloor()+1 << std::endl;
		std::cout << "Hero coordinates: x = " << me.getPosition().x + 1 << " y = " << me.getPosition().y+1 << std::endl;
		c = _getch();
		if (c == 224)
			c = _getch();
		//std::cout << c << std::endl;
		try { me.move(c, dg); }
		catch (std::exception & ex)
		{
			std::cout << ex.what() << std::endl;
		}
		//std::cout << me << std::endl;
		//system("pause");
	}
	//me.goUp(dg);

	system("pause");
	return 0;
}