#pragma once
#include "CyclicAnimation.h"

class EnemyAnimation :
	public CyclicAnimation
{
	static const float ANIMATION_LENGTH;
public:
	EnemyAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;

private:
};