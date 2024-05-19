#include "stdafx.h"
#include "ContentManager.h"
#include "BossEnemy.h"
#include "game.h"
#include "BossEnemyAnimation.h"

const float BossEnemy::SPEED = 300.0f;
const int BossEnemy::NB_BULLET = 100;
const int BossEnemy::SCORE = 10000;
const int BossEnemy::HP = 20;

BossEnemy::BossEnemy() :
  hasSpawned(false), health(HP)
{
  init(*contentManager);
}

int BossEnemy::dies()
{
  sound.setVolume(100);
  sound.play();
  return SCORE;
}

bool BossEnemy::init(const ContentManager& contentManager)
{
  bool retval = addAnimation<State::BOSS, BossEnemyAnimation>(contentManager);
  currentState = State::BOSS;

  //liste de Bullets
  for (int i = 0; i < NB_BULLET; i++)
  {
    BossEnemyBullet newBullet;
    newBullet.initialize(contentManager.getBulletBossTexture(), sf::Vector2f(0, 0), contentManager.getBossGunSoundBuffer());
    bossBullets.push_back(newBullet);
  }

  return retval && AnimatedGameObject::init(contentManager);
}

bool BossEnemy::update(const float DELTA_TIME, const Inputs& inputs, float playerPosition)
{
  for (BossEnemyBullet& b : bossBullets)
  {
    if (b.isActive())
    {
      b.update(DELTA_TIME);
    }
  }

  const BossEnemyAnimation* animation = (BossEnemyAnimation*)animations[currentState];

  if (animation->getPercentage() > 0.20f && animation->getPercentage() < 0.23f)
  {
    if (isActive()) {
      fireBullet();
    }
  }

  if (getPosition().y < 100)
  {
    move(0, SPEED * DELTA_TIME);
  }
  else
  {
      if (getPosition().x < playerPosition) {
          move(SPEED * DELTA_TIME, 0);
      }
      if (getPosition().x > playerPosition) {
          move(-SPEED * DELTA_TIME, 0);
      }
  }


  return AnimatedGameObject::update(DELTA_TIME, inputs);
}

void BossEnemy::draw(sf::RenderWindow& window) const
{
  AnimatedGameObject::draw(window);

  for (const BossEnemyBullet& b : bossBullets)
  {
    if (b.isActive())
    {
      b.draw(window);
    }
  }

}

void BossEnemy::spawn()
{
  activate();
  hasSpawned = true;
  int positionX = (rand() % (Game::GAME_WIDTH - 100)) + 25;
  int positionY = Game::GAME_HEIGHT / 2;
  setPosition(positionX, -positionY);
}

bool BossEnemy::hasBeenSpawned()
{
  return hasSpawned;
}

void BossEnemy::fireBullet()
{
  BossEnemyBullet& bullet = getAvailableBullet();
  bullet.activate();
  bullet.setPosition(getPosition());
}

BossEnemyBullet& BossEnemy::getAvailableBullet()
{
  for (BossEnemyBullet& b : bossBullets)
  {
    if (!b.isActive())
    {
      b.activate();
      return b;
    }
  }
  return bossBullets.front();
}

void BossEnemy::damage()
{
  health--;
  if (health <= 0)
  {
    dies();
    deactivate();
  }
}

int BossEnemy::getHealth()
{
  return health;
}

float BossEnemy::getHealthPercentage()
{
    return (float)health / (float)HP * 100.0f;
}

std::list<BossEnemyBullet> BossEnemy::getBullets() {
  return bossBullets;
}
