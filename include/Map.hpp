
#ifndef MAP_HPP_
# define MAP_HPP_

#include <irrlicht.h>
#include "ProceduralEngine.hpp"
#include "Wall.hpp"
#include "Box.hpp"
#include "Empty.hpp"
#include "Bomb.hpp"


class Map {
public:
	Map(irr::scene::ISceneManager *_smgr,
	irr::video::IVideoDriver *drv,
	std::vector<std::vector<E_Case> > gen,
	std::vector<Bomb *> &bomb);
	void setOrigin(irr::core::vector3df origin);
	void setSceneManager(irr::scene::ISceneManager * smgr);
	void setDriver(irr::video::IVideoDriver *driver);
	irr::core::vector3df getOrigin() const;
	void initialize(std::vector<std::vector<E_Case> > gen);
	bool isPositionValid(irr::core::vector3df pos,
	irr::core::vector3df origin, std::vector<Bomb *> &bomb) const;
	std::vector<IBlock *> initializeLine(std::vector<E_Case> gen, int y);
	void destroyBlock(int y, int x);
	irr::core::vector2di getIndex(irr::core::vector3df pos) const;
	void explosionInRow(irr::core::vector2di ind, int range);
	void explosion(irr::core::vector3df pos, int range);
	void chooseBlock(E_Case cell, irr::core::vector3df pos, int y);
	std::vector<std::vector<IBlock *> > getMap() const;
	irr::core::vector3df getCenter(irr::core::vector3df pos) const;
	bool checkCorner(irr::core::vector2di fr,
	irr::core::vector2di to) const;
	irr::core::vector3df getBlockOrigin(irr::core::vector3df pos) const;
	bool isDead(irr::core::vector3df ply, irr::core::vector3df p, int rg);
private:
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_smgr;
	std::vector<std::vector<IBlock *> > _map;
	irr::core::vector3df _origin;
	std::vector<Bomb *> _bomb;
};

# endif /* !MAP_HPP_ */