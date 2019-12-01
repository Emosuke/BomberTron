#ifndef BLOCK_HPP_
# define BLOCK_HPP_

#include <irrlicht.h>
#include "IBlock.hpp"

class Block : public IBlock {
public:
	Block(irr::scene::ISceneManager *smgr, irr::core::vector3df Pos,
	bool flag, E_Case type);
	void setBlock(irr::scene::IMeshSceneNode *cube);
	irr::scene::IMeshSceneNode *getMesh() const;
	void setBlockTexture(irr::video::ITexture *style);
	void setBlockScale(irr::core::vector3df scale);
	void setBlockPos(irr::core::vector3df pos);
	void setIsDestroyed(bool state);
	void setType(E_Case type);
	E_Case getType() const;
	irr::core::vector3df getBlockPos() const;
	void destroy();
protected:
	irr::scene::IMeshSceneNode *_block;
	irr::core::vector3df _pos;
	bool _isDestroyed;
	E_Case _type;
};

# endif /* !BLOCK_HPP_ */