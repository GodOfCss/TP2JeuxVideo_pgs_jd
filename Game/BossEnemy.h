#pragma once
#include "AnimatedGameObject.h"
#include "BossEnemyBullet.h"
class BossEnemy :
	public AnimatedGameObject
{
	static const float SPEED;
	static const int NB_BULLET;
	static const int SCORE;
	static const int HP;

public:
	BossEnemy();
	virtual bool init(const ContentManager& contentManager) override;
	bool update(const float DELTA_TIME, const Inputs& inputs, float playerPosition);
	void draw(sf::RenderWindow& window) const;
	void spawn();
	int dies();
	bool hasBeenSpawned();
	float getHealthPercentage();
	void fireBullet();
	BossEnemyBullet& getAvailableBullet();

	std::list<BossEnemyBullet> getBullets();

	void damage();
	int getHealth();

private:
	sf::Sound sound;
	bool hasSpawned;

	std::list<BossEnemyBullet> bossBullets;
	int health;

	
};
