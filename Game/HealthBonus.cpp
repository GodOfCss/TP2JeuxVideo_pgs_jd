#include "stdafx.h"
#include "HealthBonus.h"
#include "ContentManager.h"
#include "game.h"

HealthBonus::HealthBonus(const sf::Vector2f& initialPosition)
  : GameObject()
{
  setPosition(initialPosition);
  setScale(3, 3);
}

HealthBonus::HealthBonus(const HealthBonus& src)
  :GameObject(src)
{
  initialize(*src.getTexture(), src.getPosition());
}

bool HealthBonus::init(const ContentManager& contentManager, const sf::Vector2f& initialPosition)
{
  GameObject::initialize(contentManager.getHealthBonusTexture(), initialPosition);

  sound.setBuffer(contentManager.getHealthSoundBuffer());

  return false;
}

void HealthBonus::draw(sf::RenderWindow& window) const
{
  if (isActive())
    window.draw(*this);
}

void HealthBonus::playSound()
{
  sound.setVolume(100);
  sound.play();
}

void HealthBonus::spawn(const sf::Vector2f& enemyPosition)
{
  setPosition(enemyPosition);
}

void HealthBonus::move(float x, float y)
{
  GameObject::move(x, y);
}
