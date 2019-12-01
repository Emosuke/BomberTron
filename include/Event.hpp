#ifndef EVENT_HPP_
	#define EVENT_HPP_

#include <IEventReceiver.h>

class Event : public irr::IEventReceiver {
public:
	Event();
	virtual bool OnEvent(const irr::SEvent &event);
	irr::EKEY_CODE GetInput(void) const;
	void SetInput(const irr::EKEY_CODE key);
	bool isInput();
private:
	irr::EKEY_CODE input;
};

#endif /* !MENUEVENT_HPP_ */
