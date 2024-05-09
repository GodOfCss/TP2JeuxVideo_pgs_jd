#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Inputs.h"
#include "PlayerStats.h"
#define NB_STATS 10
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

    //sf::Texture menuImageTexture;
    //sf::Sprite menuImage;

    sf::Text leaderboardText;
    //sf::Text quitGameText;

    Inputs inputs;

    sf::Music leaderboardMusic;

    PlayerStats outStats[NB_STATS];
    PlayerStats inStats[NB_STATS];

    ContentManager contentManager;
    void fillWithRandomStats(PlayerStats stats[NB_STATS]);
    bool writeToFile(const std::string& path, const PlayerStats stats[NB_STATS]);
    bool readFromFile(const std::string& path, PlayerStats stats[NB_STATS]);
};

