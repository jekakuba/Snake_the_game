#include "Updatable.h"

Updatable::Updatable(const sf::Time & period) : m_period(period), m_timePassed(sf::Time::Zero) {
	
}

bool Updatable::updateTimer(const sf::Time& dt) {
	m_timePassed += dt;

	if (m_timePassed > m_period) {
		m_timePassed = sf::Time::Zero;
		return true;
	}

	return false;
}

void Updatable::resetTimer() {
	m_timePassed = m_period;
}