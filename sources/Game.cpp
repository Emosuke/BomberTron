#include "Game.hpp"

/*!
** @brief Construct a new Game:: Game object
** 
** @param device 
*/
Game::Game(irr::IrrlichtDevice *device)
{
	deviceCpy = device;
}

/*!
** @brief initialize and launch the game
** 
** @param players 
** @return int
*/
int Game::Run(int players)
{
	GameEngine *gameEngine = new GameEngine(deviceCpy);
	int check_win = -1;

	gameEngine->initializeGame(players);
	check_win = gameEngine->run();
	return check_win;
}