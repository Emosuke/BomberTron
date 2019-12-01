
#ifndef MENU_HPP_
#define MENU_HPP_

#include <irrlicht.h>
#include "Event.hpp"
#include <string>
#include "Image.hpp"
#include <iostream>
#include "Game.hpp"

enum Selected {
	PLAY = 0,
	QUIT = 1,
	TWO_P = 2,
	THREE_P = 3,
	FOUR_P = 4,
	WIN_P = 5,
	WIN_B = 6,
	WIN_Y = 7,
	WIN_R = 8,
};

static const std::string assets[9] {
	"sources/assets/BbmMenuPlay.png",
	"sources/assets/BbmMenuExit.png",
	"sources/assets/BbmMenu2P.png",
	"sources/assets/BbmMenu3P.png",
	"sources/assets/BbmMenu4P.png",
	"sources/assets/BombermanWinP.png",
	"sources/assets/BombermanWinB.png",
	"sources/assets/BombermanWinY.png",
	"sources/assets/BombermanWinR.png"
};

class Menu {
	public:
		Menu(irr::IrrlichtDevice *device);
		~Menu();
		void Run();
	private:
		int Action(Event *event, int select_player);
		void KeyUp(int check);
		void KeyDown(int check);
		void KeyUpSelectP();
		void KeyDownSelectP();
		int EnterPressed();
		void checkWin(int win);
		irr::video::IVideoDriver *driver;
		irr::IrrlichtDevice *deviceCpy;
		Selected selected;
		Image *image;
		Game *game;
};

#endif /* !MENU_HPP_ */
