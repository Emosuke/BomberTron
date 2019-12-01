
#ifndef IBLOCK_HPP_
# define IBLOCK_HPP_

#include <irrlicht.h>
#include "ProceduralEngine.hpp"

class IBlock {
public:
	virtual ~IBlock(){}
	virtual void setBlock(irr::scene::IMeshSceneNode *cube) = 0;
	virtual irr::scene::IMeshSceneNode *getMesh() const = 0;
	virtual void setBlockTexture(irr::video::ITexture *style) = 0;
	virtual void setBlockScale(irr::core::vector3df scale) = 0;
	virtual void setBlockPos(irr::core::vector3df pos) = 0;
	virtual void setIsDestroyed(bool state) = 0;
	virtual void setType(E_Case type) = 0;
	virtual irr::core::vector3df getBlockPos() const = 0 ;
	virtual E_Case getType() const = 0;
	virtual void destroy() = 0;
};

# endif /* !IBLOCK_HPP_ */