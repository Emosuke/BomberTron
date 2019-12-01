#include "Bomb.hpp"
#include <time.h>

/*!
** @brief Construct a new Bomb:: Bomb object
** 
** @param smgr 
** @param drv 
** @param pos 
** @param range 
*/
Bomb::Bomb(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *drv,
irr::core::vector3df pos, int range)
{
	_bomb = smgr->addMeshSceneNode(smgr->getMesh(
	"sources/assets/Bomb.3ds"));
	_bomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_bomb->setMaterialTexture(0,
	drv->getTexture("sources/assets/bomb.jpg"));
	_bomb->setScale(irr::core::vector3df(200.0f, 200.0f, 200.0f));
	setPosition(pos);
	_particules = new Particules(drv, smgr);
	_start = time(&_start);
	_isExploding = false;
	_hasExploded = false;
	_range = range;
}

/*!
** @brief manage bomb's explosion and refresh of timer
** 
*/
void Bomb::update()
{
	if (_bomb == nullptr)
		return;
	_check = time(&_check);
	if (difftime(_check, _start) > 1 && !_isExploding) {
		_particules->creation(_bomb->getPosition(), _range);
		_isExploding = true;
	}
	if(difftime(_check, _start) > 2 && _isExploding && !_hasExploded) {
		if (_particules != nullptr) {
			_particules->destroy();
			delete(_particules);
			_particules = nullptr;
		}
		if (_bomb != nullptr) {
			_bomb->remove();
			_bomb = nullptr;
		}	
		_hasExploded = true;
	}
}

/*!
** @brief set bomb's position
** 
** @param pos
*/
void Bomb::setPosition(irr::core::vector3df pos)
{
	irr::core::vector2di temp
	= irr::core::vector2di(pos.X, pos.Z);
	
	temp.X = (temp.X / 100) * 100;
	temp.Y = (temp.Y / 100) * 100;
	pos = irr::core::vector3df(temp.X, 52, temp.Y);
	_bomb->setPosition(pos);
	_position = pos + irr::core::vector3df(50, 0, 50);
}

/*!
** @brief get bomb's position
** 
** @return irr::core::vector3df bomb position
*/
irr::core::vector3df Bomb::getPosition() const
{
	return _position;
}

/*!
** @brief destruction of bomb and clear
** 
*/
void Bomb::destroy()
{
	if (_isExploding == true && _particules != nullptr) {
		_particules->destroy();
		delete(_particules);
		_particules = nullptr;
	}
	if (_bomb != nullptr) {
		_bomb->remove();
		_bomb = nullptr;
	}
}

/*!
** @brief Check if bomb exploded
** 
** @return true had blowed
** @return false bomb is in explosion period
*/
bool Bomb::getHasExploded() const
{
	return _hasExploded;
}

/*!
** @brief Check if bomb is in explosion period
** 
** @return true if bomb is in explosion
** @return false if not in explosion period
*/
bool Bomb::getIsExploding() const
{
	return _isExploding;
}

/*!
** @brief get bomb's range
** 
** @return int bomb's range
*/
int Bomb::getRange() const
{
	return _range;
}