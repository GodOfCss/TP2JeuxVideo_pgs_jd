#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
	static const float BULLET_SPEED;
	static const float TIME_TO_LIVE;
public:
	Bullet(const sf::Vector2f& initialPosition = sf::Vector2f(0, 0));
	Bullet(const Bullet& src);
	virtual bool update(const float elapsedTime, const ContentManager& contentManager);
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition, const sf::SoundBuffer& sb);
	void activate() override;
	void draw(sf::RenderWindow& window) const;

protected:
	sf::Sound sound;

private:
	Bullet& operator=(const Bullet& rhs);
	bool isSpecialBullet;
};