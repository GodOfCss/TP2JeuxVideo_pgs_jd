#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"
#include "Inputs.h"
#include "ContentManager.h"

TitleScene::TitleScene()
  : Scene(SceneType::TITLE_SCENE)
{

}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
  SceneType retval = getSceneType();

  if (inputs.startGameSwitch) {
    return SceneType::GAME_SCENE;
  }
  
  return getSceneType();
}

void TitleScene::draw(sf::RenderWindow& window) const
{
  window.draw(menuImage);
  window.draw(startGameText);
  window.draw(quitGameText);
}

void TitleScene::pause()
{
  titleMusic.pause();
}

void TitleScene::unPause()
{
  titleMusic.play();
}

bool TitleScene::init()
{
  if(contentManager.loadContent() == false)
    return false;

  if(!titleMusic.openFromFile("Assets\\Music\\Title\\SkyFire.ogg"))
    return false;
  titleMusic.setLoop(true);
  titleMusic.play();

  if (!menuImageTexture.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
    return false;
  menuImage.setTexture(menuImageTexture);
  menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
  menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

  const std::string startGameTextString = "Press any button to start the game";
  startGameText.setFont(contentManager.getMainFont());
  startGameText.setCharacterSize(15);
  startGameText.setString(startGameTextString);
  startGameText.setPosition(Game::GAME_WIDTH / 2 - startGameText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2 + 400);

  const std::string quitGameTextString = "Press ESC to quit the game";
  quitGameText.setFont(contentManager.getMainFont());
  quitGameText.setCharacterSize(15);
  quitGameText.setString(quitGameTextString);
  quitGameText.setPosition(Game::GAME_WIDTH / 2 - quitGameText.getLocalBounds().width / 2, Game::GAME_HEIGHT / 2 + 450);

  return true;
}

bool TitleScene::uninit()
{
  return true;
}

bool TitleScene::handleEvents(sf::RenderWindow& window)
{
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
        window.close();
        retval = true;
      }
      else
      {
        inputs.startGameSwitch = true;
      }
    }
  }
  return retval;

}
