#include "stdafx.h"
#include "EnemyAnimation.h"
#include "ContentManager.h"

const float EnemyAnimation::ANIMATION_LENGTH = 1.3f;

EnemyAnimation::EnemyAnimation(sf::Sprite& s)
	: CyclicAnimation(s, ANIMATION_LENGTH, true)
{
}

bool EnemyAnimation::init(const ContentManager& contentManager)
{
	const sf::Texture& texture = contentManager.getEnemiesTexture();
	frames.push_back(AnimationFrame(texture, sf::IntRect(28, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(101, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(174, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(247, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(320, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(393, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(466, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(539, 917, 65, 96)));
	frames.push_back(AnimationFrame(texture, sf::IntRect(612, 917, 65, 96)));
	return true;
}
