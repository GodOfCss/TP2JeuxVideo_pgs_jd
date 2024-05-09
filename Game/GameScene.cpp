#include "stdafx.h"
#include "GameScene.h"

#include "game.h"
#include <iostream>

const unsigned int GameScene::BACKGROUND_SPEED = 10;
const unsigned int GameScene::AMOUNT_OF_LIVES = 5;
const unsigned int GameScene::HUD_HEIGHT = Game::GAME_HEIGHT / 13 * 12;

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE), background(sf::Sprite()), backgroundPosition(0), lives(AMOUNT_OF_LIVES), score(0)
{

}

GameScene::~GameScene()
{

}


SceneType GameScene::update()
{
    backgroundPosition -= BACKGROUND_SPEED;
    background.setTextureRect(sf::IntRect(0, backgroundPosition, background.getTextureRect().width, background.getTextureRect().height));
    scoreText.setString("Score: " + std::to_string(score));

    player.update(1.0f / (float)Game::FRAME_RATE, inputs);
    //std::cout << 'X: ' << std::to_string(inputs.moveFactorX);
    //std::cout << 'Y: ' << std::to_string(inputs.moveFactorY);
    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(background);
    window.draw(player);



    window.draw(scoreText);
    for (int i = 0; i < lives; i++)
    {
        window.draw(livesRender.at(lives - (i+1)));
    }
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
    scoreText.setPosition(10, HUD_HEIGHT);

    //Lives
    for (int i = 0; i < AMOUNT_OF_LIVES; i++)
    {
        sf::Sprite life;
        life.setTexture(contentManager.getMainCharacterTexture());
        life.setTextureRect(sf::IntRect(270, 47, 22, 28));
        life.setScale(2.0f,2.0f);
        life.setPosition(Game::GAME_WIDTH - (50 + i * 50), HUD_HEIGHT);
        livesRender.push_back(life);
    }

    //Player
    inputs.reset();
    player.init(contentManager);

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

    inputs.moveFactorY = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? 100.0f : 0.0f;
    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -100.0f : 0.0f;
    inputs.moveFactorX = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? 100.0f : 0.0f;
    inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? -100.0f : 0.0f;

    return retval;

}
