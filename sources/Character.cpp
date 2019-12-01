#include "Character.hpp"

/*!
** @brief Construct a new Character:: Character object
** 
** @param mesh 
** @param texture 
** @param driver 
** @param scene 
** @param id 
** @param pos 
** @param event 
*/
Character::Character(std::string mesh, std::string texture,
irr::video::IVideoDriver *driver,
irr::scene::ISceneManager *scene,
int id,
irr::core::vector3df pos,
std::shared_ptr<LocalBehavior> event)
: _id(id)
{
	_isMoving = false;
	_animation = irr::scene::EMAT_STAND;
	_character = scene->addAnimatedMeshSceneNode(
	scene->getMesh(mesh.c_str()));
	_character->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_character->setMaterialTexture(0,
	driver->getTexture(texture.c_str()));
	_character->setScale(irr::core::vector3df(4.0f, 4.0f, 4.0f));
	_character->setPosition(pos);
	_event = event;
}

/*!
** @brief get the character Mesh
** 
** @return irr::scene::IAnimatedMeshSceneNode*
*/
irr::scene::IAnimatedMeshSceneNode *Character::getMesh() const
{
	return _character;
}

/*!
** @brief move character (translation and rotation)
** 
** @param translate 
** @param rotate 
*/
void Character::move(irr::core::vector3df translate,
irr::core::vector3df rotate)
{
	if (_character != nullptr) {
		translate += _character->getPosition();
		_character->setRotation(rotate);
		_character->setPosition(translate);
	}
}

/*!
** @brief check if player is moving and launch updateAnmation
** 
** @param isMoving 
*/
void Character::setIsMoving(const bool isMoving)
{
	_isMoving = isMoving;
	updateAnimation();
}

/*!
** @brief update the character's animation
** 
*/
void Character::updateAnimation()
{
	if (_character != nullptr) {
		if (_isMoving && _animation != irr::scene::EMAT_RUN) {
			_character->setMD2Animation(irr::scene::EMAT_RUN);
			_animation = irr::scene::EMAT_RUN;
		}
		else if (!_isMoving && _animation != irr::scene::EMAT_STAND) {
			_character->setMD2Animation(irr::scene::EMAT_STAND);
			_animation = irr::scene::EMAT_STAND;
		}
	}
}

/*!
** @brief get character position
** 
** @return irr::core::vector3df
*/
irr::core::vector3df Character::getPosition() const
{
	irr::core::vector3df pos = irr::core::vector3df(0, 0, 0);
	
	if (_character != nullptr)
		pos =  _character->getPosition();
	return pos;
}

/*!
** @brief Move Up
** 
** @param nbInput 
** @return int
*/
int Character::Up(int nbInput)
{
	_translate += irr::core::vector3df(6, 0, 0);
	_rotate += 0;
	nbInput++;
	return nbInput;
}

/*!
** @brief Move Down
** 
** @param nbInput 
** @return int
*/
int Character::Down(int nbInput)
{
	_translate += irr::core::vector3df(-6, 0, 0);
	_rotate += 180;
	nbInput++;
	return nbInput;
}

/*!
** @brief Move Right
** 
** @param nbInput 
** @return int
*/
int Character::Right(int nbInput)
{
	_translate += irr::core::vector3df(0, 0, 6);
	_rotate += 270;
	nbInput++;
	return nbInput;
}

/*!
** @brief Move Left
** 
** @param nbInput 
** @return int
*/
int Character::Left(int nbInput)
{
	_translate += irr::core::vector3df(0, 0, -6);
	_rotate += 90;
	nbInput++;
	return nbInput;
}

/*!
** @brief Launch set isMoving and move if character != nullptr
** 
** @param nbInput 
** @return int
*/
void Character::Moving(Map *map, std::vector<Bomb *> &bomb, int nbInput)
{
	if (_character != nullptr &&
	map->isPositionValid(getTruePosition() + _translate,
	getTruePosition(), bomb)) {
		setIsMoving(true);
		move(_translate, irr::core::vector3df(0, _rotate /
		nbInput, 0));
	}
}

/*!
** @brief Move Right, Left, Up,
** 
** @param nbInput 
** @return int
*/
int Character::checkEvent2(int nbInput)
{
	if ((_event->update() & IGameBehavior::action::MOVE_UP) ==
	IGameBehavior::action::MOVE_UP)
		nbInput = Up(nbInput);
	if ((_event->update() & IGameBehavior::action::MOVE_DOWN) ==
	IGameBehavior::action::MOVE_DOWN)
		nbInput = Down(nbInput);
	if ((_event->update() & IGameBehavior::action::MOVE_RIGHT) ==
	IGameBehavior::action::MOVE_RIGHT)
		nbInput = Right(nbInput);
	if ((_event->update() & IGameBehavior::action::MOVE_LEFT) ==
	IGameBehavior::action::MOVE_LEFT)
		nbInput = Left(nbInput);
	return nbInput;
}

/*!
** @brief check event : Drop Bomb
** 
** @param map 
** @param bomb 
** @return int
*/
int Character::checkEvent(Map *map, std::vector<Bomb *> &bomb)
{
	int nbInput = 0;

	_rotate = 0;
	_translate = irr::core::vector3df(0, 0, 0);
	nbInput = checkEvent2(nbInput);
	if ((_event->update() & IGameBehavior::action::DROP) ==
	IGameBehavior::action::DROP)
		return 1;
	if (nbInput > 0) {
	Moving(map, bomb, nbInput);
	}
	else
		setIsMoving(false);
	return 0;
}

/*!
** @brief get character postion
** 
** @return irr::core::vector3df
*/
irr::core::vector3df Character::getTruePosition()
{
	irr::core::vector3df pos = irr::core::vector3df(0, 0, 0);
	
	if (_character != nullptr)
		pos =  getPosition() + irr::core::vector3df(30, 0, 30);
	return pos;
}

/*!
** @brief destroy character
** 
*/
void Character::destroy()
{
	if (_character != nullptr) {
		_character->remove();
		_character = nullptr;
	}
}