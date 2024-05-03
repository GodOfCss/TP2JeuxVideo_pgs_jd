#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Inputs.h"
class LeaderboardScene : 
  public Scene
{
  public:
    LeaderboardScene();
    ~LeaderboardScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;

    virtual void pause() override;
    virtual void unPause() override;

  private:

    sf::Texture menuImageTexture;
    sf::Sprite menuImage;

    sf::Text leaderboardText;
    sf::Text quitGameText;

    Inputs inputs;

    sf::Music leaderboardMusic;

    ContentManager contentManager;
};

