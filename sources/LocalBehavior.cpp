#include <iostream>
#include <memory>
#include "LocalBehavior.hpp"

LocalBehavior::LocalBehavior(const std::pair<std::string, std::array<char, 5>> &binds)
{
	for (uint32_t i = 0; i < irr::KEY_KEY_CODES_COUNT; i += 1) {
		keyIsDown[i] = false;
	}
	if (binds.first == "[JOYSTICK]")
		this->joystick = true;
	else
		this->joystick = false;
	for (uint32_t i = 0, j = 2; i < binds.second.size(); i += 1, j *= 2) {
		this->bindings[i].first = binds.second[i];
		this->bindings[i].second =
			static_cast<enum IGameBehavior::action> (j);
	}
	this->bindings[5].first = 27;
	this->bindings[5].second = IGameBehavior::action::ESCAPE;
	this->dispatcher = KeyDispatcher::make();
	this->action.store(0, std::memory_order_relaxed);
}

LocalBehavior::~LocalBehavior()
{
}

bool	LocalBehavior::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT &&
		this->joystick == true) {
		this->joystickEvent(event.JoystickEvent);
		return true;
	}
	if (event.EventType != irr::EET_KEY_INPUT_EVENT)
		return false;
	this->setAction(event.KeyInput.Key, event.KeyInput.PressedDown);
	return true;
}

enum IGameBehavior::action	LocalBehavior::JoystickHorizontal(const irr::SEvent::SJoystickEvent &event)
{
	enum action	xAxis = IGameBehavior::action::NONE;

	if (event.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f > 0.05f)
		xAxis = IGameBehavior::action::MOVE_RIGHT;
	else if (event.Axis[irr::SEvent::SJoystickEvent::AXIS_X] /
		 32767.f < -0.05f)
		xAxis = IGameBehavior::action::MOVE_LEFT;
	return (xAxis);
}

enum IGameBehavior::action	LocalBehavior::JoystickVertical(const irr::SEvent::SJoystickEvent &event)
{
	enum action	yAxis = IGameBehavior::action::NONE;

	if (event.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f > 0.05f)
		yAxis = IGameBehavior::action::MOVE_UP;
	else if (event.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] /
		 -32767.f < -0.05f)
		yAxis = IGameBehavior::action::MOVE_DOWN;
	return (yAxis);
}

enum IGameBehavior::action	LocalBehavior::JoystickButton(const irr::SEvent::SJoystickEvent &event)
{
	for (uint32_t i = 0; i < 32; i += 1)
		if (event.IsButtonPressed(i) == true)
			return (IGameBehavior::action::DROP);
	return (IGameBehavior::action::NONE);
}

void	LocalBehavior::joystickEvent(const irr::SEvent::SJoystickEvent &event)
{
	int	a = static_cast<int>
		(this->action.load(std::memory_order_relaxed)) & 64;
	this->action.store(this->JoystickHorizontal(event) |
			   this->JoystickVertical(event) |
			   this->JoystickButton(event) |
			   a,
			   std::memory_order_relaxed);
}

void    LocalBehavior::setAction(int key, bool press)
{
	enum IGameBehavior::action	act = IGameBehavior::action::NONE;

	for (auto a : this->bindings) {
		if (a.first == key) {
			act = a.second;
			break;
		}
	}
	if (press == true)
		this->action.fetch_or(act, std::memory_order_relaxed);
	else
		this->action.fetch_xor(act, std::memory_order_relaxed);
}

int	LocalBehavior::update()
{
	return this->action.load(std::memory_order_relaxed);
}

std::shared_ptr<LocalBehavior>	LocalBehavior::make(Binding &binds)
{
	std::shared_ptr<LocalBehavior> p
		(new LocalBehavior(binds.getBinding()));

	p->dispatcher->subscribed(p);
	return std::move(p);
}

std::shared_ptr<KeyDispatcher>	LocalBehavior::getDispatcher() const
{
	return std::shared_ptr<KeyDispatcher> (this->dispatcher);
}
