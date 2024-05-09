#include "stdafx.h"
#include "LeaderboardScene.h"
#include <iostream>
#include <fstream>

LeaderboardScene::LeaderboardScene()
  : Scene(SceneType::LEADERBOARD_SCENE)
{
  fillWithRandomStats(outStats);
  for (int i = 0; i < NB_STATS; i++)
  {
    std::cout << inStats[i].name << " " << inStats[i].score << std::endl;
  }
}

LeaderboardScene::~LeaderboardScene()
{
}

SceneType LeaderboardScene::update()
{
  return SceneType();
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