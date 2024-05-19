#pragma once
#include "Bullet.h"
class EnemyBullet : public Bullet
{
	static const float BULLET_SPEED;

public:
	EnemyBullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	EnemyBullet(const EnemyBullet& src);
	bool update(const float elapsedTime) override; 
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb) override;
	void fire();

private:
};