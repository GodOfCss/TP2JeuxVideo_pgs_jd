#include "stdafx.h"
#include "ShipAnimation.h"
#include "ContentManager.h"
#include "Inputs.h"

ShipAnimation::ShipAnimation(sf::Sprite& s)
	: InputBasedAnimation(s)
{
}

bool ShipAnimation::init(const ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getMainCharacterTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(224, 46, 14, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(300, 48, 18, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(270, 46, 23, 30)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(227, 46, 14, 30)));
	return true;
}

void ShipAnimation::adjustNextFrame(const Inputs& inputs)
{
	if (inputs.moveFactorX > 0)
	{
		nextFrame = 3;
	}
	if (inputs.moveFactorX < 0)
	{
		nextFrame = 1;
	}
	if (inputs.moveFactorX == 0)
	{
		nextFrame = 2;
	}
}