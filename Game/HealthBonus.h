#pragma once
#include "GameObject.h"

class HealthBonus : public GameObject
{
public:
	HealthBonus(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	HealthBonus(const HealthBonus& src);
	bool init(const ContentManager& contentManager, const sf::Vector2f& initialPosition);
	void playSound();
	void draw(sf::RenderWindow& window) const;

	void spawn(const sf::Vector2f& enemyPosition);
	void move(float x, float y);
private:
	HealthBonus& operator=(const HealthBonus& rhs);
	sf::Sound sound;
};

