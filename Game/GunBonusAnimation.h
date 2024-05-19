#pragma once
#include "CyclicAnimation.h"

class GunBonusAnimation :
	public CyclicAnimation
{
	static const float ANIMATION_LENGTH;
public:
	GunBonusAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;

private:
};