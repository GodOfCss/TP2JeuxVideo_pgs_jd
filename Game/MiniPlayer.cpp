#include "stdafx.h"
#include "MiniPlayer.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"
#include <iostream>


const float MiniPlayer::PLAYER_SPEED = 400.0f;


MiniPlayer::MiniPlayer()
{
}

bool MiniPlayer::init(const ContentManager& contentManager)
{
	GameObject::initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0,0));
	setPosition(sf::Vector2f(100.0f, Game::GAME_HEIGHT * 0.5f));
	setTextureRect(sf::IntRect(270, 46, 23, 30));
	return true;
}

bool MiniPlayer::update(float deltaT, const sf::Vector2f playerPosition)
{
	int xDirection = 1;
	int yDirection = 1;
	
	std::cout << getPosition().x;
	std::cout << "\n PLAYER: ";
	std::cout << playerPosition.x;
	std::cout << "\n MINI: ";

	if (playerPosition.y + 150 < getPosition().y)
	{
		yDirection = -1;
	}

	if (playerPosition.x + 290 < getPosition().x)
	{
		xDirection = -1;
	}

	if ((playerPosition.x + 290) - getPosition().x < 10 && (playerPosition.x + 290) - getPosition().x > -10) {
		xDirection = 0;
	}

	if ((playerPosition.y + 150) - getPosition().y < 10 && (playerPosition.y + 150) - getPosition().y > -10) {
		yDirection = 0;
	}

	move(xDirection * PLAYER_SPEED * deltaT, yDirection * deltaT * PLAYER_SPEED);
	return GameObject::update(deltaT);
}
