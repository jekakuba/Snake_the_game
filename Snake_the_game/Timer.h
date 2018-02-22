#pragma once
#include "Interfaces.h"
#include <SFML/System.hpp>
#include <set>
class Timer : public Notifier {
public:
	Timer(const sf::Time& period);

	void update(const sf::Time& deltaTime);
public: //Notifier implementation
	virtual void attach(Updatable*) override;
	virtual void detach(Updatable*) override;
	virtual void notify() override;
private:
	sf::Time m_timePassed;
	sf::Time m_period;

	std::set<Updatable*> m_subscribers;
};

