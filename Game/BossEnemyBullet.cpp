#include "stdafx.h"
#include "game.h"
#include "BossEnemyBullet.h"

const float BossEnemyBullet::BULLET_SPEED = 600.0f;

BossEnemyBullet::BossEnemyBullet(const sf::Vector2f& initialPosition)
	: Bullet(initialPosition)
{
}

BossEnemyBullet::BossEnemyBullet(const BossEnemyBullet& src)
	: Bullet(src)
{
}

bool BossEnemyBullet::update(const float elapsedTime)
{
	if (isActive())
	{
		if (getPosition().y > Game::GAME_HEIGHT) {
			deactivate();
		}
		move(sf::Vector2f(0, BULLET_SPEED * elapsedTime));
		if (getPosition().x > Game::GAME_WIDTH || getPosition().x < 0 || getPosition().y > Game::GAME_HEIGHT || getPosition().y < 0)
			return true;
	}
	else
		return true;
	return false;

}

void BossEnemyBullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	Bullet::initialize(texture, initialPosition, sb);

	//setTextureRect(sf::IntRect(264, 106, 16, 5));
	setRotation(270);
	setColor(sf::Color(255, 150, 150, 255));
}

void BossEnemyBullet::fire()
{
	activate();
}