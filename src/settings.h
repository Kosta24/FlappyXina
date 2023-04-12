#include <SFML/Graphics.hpp>
#include <Windows.h>

class Settings
{
public:
	int state = 0;

	float effectsVolume = 50; //50
	float musicVolume = 50;	  //50
	bool muteEffects = 0;
	bool muteMusic = 0;
	bool mutePlayerSoundEffects = 0; //turn on and off the player sound effects

	float sliderLenght;

	bool changed = 1;
	bool windowFocussed = 1;	//Flag used to mute the sound when the window is not focussed

	sf::Vector2f window; //Window Sizes

	sf::Vector2f buttonSize;
	sf::Vector2f sliderEffectsButtonSize;
	sf::Vector2f sliderMusicButtonSize;
	sf::Vector2f sliderEffectsSize;
	sf::Vector2f sliderMusicSize;
	sf::Vector2f creditsSize;
	sf::Vector2f textSize;

	sf::Vector2f settingsButtonPos;
	sf::Vector2f buttonClosePos;
	sf::Vector2f effectsMutePos;
	sf::Vector2f musicMutePos;
	sf::Vector2f playerMutePos;
	sf::Vector2f sliderEffectsButtonPos;
	sf::Vector2f sliderMusicButtonPos;
	sf::Vector2f sliderPos;
	sf::Vector2f creditsPos;
	sf::Vector2f textPos;

	sf::Texture settingsButtonTexture;
	sf::Texture backgroundTexture;
	sf::Texture creditsTexture;
	sf::Texture buttonMuteTexture;
	sf::Texture buttonUnMuteTexture;
	sf::Texture buttonCloseTexture;
	sf::Texture buttonBackTexture;
	sf::Texture buttonCreditsTexture;
	sf::Texture sliderEffectsButtonTexture;
	sf::Texture sliderMusicButtonTexture;
	sf::Texture filledSliderEffectsTexture;
	sf::Texture unfilledSliderEffectsTexture;
	sf::Texture filledSliderMusicTexture;
	sf::Texture unfilledSliderMusicTexture;
	sf::Texture musicVolumeTextTexture;
	sf::Texture effectsVolumeTextTexture;
	sf::Texture playerVolumeTextTexture;

	sf::Sprite settingsButtonSprite;
	sf::Sprite backgroundSprite;
	sf::Sprite creditsSprite;
	sf::Sprite effectsMuteSprite;
	sf::Sprite musicMuteSprite;
	sf::Sprite playerMuteSprite;
	sf::Sprite buttonCloseSprite;
	sf::Sprite buttonCreditsSprite;
	sf::Sprite sliderEffectsButtonSprite;
	sf::Sprite sliderMusicButtonSprite;
	sf::Sprite filledSliderEffectsSprite;
	sf::Sprite unfilledSliderEffectsSprite;
	sf::Sprite filledSliderMusicSprite;
	sf::Sprite unfilledSliderMusicSprite;
	sf::Sprite musicVolumeTextSprite;
	sf::Sprite effectsVolumeTextSprite;
	sf::Sprite playerVolumeTextSprite;

	Settings(sf::Vector2f Awindow)
	{
		window.x = Awindow.x; //Screen resolution
		window.y = Awindow.y;

		buttonSize.x = window.y / 18;
		buttonSize.y = buttonSize.x;

		settingsButtonPos = sf::Vector2f(window.x - buttonSize.x * 1.2 - 20, 20);

		buttonClosePos = sf::Vector2f((window.x / 2 + (window.x / 1.5) / 2) - buttonSize.x - 40, (window.y / 2 - (window.y / 1.5) / 2) + buttonSize.y + 20);

		sliderLenght = window.x / 1.6;

		loadSettings();

		sliderEffectsButtonSize.x = window.y / 20;
		sliderEffectsButtonSize.y = sliderEffectsButtonSize.x;

		sliderEffectsSize.x = sliderLenght / 2;
		sliderEffectsSize.y = 5;

		sliderMusicButtonSize.x = window.y / 20;
		sliderMusicButtonSize.y = sliderMusicButtonSize.x;

		sliderMusicSize.x = sliderLenght / 2;
		sliderMusicSize.y = 5;

		creditsSize.x = buttonSize.x * 5;
		creditsSize.y = buttonSize.y;

		textSize.y = buttonSize.y;
		textSize.x = textSize.y;

		effectsMutePos.x = 0;
		effectsMutePos.y = 0;

		musicMutePos.x = 0;
		musicMutePos.y = 0;

		playerMutePos.x = 0;
		playerMutePos.y = 0;

		sliderEffectsButtonPos.x = 0;
		sliderEffectsButtonPos.y = 0;

		sliderMusicButtonPos.x = 0;
		sliderMusicButtonPos.y = 0;

		sliderPos.x = 0;
		sliderPos.y = 0;

		creditsPos.x = 0;
		creditsPos.y = 0;

		textPos.x = 0;
		textPos.y = 0;

		if (!settingsButtonTexture.loadFromFile("src/assets/settings.png"))
			std::cout << "Error loading the settings::settings" << std::endl;

		if (!buttonUnMuteTexture.loadFromFile("src/assets/settings/buttonMute.png"))
			std::cout << "Error loading the settings::buttonMute" << std::endl;

		if (!buttonMuteTexture.loadFromFile("src/assets/settings/buttonUnMute.png"))
			std::cout << "Error loading the settings::buttonUnMute" << std::endl;

		if (!buttonCloseTexture.loadFromFile("src/assets/settings/buttonClose.png"))
			std::cout << "Error loading the settings::buttonClose" << std::endl;

		if (!buttonBackTexture.loadFromFile("src/assets/settings/buttonBack.png"))
			std::cout << "Error loading the settings::buttonBack" << std::endl;

		if (!sliderEffectsButtonTexture.loadFromFile("src/assets/settings/sliderButton.png"))
			std::cout << "Error loading the settings::sliderButton" << std::endl;

		if (!filledSliderEffectsTexture.loadFromFile("src/assets/settings/filledSlider.png"))
			std::cout << "Error loading the settings::filledSlider" << std::endl;

		if (!unfilledSliderEffectsTexture.loadFromFile("src/assets/settings/unfilledSlider.png"))
			std::cout << "Error loading the settings::unfilledSlider" << std::endl;

		if (!backgroundTexture.loadFromFile("src/assets/settings/background.jpg"))
			std::cout << "Error loading the settings::background" << std::endl;

		if (!creditsTexture.loadFromFile("src/assets/settings/credits.png"))
			std::cout << "Error loading the settings::credits" << std::endl;

		if (!musicVolumeTextTexture.loadFromFile("src/assets/settings/musicVolume.png"))
			std::cout << "Error loading the settings::musicVolume" << std::endl;

		if (!effectsVolumeTextTexture.loadFromFile("src/assets/settings/effectsVolume.png"))
			std::cout << "Error loading the settings::effectsVolume" << std::endl;

		if (!playerVolumeTextTexture.loadFromFile("src/assets/settings/playerVolume.png"))
			std::cout << "Error loading the settings::playerVolume" << std::endl;

		if (!buttonCreditsTexture.loadFromFile("src/assets/settings/buttonCredits.png"))
			std::cout << "Error loading the settings::buttonCredits" << std::endl;

		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setScale(
			window.x / 1.5 / backgroundSprite.getLocalBounds().width,
			window.y / 1.5 / backgroundSprite.getLocalBounds().height);

		creditsSprite.setTexture(creditsTexture);
		creditsSprite.setScale(
			window.x / 1.5 / creditsSprite.getLocalBounds().width,
			window.y / 1.5 / creditsSprite.getLocalBounds().height);

		settingsButtonSprite.setTexture(settingsButtonTexture);
		settingsButtonSprite.setScale(
			buttonSize.x * 1.2 / settingsButtonSprite.getLocalBounds().width,
			buttonSize.y * 1.2 / settingsButtonSprite.getLocalBounds().height);
		settingsButtonSprite.setPosition(settingsButtonPos);

		effectsMuteSprite.setTexture(buttonMuteTexture);
		effectsMuteSprite.setScale(
			buttonSize.x / effectsMuteSprite.getLocalBounds().width,
			buttonSize.y / effectsMuteSprite.getLocalBounds().height);

		musicMuteSprite.setTexture(buttonUnMuteTexture);
		musicMuteSprite.setScale(
			buttonSize.x / musicMuteSprite.getLocalBounds().width,
			buttonSize.y / musicMuteSprite.getLocalBounds().height);

		playerMuteSprite.setTexture(buttonMuteTexture);
		playerMuteSprite.setScale(
			buttonSize.x / playerMuteSprite.getLocalBounds().width,
			buttonSize.y / playerMuteSprite.getLocalBounds().height);

		buttonCloseSprite.setTexture(buttonCloseTexture);
		buttonCloseSprite.setScale(
			buttonSize.x / buttonCloseSprite.getLocalBounds().width,
			buttonSize.y / buttonCloseSprite.getLocalBounds().height);

		sliderEffectsButtonSprite.setTexture(sliderEffectsButtonTexture);
		sliderEffectsButtonSprite.setScale(
			sliderEffectsButtonSize.x / sliderEffectsButtonSprite.getLocalBounds().width,
			sliderEffectsButtonSize.y / sliderEffectsButtonSprite.getLocalBounds().height);

		filledSliderEffectsSprite.setTexture(filledSliderEffectsTexture);
		filledSliderEffectsSprite.setScale(
			sliderEffectsSize.x / filledSliderEffectsSprite.getLocalBounds().width,
			sliderEffectsSize.y / filledSliderEffectsSprite.getLocalBounds().height);

		unfilledSliderEffectsSprite.setTexture(unfilledSliderEffectsTexture);
		unfilledSliderEffectsSprite.setScale(
			(sliderLenght - sliderEffectsSize.x) / unfilledSliderEffectsSprite.getLocalBounds().width,
			sliderEffectsSize.y / unfilledSliderEffectsSprite.getLocalBounds().height);

		sliderMusicButtonSprite.setTexture(sliderEffectsButtonTexture);
		sliderMusicButtonSprite.setScale(
			sliderMusicButtonSize.x / sliderMusicButtonSprite.getLocalBounds().width,
			sliderMusicButtonSize.y / sliderMusicButtonSprite.getLocalBounds().height);

		filledSliderMusicSprite.setTexture(filledSliderEffectsTexture);
		filledSliderMusicSprite.setScale(
			sliderMusicSize.x / filledSliderMusicSprite.getLocalBounds().width,
			sliderMusicSize.y / filledSliderMusicSprite.getLocalBounds().height);

		unfilledSliderMusicSprite.setTexture(unfilledSliderEffectsTexture);
		unfilledSliderMusicSprite.setScale(
			(sliderLenght - sliderMusicSize.x) / unfilledSliderMusicSprite.getLocalBounds().width,
			sliderMusicSize.y / unfilledSliderMusicSprite.getLocalBounds().height);

		musicVolumeTextSprite.setTexture(musicVolumeTextTexture);
		musicVolumeTextSprite.setScale(
			buttonSize.y / 2 / musicVolumeTextSprite.getLocalBounds().height,
			buttonSize.y / 2 / musicVolumeTextSprite.getLocalBounds().height);

		effectsVolumeTextSprite.setTexture(effectsVolumeTextTexture);
		effectsVolumeTextSprite.setScale(
			buttonSize.y / 2 / effectsVolumeTextSprite.getLocalBounds().height,
			buttonSize.y / 2 / effectsVolumeTextSprite.getLocalBounds().height);

		playerVolumeTextSprite.setTexture(playerVolumeTextTexture);
		playerVolumeTextSprite.setScale(
			buttonSize.y / 2 / playerVolumeTextSprite.getLocalBounds().height,
			buttonSize.y / 2 / playerVolumeTextSprite.getLocalBounds().height);

		buttonCreditsSprite.setTexture(buttonCreditsTexture);
		buttonCreditsSprite.setScale(
			buttonSize.y / buttonCreditsSprite.getLocalBounds().height,
			buttonSize.y / buttonCreditsSprite.getLocalBounds().height);

		auto offset = sf::Vector2f(effectsMuteSprite.getLocalBounds().width / 2, effectsMuteSprite.getLocalBounds().height / 2) - effectsMuteSprite.getOrigin();
		effectsMuteSprite.setOrigin(sf::Vector2f(effectsMuteSprite.getLocalBounds().width / 2, effectsMuteSprite.getLocalBounds().height / 2));
		effectsMuteSprite.move(offset);

		offset = sf::Vector2f(musicMuteSprite.getLocalBounds().width / 2, musicMuteSprite.getLocalBounds().height / 2) - musicMuteSprite.getOrigin();
		musicMuteSprite.setOrigin(sf::Vector2f(musicMuteSprite.getLocalBounds().width / 2, musicMuteSprite.getLocalBounds().height / 2));
		musicMuteSprite.move(offset);

		offset = sf::Vector2f(playerMuteSprite.getLocalBounds().width / 2, playerMuteSprite.getLocalBounds().height / 2) - playerMuteSprite.getOrigin();
		playerMuteSprite.setOrigin(sf::Vector2f(playerMuteSprite.getLocalBounds().width / 2, playerMuteSprite.getLocalBounds().height / 2));
		playerMuteSprite.move(offset);

		offset = sf::Vector2f(buttonCloseSprite.getLocalBounds().width / 2, buttonCloseSprite.getLocalBounds().height / 2) - buttonCloseSprite.getOrigin();
		buttonCloseSprite.setOrigin(sf::Vector2f(buttonCloseSprite.getLocalBounds().width / 2, buttonCloseSprite.getLocalBounds().height / 2));
		buttonCloseSprite.move(offset);

		offset = sf::Vector2f(sliderEffectsButtonSprite.getLocalBounds().width / 2, sliderEffectsButtonSprite.getLocalBounds().height / 2) - sliderEffectsButtonSprite.getOrigin();
		sliderEffectsButtonSprite.setOrigin(sf::Vector2f(sliderEffectsButtonSprite.getLocalBounds().width / 2, sliderEffectsButtonSprite.getLocalBounds().height / 2));
		sliderEffectsButtonSprite.move(offset);

		offset = sf::Vector2f(sliderMusicButtonSprite.getLocalBounds().width / 2, sliderMusicButtonSprite.getLocalBounds().height / 2) - sliderMusicButtonSprite.getOrigin();
		sliderMusicButtonSprite.setOrigin(sf::Vector2f(sliderMusicButtonSprite.getLocalBounds().width / 2, sliderMusicButtonSprite.getLocalBounds().height / 2));
		sliderMusicButtonSprite.move(offset);

		offset = sf::Vector2f(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2) - backgroundSprite.getOrigin();
		backgroundSprite.setOrigin(sf::Vector2f(backgroundSprite.getLocalBounds().width / 2, backgroundSprite.getLocalBounds().height / 2));
		backgroundSprite.move(offset);

		offset = sf::Vector2f(creditsSprite.getLocalBounds().width / 2, creditsSprite.getLocalBounds().height / 2) - creditsSprite.getOrigin();
		creditsSprite.setOrigin(sf::Vector2f(creditsSprite.getLocalBounds().width / 2, creditsSprite.getLocalBounds().height / 2));
		creditsSprite.move(offset);

		offset = sf::Vector2f(effectsVolumeTextSprite.getLocalBounds().width / 2, effectsVolumeTextSprite.getLocalBounds().height / 2) - effectsVolumeTextSprite.getOrigin();
		effectsVolumeTextSprite.setOrigin(sf::Vector2f(effectsVolumeTextSprite.getLocalBounds().width / 2, effectsVolumeTextSprite.getLocalBounds().height / 2));
		effectsVolumeTextSprite.move(offset);

		offset = sf::Vector2f(musicVolumeTextSprite.getLocalBounds().width / 2, musicVolumeTextSprite.getLocalBounds().height / 2) - musicVolumeTextSprite.getOrigin();
		musicVolumeTextSprite.setOrigin(sf::Vector2f(musicVolumeTextSprite.getLocalBounds().width / 2, musicVolumeTextSprite.getLocalBounds().height / 2));
		musicVolumeTextSprite.move(offset);

		offset = sf::Vector2f(playerVolumeTextSprite.getLocalBounds().width / 2, playerVolumeTextSprite.getLocalBounds().height / 2) - playerVolumeTextSprite.getOrigin();
		playerVolumeTextSprite.setOrigin(sf::Vector2f(playerVolumeTextSprite.getLocalBounds().width / 2, playerVolumeTextSprite.getLocalBounds().height / 2));
		playerVolumeTextSprite.move(offset);

		offset = sf::Vector2f(buttonCreditsSprite.getLocalBounds().width / 2, buttonCreditsSprite.getLocalBounds().height / 2) - buttonCreditsSprite.getOrigin();
		buttonCreditsSprite.setOrigin(sf::Vector2f(buttonCreditsSprite.getLocalBounds().width / 2, buttonCreditsSprite.getLocalBounds().height / 2));
		buttonCreditsSprite.move(offset);

		backgroundSprite.setPosition(sf::Vector2f(window.x / 2, window.y / 2));
		creditsSprite.setPosition(sf::Vector2f(window.x / 2, window.y / 2));
	}

	void setSettings()
	{
		//deals with the texture
		if (muteEffects)
			effectsMuteSprite.setTexture(buttonMuteTexture);
		else
			effectsMuteSprite.setTexture(buttonUnMuteTexture);

		if (muteMusic)
			musicMuteSprite.setTexture(buttonMuteTexture);
		else
			musicMuteSprite.setTexture(buttonUnMuteTexture);

		if (mutePlayerSoundEffects)
			playerMuteSprite.setTexture(buttonMuteTexture);
		else
			playerMuteSprite.setTexture(buttonUnMuteTexture);

		if (state)
			buttonCloseSprite.setTexture(buttonBackTexture);
		else
			buttonCloseSprite.setTexture(buttonCloseTexture);

		effectsMutePos = sf::Vector2f((window.x / 2 - (window.x / 1.5) / 2) + buttonSize.x + 40, ((window.y / 2 - (window.y / 1.5) / 2) + buttonSize.y * 3 + 20));
		musicMutePos = sf::Vector2f(effectsMutePos.x, effectsMutePos.y + buttonSize.y * 2.5);
		playerMutePos = sf::Vector2f(window.x / 2, musicMutePos.y + buttonSize.y * 2.5);
		sliderPos = sf::Vector2f(musicMutePos.x + buttonSize.x, 0.0);
		creditsPos = sf::Vector2f(window.x / 2, ((window.y / 2 + (window.y / 1.5) / 2) - buttonSize.y * 1.5 - 20));
		textPos = sf::Vector2f(window.x / 2, effectsMutePos.y);

		//Calculate the lenght of the slider
		if (muteEffects)
			sliderEffectsSize.x = 0;
		else
			sliderEffectsSize.x = (sliderLenght / 2) * effectsVolume / 100;
		sliderEffectsSize.y = 5;

		if (muteMusic)
			sliderMusicSize.x = 0;
		else
			sliderMusicSize.x = (sliderLenght / 2) * musicVolume / 100;
		sliderMusicSize.y = 5;

		//Sets the lenght of the slider
		filledSliderEffectsSprite.setScale(
			sliderEffectsSize.x / filledSliderEffectsSprite.getLocalBounds().width,
			sliderEffectsSize.y / filledSliderEffectsSprite.getLocalBounds().height);

		unfilledSliderEffectsSprite.setScale(
			(sliderLenght / 2 - sliderEffectsSize.x) / unfilledSliderEffectsSprite.getLocalBounds().width,
			sliderEffectsSize.y / unfilledSliderEffectsSprite.getLocalBounds().height);

		filledSliderMusicSprite.setScale(
			sliderMusicSize.x / filledSliderMusicSprite.getLocalBounds().width,
			sliderMusicSize.y / filledSliderMusicSprite.getLocalBounds().height);

		unfilledSliderMusicSprite.setScale(
			(sliderLenght / 2 - sliderMusicSize.x) / unfilledSliderMusicSprite.getLocalBounds().width,
			sliderMusicSize.y / unfilledSliderMusicSprite.getLocalBounds().height);

		backgroundSprite.setPosition(sf::Vector2f(window.x / 2, window.y / 2));
		creditsSprite.setPosition(sf::Vector2f(window.x / 2, window.y / 2));

		effectsMuteSprite.setPosition(effectsMutePos);
		musicMuteSprite.setPosition(musicMutePos);
		playerMuteSprite.setPosition(playerMutePos);

		buttonCreditsSprite.setPosition(creditsPos);

		buttonCloseSprite.setPosition(buttonClosePos);
		//Effects Slider
		filledSliderEffectsSprite.setPosition(sf::Vector2f(sliderPos.x, effectsMutePos.y));
		unfilledSliderEffectsSprite.setPosition(sf::Vector2f(sliderPos.x + filledSliderEffectsSprite.getGlobalBounds().width, effectsMutePos.y));
		sliderEffectsButtonPos = sf::Vector2f(unfilledSliderEffectsSprite.getPosition().x, effectsMutePos.y);
		sliderEffectsButtonSprite.setPosition(sliderEffectsButtonPos);

		//Music slider
		filledSliderMusicSprite.setPosition(sf::Vector2f(sliderPos.x, musicMutePos.y));
		unfilledSliderMusicSprite.setPosition(sf::Vector2f(sliderPos.x + filledSliderMusicSprite.getGlobalBounds().width, musicMutePos.y));
		sliderMusicButtonPos = sf::Vector2f(unfilledSliderMusicSprite.getPosition().x, musicMutePos.y);
		sliderMusicButtonSprite.setPosition(sliderMusicButtonPos);

		effectsVolumeTextSprite.setPosition(sf::Vector2f(textPos.x, effectsMutePos.y - buttonSize.y));
		musicVolumeTextSprite.setPosition(sf::Vector2f(textPos.x, musicMutePos.y - buttonSize.y));
		playerVolumeTextSprite.setPosition(sf::Vector2f(textPos.x, playerMutePos.y - buttonSize.y));
	}

	//Checl the mouse position when colliding with the slider
	void checkSlider(sf::Vector2i mouse)
	{
		//if collides with the effects slider
		if (mouse.x > (sliderPos.x) && mouse.x < (unfilledSliderEffectsSprite.getPosition().x + unfilledSliderEffectsSprite.getGlobalBounds().width))
			if (mouse.y > (effectsMutePos.y - buttonSize.y / 2) && mouse.y < (effectsMutePos.y + buttonSize.y / 2))
			{
				//std::cout << ((mouse.x - sliderPos.x) / (unfilledSliderEffectsSprite.getPosition().x + unfilledSliderEffectsSprite.getGlobalBounds().width - sliderPos.x)) * 100 << std::endl;
				effectsVolume = ((mouse.x - sliderPos.x) / (unfilledSliderEffectsSprite.getPosition().x + unfilledSliderEffectsSprite.getGlobalBounds().width - sliderPos.x)) * 100;
				if (effectsVolume < 2.5)
					muteEffects = 1;
				else
					mutePlayerSoundEffects = muteEffects = 0;
				if (muteEffects)
					mutePlayerSoundEffects = 1;
				changed = 1;
			}

		//if collides with the effects slider
		if (mouse.x > (sliderPos.x) && mouse.x < (unfilledSliderMusicSprite.getPosition().x + unfilledSliderMusicSprite.getGlobalBounds().width))
			if (mouse.y > (musicMutePos.y - buttonSize.y / 2) && mouse.y < (musicMutePos.y + buttonSize.y / 2))
			{
				//std::cout << ((mouse.x - sliderPos.x) / (unfilledSliderMusicSprite.getPosition().x + unfilledSliderMusicSprite.getGlobalBounds().width  - sliderPos.x)) * 100 << std::endl;
				musicVolume = ((mouse.x - sliderPos.x) / (unfilledSliderMusicSprite.getPosition().x + unfilledSliderMusicSprite.getGlobalBounds().width - sliderPos.x)) * 100;
				if (musicVolume < 2.5)
					muteMusic = 1;
				else
					muteMusic = 0;
				changed = 1;
			}
	}

	//checks with button is being pressed
	void checkCollision(sf::Vector2i mouse)
	{
		//if collides with the credits
		if (mouse.x > (creditsPos.x - buttonCreditsSprite.getGlobalBounds().width / 2) && mouse.x < (creditsPos.x + buttonCreditsSprite.getGlobalBounds().width / 2))
			if (mouse.y > (creditsPos.y - buttonSize.y / 2) && mouse.y < (creditsPos.y + buttonSize.y / 2))
			{
				setState(1);
				changed = 1;
			}

		//if collides with the effects mute
		if (mouse.x > (effectsMutePos.x - buttonSize.x / 2) && mouse.x < (effectsMutePos.x + buttonSize.x / 2))
			if (mouse.y > (effectsMutePos.y - buttonSize.y / 2) && mouse.y < (effectsMutePos.y + buttonSize.y / 2))
			{
				muteEffects = (muteEffects + 1) % 2;
				if (effectsVolume < 2.5)
					muteEffects = 1;
				if (muteEffects)
					mutePlayerSoundEffects = 1;
				changed = 1;
			}

		//if collides with the volume mute
		if (mouse.x > (musicMutePos.x - buttonSize.x / 2) && mouse.x < (musicMutePos.x + buttonSize.x / 2))
			if (mouse.y > (musicMutePos.y - buttonSize.y / 2) && mouse.y < (musicMutePos.y + buttonSize.y / 2))
			{
				muteMusic = (muteMusic + 1) % 2;
				if (musicVolume < 2.5)
					muteMusic = 1;
				changed = 1;
			}

		//if collides with the player mute
		if (mouse.x > (playerMutePos.x - buttonSize.x / 2) && mouse.x < (playerMutePos.x + buttonSize.x / 2))
			if (mouse.y > (playerMutePos.y - buttonSize.y / 2) && mouse.y < (playerMutePos.y + buttonSize.y / 2))
			{
				mutePlayerSoundEffects = (mutePlayerSoundEffects + 1) % 2;
				if (effectsVolume < 2.5)
					mutePlayerSoundEffects = 1;
				changed = 1;
			}

		//
		//if collides with the back button
		if (mouse.x > (buttonClosePos.x - buttonSize.x / 2) && mouse.x < (buttonClosePos.x + buttonSize.x / 2))
			if (mouse.y > (buttonClosePos.y - buttonSize.y / 2) && mouse.y < (buttonClosePos.y + buttonSize.y / 2))
			{
				setState(0);
				changed = 1;
			}
	}

	//Legge dal Registro di sistema
	std::string OpenRegistryKey(LPCSTR subkey, LPCSTR name, DWORD type)
	{
		type = type;
		name = name;
		HKEY hKey;
		TCHAR value[255];
		DWORD value_length = 255;
		LONG lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_READ, &hKey);

		//Se non è stato trovato il registro lo crea
		if (lError == ERROR_NOT_REGISTRY_FILE)
		{
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &value_length);
			RegSetValueEx(hKey, "effectsVolume", 0, REG_SZ, (LPBYTE)"0", strlen("50") * sizeof(char));			//creates the key
			RegSetValueEx(hKey, "musicVolume", 0, REG_SZ, (LPBYTE)"0", strlen("50") * sizeof(char));			//creates the key
			RegSetValueEx(hKey, "muteEffects", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char));			//creates the key
			RegSetValueEx(hKey, "muteMusic", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char));				//creates the key
			RegSetValueEx(hKey, "mutePlayerSoundEffects", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char)); //creates the key
			return "";
		}

		if (lError != ERROR_SUCCESS)
		{
			//std::cout << "Something is wrong. Could no topen or create the key" << std::endl;
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &value_length); //creates the register
			RegSetValueEx(hKey, "effectsVolume", 0, REG_SZ, (LPBYTE)"0", strlen("50") * sizeof(char));										  //creates the key
			RegSetValueEx(hKey, "musicVolume", 0, REG_SZ, (LPBYTE)"0", strlen("50") * sizeof(char));										  //creates the key
			RegSetValueEx(hKey, "muteEffects", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char));										  //creates the key
			RegSetValueEx(hKey, "muteMusic", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char));											  //creates the key
			RegSetValueEx(hKey, "mutePlayerSoundEffects", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char));								  //creates the key										  //creates the key
			return "";
		}

		//std::cout << "error: " << lError << endl;//return value of the open condition
		RegQueryValueEx(hKey, name, NULL, &type, (LPBYTE)&value, &value_length); //reads the key
		RegCloseKey(hKey);														 //closes the hkey
		return value;
	}

	//Scrive sul registro di sistema
	void registry_write(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value)
	{
		HKEY hKey;
		RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
		RegSetValueEx(hKey, name, 0, type, (LPBYTE)value, strlen(value) * sizeof(char));
		RegCloseKey(hKey);
	}

	//reads the highscore from the system variable
	void loadSettings()
	{

		std::string result = OpenRegistryKey("SOFTWARE\\FlappyXina", "effectsVolume", REG_SZ);
		//std::cout << "effectsVolume: |" + result + "|" << std::endl;
		if (result.size() > 0)
			effectsVolume = 50;
		else
			effectsVolume = std::stoi(result);

		result = OpenRegistryKey("SOFTWARE\\FlappyXina", "musicVolume", REG_SZ);
		//std::cout << "musicVolume: |" + result + "|" << std::endl;
		if (result.size() > 0)
			musicVolume = 50;
		else
			musicVolume = std::stoi(result); //*/

		result = OpenRegistryKey("SOFTWARE\\FlappyXina", "muteEffects", REG_SZ);
		//std::cout << "muteEffects: |" + result + "|" << std::endl;
		if (result.size() > 0)
			muteEffects = 0;
		else
			muteEffects = std::stoi(result); //*/

		result = OpenRegistryKey("SOFTWARE\\FlappyXina", "muteMusic", REG_SZ);
		//std::cout << "muteMusic: |" + result + "|" << std::endl;
		if (result.size() > 0)
			muteMusic = 0;
		else
			muteMusic = std::stoi(result); //*/

		result = OpenRegistryKey("SOFTWARE\\FlappyXina", "mutePlayerSoundEffects", REG_SZ);
		//std::cout << "mutePlayerSoundEffects: |" + result + "|" << std::endl;
		if (result.size() > 0)
			mutePlayerSoundEffects = 0;
		else
			mutePlayerSoundEffects = std::stoi(result); //*/
	}

	//sets the system variable highscore
	void writeSettings()
	{
		registry_write("SOFTWARE\\FlappyXina", "effectsVolume", REG_SZ, std::to_string((int)effectsVolume).c_str());
		registry_write("SOFTWARE\\FlappyXina", "musicVolume", REG_SZ, std::to_string((int)musicVolume).c_str());
		registry_write("SOFTWARE\\FlappyXina", "muteEffects", REG_SZ, std::to_string(muteEffects).c_str());
		registry_write("SOFTWARE\\FlappyXina", "muteMusic", REG_SZ, std::to_string(muteMusic).c_str());
		registry_write("SOFTWARE\\FlappyXina", "mutePlayerSoundEffects", REG_SZ, std::to_string(mutePlayerSoundEffects).c_str());
	}

	int getState()
	{
		return state;
	}

	void setState(int aState)
	{
		state = aState;
	}
};