#pragma once
#include "InputBasedAnimation.h"

class ShipAnimation :
	public InputBasedAnimation
{
public:
	ShipAnimation(sf::Sprite& s);
	bool init(const ContentManager& contentManager) override;
	void adjustNextFrame(const Inputs& inputs) override;

private:
};