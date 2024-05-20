#pragma once
#pragma once
#include "GameObject.h"
struct Inputs;
class MiniPlayer :
    public GameObject
{
    static const float PLAYER_SPEED;
    static const float BORDER_THICKNESS;
    static const float MAX_INVINCIBLE;

public:
    MiniPlayer();
    virtual bool init(const ContentManager& contentManager) override;

    bool update(float deltaT, const sf::Vector2f playerPosition);
};