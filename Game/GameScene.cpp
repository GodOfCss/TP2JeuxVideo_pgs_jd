#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include <iostream>

const unsigned int GameScene::BACKGROUND_SPEED = 10;
const unsigned int GameScene::AMOUNT_OF_LIVES = 5;
const unsigned int GameScene::NB_BULLETS = 15;
const unsigned int GameScene::NB_ENEMIES = 15;
const unsigned int GameScene::MAX_BONUSES = 5;
const unsigned int GameScene::HUD_HEIGHT = Game::GAME_HEIGHT / 13 * 12;
const unsigned int GameScene::MAX_RECOIL = 20;
const double GameScene::BONUS_PCT = 0.10;
const double GameScene::BONUS_50 = 0.50;

GameScene::GameScene()
    : Scene(SceneType::GAME_SCENE), background(sf::Sprite()), backgroundPosition(0), lives(AMOUNT_OF_LIVES), score(0), recoil(0), spawnCooldown(0)
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

    if (inputs.fireBullet) 
    {
       fireBullet();
    }
    if (recoil > 0) 
    {
        recoil--;
    }
    if (spawnCooldown > 0) 
    {
        spawnCooldown -= 1.0f / (float)Game::FRAME_RATE;
    }
    else 
    {
        spawnCooldown = 0;
    }

    for (Bullet& b : bullets)
    {
        sf::Vector2f bulletPos = b.getPosition();

        if (b.isActive())
        {
            if (b.update(1.0f / (float)Game::FRAME_RATE, contentManager))
            {
                b.deactivate();
            }
        }

        for (Enemy& e : enemies)
        {
            if (isEnemyAvailable(e) && spawnCooldown == 0) {
                e.spawn();
                spawnCooldown = 200.0f;
            }
            e.update(1.0f / (float)Game::FRAME_RATE, inputs);
            
            //Bullets colliding with enemies + score
            if (b.collidesWith(e))
            {
              b.deactivate();
              e.damage();
              if (e.getHealth() == 0) {
                score += e.dies();

                double bonusNumber = bonusRate.nextDouble();

                if (bonusNumber > BONUS_PCT) {
                  spawnBonus(e.getPosition());
                }
              }
            }
        }
    }

    for (GunBonus& b : gunBonuses)
    {
      if (b.isActive())
        b.move(0, 150.0f / (float)Game::FRAME_RATE);
        if (b.getPosition().y > Game::GAME_HEIGHT)
        {
          b.deactivate();
        }
     
        b.update(1.0f / (float)Game::FRAME_RATE, inputs);
        if (b.collidesWith(player))
        {
         /* b.playSound();*/
          b.deactivate();
          score += 5000;
         /* player.upgradeGun();*/
        }
    }

    for (HealthBonus& b : healthBonuses)
    {
      if (b.isActive())
        b.move(0, 150.0f / (float)Game::FRAME_RATE);
      if (b.getPosition().y > Game::GAME_HEIGHT)
      {
        b.deactivate();
      }

      b.update(1.0f / (float)Game::FRAME_RATE, inputs);
      if (b.collidesWith(player))
      {
        //b.playSound();
        if (lives < AMOUNT_OF_LIVES) {
          lives += 1;
        }
        b.deactivate();
        score += 5000;
      }
    }
  


    //std::cout << 'X: ' << std::to_string(inputs.moveFactorX);
    //std::cout << 'Y: ' << std::to_string(inputs.moveFactorY);
    return getSceneType();
}


void GameScene::fireBullet()
{
    Bullet& b = getAvailableBullet();
    b.setPosition(player.getPosition());
    inputs.fireBullet = false;
    recoil = MAX_RECOIL;
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(background);
    window.draw(scoreText);

    for (int i = 0; i < lives; i++)
    {
        window.draw(livesRender.at(lives - (i+1)));
    }

    for (const Bullet& b : bullets)
    {
        if (b.isActive())
        {
            b.draw(window);
        }
    }

    for (const Enemy& e : enemies)
    {
        e.draw(window);
    }

    for (const GunBonus& b : gunBonuses)
    {
      if (b.isActive()) {
          b.draw(window);
      }
    } 

    for (const HealthBonus& b : healthBonuses)
    {
      if (b.isActive())
      {
            b.draw(window);
        }
    }

    window.draw(player);
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

    //liste de Bullets
    for (int i = 0; i < NB_BULLETS; i++)
    {
        Bullet newBullet;
        newBullet.initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0), contentManager.getPlayerGunSoundBuffer());
        bullets.push_back(newBullet);
    }
    
    //Liste d'enemies
    for (int i = 0; i < NB_ENEMIES; i++)
    {
        Enemy newEnemy;
        newEnemy.init(contentManager);
        enemies.push_back(newEnemy);
    }

    //Liste de Bonus
    for (int i = 0; i < MAX_BONUSES; i++)
    {
        GunBonus newBonus;
        newBonus.init(contentManager, sf::Vector2f(0, 0));
        gunBonuses.push_back(newBonus);
    }

    for (int i = 0; i < MAX_BONUSES; i++)
    {
      HealthBonus newBonus;
      newBonus.init(contentManager, sf::Vector2f(0, 0));
      healthBonuses.push_back(newBonus);
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
    inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (recoil == 0);

    return retval;

}

Bullet& GameScene::getAvailableBullet()
{
    for (Bullet& b : bullets)
    {
        if (!b.isActive())
        {
            b.activate();
            return b;
        }
    }
    // Tous les projectiles sont déjà utilisés: on en crée ... au moins au autre pour nos besoins.
    // On pourrait ajouter plus d'un Bullet ici
    Bullet newBullet;
    newBullet.initialize(contentManager.getMiscTexture(), sf::Vector2f(0, 0), contentManager.getPlayerGunSoundBuffer());
    bullets.push_back(newBullet);
    Bullet& b = bullets.back();
    b.activate();
    return b;
}


void GameScene::spawnBonus(sf::Vector2f enemyPosition)
{
  double fiftyPercentRate = bonusType.nextDouble();

  if (fiftyPercentRate > BONUS_PCT) {
    HealthBonus& healthBonus = getAvailableHealthBonus();
    healthBonus.spawn(enemyPosition);
  }
  else
  {
    GunBonus& gunBonus = getAvailableGunBonus();
    gunBonus.spawn(enemyPosition);
  }

}

GunBonus& GameScene::getAvailableGunBonus()
{
  for (GunBonus& b : gunBonuses)
  {
    if (!b.isActive())
    {
      b.activate();
      return b;
    }
  }

  GunBonus newGunBonus;
  newGunBonus.init(contentManager, sf::Vector2f(0, 0));
  gunBonuses.push_back(newGunBonus);
  GunBonus& b = gunBonuses.back();
  b.activate();
  return b;
}

HealthBonus& GameScene::getAvailableHealthBonus()
{
  for (HealthBonus& b : healthBonuses)
  {
    if (!b.isActive())
    {
      b.activate();
      return b;
    }
  }

  HealthBonus newHealthBonus;
  newHealthBonus.init(contentManager, sf::Vector2f(0, 0));
  healthBonuses.push_back(newHealthBonus);
  HealthBonus& b = healthBonuses.back();
  b.activate();
  return b;
}

bool GameScene::isEnemyAvailable(Enemy& e)
{
    if (e.isActive() || e.hasBeenSpawned())
    {
        return false;
    }

    return true;
}
