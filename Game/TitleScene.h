#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "Inputs.h"
class TitleScene :
    public Scene
{
public:
  // H�rit�es via Scene
  TitleScene();
  ~TitleScene();
  virtual SceneType update() override;
  virtual void draw(sf::RenderWindow& window) const override;
  virtual bool init() override;
  virtual bool uninit() override;
  virtual bool handleEvents(sf::RenderWindow& window) override;

  virtual void pause() override;
  virtual void unPause() override;
private:

  
  sf::Texture menuImageTexture;
  sf::Sprite menuImage;

  sf::Text startGameText;
  sf::Text quitGameText;

  Inputs inputs;

  sf::Music titleMusic;

  ContentManager contentManager;  

};

