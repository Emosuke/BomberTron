#include "Wall.hpp"

/*!
**@brief Construct a new Wall:: Wall object
**
**@param smgr 
**@param drv 
**@param pos 
*/
Wall::Wall(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *drv, irr::core::vector3df pos)
: Block(smgr, pos, true, WALL)
{
	irr::video::ITexture *wall = drv->getTexture("sources/assets/Wall.jpg");

	setBlockTexture(wall);
}
