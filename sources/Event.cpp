#include "Event.hpp"

Event::Event()
{
}

/*!
** @brief get input event
** 
** @param event 
** @return true 
** @return false 
*/
bool Event::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT
	&& event.KeyInput.PressedDown) {
		input = event.KeyInput.Key;
		return true;
	}
	SetInput(irr::KEY_OEM_8);
	return false;
}

/*!
** @brief Get keyboard input
** 
** @return irr::EKEY_CODE 
*/
irr::EKEY_CODE Event::GetInput(void) const
{
	return input;
}

/*!
** @brief check if event is an input
** 
** @return true 
** @return false 
*/
bool Event::isInput()
{
	if (input == irr::KEY_OEM_8)
		return false;
	return true;
}

/*!
** @brief set input to a key
** 
** @param key 
*/
void Event::SetInput(const irr::EKEY_CODE key)
{
	input = key;
}