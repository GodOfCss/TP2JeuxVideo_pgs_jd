#pragma once
class ContentManager
{
public:
	ContentManager();
	virtual bool loadContent();

	const sf::Texture& getBackgroundTexture() const;
	const sf::Texture& getMainCharacterTexture() const;
	const sf::Texture& getMiscTexture() const;
	const sf::Texture& getEnemiesTexture() const;

	const sf::Texture& getGunBonusTexture() const;
	const sf::Texture& getHealthBonusTexture() const;

	const sf::Texture& getHealthBarTexture() const;

	const sf::Texture& getTitleScreenTexture() const;
	const sf::Font& getMainFont() const;
	const sf::SoundBuffer& getPlayerGunSoundBuffer() const;
	const sf::SoundBuffer& getEnemyGunSoundBuffer() const;
	const sf::SoundBuffer& getHealthSoundBuffer() const;
	const sf::SoundBuffer& getGunBonusSoundBuffer() const;
	const sf::SoundBuffer& getEnemyKilledSoundBuffer() const;
private:
	sf::Texture mainCharacterTexture;
	sf::Texture backgroundTexture;
	sf::Texture miscTexture;
	sf::Texture enemiesTexture;
	sf::Texture healthBarTexture;

	sf::Texture gunBonusTexture;
	sf::Texture healthBonusTexture;
	sf::SoundBuffer healthBonusSoundBuffer;
	sf::SoundBuffer gunBonusSoundBuffer;

	sf::Texture titleScreenTexture;
	sf::Font mainFont;
	sf::SoundBuffer playerGunSoundBuffer;
	sf::SoundBuffer enemyGunSoundBuffer;
	sf::SoundBuffer enemyKilledSoundBuffer;
};



