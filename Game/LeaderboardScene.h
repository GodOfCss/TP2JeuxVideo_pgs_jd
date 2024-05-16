#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Inputs.h"
#include "PlayerStats.h"
#include <array>


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

    void fillWithRandomStats(PlayerStats stats[NB_STATS]);
    bool writeToFile(const std::string& path, const PlayerStats stats[NB_STATS]);
    bool readFromFile(const std::string& path, PlayerStats stats[NB_STATS]);
    void writeScore(PlayerStats stats[NB_STATS], int score, const std::string& playerName);
    void updateTemporaryScore();

    std::string tableSort(PlayerStats stats[NB_STATS]);

    sf::Text leaderboardText;
    sf::Text scoreLeaderboardText;
    sf::Text returnToMainMenuText;
    sf::Text playerName;
    sf::Music leaderboardMusic;

    Inputs inputs;

    ContentManager contentManager;
    PlayerStats outStats[NB_STATS];
    PlayerStats inStats[NB_STATS];

    int finalScore;
    bool nameEntered;
    std::string name;

};

