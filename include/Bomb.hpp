#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <irrlicht.h>
#include "Particules.hpp"

class Bomb {
public:
	Bomb(irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *_drv,
	irr::core::vector3df pos, int range);
	void update();
	void setPosition(irr::core::vector3df pos);
	irr::core::vector3df getPosition() const;
	bool getHasExploded() const;
	bool getIsExploding() const;
	void destroy();
	int getRange() const;
private:
	irr::scene::IMeshSceneNode *_bomb = nullptr;
	Particules *_particules;
	irr::core::vector3df _position;
	bool _isExploding;
	bool _hasExploded;
	time_t _check;
	time_t _start;
	int _range;
};

#endif /* !BOMB_HPP_ */