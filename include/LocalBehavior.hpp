
#ifndef LOCALBEHAVIOR_HPP_
	#define LOCALBEHAVIOR_HPP_

#include <memory>
#include <atomic>
#include <irrlicht.h>
#include "IGameBehavior.hpp"
#include "Binding.hpp"

class LocalBehavior;

#include "KeyDispatcher.hpp"

class LocalBehavior : public IGameBehavior, public irr::IEventReceiver {
public:
	~LocalBehavior();
	bool OnEvent(const irr::SEvent &event) override;
	int	update() override;
	void setAction(int key, bool press);
	static std::shared_ptr<LocalBehavior> make(Binding &);
	std::shared_ptr<KeyDispatcher> getDispatcher() const;

	enum IGameBehavior::action JoystickHorizontal(const irr::SEvent::
	SJoystickEvent &event);
	enum IGameBehavior::action JoystickVertical(const irr::SEvent::
	SJoystickEvent &event);
	enum IGameBehavior::action JoystickButton(const irr::SEvent::
	SJoystickEvent &event);
	void joystickEvent(const irr::SEvent::SJoystickEvent &event);
private:
	LocalBehavior(const std::pair<std::string, std::array<char, 5>> &);
	bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
	std::string title;
	std::array<std::pair<char, enum IGameBehavior::action>, 6>
	bindings;
	std::shared_ptr<KeyDispatcher> dispatcher;
	std::atomic<int> action;
	bool joystick;
};

#endif
