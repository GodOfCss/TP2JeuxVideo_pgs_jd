#pragma once
#include "GameObject.h"

class GunBonus : public GameObject
{
public:
	GunBonus(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	GunBonus(const GunBonus& src);
	bool init(const ContentManager& contentManager, const sf::Vector2f& initialPosition);
	void playSound();
	void draw(sf::RenderWindow& window) const;

	void spawn(const sf::Vector2f& enemyPosition);
	void move(float x, float y);
private:
	GunBonus& operator=(const GunBonus& rhs);
	sf::Sound sound;
};

