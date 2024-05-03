#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Inputs.h"
class GameScene :
    public Scene
{
public:
    static const unsigned int BACKGROUND_SPEED;

    // Héritées via Scene
    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;

    virtual void pause() override;
    virtual void unPause() override;
private:
    ContentManager contentManager;
    sf::Sprite background;
    sf::Music gameMusic;
    int backgroundPosition;

    bool hasStarted;
    Inputs inputs;
};