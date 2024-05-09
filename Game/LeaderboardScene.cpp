#include "stdafx.h"
#include "LeaderboardScene.h"
#include <iostream>
#include <fstream>
#include "game.h"

LeaderboardScene::LeaderboardScene()
  : Scene(SceneType::LEADERBOARD_SCENE)
{
  fillWithRandomStats(outStats);
  for (int i = 0; i < NB_STATS; i++)
  {
    inStats[i].score = 0;
    inStats[i].name[0] = '\0';
    outStats[i].score = 0;
    outStats[i].name[0] = '\0';
  }
}

LeaderboardScene::~LeaderboardScene()
{
}

SceneType LeaderboardScene::update()
{
  SceneType retval = getSceneType();

  if (inputs.returnToMainMenuSwitch) {
    return SceneType::NONE;
  }

  return retval;
}


void LeaderboardScene::draw(sf::RenderWindow& window) const
{
  window.draw(leaderboardText);
}

void LeaderboardScene::pause()
{
  leaderboardMusic.pause();
}

void LeaderboardScene::unPause()
{
  leaderboardMusic.play();
}

bool LeaderboardScene::init()
{
  if (contentManager.loadContent() == false)
    return false;

  if (!leaderboardMusic.openFromFile("Assets\\Music\\Leaderboard\\Leaderboard theme.ogg"))
    return false;
  leaderboardMusic.setLoop(true);
  leaderboardMusic.play();

  const std::string leaderBoardEndText = "Leaderboard text";
  leaderboardText.setFont(contentManager.getMainFont());
  leaderboardText.setCharacterSize(15);
  leaderboardText.setString(leaderBoardEndText);
  leaderboardText.setPosition(Game::GAME_WIDTH / 2 - leaderboardText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2);

  return true;
}

bool LeaderboardScene::uninit()
{
  return true;
}

bool LeaderboardScene::handleEvents(sf::RenderWindow& window)
{
  bool retval = false;
  sf::Event event;
  inputs.reset();
  while (window.pollEvent(event))
  {
    //x sur la fenêtre
    if (event.type == sf::Event::Closed)
    {
      window.close();
      retval = true;
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape) {
          inputs.returnToMainMenuSwitch = true;
        }
      }
    }
  }
  return retval;

}

void LeaderboardScene::fillWithRandomStats(PlayerStats stats[NB_STATS])
{
  srand((unsigned)time(nullptr));
  std::string randomNames[] = { "Bob", "Joe", "Luke", "Darth", "Leia", "Anakin", "Aragon", "Cole", "Jack", "Tom" };

  for (int i = 0; i < NB_STATS; i++)
  {
     sprintf_s(stats[i].name, "%s", randomNames[rand()%(sizeof(randomNames)/sizeof(randomNames[0]))].c_str());
     stats[i].score = 1000000 + rand()%1000;
  }
}

bool LeaderboardScene::writeToFile(const std::string& path, const PlayerStats stats[NB_STATS])
{
  std::ofstream ofs(path, std::ios::binary);
  if(!ofs)
    return false;
  ofs.write((char*)stats, sizeof(PlayerStats)*NB_STATS);
  ofs.close();
  return true;
}

bool LeaderboardScene::readFromFile(const std::string& path, PlayerStats stats[NB_STATS])
{
  std::ifstream ifs(path, std::ios::binary);
  if(!ifs)
    return false;
  ifs.read((char*)stats, sizeof(PlayerStats)*NB_STATS);
  ifs.close();
  return true;
}