#include "stdafx.h"
#include "BossEnemyAnimation.h"
#include "ContentManager.h"

const float BossEnemyAnimation::ANIMATION_LENGTH = 1.5f;

BossEnemyAnimation::BossEnemyAnimation(sf::Sprite& s)
	: CyclicAnimation(s, ANIMATION_LENGTH, true)
{
}

bool BossEnemyAnimation::init(const ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getEnemiesTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(32, 1905, 84, 124)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(133, 1905, 82, 126)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(232, 1905, 76, 139)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(329, 1905, 74, 143)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(426, 1905, 74, 147)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(522, 1905, 72, 147)));
	return true;
}
