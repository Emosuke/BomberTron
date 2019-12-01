#include "GameEngine.hpp"

/*!
** @brief Construct a new Game Engine:: Game Engine object
** 
** @param device
*/
GameEngine::GameEngine(irr::IrrlichtDevice *device)
{
	_device = device;
	_device->getCursorControl()->setVisible(false);
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
    	_env = _device->getGUIEnvironment();
	_driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
	initializeBomb();
}

/*!
** @brief function that initialize the bomb array
** 
*/
void GameEngine::initializeBomb()
{
	std::vector<Bomb *> bomb;

	for (size_t i = 0; i < 4; i ++)
		bomb.push_back(nullptr);
	_bomb = bomb;
}

/*!
** @brief function that add and set the camera
** 
*/
void GameEngine::addCamera()
{
	irr::scene::ICameraSceneNode *camera = _smgr->addCameraSceneNode(0, 
	irr::core::vector3df(702 , 1200, 700),
	irr::core::vector3df(700, 0, 700));
}

/*!
** @brief function that add the map ground
** 
*/
void GameEngine::addMap()
{
	irr::scene::IAnimatedMesh *landscape = _smgr->addHillPlaneMesh("land",
	irr::core::dimension2d<irr::f32>(1000.0f, 1000.0f),
	irr::core::dimension2d<irr::u32>(15, 15), 0, 0.0f,
	irr::core::dimension2d<irr::f32>(0.0f, 0.0f),
	irr::core::dimension2d<irr::f32>(10.0f, 10.0f));
	irr::scene::ISceneNode *land = _smgr->addMeshSceneNode(landscape);
    land->setMaterialTexture(0, _driver->
	getTexture("sources/assets/Landscape.png"));
	land->setPosition(irr::core::vector3df(700, 0, 700));
	land->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	land->setPosition(irr::core::vector3df(0,-100,0));
	irr::scene::IAnimatedMesh *map = _smgr->addHillPlaneMesh("ground",
	irr::core::dimension2d<irr::f32>(100.0f, 100.0f),
	irr::core::dimension2d<irr::u32>(15, 15), 0, 0.0f,
	irr::core::dimension2d<irr::f32>(0.0f, 0.0f),
	irr::core::dimension2d<irr::f32>(4.0f, 4.0f));
	irr::scene::ISceneNode *ground = _smgr->addMeshSceneNode(map);
    ground->setMaterialTexture(0, _driver->
	getTexture("sources/assets/Ground.jpg"));
	ground->setPosition(irr::core::vector3df(700, 0, 700));
	ground->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

/*!
** @brief function that add the skydom to the scene
** 
*/
void GameEngine::addEnvironment()
{
 	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
    	_smgr->addSkyBoxSceneNode(
		    _driver->getTexture("sources/assets/irrlicht2_up.jpg"),
		    _driver->getTexture("sources/assets/irrlicht2_dn.jpg"),
		    _driver->getTexture("sources/assets/irrlicht2_lf.jpg"),
		    _driver->getTexture("sources/assets/irrlicht2_rt.jpg"),
		    _driver->getTexture("sources/assets/irrlicht2_ft.jpg"),
		    _driver->getTexture("sources/assets/irrlicht2_bk.jpg"));
    	_smgr->addSkyDomeSceneNode(_driver->
		getTexture("sources/assets/skydome.jpg"),16,8,0.95f,2.0f);
    	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS,
		true);
}

/*!
** @brief function that create the map depending on a procedural generated map
** 
** @param map tableau d'énum listant les différents block de la carte
*/
void GameEngine::setUpMap(std::vector<std::vector<E_Case> > map)
{
	_map = new Map(_smgr, _driver, map, _bomb);
}

/*!
** @brief function that call all initialization functions
** 
** @param players number of player for this round
*/
void GameEngine::initializeGame(int players)
{
	ProceduralEngine *gen = new ProceduralEngine;	

	_Actualplayers = players;
	addCamera();
	addMap();
	setUpMap(gen->getMap());
	addEnvironment();
}

/*!
** @brief function that count the number of player still alive
** 
** @return int number of player alive
*/
int GameEngine::countPlayerAlive() const
{
	int player = 0;

	for (size_t i = 0; i < _character.size(); i++) {
		if (_character[i] != nullptr)
			player += 1;
	}
	return player;
}

/*!
** @brief function that return the winner index if there is one
** 
** @return int winner index in the character array
*/
int GameEngine::getWinner() const
{
	int player = 0;

	for (size_t i = 0; i < _character.size(); i++) {
		if (_character[i] != nullptr) {
			player = i;
			break;
		}
	}
	return player;
}

/*!
** @brief function that call all winner detection functions
** 
** @return int 
*/
int GameEngine::winCondition() const
{
	int winner = -1;

	if (countPlayerAlive() == 1)
		winner = getWinner();
	return winner;
}

/*!
** @brief function that detect elimination, check and return the winner index
** 
** @param pos bomb position on the map
** @param rge bomb range
** @return int 
*/
int GameEngine::killPlayer(irr::core::vector3df pos, int rge)
{
	int theWinner = -1;

	for (size_t i = 0; i < _character.size(); i++) {
		if (_character[i] != nullptr
		&& _map->isDead(_character[i]->getTruePosition(), pos, rge)) {
			_character[i]->destroy();
			_character[i] = nullptr;
		}
		theWinner = winCondition();
		if (theWinner != -1)
			break;
	}
	return theWinner;
}

/*!
** @brief manager funtion for bomb explosion
** 
** @return int index du gagnant en cas de victoire après explosion d'une bombe
*/
int GameEngine::manageBomB()
{
	int winner = -1;

	for (int i = 0 ; _nbPlayer != i ; i++) {
		if (_bomb[i] != nullptr)
			_bomb[i]->update();
		if (_bomb[i] != nullptr && _bomb[i]->getIsExploding() == true) {
			winner = killPlayer(_bomb[i]->getPosition(), _bomb[i]->getRange());
			_map->explosion(_bomb[i]->getPosition(), _bomb[i]->getRange());
		}
		if (_bomb[i] != nullptr && _bomb[i]->getHasExploded()) {
			delete(_bomb[i]);
			_bomb[i] = nullptr;
		}
		if (_character[i] != nullptr &&
		_character[i]->checkEvent(_map, _bomb) && _bomb[i] == nullptr)
			_bomb[i] = new Bomb(_smgr, _driver,
			_character[i]->getTruePosition(), 1);
	}
	return (winner);
}

/*!
** @brief main loop to manage bomb, character and inputs
** 
** @return int index du gagnant dans le tableau de joueur
*/
int GameEngine::run()
{
	int winner = -1;
	Binding binds = Binding();

	binds.setFile("example/test.conf");
	binds.run();
	_event = LocalBehavior::make(binds);
	_device->setEventReceiver(_event->getDispatcher().get());
	createCharacters(binds);
	while (_device->run()) {
		if ((_event->update() & IGameBehavior::action::ESCAPE) ==
		IGameBehavior::action::ESCAPE) {
			clearScene();
			return -2;
		}
		winner = manageBomB();
		if (winner != -1)
			break;
		drawAll();	
	}
	clearScene();
	return winner;
}

/*!
** @brief clear function to delete all Character object
** 
*/
void GameEngine::clearCharacter()
{
	for (size_t i = 0; i < 4; i++) {
		if (_character[i] != nullptr) {
			_character[i]->destroy();
			_character[i] = nullptr;
		}
	}
	_character.clear();
}

/*!
** @brief clear function to delete and clear all bombs object
** 
*/
void GameEngine::clearBomb()
{
	for (size_t i = 0; i < _bomb.size(); i++) {
		if (_bomb[i] != nullptr) {
			_bomb[i]->destroy();
			_bomb[i] = nullptr;
		}
	}
	_bomb.clear();
}

/*!
** @brief main function to clear all graphic object of the scene
** 
*/
void GameEngine::clearScene()
{
	clearBomb();
	clearCharacter();
	_smgr->clear();
}

/*!
** @brief getter function for scene manager
** 
** @return irr::scene::ISceneManager* 
*/
irr::scene::ISceneManager *GameEngine::getScene() const
{
	return _smgr;
}

/*!
** @brief draw the scene all oject in it
** 
*/
void GameEngine::drawAll()
{
	if (_device->isWindowActive()) {
		_driver->beginScene(true, true, 0 );
		_smgr->drawAll();
        	_driver->endScene();
        }
}

/*!
** @brief characters creation function
** 
** @param binds objet de gestion des input propre aux personnages
*/
void GameEngine::createCharacters(Binding binds)
{
	irr::core::vector2di pos = irr::core::vector2di(100, 100);
	std::array<std::string, 5> Texture = {"",
	"sources/assets/neon2.jpg",
	"sources/assets/neon.jpg",
	"sources/assets/sun.jpg",
	"sources/assets/rouge.png"};

	for (int i = 1; i <= 4; i++) {
		if (i <= _Actualplayers)
			_character.push_back(
			new Character("sources/assets/sydney.md2",
			Texture[i], _driver, _smgr, i,
			irr::core::vector3df(pos.X, 90, pos.Y),
			LocalBehavior::make(binds)));
		else
		  	_character.push_back(nullptr);
		pos.X = i % 2 != 0 ? 1300 : 100;
		pos.Y = i < 2 ? 100 : 1300;
	}
}
