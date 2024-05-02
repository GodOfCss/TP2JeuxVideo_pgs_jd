#include "stdafx.h"
#include "GameScene.h"

#include "game.h"

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE)
{

}

GameScene::~GameScene()
{

}
SceneType GameScene::update()
{
    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(menuImage);
}

bool GameScene::init()
{
    if (!menuImageTexture.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
        return false;
    menuImage.setTexture(menuImageTexture);
    menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
    menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

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
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
    }
    return retval;

}
