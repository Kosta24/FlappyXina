#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

class Background
{
	//void setClickToJumpPos(sf::Time dt)		//Calculates and sets the "Click to Jump" Sprite
	//void rotateBg(float dt)					//Rotates the background
	//void setDaySpeed(float Aspeed)			//Sets the speed of the rotatio
	//sf::Sprite getClickToJumpSprite()			//
	//sf::Sprite getBackground_Foreground()		//
	//sf::Sprite getBackground_Background()		//
	//sf::Sprite getLoadingSprite()				//

public:
	int FPS;

	float daySpeed = 1;
	float clickToJumpYSpeed = 20;
	float loadingDuration = 5;
	float loadingSlider = 0;

	bool visibleNeon1 = 1;
	bool visibleNeon2 = 1;

	sf::Vector2f window; //Window Sizes

	sf::Texture background_ForegroundTexture;
	sf::Texture background_BackgroundTexture;
	sf::Texture clickToJumpTexture;
	sf::Texture titleScreenTexture;
	sf::Texture loadingBgTexture;
	sf::Texture anUndefinedTexture;
	sf::Texture productionTexture;
	sf::Texture loadingTextTexture;
	sf::Texture loadingPxTexture;

	sf::Sprite background_ForegroundSprite;
	sf::Sprite background_BackgroundSprite;
	sf::Sprite clickToJumpSprite;
	sf::Sprite titleScreenSprite;
	sf::Sprite loadingBgSprite;
	sf::Sprite anUndefinedSprite;
	sf::Sprite productionSprite;
	sf::Sprite loadingTextSprite;
	sf::Sprite loadingPxSprite;

	sf::SoundBuffer loadingSoundBuffer;
	sf::Sound loadingSound;

	Background(sf::Vector2f Awindow, int AFPS)
	{
		window.x = Awindow.x; //Screen resolution
		window.y = Awindow.y;

		FPS = AFPS;

		//LOADING SCREEN WHILE WAITING
		if (!loadingBgTexture.loadFromFile("src/assets/loading/bg.png"))
			std::cout << "Error loading the loading bg" << std::endl;

		if (!anUndefinedTexture.loadFromFile("src/assets/loading/anUndefinedGames.png"))
			std::cout << "Error loading the clickToJump" << std::endl;

		if (!productionTexture.loadFromFile("src/assets/loading/production.png"))
			std::cout << "Error loading the clickToJump" << std::endl;

		if (!loadingTextTexture.loadFromFile("src/assets/loading/loading.png"))
			std::cout << "Error loading the clickToJump" << std::endl;

		if (!loadingPxTexture.loadFromFile("src/assets/loading/loadingpx.png"))
			std::cout << "Error loading the clickToJump" << std::endl;

		if (!titleScreenTexture.loadFromFile("src/assets/title.png"))
			std::cout << "Error loading the clickToJump" << std::endl;

		if (!background_ForegroundTexture.loadFromFile("src/assets/background_Foreground.png"))
			std::cout << "Error loading the background" << std::endl;

		if (!background_BackgroundTexture.loadFromFile("src/assets/background_Background.png"))
			std::cout << "Error loading the background" << std::endl;

		if (!clickToJumpTexture.loadFromFile("src/assets/clickToJump.png"))
			std::cout << "Error loading the clickToJump" << std::endl;

		if (!loadingSoundBuffer.loadFromFile("src/music/loading.ogg"))
			std::cout << "Error loading loading sound" << std::endl;

		loadingSound.setBuffer(loadingSoundBuffer);

		loadingBgSprite.setTexture(loadingBgTexture);
		//Adapts the texture to the sprite
		loadingBgSprite.setScale(
			window.x / loadingBgSprite.getLocalBounds().width,
			window.y / loadingBgSprite.getLocalBounds().height);

		anUndefinedSprite.setTexture(anUndefinedTexture);
		//Adapts the texture to the sprite
		anUndefinedSprite.setScale(
			window.x / anUndefinedSprite.getLocalBounds().width,
			window.y / anUndefinedSprite.getLocalBounds().height);

		productionSprite.setTexture(productionTexture);
		//Adapts the texture to the sprite
		productionSprite.setScale(
			window.x / productionSprite.getLocalBounds().width,
			window.y / productionSprite.getLocalBounds().height);

		loadingTextSprite.setTexture(loadingTextTexture);
		//Adapts the texture to the sprite
		loadingTextSprite.setScale(
			window.x / 2 / loadingTextSprite.getLocalBounds().width,
			window.x / 2 / loadingTextSprite.getLocalBounds().width);

		loadingPxSprite.setTexture(loadingPxTexture);
		//Adapts the texture to the sprite
		loadingPxSprite.setScale(
			window.x / 2 / loadingPxSprite.getLocalBounds().width,
			7.5 / loadingPxSprite.getLocalBounds().height);

		//Sets the Background Texture
		background_BackgroundSprite.setTexture(background_BackgroundTexture);
		background_BackgroundSprite.setColor(sf::Color(255, 255, 255, 255));

		//Adapts the texture to the sprite
		background_BackgroundSprite.setScale(
			sqrt(((window.y / 2) * (window.y / 2)) + ((window.x / 2) * (window.x / 2))) * 2 / background_BackgroundSprite.getLocalBounds().height,
			sqrt(((window.y / 2) * (window.y / 2)) + ((window.x / 2) * (window.x / 2))) * 2 / background_BackgroundSprite.getLocalBounds().height);

		//Sets the Background Texture
		background_ForegroundSprite.setTexture(background_ForegroundTexture);
		background_ForegroundSprite.setColor(sf::Color(225, 225, 225, 255));

		//Adapts the texture to the sprite
		background_ForegroundSprite.setScale(
			window.x / background_ForegroundSprite.getLocalBounds().width,
			window.y / background_ForegroundSprite.getLocalBounds().height);

		clickToJumpSprite.setTexture(clickToJumpTexture);
		clickToJumpSprite.setColor(sf::Color(243, 195, 62)); //(218, 10, 10)
		clickToJumpSprite.setScale(
			window.y / 20 / clickToJumpSprite.getLocalBounds().height,
			window.y / 20 / clickToJumpSprite.getLocalBounds().height);
		clickToJumpSprite.setPosition(sf::Vector2f(window.x / 2 - clickToJumpSprite.getGlobalBounds().width / 2, window.y / 8 * 2.35));

		titleScreenSprite.setTexture(titleScreenTexture);
		titleScreenSprite.setScale(
			window.x / 10 * 9 / titleScreenSprite.getLocalBounds().width,
			window.x / 10 * 9 / titleScreenSprite.getLocalBounds().width);
		titleScreenSprite.setPosition(sf::Vector2f(window.x / 2 - titleScreenSprite.getGlobalBounds().width / 2, window.y / 8 * 0.75));

		auto offset = sf::Vector2f(background_BackgroundSprite.getLocalBounds().width / 2, background_BackgroundSprite.getLocalBounds().width / 2) - background_BackgroundSprite.getOrigin();
		background_BackgroundSprite.setOrigin(sf::Vector2f(background_BackgroundSprite.getLocalBounds().width / 2, background_BackgroundSprite.getLocalBounds().width / 2));
		background_BackgroundSprite.move(offset);
		background_BackgroundSprite.setPosition(sf::Vector2f(window.x / 2, window.y / 2));

		offset = sf::Vector2f(loadingTextSprite.getLocalBounds().width / 2, loadingTextSprite.getLocalBounds().height / 2) - loadingTextSprite.getOrigin();
		loadingTextSprite.setOrigin(sf::Vector2f(loadingTextSprite.getLocalBounds().width / 2, loadingTextSprite.getLocalBounds().height / 2));
		loadingTextSprite.move(offset);

		loadingTextSprite.setPosition(sf::Vector2f(window.x / 2, window.y / 2 + loadingTextSprite.getGlobalBounds().height * 2));
		loadingPxSprite.setPosition(sf::Vector2f(window.x / 4, window.y / 2 + loadingTextSprite.getGlobalBounds().height * 2.75));

		loadingSound.play();
	}

	bool loadingScreen(sf::RenderWindow& window, sf::Time now)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Closes the window if not focused
			if (event.type == sf::Event::Closed) // || event.type == Event::LostFocus
			{
				window.close(); //When the X is clicked it closes the Window
				return false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close(); //When escape is pressed it closes the Window
				return false;
			}
		}

		//std::cout << now.asSeconds() << std::endl;
		if (now.asSeconds() < loadingDuration - 2 && ((window.getSize().x / 2) * now.asSeconds() / (loadingDuration - 2)) > loadingSlider)
		{
			loadingSlider = ((window.getSize().x / 2) * now.asSeconds() / (loadingDuration - 2));
			loadingPxSprite.setScale(loadingSlider / loadingPxSprite.getLocalBounds().width, 1);
		}


		//Flicker effect
		if (now.asSeconds() < 1.8)
			anUndefinedSprite.setColor(sf::Color(255, 255, 255, sin((now.asMilliseconds() / 60 % 360)) * 127.5 + 127.5));
		else
			anUndefinedSprite.setColor(sf::Color(255, 255, 255, 255));

		//Flicker effect
		if (now.asSeconds() < 2.3)
			productionSprite.setColor(sf::Color(255, 255, 255, sin(((now.asMilliseconds() / 20 + 20) % 360)) * 127.5 + 127.5));
		else
			productionSprite.setColor(sf::Color(255, 255, 255, 255));

		window.clear();
		window.draw(loadingBgSprite);
		if (now.asSeconds() > 0.3)
			window.draw(anUndefinedSprite);
		if (now.asSeconds() > 0.5)
			window.draw(productionSprite);
		window.draw(loadingTextSprite);
		window.draw(loadingPxSprite);
		window.display();

		if (now.asSeconds() < loadingDuration)
			return true;
		loadingSound.stop();
		return false;
		//return true;//questo va cancellato poi
	}

	void setClickToJumpPos(sf::Time dt)
	{
		//Calculates the Click To Jump text Movement
		if (clickToJumpSprite.getPosition().y < window.y / 8 * 2.35 - 12.5)
		{
			clickToJumpSprite.setPosition(sf::Vector2f(window.x / 2 - clickToJumpSprite.getGlobalBounds().width / 2, window.y / 8 * 2.35 - 12.5));
			clickToJumpYSpeed *= -1;
		}
		else if (clickToJumpSprite.getPosition().y > window.y / 8 * 2.35 + 12.5)
		{
			clickToJumpSprite.setPosition(sf::Vector2f(window.x / 2 - clickToJumpSprite.getGlobalBounds().width / 2, window.y / 8 * 2.35 + 12.5));
			clickToJumpYSpeed *= -1;
		}
		clickToJumpSprite.setPosition(sf::Vector2f(window.x / 2 - clickToJumpSprite.getGlobalBounds().width / 2, (clickToJumpSprite.getPosition().y + clickToJumpYSpeed * dt.asSeconds())));
	}

	void rotateBg(float dt)
	{
		dt = dt;
		background_BackgroundSprite.rotate(daySpeed * dt * 50);
	}

	void setDaySpeed(float Aspeed)
	{
		daySpeed = Aspeed / 1000;
	}

	sf::Sprite getClickToJumpSprite()
	{
		return clickToJumpSprite;
	}

	sf::Sprite getBackground_Foreground()
	{
		return background_ForegroundSprite;
	}

	sf::Sprite getBackground_Background()
	{
		return background_BackgroundSprite;
	}

	sf::Sprite getLoadingBgSprite()
	{
		return loadingBgSprite;
	}
};