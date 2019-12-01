#include "KeyDispatcher.hpp"

KeyDispatcher::KeyDispatcher()
{
}

KeyDispatcher::~KeyDispatcher()
{
	key = nullptr;
}

bool	KeyDispatcher::OnEvent(const irr::SEvent &event)
{
	for (uint32_t i = 0; i < this->storage.size(); i += 1)
		if (this->storage[i].expired() == true) {
			this->storage.erase(this->storage.begin() + i);
			i = i - 1;
		} else
			this->storage[i].lock()->OnEvent(event);
	return true;

}

void	KeyDispatcher::subscribed(std::shared_ptr<LocalBehavior> &local)
{
	this->storage.emplace_back(std::weak_ptr<LocalBehavior>(local));
}

void	KeyDispatcher::unsubscribed(std::shared_ptr<LocalBehavior> &local)
{
	for (uint32_t i = 0; i < this->storage.size(); i += 1)
		if (this->storage[i].lock().get() == local.get()) {
			this->storage.erase(this->storage.begin() + i);
			i -= 1;
		}
}

std::shared_ptr<KeyDispatcher>	KeyDispatcher::make()
{
	if (key == nullptr)
		key = std::shared_ptr<KeyDispatcher> (new KeyDispatcher);
	return std::shared_ptr<KeyDispatcher> (key);
}
