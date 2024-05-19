#include <iostream>
#include "stdafx.h"
#include "Bullet.h"
#include "game.h"

const float Bullet::BULLET_SPEED = 1000;

Bullet::Bullet(const sf::Vector2f& initialPosition)
	: GameObject()
	, isSpecialBullet(false)
{
	setPosition(initialPosition);
}

Bullet::Bullet(const Bullet& src)
	:GameObject(src)
{
	initialize(*src.getTexture(), src.getPosition(), *src.sound.getBuffer());
}


void Bullet::draw(sf::RenderWindow& window) const
{
	if (isActive())
	{
 		window.draw(*this);
	}
}


bool Bullet::update(const float elapsedTime, const ContentManager& contentManager)
{
	if (isActive())
	{
		move(sf::Vector2f(0, -BULLET_SPEED * elapsedTime));
		if (getPosition().x > Game::GAME_WIDTH || getPosition().x < 0 || getPosition().y > Game::GAME_HEIGHT || getPosition().y < 0)
			return true;
	}
	else
		return true;
	return false;

}

void Bullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb)
{
	GameObject::initialize(texture, initialPosition);

	setTextureRect(sf::IntRect(264,106,16,5));
	setRotation(90);
	setScale(2, 2);
	sound.setBuffer(sb);
}

void Bullet::activate()
{
	GameObject::activate();
	sound.play();
}
