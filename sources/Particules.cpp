#include "Particules.hpp"

/*!
**@brief Construct a new Particules:: Particules object
**
**@param driver 
**@param sceneManager 
*/
Particules::Particules(irr::video::IVideoDriver *driver,
irr::scene::ISceneManager *sceneManager)
: _D(driver), _SM(sceneManager)
{
}

/*!
**@brief Create Particle emitter in every direction with range and direction
**
**@param position 
**@param range 
*/
void Particules::creation(irr::core::vector3df position, int range)
{
	_pos = position;
	_nodeUp = Fire(irr::core::vector3df(0.0f, 0.0f, -2.0f), range);
	_nodeDown = Fire(irr::core::vector3df(0.0f, 0.0f, 2.0f), range);
	_nodeLeft = Fire(irr::core::vector3df(2.0f, 0.0f, 0.0f), range);
	_nodeRight = Fire(irr::core::vector3df(-2.0f, 0.0f, 0.0f), range);
}

/*!
**@brief Create a particle emitter with range and direction
**
**@param direction 
**@param range 
**@return irr::scene::IParticleSystemSceneNode* 
*/
irr::scene::IParticleSystemSceneNode *Particules::Fire(
irr::core::vector3df direction, int range)
{
	irr::scene::IParticleSystemSceneNode* partS =
	_SM->addParticleSystemSceneNode(false);
	irr::scene::IParticleEmitter* emitter = partS->createBoxEmitter(
	irr::core::aabbox3d<irr::f32>(-20, -20 * range, -20, 20, 20, 20),
	direction, 500 * range, 500 * range,irr::video::SColor(0,0,0,0),
	irr::video::SColor(0,255,255,255), 40 * range, 40 * range, 0,
	irr::core::dimension2df(20.0f,20.0f),
	irr::core::dimension2df(30.0f,30.0f));
	
	partS->setEmitter(emitter);
	emitter->drop();
	partS->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	partS->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	partS->setMaterialTexture(0,
	_D->getTexture("sources/assets/fire.bmp"));
	partS->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	partS->setPosition(_pos);
	return (partS);
}

/*!
**@brief destroy every Particles
**
*/
void Particules::destroy()
{
	if (_nodeUp != nullptr && _nodeDown != nullptr) {
		_nodeUp->remove();
		_nodeDown->remove();
		_nodeUp = nullptr;
		_nodeDown = nullptr;
	}
	if (_nodeLeft != nullptr && _nodeRight != nullptr) {
		_nodeLeft->remove();
		_nodeRight->remove();
		_nodeLeft = nullptr;
		_nodeRight = nullptr;
	}
}