#ifndef BOX_HPP_
# define BOX_HPP_

#include <irrlicht.h>
#include "Block.hpp"

class Box : public Block {
public:
	Box(irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *drv, irr::core::vector3df Pos);
	void destroy();
};

# endif /* !BOX_HPP_ */