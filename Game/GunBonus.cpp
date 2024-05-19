#include "stdafx.h"
#include "GunBonus.h"
#include "ContentManager.h"
#include "game.h"

GunBonus::GunBonus(const sf::Vector2f& initialPosition)
  : GameObject()
{
  setPosition(initialPosition);
  setScale(3, 3);
}


GunBonus::GunBonus(const GunBonus& src)
  :GameObject(src)
{
  initialize(*src.getTexture(), src.getPosition());
}

bool GunBonus::init(const ContentManager& contentManager, const sf::Vector2f& initialPosition)
{
  GameObject::initialize(contentManager.getGunBonusTexture(), initialPosition);

  sound.setBuffer(contentManager.getGunBonusSoundBuffer());

  return false;
}

void GunBonus::draw(sf::RenderWindow& window) const
{
  if (isActive())
    window.draw(*this);
}

void GunBonus::playSound()
{
  sound.play();
}

void GunBonus::spawn(const sf::Vector2f& enemyPosition)
{
  setPosition(enemyPosition);
}

void GunBonus::move(float x, float y)
{
  GameObject::move(x, y);
}
