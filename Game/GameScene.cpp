#include "stdafx.h"
#include "GameScene.h"
#include "game.h"
#include "BossEnemy.h"
#include <iostream>
#include "ScoreUnion.h"

const float GameScene::GAMEPAD_SPEEDRATIO = 0.5f;
const unsigned int GameScene::BACKGROUND_SPEED = 10;
const float GameScene::TIME_PER_FRAME = 1.0f / (float)Game::FRAME_RATE;
const unsigned int GameScene::AMOUNT_OF_LIVES = 5;
const unsigned int GameScene::NB_BULLETS = 15;
const unsigned int GameScene::NB_ENEMIES = 1;
const unsigned int GameScene::MAX_BONUSES = 5;
const unsigned int GameScene::HUD_HEIGHT = Game::GAME_HEIGHT / 13 * 12;
const unsigned int GameScene::MAX_RECOIL = 10;
const double GameScene::BONUS_PCT = 0.10;
const double GameScene::BONUS_50 = 0.50;
const int GameScene::CONTROLLER_DEAD_ZONE = 20;

GameScene::GameScene()
 : Scene(SceneType::GAME_SCENE)
 , background(sf::Sprite())
 , backgroundPosition(0)
 , hasStarted(false)
 , lives(AMOUNT_OF_LIVES)
 , score(0)
 , recoil(0)
 , spawnCooldown(0)
 , spawnBoss(false)
 , enemyTotal(NB_ENEMIES)
{
    g_ScoreUnion.score = score;
    g_ScoreUnion.bonusCount = player.bonusCount;
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
      g_ScoreUnion.score = score;
      retval = SceneType::LEADERBOARD_SCENE;
      return retval;
    }

    backgroundPosition -= BACKGROUND_SPEED;
    background.setTextureRect(sf::IntRect(0, backgroundPosition, background.getTextureRect().width, background.getTextureRect().height));
    scoreText.setString("Score: " + std::to_string(score));
    bonusText.setString("Bonus: " + std::to_string(player.bonusCount));

    player.update(TIME_PER_FRAME, inputs);
    boss.update(TIME_PER_FRAME, inputs, player.getPosition().x);
    recoil = std::max(0, recoil - 1);

    if (enemyTotal == 0 && spawnBoss == false)
    {
        boss.spawn();
        spawnBoss = true;
    }

    if (boss.isActive())
    {
        healthBar.setPosition(boss.getPosition().x - 30, boss.getPosition().y - 50);

        float healthBossPercentage = boss.getHealthPercentage();
        
        if (healthBossPercentage > 85) {
            healthBar.setTextureRect(sf::IntRect(13, 126, 82, 20));
        }
        else if (healthBossPercentage > 70) {
            healthBar.setTextureRect(sf::IntRect(13, 102, 82, 20));
        }
        else if (healthBossPercentage > 55) {
            healthBar.setTextureRect(sf::IntRect(13, 78, 82, 20));
        }
        else if (healthBossPercentage > 40) {
            healthBar.setTextureRect(sf::IntRect(13, 54, 82, 20));
        }
        else if (healthBossPercentage > 25) {
            healthBar.setTextureRect(sf::IntRect(13, 30, 82, 20));
        }
        else {
            healthBar.setTextureRect(sf::IntRect(13, 6, 82, 20));
        }
    }

    if (inputs.fireBullet) 
    {
       fireBullet();
    }

    if (spawnCooldown > 0) 
    {
        spawnCooldown -= 1.0f / (float)Game::FRAME_RATE;
    }
    else 
    {
        spawnCooldown = 0;
    }


    for (Enemy& e : enemies)
    {
        if (isEnemyAvailable(e) && spawnCooldown == 0) {
            e.spawn();
            spawnCooldown = 10.0f;
        }

        if (player.collidesWith(e))
        {
            if (!player.isPlayerInvincible())
            {
              if (player.bonusCount > 0) {
                player.bonusCount--;
              }
              else
              {
                player.isHit();
                lives--;
              }
                e.deactivate();
                enemyTotal--;
                if (lives == 0) {
                    hasStarted = true;
                    g_ScoreUnion.score = score;
                    retval = SceneType::TITLE_SCENE;
                    return retval;
                }
            }
        }

        for (EnemyBullet& enemyBullet : e.getBullets())
        {
            if (enemyBullet.collidesWith(player) && !player.isPlayerInvincible())
            {
                enemyBullet.deactivate();
                player.isHit();
                lives--;
                if (lives == 0) {
                    hasStarted = true;
                    g_ScoreUnion.score = score;
                    retval = SceneType::TITLE_SCENE;
                    return retval;
                }
            }
        }

        e.update(1.0f / (float)Game::FRAME_RATE, inputs);
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

            if (boss.isActive() && b.collidesWith(boss))
            {
                b.deactivate();
                boss.damage();
                if (boss.getHealth() <= 0) {
                    hasStarted = true;
                    g_ScoreUnion.score = score;
                    retval = SceneType::LEADERBOARD_SCENE;
                    return retval;
                }
            }

            for (Enemy& e : enemies)
            {
                //Bullets colliding with enemies + score
                if (b.collidesWith(e))
                {
                    b.deactivate();
                    e.damage();
                    if (e.getHealth() == 0)
                    {
                        score += e.dies();
                        enemyTotal--;

                        double bonusNumber = bonusRate.nextDouble();

                        if (bonusNumber > BONUS_PCT)
                        {
                            spawnBonus(e.getPosition());
                        }
                    }
                }
            }
        }
  }

        if (enemyTotal == 0 && spawnBoss == false)
        {
            boss.spawn();
            spawnBoss = true;
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
            player.bonusCount++;
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

      if (player.collidesWith(boss) && !player.isPlayerInvincible())
      {
        player.isHit();
        lives--;
        if (lives == 0) {
          hasStarted = true;
          g_ScoreUnion.score = score;
          retval = SceneType::TITLE_SCENE;
          return retval;
        }
      }
  
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
    window.draw(bonusText);

    for (int i = 0; i < lives; i++)
    {
        window.draw(livesRender.at(lives - (i + 1)));
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

    boss.draw(window);
    if (boss.isActive())
    { 
        window.draw(healthBar);
    }
   
    window.draw(player);
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
    inputs.reset();
    recoil = MAX_RECOIL;

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

    //Boss Bar de vie
    healthBar.setTexture(contentManager.getHealthBarTexture());
    healthBar.setTextureRect(sf::IntRect(13, 126, 82, 20));
    healthBar.setOrigin(sf::Vector2f(healthBar.getLocalBounds().height / 2, healthBar.getLocalBounds().width / 2));

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

    bonusText.setFont(contentManager.getMainFont());
    bonusText.setCharacterSize(20);
    bonusText.setFillColor(sf::Color::Cyan);
    bonusText.setOutlineThickness(4);
    bonusText.setOutlineColor(sf::Color::White);
    bonusText.setString("Bonus : 0");
    bonusText.setPosition(Game::GAME_WIDTH - 230, 30);

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
    player.init(contentManager);

    //Boss
    boss.init(contentManager);

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
    }

    if (sf::Joystick::isConnected(0))
    {
      inputs.moveFactorY = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)) / -GAMEPAD_SPEEDRATIO;
      inputs.moveFactorX = handleControllerDeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)) / -GAMEPAD_SPEEDRATIO;

      inputs.shouldFire = sf::Joystick::isButtonPressed(0, 0) && (recoil == 0);
      inputs.fireBullet = sf::Joystick::isButtonPressed(0, 5);
    }
    //Sinon on se rabat sur le clavier
    else {  
      inputs.moveFactorY = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? 100.0f : 0.0f;
      inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? -100.0f : 0.0f;
      inputs.moveFactorX = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? 100.0f : 0.0f;
      inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? -100.0f : 0.0f;
      inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (recoil == 0);
    }

    return retval;
}

float GameScene::handleControllerDeadZone(float analogInput)
{
  if (fabs(analogInput) < CONTROLLER_DEAD_ZONE)
  {
    analogInput = 0.0f;
  }
  return analogInput;
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
    newBullet.initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0), contentManager.getPlayerGunSoundBuffer());
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
