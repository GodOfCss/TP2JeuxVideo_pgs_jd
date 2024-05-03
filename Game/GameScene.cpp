#include "stdafx.h"
#include "GameScene.h"

#include "game.h"

const unsigned int GameScene::BACKGROUND_SPEED = 10;

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE)
    , background(sf::Sprite())
    , backgroundPosition(0)
    , hasStarted(false)
{

}

GameScene::~GameScene()
{

}


SceneType GameScene::update()
{
    SceneType retval = getSceneType();

    if (hasStarted) {
      retval = SceneType::NONE;
      return retval;
    }
    
    if (inputs.goToLeaderboardSwitch) {
      hasStarted = true;
      retval = SceneType::LEADERBOARD_SCENE;
      return retval;
    }

    backgroundPosition += BACKGROUND_SPEED;
    background.setTextureRect(sf::IntRect(0, backgroundPosition, background.getTextureRect().width, background.getTextureRect().height));

    return retval;
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(background);
}

void GameScene::pause()
{
  gameMusic.pause();
}

void GameScene::unPause()
{
  gameMusic.play();
}

bool GameScene::init()
{
    // Chargement des ressources
    if (contentManager.loadContent() == false)
    {
        return false;
    }

    if (!gameMusic.openFromFile("Assets\\Music\\Game\\NiceTryStarFox.ogg"))
    {
        return false;
    }

    // Arrière-plan
    background.setTexture(contentManager.getBackgroundTexture());
    gameMusic.setLoop(true);
    gameMusic.play();

    return true;
}

bool GameScene::uninit()
{
    return true;
}

bool GameScene::handleEvents(sf::RenderWindow& window)
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
        if (event.key.code == sf::Keyboard::BackSpace) //Pour test leaderboard, a modif
        {
          inputs.goToLeaderboardSwitch = true;
        }
    }
    return retval;

}
