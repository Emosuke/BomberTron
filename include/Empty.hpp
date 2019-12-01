#ifndef EMPTY_HPP_
# define EMPTY_HPP_

#include <irrlicht.h>
#include "Block.hpp"

class Empty : public Block {
public:
	Empty(irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *drv, irr::core::vector3df Pos);
};

# endif /* !EMPTY_HPP_ */