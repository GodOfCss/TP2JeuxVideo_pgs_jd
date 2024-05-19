#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Player.h"
#include "Inputs.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GunBonus.h"
#include "random.h"
#include "HealthBonus.h"
#include "BossEnemy.h"
class GameScene :
    public Scene
{
public:
    static const unsigned int BACKGROUND_SPEED;
    static const unsigned int AMOUNT_OF_LIVES;
    static const unsigned int HUD_HEIGHT;
    static const unsigned int NB_BULLETS;
    static const unsigned int NB_ENEMIES;
    static const unsigned int MAX_BONUSES;
    static const unsigned int MAX_RECOIL;
    static const double BONUS_PCT;
    static const double BONUS_50;
    static const float GAMEPAD_SPEEDRATIO;
    static const float TIME_PER_FRAME;
    static const int CONTROLLER_DEAD_ZONE;

    // H�rit�es via Scene
    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    void fireBullet();
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
    float handleControllerDeadZone(float analogInput);

    virtual void pause() override;
    virtual void unPause() override;
    void spawnBonus(sf::Vector2f enemyPosition);

    Bullet& getAvailableBullet();
    GunBonus& getAvailableGunBonus();
    HealthBonus& getAvailableHealthBonus();

    bool isEnemyAvailable(Enemy& e);
private:
    ContentManager contentManager;

    sf::Sprite background;
    sf::Sprite healthBar;
    sf::Music gameMusic;
    int backgroundPosition;

    bool hasStarted;
    sf::Text scoreText;
    sf::Text bonusText;
    std::vector<sf::Sprite> livesRender;
    int lives;
    int score;

    Player player;
    Inputs inputs;

    std::list<Bullet> bullets;
    int recoil;

    std::list<Enemy> enemies;
    int spawnCooldown;
    int enemyTotal;

    BossEnemy boss;
    std::list<BossEnemyBullet> bossBullets;
    bool spawnBoss;

    std::list<GunBonus> gunBonuses;
    std::list<HealthBonus> healthBonuses;

    Random bonusRate;
    Random bonusType;

};