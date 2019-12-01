
#include "Empty.hpp"

/*!
** @brief Construct a new Empty:: Empty object
** 
** @param smgr 
** @param drv 
** @param pos 
*/
Empty::Empty(irr::scene::ISceneManager *smgr,
irr::video::IVideoDriver *drv, irr::core::vector3df pos)
: Block(smgr, pos, false, EMPTY)
{
}