#include "Map.hpp"

/*!
** @brief Construct a new Map:: Map object
** 
** @param smgr 
** @param drv 
** @param gen 
** @param bomb 
*/
Map::Map(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *drv,
std::vector<std::vector<E_Case> > gen, std::vector<Bomb *> &bomb)
{
	setOrigin(irr::core::vector3df(-700, 0, 700));
	setSceneManager(smgr);
	setDriver(drv);
	initialize(gen);
	_bomb = bomb;
}

/*!
** @brief check if the corner of the map are empty
** 
** @param from 
** @param to 
** @return true 
** @return false 
*/
bool Map::checkCorner(irr::core::vector2di from, irr::core::vector2di to) const
{
	bool state = true;

	if (to.X == from.X + 1 && to.Y == from.Y + 1
	&& _map[from.Y][from.X + 1]->getType() != EMPTY
	&& _map[from.Y + 1][from.X]->getType() != EMPTY)
		state = false;
	if (to.X == from.X - 1 && to.Y == from.Y + 1
	&& _map[from.Y][from.X - 1]->getType() != EMPTY
	&& _map[from.Y + 1][from.X]->getType() != EMPTY)
		state = false;
	if (to.X == from.X + 1 && to.Y == from.Y - 1
	&& _map[from.Y][from.X + 1]->getType() != EMPTY
	&& _map[from.Y - 1][from.X]->getType() != EMPTY)
		state = false;
	if (to.X == from.X - 1 && to.Y == from.Y - 1
	&& _map[from.Y][from.X - 1]->getType() != EMPTY
	&& _map[from.Y - 1][from.X]->getType() != EMPTY)
		state = false;
	return state;
}

/*!
** @brief check if the param pos is a valid position
** 
** @param pos 
** @param origin 
** @param bomb 
** @return true 
** @return false 
*/
bool Map::isPositionValid(irr::core::vector3df pos,
irr::core::vector3df origin, std::vector<Bomb *> &bomb) const
{
	irr::core::vector2di to = getIndex(pos);
	bool state = false;

	if (to.Y < 15 && to.X < 15 && to.X > 0
	&& to.Y > 0 && _map[to.Y][to.X]->getType() == EMPTY)
		state = true;
	if (!checkCorner(getIndex(origin), to))
		state = false;
	for (size_t i = 0; i < bomb.size(); i++) {
		if (bomb[i] != nullptr
		&& getIndex(bomb[i]->getPosition()) == getIndex(pos)
		&& getIndex(bomb[i]->getPosition()) != getIndex(origin)) {
			state = false;
			break;
		}
	}
	return state;
}

/*!
** @brief get the two dimensional position
** 
** @param pos 
** @return irr::core::vector2di 
*/
irr::core::vector2di Map::getIndex(irr::core::vector3df pos) const
{
	irr::core::vector2di index;

	index.X = pos.X / 100;
	index.Y = pos.Z / 100;
	return index;
}

/*!
** @brief launch destroyBlock if blockis on explosion range
** 
** @param pos 
** @param range 
*/
void Map::explosionInRow(irr::core::vector2di ind, int range)
{
	for (size_t i = ind.Y + 1; i <= ind.Y + range && i < 15; i++) {
		if (_map[i][ind.X]->getType() == BOX) {
			destroyBlock(i, ind.X);
			break;
		}
	}
	for (size_t i = ind.Y - 1; i >= ind.Y - range && i > 0; i--) {
		if (_map[i][ind.X]->getType() == BOX) {
			destroyBlock(i, ind.X);
			break;
		}
	}
}

/*!
** @brief launch destroyBlock if blockis on explosion range
** 
** @param pos 
** @param range 
*/
void Map::explosion(irr::core::vector3df pos, int range)
{
	irr::core::vector2di ind = getIndex(pos);

	for (size_t i = ind.X + 1; i <= ind.X + range && i < 15; i++) {
		if (_map[ind.Y][i]->getType() == BOX) {
			destroyBlock(ind.Y, i);
			break;
		}
	}
	for (size_t i = ind.X - 1; i >= ind.X - range && i > 0; i--) {
		if (_map[ind.Y][i]->getType() == BOX) {
			destroyBlock(ind.Y, i);
			break;
		}
	}
	explosionInRow(ind, range);
}

/*!
** @brief destroy a Block
** 
** @param y 
** @param x 
*/
void Map::destroyBlock(int y, int x)
{
	if (_map[y][x]->getType() == BOX) {
		_map[y][x]->destroy();
		_map[y][x]->setType(EMPTY);
	}
}

/*!
** @brief get center of the map
** 
** @param pos 
** @return irr::core::vector3df 
*/
irr::core::vector3df Map::getCenter(irr::core::vector3df pos) const
{
	irr::core::vector3df center;

	center.X = (pos.X / 100) * 100 + 50;
	center.Y = (pos.Y / 100) * 100 + 50;
	return center;
}

/*!
** @brief get the vector3df of the first Block
** 
** @param pos 
** @return irr::core::vector3df 
*/
irr::core::vector3df Map::getBlockOrigin(irr::core::vector3df pos) const
{
	irr::core::vector3df origin;

	origin.X = (pos.X / 100) * 100;
	origin.Y = (pos.Y / 100) * 100;
	return origin;
}

/*!
** @brief check if player is dead
** 
** @param player 
** @param pos 
** @param range 
** @return true 
** @return false 
*/
bool Map::isDead(irr::core::vector3df player, irr::core::vector3df pos, int range)
{
	irr::core::vector2di body = getIndex(player);
	irr::core::vector2di bomb = getIndex(pos);
	bool state = false;

	if ((body.X <= bomb.X && body.X >= bomb.X - range
	|| body.X >= bomb.X && body.X <= bomb.X + range)
	&& bomb.Y == body.Y)
		state = true;
	if ((body.Y <= bomb.Y && body.Y >= bomb.Y - range
	|| body.Y >= bomb.Y && body.Y <= bomb.Y + range)
	&& bomb.X == body.X)
		state = true;
	return state;
}

/*!
** @brief initialize every single line of the map
** 
** @param gen 
** @param y 
** @return std::vector<IBlock**> 
*/
std::vector<IBlock *> Map::initializeLine(std::vector<E_Case> gen, int y)
{
	std::vector<IBlock *> line;
	irr::core::vector3df pos;
	float posX = 0;

	for (size_t x = 0; x < gen.size(); x++) {
		pos = irr::core::vector3df(posX, 52, y);
		if (gen[x] == WALL || gen[x] == COL)
			line.push_back(new Wall(_smgr, _driver, pos));
		else if (gen[x] == BOX)
			line.push_back(new Box(_smgr, _driver, pos));
		else if (gen[x] == EMPTY || gen[x] == PLAYER)
			line.push_back(new Empty(_smgr, _driver, pos));
		posX += 100;
	}
	return line;
}

/*!
** @brief initialize map
** 
** @param gen 
*/
void Map::initialize(std::vector<std::vector<E_Case> > gen)
{
	float y = 0;

	for (int indY = 0; indY < 15; indY++) {
		_map.push_back(initializeLine(gen[indY], y));
		y += 100;
	}
}

/*!
** @brief set the origin of the map
** 
** @param origin 
*/
void Map::setOrigin(irr::core::vector3df origin)
{
	_origin = origin;
}

/*!
** @brief get the origin of the map
** 
** @return irr::core::vector3df 
*/
irr::core::vector3df Map::getOrigin() const
{
	return _origin;
}

/*!
** @brief getter Map
** 
** @return std::vector<std::vector<IBlock**> > 
*/
std::vector<std::vector<IBlock *> > Map::getMap() const
{
	return _map;
}

/*!
** @brief set the ISceneManager
** 
** @param smgr 
*/
void Map::setSceneManager(irr::scene::ISceneManager *smgr)
{
	_smgr = smgr;
}

/*!
** @brief set the IVideo driver
** 
** @param driver 
*/
void Map::setDriver(irr::video::IVideoDriver *driver)
{
	_driver = driver;
}