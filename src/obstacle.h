#include <SFML/Graphics.hpp>
#include <iostream>

class Obstacle
{

public:
	int state = 0;
	int stage = 1;

	bool scored = 0;

	float XOffset;
	float YOffset;
	float gap = 270; //250

	sf::Vector2f sizeT; //top obstacle size
	sf::Vector2f sizeB; //bottom obstacle size
	sf::Vector2f posT;	//top obstacle position
	sf::Vector2f posB;	//bottom obstacle position
	sf::Vector2f vel;
	sf::Vector2f window; //Window Sizes

	sf::Texture texture1;
	sf::Texture texture2;
	sf::Sprite topSprite;
	sf::Sprite botSprite;

	void setObstacle(sf::Vector2f Awindow, float AXOffset, float AYOffset, int Astate = 0)
	{
		state = Astate; //Stato in cui si trovano i tubi, 1 = play

		window.x = Awindow.x; //screen resolution
		window.y = Awindow.y;

		XOffset = AXOffset; //screen Offset
		YOffset = AYOffset;

		//Top block size
		sizeT.x = 100;		//Width
		sizeT.y = window.y; //Height

		//Bottom block size
		sizeB.x = 100;		//Width
		sizeB.y = window.y; //Height

		posT.x = window.x * 2 + XOffset;
		posT.y = -window.y + YOffset;

		posB.x = posT.x;
		posB.y = posT.y + sizeT.y + gap;

		vel.x = 200;
		vel.y = 30;

		//Loads the texture

		if (!texture1.loadFromFile("src/assets/tower.png")) //tower
			std::cout << "Error loading obstacle sprite" << std::endl;

		if (!texture2.loadFromFile("src/assets/tower2.png")) //tower2
			std::cout << "Error loading obstacle sprite" << std::endl;

		topSprite.setTexture(texture1);
		botSprite.setTexture(texture2);

		//topSprite.setColor(Color::White);
		//botSprite.setColor(Color::White);

		//Adapts the texture to the sprite
		topSprite.setScale(
			sizeT.x / topSprite.getLocalBounds().width,
			sizeT.y / topSprite.getLocalBounds().height);

		//topSprite.setRotation(180);

		//Adapts the texture to the sprite
		botSprite.setScale(
			sizeB.x / botSprite.getLocalBounds().width,
			sizeB.y / botSprite.getLocalBounds().height);

		//Iniziatilze the position
		topSprite.setPosition(posT);
		botSprite.setPosition(posB);
	}

	sf::Vector2f move(float dt, int Asrand, int score)
	{
		switch (state)
		{
		case 0: //Stop

			break;

		case 1:					  //Game running stage 1
			posT.x -= vel.x * dt; //moves the top to the left
			//posT.y -= -20 * dt; //moves the top to the left

			posB.x = posT.x; //moves the bottom to the left
			//posB.y = posT.y + sizeT.y + gap; //moves the bottom to the left

			if ((posT.x + sizeT.x) < 0) //if the block goes off screen its resetted and the gap changes
			{
				posT.x = window.x;
				posB.x = window.x;
				scored = 0;
				if (score >= 10 && score < 100 && (rand() % (10 - ((score / 10) % 10))) == 0)
					state = 2;
				else if (score >= 100)
					state = 2;

				//Changind randomly the gap height with a margin of 100 pixels from top and bottom
				srand(Asrand);
				changeYOffset((rand() % ((int)(window.y - gap) - 200)) + 100);
			}
			break;

		case 2:					  //Game running stage 2
			posT.x -= vel.x * dt; //moves the top to the left
			posT.y -= vel.y * dt; //moves the top to the left

			if (posT.y + sizeT.y < 100)
				vel.y = (vel.y * ((vel.y > 0) - (vel.y < 0))) * (-1);
			if (posB.y > window.y - 100)
				vel.y = (vel.y * ((vel.y > 0) - (vel.y < 0))) * (1);

			posB.x = posT.x;				 //moves the bottom to the left
			posB.y = posT.y + sizeT.y + gap; //moves the bottom to the left

			if ((posT.x + sizeT.x) < 0) //if the block goes off screen its resetted and the gap changes
			{
				posT.x = window.x;
				posB.x = posT.x;
				scored = 0;
				//if the score is <100 but >10 there is a growing change of moving obstacles
				if (score >= 10 && score < 100)
				{
					if ((rand() % (10 - ((score / 10) % 10))) == 0)
						state = 2;
					else
						state = 1;
				}
				else if (score >= 100)
					state = 2;

				//Changind randomly the gap height with a margin of 100 pixels from top and bottom
				srand(Asrand);
				changeYOffset((rand() % ((int)(window.y - gap) - 200)) + 100);
			}
			break;

		default: //Optional
			break;
		}

		return posT;
	}

	//Changes the Height of the Top Block and so the Position of the Bottom one
	void changeYOffset(float AYOffset)
	{

		YOffset = AYOffset;
		posT.y = -window.y + YOffset;	 //Changes the top block hight
		posB.y = posT.y + sizeT.y + gap; //Changes the bottom block position

		//Scales the top block
		topSprite.setScale(
			sizeT.x / topSprite.getLocalBounds().width,
			sizeT.y / topSprite.getLocalBounds().height);

		//Scales the Bottom block
		botSprite.setScale(
			sizeB.x / botSprite.getLocalBounds().width,
			sizeB.y / botSprite.getLocalBounds().height);
	}

	//rResets the obstacles to the new game state
	void reset()
	{
		posB.y = posT.y + sizeT.y + gap;
		changeYOffset((rand() % ((int)(window.y - gap) - 200)) + 100);
		scored = 0;
		state = 5;
		sizeT.y = window.y; //Changes the top block hight

		posT.x = window.x * 2 + XOffset;
		posT.y = -window.y + YOffset;

		posB.x = posT.x;
		posB.y = posT.y + sizeT.y + gap;

		//Scales the top block
		topSprite.setScale(
			sizeT.x / topSprite.getLocalBounds().width,
			sizeT.y / topSprite.getLocalBounds().height);

		//Scales the Bottom block
		botSprite.setScale(
			sizeB.x / botSprite.getLocalBounds().width,
			sizeB.y / botSprite.getLocalBounds().height);
	}

	int setState(int Astate)
	{
		state = Astate;
		return state;
	}

	int getState()
	{
		return state;
	}

	sf::Vector2f getVel()
	{
		return vel;
	}

	sf::Vector2f getPosT() //Gets the position of the Top Block
	{
		return posT;
	}

	sf::Vector2f getPosB() //Gets the position of the Bottom Block
	{
		return posB;
	}

	sf::Vector2f getSizeT() //Gets the size of the Top Block
	{
		return sizeT;
	}

	sf::Vector2f getSizeB() //Gets the size of the Bottom Block
	{
		return sizeB;
	}

	sf::Sprite getSprite(int obstacle)
	{
		switch (obstacle)
		{
		case 0:
			topSprite.setPosition(posT);
			return topSprite;
		case 1:
			botSprite.setPosition(posB);
			return botSprite;

		default:
			return botSprite;
			break;
		}
	}
};