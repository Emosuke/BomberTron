
#ifndef GENERATOR_HPP_
# define GENERATOR_HPP_

# include <vector>
# include <iostream>
# include <stdlib.h>
# include <time.h>
# define MAP_SIZE 15

/*!
** @brief List of different blocs on map
** 
*/
enum E_Case {
	EMPTY = 0,
	WALL = 1,
	COL = 2,
	PLAYER = 3,
	BOX = 4,
	BOMB = 5
};

class ProceduralEngine {
public:
	ProceduralEngine();
	void DrawMap();
	const std::vector<std::vector<E_Case> >	getMap();
private:
	void Creation();
	void FloorCreator();
	void WallCreator();
	void ColCreator();
	void PCreator();
	void ProceduralBox();
	int isPlayerStart(int x, int y);
	std::vector<std::vector<E_Case> > map;
	void checkEmptyCol(int y);
	void checkPlayer(int y);
	void checkBox(int y);
};

# endif	/* GENERATOR_HPP_ */
