#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Player.h"
#include "Inputs.h"
class GameScene :
    public Scene
{
public:
    static const unsigned int BACKGROUND_SPEED;
    static const unsigned int AMOUNT_OF_LIVES;
    static const unsigned int HUD_HEIGHT;

    // Héritées via Scene
    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    ContentManager contentManager;

    sf::Sprite background;
    sf::Music gameMusic;
    int backgroundPosition;

    sf::Text scoreText;
    std::vector<sf::Sprite> livesRender;
    int lives;
    int score;

    Player player;
    Inputs inputs;

};