#ifndef GAME_HPP_
	#define GAME_HPP_

#include <irrlicht.h>
#include "GameEngine.hpp"
#include "ProceduralEngine.hpp"

class Game {
public:
	Game(irr::IrrlichtDevice *device);
	int Run(int nb_player);
private:
	irr::IrrlichtDevice *deviceCpy;
};

#endif /* !GAME_HPP_ */