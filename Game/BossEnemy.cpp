#include "stdafx.h"
#include "ContentManager.h"
#include "BossEnemy.h"
#include "game.h"
#include "BossEnemyAnimation.h"

const float BossEnemy::SPEED = 300.0f;
const float BossEnemy::MAX_RECOIL = 1000.0f;
const int BossEnemy::NB_BULLET = 50;
const int BossEnemy::SCORE = 10000;
const int BossEnemy::HP = 20;

BossEnemy::BossEnemy() :
  hasSpawned(false), recoil(MAX_RECOIL), health(HP)
{
  init(*contentManager);
}

//BossEnemy::BossEnemy(const BossEnemy& src)
//  : AnimatedGameObject(src), hasSpawned(false), recoil(MAX_RECOIL), health(HP)
//{
//  init(*contentManager);
//}


int BossEnemy::dies()
{
  sound.setVolume(100);
  sound.play();
  return SCORE;
}

bool BossEnemy::init(const ContentManager& contentManager)
{
  //sound.setBuffer(contentManager.getEnemyKilledSoundBuffer());

  bool retval = addAnimation<State::BOSS, BossEnemyAnimation>(contentManager);
  currentState = State::BOSS;

  //liste de Bullets
  //for (int i = 0; i < NB_BULLET; i++)
  //{
  //  EnemyBullet newBullet;
  //  newBullet.initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0), contentManager.getEnemyGunSoundBuffer());
  //  bullets.push_back(newBullet);
  //}

  return retval && AnimatedGameObject::init(contentManager);
}

bool BossEnemy::update(const float DELTA_TIME, const Inputs& inputs, float playerPosition)
{
  //for (EnemyBullet& b : bullets)
  //{
  //  if (b.isActive())
  //  {
  //    b.update(DELTA_TIME);
  //  }
  //}

  //recoil -= DELTA_TIME;
  //if (recoil <= 0)
  //{
  //  if (isActive()) {
  //    fireBullet();
  //    recoil = MAX_RECOIL;
  //  }
  //}

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

  //for (const EnemyBullet& b : bullets)
  //{
  //  if (b.isActive())
  //  {
  //    b.draw(window);
  //  }
  //}

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

//void BossEnemy::fireBullet()
//{
//  EnemyBullet& bullet = getAvailableBullet();
//  bullet.activate();
//  bullet.setPosition(getPosition());
//}
//
//EnemyBullet& BossEnemy::getAvailableBullet()
//{
//  for (EnemyBullet& b : bullets)
//  {
//    if (!b.isActive())
//    {
//      b.activate();
//      return b;
//    }
//  }
//  return bullets.front();
//}

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
