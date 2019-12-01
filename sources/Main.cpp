#include "Menu.hpp"

/*!
**@brief Main of the program
**
**@return int 
*/
int main(void)
{
	irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL,
	irr::core::dimension2d<irr::u32>(1920, 1080), 32);

	device->setResizable(false);
	Menu menu(device);
	menu.Run();
	device->drop();
	return 0;
}