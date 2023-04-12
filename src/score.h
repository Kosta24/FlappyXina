#include <SFML/Graphics.hpp>
//#include <Windows.h>
#include <iostream>

class Score
{
public:
	int startScore = 0;
	int score = 0;
	int highScore = 0;
	int i = 0;

	float YOffset = 0;

	bool deathScreenFlag = 0; //Used in the main to call the death function

	sf::Color ChineseYellow = sf::Color(243, 195, 62, 255);

	sf::Vector2f size;

	sf::Vector2f digit1Pos;
	sf::Vector2f digit2Pos;
	sf::Vector2f digit3Pos;
	sf::Vector2f digit4Pos;
	sf::Vector2f digit5Pos;
	sf::Vector2f digit6Pos;

	sf::Vector2f Hdigit1Pos;
	sf::Vector2f Hdigit2Pos;
	sf::Vector2f Hdigit3Pos;
	sf::Vector2f Hdigit4Pos;
	sf::Vector2f Hdigit5Pos;
	sf::Vector2f Hdigit6Pos;

	sf::Vector2f window; //Window Sizes

	sf::Texture digitsTexture[10];		//digits
	sf::Texture deathScreenTexture;		//Red background for normal Score
	sf::Texture deathHighScreenTexture; //Red background for new HighScore
	sf::Texture highScoreTexture;		//Highscore text png
	sf::Texture scoreTexture;			//Score text png

	sf::Sprite digitsSprites[10]; //digits
	sf::Sprite deathScreenSprite; //Red background Sprite
	sf::Sprite highScoreSprite;	  //Highscore text png
	sf::Sprite scoreSprite;		  // Score text png

	//CONSTRUCTOR
	Score(sf::Vector2f Awindow, int AstartScore)
	{
		window.x = Awindow.x; //Screen resolution
		window.y = Awindow.y;

		startScore = AstartScore;
		score = startScore;
		highScore = 0;

		deathScreenFlag = 0;
		YOffset = 0;

		//size.y = 52;
		//size.x = 36;
		size.y = window.y / 18;
		size.x = size.y * 0.70;


		//readHighScore();

		for (i = 0; i < 10; i++)
		{
			if (!digitsTexture[i].loadFromFile("src/assets/digits/" + std::to_string(i) + "_.png"))
				std::cout << "Error loading digit " + std::to_string(i) + " sprite" << std::endl;

			digitsSprites[i].setTexture(digitsTexture[i]);
			digitsSprites[i].setColor(ChineseYellow); //Color(243, 195, 62)

			digitsSprites[i].setScale(
				size.x / digitsSprites[i].getLocalBounds().width,
				size.y / digitsSprites[i].getLocalBounds().height);
		}
		//sets the deathscreen texture
		if (!deathScreenTexture.loadFromFile("src/assets/score_death_Screen.png"))//score_death_Screen
			std::cout << "Error loading deathscreen Texture" << std::endl;

		if (!deathHighScreenTexture.loadFromFile("src/assets/highscore_death_Screen.png"))//
			std::cout << "Error loading deathscreen Texture" << std::endl;

		//sets the hiscore texture
		if (!highScoreTexture.loadFromFile("src/assets/highscore.png"))
			std::cout << "Error loading highscore Texture" << std::endl;

		if (!scoreTexture.loadFromFile("src/assets/score.png"))
			std::cout << "Error loading score Texture" << std::endl;


		deathScreenSprite.setTexture(deathScreenTexture);

		deathScreenSprite.setScale(
			window.x / 1.5 / deathScreenSprite.getLocalBounds().width,
			window.y / 1.5 / deathScreenSprite.getLocalBounds().height);

		deathScreenSprite.setPosition(sf::Vector2f(window.x / 2 - deathScreenSprite.getGlobalBounds().width / 2, window.y / 2 - deathScreenSprite.getGlobalBounds().height / 2 - size.y));

		//Setting the highscore sprite
		highScoreSprite.setTexture(highScoreTexture);
		highScoreSprite.setColor(ChineseYellow);

		highScoreSprite.setScale(
			size.y / 2 / highScoreSprite.getLocalBounds().height,
			size.y / 2 / highScoreSprite.getLocalBounds().height);

		scoreSprite.setTexture(scoreTexture);
		scoreSprite.setColor(ChineseYellow);

		scoreSprite.setScale(
			size.y / 2 / scoreSprite.getLocalBounds().height,
			size.y / 2 / scoreSprite.getLocalBounds().height);



		setPosition();
	}

	//Adds To the score
	bool addScore(sf::Vector2f a, sf::Vector2f b, float playerSize)
	{
		//If the obstacle is behind the player adds to the score
		if (b.x < a.x + playerSize / 5 * 1.1)
		{
			score++;
			return true;
		}
		return false;
	}

	//retests The score
	void reset()
	{
		deathScreenFlag = 0;
		//highScore = scoree;//readHighScore();
		score = startScore; //resets the score
		YOffset = window.y / 2;
		digit1Pos.y = window.y / 14;
		void setPosition();
		for (i = 0; i < 10; i++)
			digitsSprites[i].setColor(ChineseYellow); //Color(243, 195, 62)
	}

	//Sets the position of the digits Score
	void setPosition()
	{
		digit6Pos.y = digit5Pos.y = digit4Pos.y = digit3Pos.y = digit2Pos.y = digit1Pos.y;

		scoreSprite.setPosition(sf::Vector2f(window.x / 2 - scoreSprite.getGlobalBounds().width / 2, digit6Pos.y - size.y / 2 - 20));

		if (getScore() < 10)
		{
			digit6Pos.x = digit5Pos.x = digit4Pos.x = digit3Pos.x = digit2Pos.x = digit1Pos.x = window.x / 2 - size.x / 2;
			return; //if the number is <10
		}

		if (getScore() < 100)
		{
			digit1Pos.x = window.x / 2 + 2.5;
			digit6Pos.x = digit5Pos.x = digit4Pos.x = digit3Pos.x = digit2Pos.x = window.x / 2 - size.x - 2.5;
			return; //if the number is <100
		}
		//if the number is >=100 sets all3  digits position
		if (getScore() < 1000)
		{
			digit1Pos.x = window.x / 2 + size.x / 2 + 5;
			digit2Pos.x = window.x / 2 - size.x / 2;
			digit3Pos.x = window.x / 2 - size.x / 2 * 3 - 5;
			digit6Pos.x = digit5Pos.x = digit4Pos.x = digit3Pos.x;
			return; //if the number is <100
		}
		if (getScore() < 10000)
		{
			digit1Pos.x = window.x / 2 + size.x + 7.5;
			digit2Pos.x = window.x / 2 + 2.5;
			digit3Pos.x = window.x / 2 - size.x - 2.5;
			digit4Pos.x = window.x / 2 - size.x * 2 - 7.5;
			digit6Pos.x = digit5Pos.x = digit4Pos.x;
			return; //if the number is <100
		}

		if (getScore() < 100000)
		{
			digit1Pos.x = window.x / 2 + size.x / 2 * 3 + 10;
			digit2Pos.x = window.x / 2 + size.x / 2 + 5;
			digit3Pos.x = window.x / 2 - size.x / 2;
			digit4Pos.x = window.x / 2 - size.x / 2 * 3 - 5;
			digit5Pos.x = window.x / 2 - size.x / 2 * 5 - 10;
			digit6Pos.x = digit5Pos.x;
			return; //if the number is <100
		}

		digit1Pos.x = window.x / 2 + size.x * 2 + 12.5;
		digit2Pos.x = window.x / 2 + size.x + 7.5;
		digit3Pos.x = window.x / 2 + 2.5;
		digit4Pos.x = window.x / 2 - size.x - 2.5;
		digit5Pos.x = window.x / 2 - size.x * 2 - 7.5;
		digit6Pos.x = window.x / 2 - size.x * 3 - 12.5;
	}

	//Sets the position of the highscore digits
	void setHighScorePosition()
	{

		Hdigit6Pos.y = Hdigit5Pos.y = Hdigit4Pos.y = Hdigit3Pos.y = Hdigit2Pos.y = Hdigit1Pos.y = digit1Pos.y + size.y + (size.y) + 40;

		highScoreSprite.setPosition(sf::Vector2f(window.x / 2 - highScoreSprite.getGlobalBounds().width / 2, Hdigit6Pos.y - size.y / 2 - 20));

		if (getHighScore() < 10)
		{
			Hdigit6Pos.x = Hdigit5Pos.x = Hdigit4Pos.x = Hdigit3Pos.x = Hdigit2Pos.x = Hdigit1Pos.x = window.x / 2 - size.x / 2;
			return; //if the number is <10
		}

		if (getHighScore() < 100)
		{
			Hdigit1Pos.x = window.x / 2 + 2.5;
			Hdigit6Pos.x = Hdigit5Pos.x = Hdigit4Pos.x = Hdigit3Pos.x = Hdigit2Pos.x = window.x / 2 - size.x - 2.5;
			return; //if the number is <100
		}
		//if the number is >=100 sets all3  digits position
		if (getHighScore() < 1000)
		{
			Hdigit1Pos.x = window.x / 2 + size.x / 2 + 5;
			Hdigit2Pos.x = window.x / 2 - size.x / 2;
			Hdigit3Pos.x = window.x / 2 - size.x / 2 * 3 - 5;
			Hdigit6Pos.x = Hdigit5Pos.x = Hdigit4Pos.x = Hdigit3Pos.x;
			return; //if the number is <100
		}
		if (getHighScore() < 10000)
		{
			Hdigit1Pos.x = window.x / 2 + size.x + 7.5;
			Hdigit2Pos.x = window.x / 2 + 2.5;
			Hdigit3Pos.x = window.x / 2 - size.x - 2.5;
			Hdigit4Pos.x = window.x / 2 - size.x * 2 - 7.5;
			Hdigit6Pos.x = Hdigit5Pos.x = Hdigit4Pos.x;
			return; //if the number is <100
		}

		if (getHighScore() < 100000)
		{
			Hdigit1Pos.x = window.x / 2 + size.x / 2 * 3 + 10;
			Hdigit2Pos.x = window.x / 2 + size.x / 2 + 5;
			Hdigit3Pos.x = window.x / 2 - size.x / 2;
			Hdigit4Pos.x = window.x / 2 - size.x / 2 * 3 - 5;
			Hdigit5Pos.x = window.x / 2 - size.x / 2 * 5 - 10;
			Hdigit6Pos.x = Hdigit5Pos.x;
			return; //if the number is <100
		}

		Hdigit1Pos.x = window.x / 2 + size.x * 2 + 12.5;
		Hdigit2Pos.x = window.x / 2 + size.x + 7.5;
		Hdigit3Pos.x = window.x / 2 + 2.5;
		Hdigit4Pos.x = window.x / 2 - size.x - 2.5;
		Hdigit5Pos.x = window.x / 2 - size.x * 2 - 7.5;
		Hdigit6Pos.x = window.x / 2 - size.x * 3 - 12.5;
	}

	//Creates the card and all the elements in it
	void setDeathScreen(float dt)
	{
		if (deathScreenFlag)
		{
			if (YOffset > 0)
				YOffset -= YOffset * 10 * dt;
			if (YOffset < 0)
				YOffset = 0;
		}
		else
		{
			if (getScore() > getHighScore())
			{
				//writeHighScore();
				highScore = getScore();
				deathScreenSprite.setTexture(deathHighScreenTexture);
			}

			else
				deathScreenSprite.setTexture(deathScreenTexture);
		}

		deathScreenFlag = 1;
		deathScreenSprite.setPosition(sf::Vector2f(window.x / 2 - deathScreenSprite.getGlobalBounds().width / 2, window.y / 2 - deathScreenSprite.getGlobalBounds().height / 2 - size.y - YOffset)); //- YOffset
		digit1Pos.y = deathScreenSprite.getPosition().y + size.y + (size.y / 2 + 30);
		
	}

	//Legge dal Registro di sistema
	/*std::string OpenRegistryKey(LPCSTR subkey, LPCSTR name, DWORD type)
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
			RegSetValueEx(hKey, "HighScore", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char)); //creates the key
			return "";
		}

		if (lError != ERROR_SUCCESS)
		{
			//std::cout << "Something is wrong. Could no topen or create the key" << std::endl;
			RegCreateKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &value_length); //creates the register
			RegSetValueEx(hKey, "HighScore", 0, REG_SZ, (LPBYTE)"0", strlen("0") * sizeof(char));											  //creates the key
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
	int readHighScore()
	{
		std::string result = OpenRegistryKey("SOFTWARE\\FlappyXina", "HighScore", REG_SZ);
		//std::cout << "result: |"+ result+"|" << endl;

		if (result.size() > 0)
			highScore = 0;
		else
			highScore = std::stoi(result);
		//cout <<"highscore: "<< highScore<< endl;
		return highScore;
	}*/

	//gets The highscore
	int getHighScore()
	{
		return highScore;
	}

	//sets the system variable highscore
	/*void writeHighScore()
	{
		registry_write("SOFTWARE\\FlappyXina", "HighScore", REG_SZ, std::to_string(getScore()).c_str());
		highScore = score;
	}*/

	//gets The score
	int getScore()
	{
		return score;
	}

	bool getDeathScreenFlag()
	{
		return deathScreenFlag;
	}

	//Gives the sprite back
	sf::Sprite getScoreSprite(int digit)
	{
		setPosition();
		switch (digit)
		{
		case 1: //First digit sprite
			digitsSprites[getScore() % 10].setPosition(digit1Pos);
			return digitsSprites[getScore() % 10];

		case 2: //Second digit sprite
			digitsSprites[(int)(getScore() / 10) % 10].setPosition(digit2Pos);
			return digitsSprites[(int)(getScore() / 10) % 10];

		case 3: //Third digit sprite
			digitsSprites[(int)(getScore() / 100) % 10].setPosition(digit3Pos);
			return digitsSprites[(int)(getScore() / 100) % 10];

		case 4: //Third digit sprite
			digitsSprites[(int)(getScore() / 1000) % 10].setPosition(digit4Pos);
			return digitsSprites[(int)(getScore() / 1000) % 10];

		case 5: //Third digit sprite
			digitsSprites[(int)(getScore() / 10000) % 10].setPosition(digit5Pos);
			return digitsSprites[(int)(getScore() / 10000) % 10];

		case 6: //Third digit sprite
			digitsSprites[(int)(getScore() / 100000) % 10].setPosition(digit6Pos);
			return digitsSprites[(int)(getScore() / 100000) % 10];

		default:
			break;
		}

		return digitsSprites[0]; //if the number is >100
	}

	//Gives the sprite back
	sf::Sprite getHighScoreSprite(int digit)
	{
		setHighScorePosition();
		switch (digit)
		{
		case 1: //First digit sprite
			digitsSprites[getHighScore() % 10].setPosition(Hdigit1Pos);
			return digitsSprites[getHighScore() % 10];

		case 2: //Second digit sprite
			digitsSprites[(int)(getHighScore() / 10) % 10].setPosition(Hdigit2Pos);
			return digitsSprites[(int)(getHighScore() / 10) % 10];

		case 3: //Third digit sprite
			digitsSprites[(int)(getHighScore() / 100) % 10].setPosition(Hdigit3Pos);
			return digitsSprites[(int)(getHighScore() / 100) % 10];

		case 4: //Third digit sprite
			digitsSprites[(int)(getHighScore() / 1000) % 10].setPosition(Hdigit4Pos);
			return digitsSprites[(int)(getHighScore() / 1000) % 10];

		case 5: //Third digit sprite
			digitsSprites[(int)(getHighScore() / 10000) % 10].setPosition(Hdigit5Pos);
			return digitsSprites[(int)(getHighScore() / 10000) % 10];

		case 6: //Third digit sprite
			digitsSprites[(int)(getHighScore() / 100000) % 10].setPosition(Hdigit6Pos);
			return digitsSprites[(int)(getHighScore() / 100000) % 10];

		default:
			break;
		}

		return digitsSprites[0]; //if the number is >100
	}

	sf::Sprite getDeathSprite()
	{
		return deathScreenSprite;
	}
};	