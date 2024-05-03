#include "stdafx.h"
#include "LeaderboardScene.h"
#include "game.h"
#include "Inputs.h"
#include "ContentManager.h"

LeaderboardScene::LeaderboardScene() 
: Scene(SceneType::LEADERBOARD_SCENE)
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

  return retval;
}

void LeaderboardScene::draw(sf::RenderWindow& window) const
{
  //window.draw(menuImage);
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

  const std::string startGameTextString = "This is the leaderboard";
  leaderboardText.setFont(contentManager.getMainFont());
  leaderboardText.setCharacterSize(15);
  leaderboardText.setString(startGameTextString);
  leaderboardText.setPosition(Game::GAME_WIDTH / 2 - leaderboardText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2);

  return true;
}

bool LeaderboardScene::uninit()
{
  return true;
}


bool LeaderboardScene::handleEvents(sf::RenderWindow& window)
{
  inputs.reset();
  bool retval = false;
  sf::Event event;
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
      if (event.key.code == sf::Keyboard::Escape)
      {
        inputs.returnToMainMenuSwitch = true;
      }
    }
    if (sf::Joystick::isConnected(0))
    {
      if (sf::Joystick::isButtonPressed(0, 1))
      {
        inputs.returnToMainMenuSwitch = true;
      }
    }
  }
  return retval;
}