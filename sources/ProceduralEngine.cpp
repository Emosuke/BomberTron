# include "../include/ProceduralEngine.hpp"

/*!
** @brief Construct a new Procedural Engine:: Procedural Engine object
** 
*/
ProceduralEngine::ProceduralEngine()
	: map(MAP_SIZE)
{
 	Creation();
}

/*!
** @brief get map
** 
** @return const std::vector<std::vector<E_Case> > 
*/
const std::vector<std::vector<E_Case> >	ProceduralEngine::getMap()
{
	return map;
}

/*!
** @brief Create Floor on map
** 
*/
void ProceduralEngine::FloorCreator()
{
	int x;
	int y;

	for (y = 0; y < MAP_SIZE; y++) {
		for (x = 0; x < MAP_SIZE; x++) {
			this->map[y].push_back(EMPTY);
		}
	}
}

/*!
** @brief Create Wall on map
** 
*/
void ProceduralEngine::WallCreator()
{
	int x;
	int y;

	for (y = 0; y < MAP_SIZE; y++) {
		for (x = 0; x < MAP_SIZE; x++) {
			if (x == 0 || y == 0 || x == MAP_SIZE - 1
			|| y == MAP_SIZE - 1)
				this->map[y].at(x) = WALL;
		}
	}
}

/*!
** @brief Check for empty col
** 
** @param y 
*/
void ProceduralEngine::checkEmptyCol(int y)
{
	for (int x = 1; x < MAP_SIZE; x++) {
		if (x % 2 == 0 && y % 2 == 0 && map[y].at(x) == EMPTY)
			this->map[y].at(x) = COL;
	}
}

/*!
** @brief Create Column on map
** 
*/
void ProceduralEngine::ColCreator()
{
	for (int y = 1; y < MAP_SIZE; y++)
		checkEmptyCol(y);
}

/*!
** @brief Check for player
** 
*/
void ProceduralEngine::checkPlayer(int y)
{
	for (int x = 1; x < MAP_SIZE; x++) {
		if ((x == 1 && y == 1) ||
		(x == 1 && y == MAP_SIZE - 2) ||
		(x == MAP_SIZE - 2 && y == 1) ||
		(x == MAP_SIZE - 2 && y == MAP_SIZE - 2))
			this->map[y].at(x) = PLAYER;
	}
}

/*!
** @brief Put Player on map
** 
*/
void ProceduralEngine::PCreator()
{
	for (int y = 1; y < MAP_SIZE; y++)
		checkPlayer(y);
}

/*!
** @brief Determin if a player is next to the case in parameter
** 
** @param x 
** @param y 
** @return int 
*/
int ProceduralEngine::isPlayerStart(int x, int y)
{
	int toReturn = 1;

	if (map[y].at(x - 1) == PLAYER ||
	map[y].at(x + 1) == PLAYER ||
	map[y + 1].at(x) == PLAYER ||
	map[y - 1].at(x) == PLAYER)
		toReturn = 0;
	return toReturn;
}

/*!
** @brief Check for box
** 
** @param y 
*/
void ProceduralEngine::checkBox(int y)
{
	for (int x = 1; x < MAP_SIZE; x++) {
		if (rand() % 2 != 0 && map[y].at(x) == EMPTY &&
		isPlayerStart(x, y) != 0)
			this->map[y].at(x) = BOX;
	}
	
}

/*!
** @brief Put boxes on map procedurally
** 
*/
void ProceduralEngine::ProceduralBox()
{
	srand(time(NULL));
	for (int y = 1; y < MAP_SIZE; y++)
		checkBox(y);
}

/*!
** @brief Call every function to create map
** 
*/
void	ProceduralEngine::Creation()
{
	FloorCreator();
	WallCreator();
	ColCreator();
	PCreator();
	ProceduralBox();
}

/*!
** @brief Draw the map on terminal
** 
*/
void	ProceduralEngine::DrawMap()
{
	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++) {
			std::cout << map[y][x];
		}
		std::cout << std::endl;
	}
}