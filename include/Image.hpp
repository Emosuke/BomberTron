
#ifndef IMAGE_HPP_
	#define IMAGE_HPP_

#include <irrlicht.h>
#include <irrString.h>
#include <string>

class Image {
public:
		Image(std::string path,	irr::video::IVideoDriver *driver);
		void Draw(irr::video::IVideoDriver *driver);
		void Update(std::string path, irr::video::IVideoDriver *driver);
private:
		irr::video::ITexture *texture;
		irr::core::position2d<irr::s32> start;
		irr::core::position2d<irr::s32> end;
		irr::core::rect<irr::s32> rect;
};

#endif /* !IMAGE_HPP_ */
