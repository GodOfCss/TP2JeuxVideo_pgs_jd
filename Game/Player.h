#pragma once
#include "AnimatedGameObject.h"
struct Inputs;
class Player :
    public AnimatedGameObject
{
    static const float PLAYER_SPEED;
    static const float BORDER_THICKNESS;
    static const float MAX_INVINCIBLE;

public:
    Player();
    virtual bool init(const ContentManager& contentManager) override;

    bool update(float deltaT, const Inputs& inputs) override;
    sf::Vector2f normalizeMovement(const sf::Vector2f& playerMovement);
    void isHit();

    bool isPlayerInvincible();

    float invincible;

    int bonusCount;
};