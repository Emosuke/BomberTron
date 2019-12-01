
#include "Block.hpp"

/*
**@brief Construct a new Block:: Block object
**
**@param smgr 
**@param pos 
**@param flag 
**@param type 
*/
Block::Block(irr::scene::ISceneManager *smgr,
irr::core::vector3df pos, bool flag, E_Case type)
{
	irr::scene::IMeshSceneNode *block;

	if (flag == true) {
		_block = smgr->addCubeSceneNode(1, 0, -1, pos);
		_isDestroyed = false;
		setBlockScale(irr::core::vector3df(100.0f, 100.0f, 100.0f));
		_block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	} else {
		_isDestroyed = true;
		_block = nullptr;
	}
	setBlockPos(pos);
	_type = type;
}

/*
**@brief set texture to the Block
**
**@param style
*/
void Block::setBlockTexture(irr::video::ITexture *style)
{
	_block->setMaterialTexture(0, style);
}

/*
**@brief get the block Mesh
**
**@return irr::scene::IMeshSceneNode*
*/
irr::scene::IMeshSceneNode *Block::getMesh() const
{
	return _block;
}

/*
**@brief set the block Mesh 
**
**@param block 
*/
void Block::setBlock(irr::scene::IMeshSceneNode *block)
{
	_block = block;
}

/*
**@brief set the block scale
**
**@param scale 
*/
void Block::setBlockScale(irr::core::vector3df scale)
{
	_block->setScale(scale);
}

/*
**@brief set the block position
**
**@param pos 
*/
void Block::setBlockPos(irr::core::vector3df pos)
{
	_pos = pos;
}

/*
**@brief check if block is destroyed
**
**@param state 
*/
void Block::setIsDestroyed(bool state)
{
	_isDestroyed == state;
}

/*
**@brief get the block position
**
**@return irr::core::vector3df
*/
irr::core::vector3df Block::getBlockPos() const
{
	return _pos;
}

/*
**@brief do nothing
**
*/
void Block::destroy()
{
	_isDestroyed = _isDestroyed;
}

/*
**@brief setter _type
**
**@param type 
*/
void Block::setType(E_Case type)
{
	_type = type;
}

/*
**@brief getter _type
**
**@return E_Case
*/
E_Case Block::getType() const
{
	return _type;
}