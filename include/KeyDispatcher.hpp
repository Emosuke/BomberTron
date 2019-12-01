
#ifndef	KEYDISPATCHER_HPP_
	#define KEYDISPATCHER_HPP_

class KeyDispatcher;

#include "LocalBehavior.hpp"
#include <memory>

class KeyDispatcher : public irr::IEventReceiver {
public:
	~KeyDispatcher();
	bool OnEvent(const irr::SEvent &event) override;
	
	static std::shared_ptr<KeyDispatcher> make();
	void subscribed(std::shared_ptr<LocalBehavior> &local);
	void unsubscribed(std::shared_ptr<LocalBehavior> &local);
private:
	KeyDispatcher();
	std::vector<std::weak_ptr<LocalBehavior>>	storage;
};

static std::shared_ptr<KeyDispatcher> key = nullptr;

#endif
