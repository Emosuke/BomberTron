#include "Box.hpp"

/*
**@brief Construct a new Box:: Box object
**
**@param smgr 
**@param drv 
**@param pos 
*/
Box::Box(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *drv,
irr::core::vector3df pos)
: Block(smgr, pos, true, BOX)
{
	irr::video::ITexture *box = drv->getTexture("sources/assets/box.jpg");

	setBlockTexture(box);
}

/*!
**@brief destroy object block
**
*/
void Box::destroy()
{
	if (_isDestroyed == false && _block != nullptr) {
		_block->remove();
		_block = nullptr;
		_isDestroyed = true;
	}
}
