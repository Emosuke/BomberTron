#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <string>
#include <irrlicht.h>
#include <iostream>
#include "LocalBehavior.hpp"
#include "Map.hpp"
#include "Bomb.hpp"


class Character {
public:
	Character(std::string mesh, std::string texture,
	irr::video::IVideoDriver *driver,
	irr::scene::ISceneManager *scene,
	int id, irr::core::vector3df pos,
	std::shared_ptr<LocalBehavior>);
	irr::scene::IAnimatedMeshSceneNode *getMesh() const;
	void move(irr::core::vector3df translate,
	irr::core::vector3df rotate);
	void setIsMoving(const bool isMoving);
	irr::core::vector3df getPosition() const;
	int checkEvent(Map *map, std::vector<Bomb *> &bomb);
	irr::core::vector3df getTruePosition();
	void destroy();
private:
	void updateAnimation();
	int Up(int nbInput);
	int Down(int nbInput);
	int Left(int nbInput);
	int Right(int nbInput);
	void Moving(Map *map, std::vector<Bomb *> &bomb,
	int nbInput);
	int checkEvent2(int nbInput);
	int _id;
	int _dir;
	bool _isMoving;
	int _rotate;
	irr::core::vector3df _translate;
	irr::scene::IAnimatedMeshSceneNode *_character;
	irr::scene::EMD2_ANIMATION_TYPE _animation;
	std::shared_ptr<LocalBehavior> _event;
};

#endif /* !CHARACTER_HPP_ */
