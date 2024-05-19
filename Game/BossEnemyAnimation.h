#pragma once
#include "AnimatedGameObject.h"
#include "CyclicAnimation.h"

class BossEnemyAnimation :
	public CyclicAnimation
{
	static const float ANIMATION_LENGTH;
public:
	BossEnemyAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;

private:
};