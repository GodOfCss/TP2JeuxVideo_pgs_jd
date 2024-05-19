#pragma once
#include "AnimatedGameObject.h"
#include "EnemyBullet.h"
class Enemy :
	public AnimatedGameObject
{
	static const float SPEED;
	static const float MAX_RECOIL;
	static const int NB_BULLET;
	static const int SCORE;

public:
	Enemy();
	Enemy(const Enemy& src);
	virtual bool init(const ContentManager& contentManager) override;
	bool update(const float DELTA_TIME, const Inputs& inputs) override;
	void draw(sf::RenderWindow& window) const;
	void spawn();
	int dies();
	bool hasBeenSpawned();
	void fireBullet();
	EnemyBullet& getAvailableBullet();

	void damage();
	int getHealth();

private:
	sf::Sound sound;
	bool hasSpawned;

	std::list<EnemyBullet> bullets;
	int recoil;
	int health;
};