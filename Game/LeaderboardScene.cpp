#include "stdafx.h"
#include "LeaderboardScene.h"
#include <iostream>
#include <fstream>
#include "game.h"

LeaderboardScene::LeaderboardScene()
  : Scene(SceneType::LEADERBOARD_SCENE)
  , finalScore(1400508)
  , nameEntered(false)
  , name("")

{
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

  playerName.setString(name);

  return retval;
}

std::string LeaderboardScene::tableSort(PlayerStats stats[NB_STATS]) {
  std::string table = "Name\tScore\n\n";
  char buffer[32];

  std::sort(stats, stats + NB_STATS, [](const PlayerStats& a, const PlayerStats& b) {
    return a.score > b.score;
  });

  for (int i = 0; i < NB_STATS; i++) {
    if (stats[i].score != 0) {
      snprintf(buffer, sizeof(buffer), "%-3s\t%07d\n", stats[i].name, stats[i].score);
      table += buffer;
      //table += stats[i].name;
      //table += "\t";
      //table += std::to_string(stats[i].score);
      //table += "\n";
    }
  }

  return table;
}



void LeaderboardScene::draw(sf::RenderWindow& window) const
{
  window.draw(leaderboardText);
  window.draw(scoreLeaderboardText);
  window.draw(returnToMainMenuText);
  if(!nameEntered)
    window.draw(playerName);
}

void LeaderboardScene::pause()
{
  leaderboardMusic.pause();
}

void LeaderboardScene::unPause()
{
  leaderboardMusic.play();
}

bool LeaderboardScene::init() {
  if (contentManager.loadContent() == false)
    return false;

  if (!leaderboardMusic.openFromFile("Assets\\Music\\Leaderboard\\Leaderboard theme.ogg"))
    return false;
  leaderboardMusic.setLoop(true);
  leaderboardMusic.play();

  const std::string leaderBoardEndText = "Leaderboard";
  leaderboardText.setFont(contentManager.getMainFont());
  leaderboardText.setCharacterSize(30);
  leaderboardText.setString(leaderBoardEndText);
  leaderboardText.setPosition(Game::GAME_WIDTH / 2 - leaderboardText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2 - 400);

  readFromFile("leaderboard.bin", outStats);

  if (finalScore > inStats[NB_STATS - 1].score) {
    updateTemporaryScore();
  }

  if (writeToFile("leaderboard.bin", outStats)) {
    if (readFromFile("leaderboard.bin", inStats)) {
      if (0 == ::memcmp(outStats, inStats, NB_STATS * sizeof(PlayerStats))) {
        std::cout << "La deserialisation est similaire à la serialisation" << std::endl;
      }
      else {
        std::cout << "Il y a eu un problème" << std::endl;
      }
    }
  }

  const std::string leaderboardTextScore = tableSort(inStats);
  scoreLeaderboardText.setFont(contentManager.getMainFont());
  scoreLeaderboardText.setCharacterSize(30);
  scoreLeaderboardText.setString(leaderboardTextScore);
  scoreLeaderboardText.setPosition(Game::GAME_WIDTH / 2 - scoreLeaderboardText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2 - 250);

  const std::string returnToMainText = "Appuyer sur Escape pour le menu principal";
  returnToMainMenuText.setFont(contentManager.getMainFont());
  returnToMainMenuText.setCharacterSize(15);
  returnToMainMenuText.setString(returnToMainText);
  returnToMainMenuText.setPosition(Game::GAME_WIDTH / 2 - returnToMainMenuText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2 + 400);

  return true;
}


bool LeaderboardScene::uninit()
{
  return true;
}


bool LeaderboardScene::handleEvents(sf::RenderWindow& window) {
  bool retval = false;
  sf::Event event;
  inputs.reset();

  while (window.pollEvent(event)) {
    
    if (event.type == sf::Event::Closed) {
      window.close();
      retval = true;
    }
    else if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) {
        inputs.returnToMainMenuSwitch = true;
      }
    }
    else if (event.type == sf::Event::TextEntered && !nameEntered) {
      if (event.text.unicode < 128) {
        char enteredChar = static_cast<char>(event.text.unicode);
        if (enteredChar == '\b') { 
          if (!name.empty()) {
            name.pop_back();
          }
        }
        else if (enteredChar == '\r') { 
          nameEntered = true;
        }
        else {
          if (name.length() <= 2) {
            name += enteredChar;
          }
        }
        playerName.setString(name);

        PlayerStats tempStats[NB_STATS];
        memcpy(tempStats, inStats, sizeof(PlayerStats) * NB_STATS);
        writeScore(tempStats, finalScore, name.empty() ? "---" : name);
      }
    }
  }
  draw(window);
  return retval;
}



void LeaderboardScene::fillWithRandomStats(PlayerStats stats[NB_STATS])
{
  srand((unsigned)time(nullptr));
  std::string randomNames[] = { "Bob", "Joe", "Ike", "Sam", "Zea", "Kin", "Mis", "Col", "Mat", "Tom" };

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


void LeaderboardScene::writeScore(PlayerStats stats[NB_STATS], int score, const std::string& playerName) {
  finalScore = score;

  for (int i = 0; i < NB_STATS; ++i) {
    if (finalScore > stats[i].score) {
      for (int j = NB_STATS - 1; j > i; --j) {
        stats[j] = stats[j - 1];
      }
      stats[i].score = finalScore;
      snprintf(stats[i].name, sizeof(stats[i].name), "%s", playerName.c_str());
      break;
    }
  }

  const std::string leaderboardTextScore = tableSort(stats);
  scoreLeaderboardText.setString(leaderboardTextScore);
  writeToFile("leaderboard.bin", stats);
}



void LeaderboardScene::updateTemporaryScore() {
  PlayerStats tempStats[NB_STATS];
  memcpy(tempStats, inStats, sizeof(PlayerStats) * NB_STATS);
  writeScore(tempStats, finalScore, "---");
}