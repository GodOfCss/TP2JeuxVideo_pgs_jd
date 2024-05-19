#pragma once
#include "Bullet.h"
class BossEnemyBullet : public Bullet
{
	static const float BULLET_SPEED;

public:
	BossEnemyBullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	BossEnemyBullet(const BossEnemyBullet& src);
	bool update(const float elapsedTime) override;
	void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb) override;
	void fire();

private:
};