#include "stdafx.h"
#include "ContentManager.h"
#include "Enemy.h"
#include "game.h"
#include "EnemyAnimation.h"

const float Enemy::SPEED = 15.0f;
const float Enemy::MAX_RECOIL = 1000.0f;
const int Enemy::NB_BULLET = 50;
const int Enemy::SCORE = 1000;

Enemy::Enemy() :
    hasSpawned(false), recoil(MAX_RECOIL), health(3)
{

}
Enemy::Enemy(const Enemy& src)
    : AnimatedGameObject(src), hasSpawned(false), recoil(MAX_RECOIL), health(3)
{
    init(*contentManager);
}


int Enemy::dies()
{
    sound.setVolume(100);
    sound.play();
    return SCORE;
}

bool Enemy::init(const ContentManager& contentManager)
{
    sound.setBuffer(contentManager.getEnemyKilledSoundBuffer());

    //setTexture(contentManager.getEnemiesTexture());
    //setTextureRect(sf::IntRect(28, 917, 65, 96));

    bool retval = addAnimation<State::STANDARD_ENEMY, EnemyAnimation>(contentManager);
    currentState = State::STANDARD_ENEMY;

    //liste de Bullets
    for (int i = 0; i < NB_BULLET; i++)
    {
        EnemyBullet newBullet;
        newBullet.initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0), contentManager.getEnemyGunSoundBuffer());
        bullets.push_back(newBullet);
    }


    return retval && AnimatedGameObject::init(contentManager);
}

bool Enemy::update(const float DELTA_TIME, const Inputs& inputs)
{
    for (EnemyBullet& b : bullets)
    {
        if (b.isActive())
        {
            b.update(DELTA_TIME);
        }
    }

    recoil -= DELTA_TIME;
    if (recoil <= 0)
    {
      if (isActive()) {
        fireBullet();
        recoil = MAX_RECOIL;
      }
    }

    move(0, SPEED * DELTA_TIME);
    if (getPosition().y > Game::GAME_HEIGHT + 500)
    {
       setPosition(getPosition().x, -100);
    }

    return AnimatedGameObject::update(DELTA_TIME, inputs);
}

void Enemy::draw(sf::RenderWindow& window) const
{
    AnimatedGameObject::draw(window);

    for (const EnemyBullet& b : bullets)
    {
        if (b.isActive())
        {
            b.draw(window);
        }
    }

}

void Enemy::spawn()
{
    activate();
    hasSpawned = true;
    int positionX = (rand() % (Game::GAME_WIDTH - 50)) + 25;
    int positionY = Game::GAME_HEIGHT / 2;
    setPosition(positionX, -positionY);
}

bool Enemy::hasBeenSpawned()
{
    return hasSpawned;
}

void Enemy::fireBullet()
{
    EnemyBullet& bullet = getAvailableBullet();
    bullet.activate();
    bullet.setPosition(getPosition());
}

EnemyBullet& Enemy::getAvailableBullet()
{
    for (EnemyBullet& b : bullets)
    {
        if (!b.isActive())
        {
            b.activate();
            return b;
        }
    }
    return bullets.front();
}

void Enemy::damage()
{
    health--;
    if (health <= 0)
    {
        dies();
        deactivate();
    }
}

int Enemy::getHealth()
{
    return health;
}
