
#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

#include <irrlicht.h>
#include <driverChoice.h>
#include <iostream>
#include "ProceduralEngine.hpp"
#include "Character.hpp"
#include "LocalBehavior.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Empty.hpp"
#include "Map.hpp"
#include "Bomb.hpp"
#include "Particules.hpp"
#include "Bomb.hpp"


class GameEngine {
public:
	GameEngine(irr::IrrlichtDevice *device);
	void initializeGame(int players);
	void setUpMap(std::vector<std::vector<E_Case> > map);
	void addEnvironment();
	void addMap();
	void addCamera();
	void drawAll();
	int run();
	void initializeBomb();
	irr::scene::ISceneManager *getScene() const;
	void createCharacters(Binding b);
	int killPlayer(irr::core::vector3df pos, int range);
	int winCondition() const;
	int getWinner() const;
	int countPlayerAlive() const;
	void clearBomb();
	void clearScene();
	void clearCharacter();
	int manageBomB();
	void setBindings(Binding binds);
private:
	std::shared_ptr<LocalBehavior> _event;
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
    	irr::scene::ISceneManager *_smgr;
    	irr::gui::IGUIEnvironment *_env;
	std::vector<Bomb *> _bomb;
	std::vector<Character *> _character;
	int _nbPlayer = 4;
	int _Actualplayers;
	Map *_map;
};

# endif /* !GAMEENGINE_HPP_ */