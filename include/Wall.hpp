
#ifndef WALL_HPP_
# define WALL_HPP_

#include <irrlicht.h>
#include "Block.hpp"

class Wall : public Block {
public:
	Wall(irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *drv, irr::core::vector3df Pos);
};

# endif /* !WALL_HPP_ */