#include "stdafx.h"
#include "GameScene.h"

#include "game.h"

const unsigned int GameScene::BACKGROUND_SPEED = 10;

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE), background(sf::Sprite()), backgroundPosition(0)
{

}

GameScene::~GameScene()
{

}


SceneType GameScene::update()
{
    backgroundPosition -= BACKGROUND_SPEED;
    background.setTextureRect(sf::IntRect(0, backgroundPosition, background.getTextureRect().width, background.getTextureRect().height));

    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(background);
    window.draw(scoreText);
}

bool GameScene::init()
{
    // Chargement des ressources
    if (contentManager.loadContent() == false)
    {
        return false;
    }

    if (!gameMusic.openFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg"))
    {
        return false;
    }

    // Arrière-plan
    background.setTexture(contentManager.getBackgroundTexture());

    // Musique
    gameMusic.setLoop(true);
    gameMusic.play();

    // HUD

    scoreText.setFont(contentManager.getMainFont());
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::Cyan);
    scoreText.setOutlineThickness(4);
    scoreText.setOutlineColor(sf::Color::White);
    scoreText.setString("Score : 0");
    scoreText.setPosition(10, Game::GAME_HEIGHT / 9 * 8);

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
