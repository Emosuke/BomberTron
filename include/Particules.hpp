
#ifndef PARTICULES_HPP_
#define PARTICULES_HPP_

#include <irrlicht.h>

class Particules {
public:
	Particules(irr::video::IVideoDriver *driver,
	irr::scene::ISceneManager *sceneManager);
	void creation(irr::core::vector3df position, int range);
	void destroy();
private:
	irr::scene::IParticleSystemSceneNode *Fire(
	irr::core::vector3df dir, int na);
	irr::video::IVideoDriver *_D;
	irr::scene::ISceneManager *_SM;
	irr::scene::IParticleSystemSceneNode *_nodeUp;
	irr::scene::IParticleSystemSceneNode *_nodeLeft;
	irr::scene::IParticleSystemSceneNode *_nodeRight;
	irr::scene::IParticleSystemSceneNode *_nodeDown;
	irr::core::vector3df _pos;
};

#endif /* PARTICULES_HPP_ */
