#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "game.h"
#include "ContentManager.h"
#include "ShipAnimation.h"


const float Player::PLAYER_SPEED = 300.0f;
const float Player::BORDER_THICKNESS = 30;
const float Player::MAX_INVINCIBLE = 3;

Player::Player() :
	invincible(0)
{

}

bool Player::init(const ContentManager& contentManager)
{
	activate();
	setPosition(sf::Vector2f(100.0f, Game::GAME_HEIGHT * 0.5f));
	setScale(2.5f, 2.5f);
	bool retval = addAnimation<State::SHIP, ShipAnimation>(contentManager);
	currentState = State::SHIP;

	// Ne pas oublier de changer la super-classe ici
	return retval && AnimatedGameObject::init(contentManager);
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	if (invincible > 0) 
	{
		invincible-= deltaT;
		setColor(sf::Color(getColor().r, getColor().g, getColor().b, 150));
	}
	else 
	{
		invincible = 0;
		setColor(sf::Color(getColor().r, getColor().g, getColor().b, 255));
	}

	sf::Vector2f playerMovement = normalizeMovement(sf::Vector2f(-inputs.moveFactorX, -inputs.moveFactorY));
	move(playerMovement * deltaT * PLAYER_SPEED);
	
	if (getPosition().y < BORDER_THICKNESS)
	{
		setPosition(getPosition().x, BORDER_THICKNESS);
	}

	if (getPosition().x < BORDER_THICKNESS)
	{
		setPosition(BORDER_THICKNESS, getPosition().y);
	}

	if (getPosition().x > Game::GAME_WIDTH - BORDER_THICKNESS)
	{
		setPosition(Game::GAME_WIDTH - BORDER_THICKNESS, getPosition().y);
	}

	if (getPosition().y > Game::GAME_HEIGHT - BORDER_THICKNESS*6)
	{
		setPosition(getPosition().x, Game::GAME_HEIGHT - BORDER_THICKNESS*6);
	}

	return AnimatedGameObject::update(deltaT, inputs);
}

sf::Vector2f Player::normalizeMovement(const sf::Vector2f& playerMovement)
{
	float vectorLength = sqrt((playerMovement.x * playerMovement.x) + (playerMovement.y * playerMovement.y));
	if (vectorLength != 0)
		return sf::Vector2f(playerMovement.x / vectorLength, playerMovement.y / vectorLength);
	else
		return playerMovement;
}

void Player::isHit()
{
	if (!invincible <= 0)
	{
		invincible = MAX_INVINCIBLE;
	}
}