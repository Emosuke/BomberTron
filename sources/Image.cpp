#include "Image.hpp"

/*!
** @brief Construct a new Image:: Image object
** 
** @param path 
** @param driver 
*/
Image::Image(std::string path, irr::video::IVideoDriver *driver)
{
	Update(path, driver);
	start.X = 0;
	start.Y = 0;
	end.X = 1920;
	end.Y = 1080;
	rect.UpperLeftCorner = start;
	rect.LowerRightCorner = end;
}

/*!
** @brief function that draw a picture to the screen
** 
** @param driver 
*/
void Image::Draw(irr::video::IVideoDriver *driver)
{
	driver->draw2DImage(texture, start, rect, 0,
	irr::video::SColor (255,255,255,255), true);
}

/*!
** @brief function that update menu picture
** 
** @param path 
** @param driver 
*/
void Image::Update(std::string path, irr::video::IVideoDriver *driver)
{
	texture = driver->getTexture(path.c_str());
}
