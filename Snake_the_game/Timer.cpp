#include "Timer.h"

Timer::Timer(const sf::Time& period) : m_period(period), m_timePassed(sf::Time::Zero) {

}

void Timer::update(const sf::Time& deltaTime) {
	m_timePassed += deltaTime;

	if (m_timePassed > m_period) {
		m_timePassed = sf::Time::Zero;
		notify();
	}
}

void Timer::attach(Updatable* obj) {
	m_subscribers.insert(obj);
}

void Timer::detach(Updatable* obj) {
	m_subscribers.erase(obj);
}

void Timer::notify() {
	for (auto& obj : m_subscribers) {
		obj->update();
	}
}