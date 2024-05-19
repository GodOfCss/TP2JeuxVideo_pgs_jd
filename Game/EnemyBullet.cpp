#include "stdafx.h"
#include "game.h"
#include "EnemyBullet.h"

const float EnemyBullet::BULLET_SPEED = 50;

EnemyBullet::EnemyBullet(const sf::Vector2f& initialPosition)
	: Bullet(initialPosition)
{
}

EnemyBullet::EnemyBullet(const EnemyBullet& src)
	:Bullet(src)
{
}

bool EnemyBullet::update(const float elapsedTime)
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

void EnemyBullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	GameObject::initialize(texture, initialPosition);

	setTextureRect(sf::IntRect(264, 106, 16, 5));
	setRotation(90);
	setScale(2, 2);
	setColor(sf::Color(255, 150, 150, 255));
	sound.setBuffer(sb);
}