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

    // Héritées via Scene
    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    void fireBullet();
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
    void spawnBonus(sf::Vector2f enemyPosition);

    Bullet& getAvailableBullet();
    GunBonus& getAvailableGunBonus();
    HealthBonus& getAvailableHealthBonus();

    bool isEnemyAvailable(Enemy& e);
private:
    ContentManager contentManager;

    sf::Sprite background;
    sf::Music gameMusic;
    int backgroundPosition;

    sf::Text scoreText;
    std::vector<sf::Sprite> livesRender;
    int lives;
    int score;

    Player player;
    Inputs inputs;

    std::list<Bullet> bullets;
    int recoil;

    std::list<Enemy> enemies;
    int spawnCooldown;

    std::list<GunBonus> gunBonuses;
    std::list<HealthBonus> healthBonuses;

    Random bonusRate;
    Random bonusType;

};