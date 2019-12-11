#include "../RogueLib/Hero.h"
#include "../RogueLib/Dungeon.h"
#include "SDLfunks.h"
#include <conio.h>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char *argv[]) {
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
	const int SCREEN_WIDTH = TILE_SIZE * MAX_X; 
	const int SCREEN_HEIGHT = TILE_SIZE * MAX_Y;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	window = SDL_CreateWindow("Lesson 4", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 2;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}
	SDL_Texture *background = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/WhiteSquare.jpg", renderer);
	SDL_Texture *wall = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/BlackSquare.jpg", renderer);
	SDL_Texture *chest = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/Chest.jpeg", renderer);
	SDL_Texture *hero = loadTexture("C:/Users/Vlada/source/repos/SDL_learning/Kappa_Emoji.bmp", renderer);
	SDL_Texture *stair = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/Stair.jpg", renderer);
	SDL_Texture *sword = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/Sword.jpg", renderer);
	SDL_Texture *armor = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/Armor.png", renderer);
	SDL_Texture *masterkey = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/MasterKey.jpg", renderer);
	SDL_Texture *door = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/Door.jpg", renderer);
	SDL_Texture *dooropened = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/DoorOpened.png", renderer);
	SDL_Texture *potion = loadTexture("C:/Users/Vlada/source/repos/sem3/Prog4_GameRogue/Potion.jpg", renderer);
	// ѕроверка
	if (!background || !hero || !wall || !chest || !stair || !sword || !armor || !masterkey || !door || !dooropened || !potion)
	{
		// ¬ оригинале, эта часть использовала шаблонную функцию cleanup(), рассмотренную в P.S. к первому уроку, добавленному уже после написани€ перевода, и посему, не попавшему в перевод. 
		SDL_DestroyTexture(background);
		SDL_DestroyTexture(hero);
		SDL_DestroyTexture(chest);
		SDL_DestroyTexture(wall);
		SDL_DestroyTexture(stair);
		SDL_DestroyTexture(sword);
		SDL_DestroyTexture(armor);
		SDL_DestroyTexture(door);
		SDL_DestroyTexture(masterkey);
		SDL_DestroyTexture(dooropened);
		SDL_DestroyTexture(potion);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	// ќпределение количества плиток, необходимого дл€ покрыти€ всего окна
// ќт переводчика: € бы заменил на ceil(float(SCREEN_WIDTH) / TILE_SIZE), чтобы в том случае, кода размер окна не кратен размеру плитки, оставша€с€ часть окна не оставалась пустой; однако, в данном примере размеры заданы константой и кратны, так что это не страшно.
	int xTiles = MAX_X;
	int yTiles = MAX_Y;

	int iW, iH;
	SDL_QueryTexture(hero, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 4;
	int y = SCREEN_HEIGHT / 2 - iH / 4;
	// —труктура событи€
	SDL_Event e;
	// ‘лаг выхода
	bool quit = false;
	int xim = 0;
	int yim = TILE_SIZE * (MAX_Y - 1);
	/*
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
	}*/
	while (!quit)
	{
		// ќбработка событий
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					try {me.goUp(dg);}
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
						break;
					}
					yim -= TILE_SIZE;
					break;
				case SDLK_DOWN:
					try { me.goDown(dg); }
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
						break;
					}
					yim += TILE_SIZE;
					break;
				case SDLK_RIGHT:
					try { me.goRight(dg); }
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
						break;
					}
					xim += TILE_SIZE;
					break;
				case SDLK_LEFT:
					try { me.goLeft(dg); }
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
						break;
					}
					xim -= TILE_SIZE;
					break;
				}
				//quit = true;
			}
			/*if (e.type == SDL_SCANCODE_D)
			{
				xim += TILE_SIZE;
				yim += TILE_SIZE;
			}*/
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				quit = true;
			}
		}
		// ќтображение сцены
		SDL_RenderClear(renderer);
		// ќтрисовка фона
		for (int i = 0; i < xTiles * yTiles; ++i)
		{
			int xi = i % xTiles;
			int yi = i / xTiles;
			renderTexture(background, renderer, xi * TILE_SIZE, yi * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
		for (int i = 0; i < MAX_X; ++i)
			for (int j = 0; j < MAX_Y; ++j)
			{
				if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getType() == S_Wall)
					renderTexture(wall, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
				if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getType() == S_Chest)
					renderTexture(chest, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
				if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getType() == S_Stair)
					renderTexture(stair, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
				if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getType() == S_Door)
				{
					Door* dr = dynamic_cast<Door*>(dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]);
					if (dr->getState() == opened)
						renderTexture(dooropened, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
					if (dr->getState() == closed)
						renderTexture(door, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
				}
				if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getType() == S_Loot)
				{
					if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getLoot()->getID() == O_Armor)
						renderTexture(armor, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
					if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getLoot()->getID() == O_Weapon)
						renderTexture(sword, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
					if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getLoot()->getID() == O_MasterKey)
						renderTexture(masterkey, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
					if (dg.getFloors()[dg.getCurFloor()].getSquares()[j][i]->getLoot()->getID() == O_Potion)
						renderTexture(potion, renderer, i * TILE_SIZE, (MAX_Y - j - 1)* TILE_SIZE, TILE_SIZE, TILE_SIZE);
				}
			}
		renderTexture(hero, renderer, xim, yim, TILE_SIZE, TILE_SIZE);
		SDL_RenderPresent(renderer);
	}
	//SDL_Delay(2000);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(hero);
	SDL_DestroyTexture(chest);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(stair);
	SDL_DestroyTexture(sword);
	SDL_DestroyTexture(armor);
	SDL_DestroyTexture(door);
	SDL_DestroyTexture(potion);
	SDL_DestroyTexture(dooropened);
	SDL_DestroyTexture(masterkey);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	system("pause");
	return 0;
}