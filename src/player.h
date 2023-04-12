#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <cmath>

class Player
{

public:
	//FUNCTION PROTOTYPES
	//Vector2f move(float);						//Calculate the movement
	//bool is_aabb_collision(Vector2f, Vector2f); //Calculate if is colliding
	//bool checkCollisions(Vector2f, Vector2f);	//Calculate where is colliding
	//void jump(Time);							//Calculates the jump
	//void setDefaultPos(float, float);			//Changes the startPosition
	//void resetPlayer();							//Sets the player to the start position
	//Sprite getSprite();							//Gives the Sprite

	//CONSTANTS DEFINITION
	const float jumpPow = 760;//820
	const float gravity = 2400;
	const float terminalVel = 1000;

	//VARIABLES DEFINITION
	int state = 0; //State of the player
	unsigned int i = 0;
	unsigned int j = 0;

	float idleGravity = 1;

	sf::Vector2f size;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f startPos; //Starting position
	sf::Vector2f window;   //Window Sizes

	sf::Texture texture;
	sf::Texture death_texture;
	sf::Texture talking_texture;
	sf::Sprite sprite;
	sf::Time lastJump = sf::milliseconds(0);
	sf::Time lastTalk = sf::milliseconds(0);

	sf::SoundBuffer playerSoundBuffer[10];
	sf::Sound playerSounds[10];
	//SoundBuffer playerSoundsBuffer[10];
	//Sound playerSounds[10];

	//CONSTRUCTOR
	Player(sf::Vector2f Awindow, int Astate = 4)
	{
		window.x = Awindow.x; //Screen resolution
		window.y = Awindow.y;

		state = Astate;

		size.x = 90; //32
		size.y = 90; //24

		pos.x = 0;
		pos.y = 0;

		startPos.x = 0;
		startPos.y = 0;

		vel.x = 0;
		vel.y = 0;

		//Loads the texture
		if (!texture.loadFromFile("src/assets/player/player_sprite.png")) //player_sprite White_Square2
			std::cout << "Error loading player sprite" << std::endl;

		if (!death_texture.loadFromFile("src/assets/player/player_death_sprite.png")) //player_sprite White_Square2
			std::cout << "Error loading player death sprite" << std::endl;

		if (!talking_texture.loadFromFile("src/assets/player/player_talking_sprite.png")) //player_sprite White_Square2
			std::cout << "Error loading player talking sprite" << std::endl;

		//loads the sounds in the buffer array
		for (i = 0; i < 10; i++)
		{
			j = i;
			if (i >= 7 && i < 9)
				j = 2;
			if ((i < 7 || i >= 9) && !playerSoundBuffer[i].loadFromFile("src/music/playerSounds/" + std::to_string(j) + "_.ogg"))
				std::cout << "Error loading player sound " + std::to_string(j) + "_" << std::endl;

			playerSounds[i].setBuffer(playerSoundBuffer[j]);
		}

		sprite.setTexture(texture); //*/

		//Adapts the texture to the sprite
		sprite.setScale(
			size.x / sprite.getLocalBounds().width,
			size.y / sprite.getLocalBounds().height);

		auto offset = sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().width / 2) - sprite.getOrigin();
		sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().width / 2));
		sprite.move(offset);

	}

	//MOVEMENT CALCULATION
	sf::Vector2f move(float dt)
	{
		switch (state)
		{
		case 0: //Beginning
			resetPlayer();
			break;

		case 1:						 //Normal movement
			if (vel.y < terminalVel) //la velocità aumenta fino ad un certo punto
				vel.y += gravity * dt;

			pos.x += vel.x * dt;
			pos.y += vel.y * dt;

			//Rotation
			if (vel.y >= terminalVel / 5 * 4.5 && (sprite.getRotation() >= 0 || sprite.getRotation() < 180))
			{
				sprite.rotate(250 * dt);
				if (sprite.getRotation() > 180) //Prevents the player from turning more than 90°
					sprite.setRotation(180);
			}
			break;

		case 2:						 //Invulnerability
			if (vel.y < terminalVel) //la velocità aumenta fino ad un certo punto
				vel.y += gravity * dt;

			pos.x += vel.x * dt;
			pos.y += vel.y * dt;

			//Rotation
			if (vel.y >= terminalVel / 5 * 4.5 && (sprite.getRotation() >= 0 || sprite.getRotation() < 180))
			{
				sprite.rotate(250 * dt);
				if (sprite.getRotation() > 180) //Prevents the player from turning more than 90°
					sprite.setRotation(180);
			}
			break;

		case 3:								  //Death case
			sprite.setTexture(death_texture); //*/
			/*vel.y = 0;// */
			if (vel.y < terminalVel) //la velocità aumenta fino ad un certo punto
				vel.y += gravity * dt;

			pos.x += vel.x * dt;
			pos.y += vel.y * dt;

			//if the player touches the ground
			if ((pos.y + size.y * (1 - sprite.getRotation() / 180)) >= window.y - 50) //
			{
				vel.y = 0;
				pos.y = window.y - size.y * (1 - sprite.getRotation() / 180) - 50;
				state = 5; //5
			}
			else //if the player doesent tocuh the ground
			{
				//Rotation
				if (sprite.getRotation() >= 0 || sprite.getRotation() < 180)
				{
					sprite.rotate(500 * dt);
					if (sprite.getRotation() > 180) //Prevents the player from turning more than 90°
						sprite.setRotation(180);
				}
			} //*/
			break;

		case 4: //idle case
			if (vel.y < -60)
			{
				idleGravity = 100;
			}
			if (vel.y > 60)
			{
				idleGravity = -100;
				pos.y = startPos.y;
			}
			vel.y += idleGravity * dt;
			pos.y += vel.y * dt;
			//std::cout << vel.y << std::endl;
			//sprite.setRotation((90 + (45*(pos.y - startPos.y - idleMove)/idleMove*2)));
			break;

		case 5: //Fallen case
			vel.x = 0;
			vel.y = 0;
			break;

		case 6: //pause case

			break;

		default: //Optional
			break;
		}

		return pos;
	}

	//CALCULATE IF THE PLAYER IS COLLIDING
	bool is_aabb_collision(sf::Vector2f objPos, sf::Vector2f objSize)
	{
		//float x_collision = (fabs(pos.x - objPos.x) * 2) < (size.x + objSize.x);
		//float y_collision = (fabs(pos.y + 1 - objPos.y) * 2) < (size.y + objSize.y);
		//X
		if ((pos.x - size.x / 2 + size.x / 5 * 1.1) > objPos.x + objSize.x) //if player min > object max
			return false;

		if ((pos.x + size.x / 2 - size.x / 5 * 1.1) < objPos.x) //if player max < object min (pos.x + size.x*((fabs(sprite.getRotation()-90))/90) - size.x/5*1.1)
			return false;

		//Y
		//adds the hypotenusas to the height
		if ((pos.y - size.y / 2) > objPos.y + objSize.y) //if player min > object max
			return false;

		if ((pos.y + size.y / 2) < objPos.y) //if player max < object min
			return false;

		return true;
	}

	//CONTROLLA COLLIZIONI
	bool checkCollisions(sf::Vector2f objPos, sf::Vector2f objSize)
	{
		if (is_aabb_collision(objPos, objSize))
		{
			// Player is to the left
			if ((pos.x - 2 < objPos.x) && (pos.y + size.y / 2.0 > objPos.y - objSize.y / 2.0)) // && (pos.y + size.y / 2.0 > objPos.y - objSize.y / 2.0)
			{
				//cout << "Left" << endl;
				return true;
			}
			//player is on bottom
			else if ((pos.y - size.y / 2) < objPos.y + objSize.y && pos.y + size.y / 2 > objPos.y + objSize.y)
			{
				//std::cout << "Bottom" << std::endl;
				pos.y = objPos.y + objSize.y + size.y / 2;
				vel.y = 0;
			}
			//player is on the top
			else if ((pos.y + size.y / 2) > objPos.y && pos.y - size.y / 2 < objPos.y + objSize.y)
			{
				//std::cout << "Top" << std::endl;
				//sprite.setRotation(0);
				pos.y = objPos.y - size.y / 2;
				vel.y = 0;
			}
			return true;
		}

		//Checks collision with the ground
		//if the player touches the ground
		if (pos.y + size.y / 2 >= window.y - 50)
		{
			sprite.setTexture(death_texture); //*/
			vel.y = 0;
			pos.y = window.y - size.y / 2 - 50;
			sprite.setPosition(pos);
			state = 5; // its alreadye state 4 because youre on the ground
			return true;
		}
		//Checks collision with the sky
		else if (pos.y - size.y / 2 < -100 && (pos.x + size.x > objPos.x && pos.x < objPos.x + objSize.x))
		{
			pos.y = -100 + size.y / 2;
			return true;
		}
		return false;
	}

	void jump(sf::Time tLastJump) //Calculates the jump
	{

		if ((tLastJump - lastTalk) > sf::milliseconds(0) && sprite.getTexture() != &texture)
			sprite.setTexture(texture);
		//Only jumps when the state is either 1 or 2 and it have been 125 ms since the last jump
		if ((state == 1 || state == 2) && (tLastJump - lastJump) > sf::milliseconds(125))
		{
			lastJump = tLastJump;
			vel.y = -jumpPow;
			sprite.setRotation(0);

			//std::cout <<state<< std::endl;
		}
		else if (state == 4 && (tLastJump - lastJump) > sf::milliseconds(375))
			jump(tLastJump);
	}

	void setDefaultPos(float x, float y) //Sets the start position
	{
		startPos.x = x;
		startPos.y = y;
	}

	void resetPos() //Resets the player position
	{
		pos.x = startPos.x;
		pos.y = startPos.y;
	}

	void resetPlayer() //Resets the player Condition
	{
		state = 4;
		vel.x = 0;
		vel.y = 60;

		sprite.setTexture(texture); //*/
		resetPos();					//Resets the player position
		sprite.setRotation(0);
	}

	int getState()
	{
		return state;
	}

	void setState(int Astate)
	{
		state = Astate;
	}

	void setPlayerVolume(float volume, int start = 0, int end = -1)
	{
		if (end == -1)
			end = start;
		for (i = start; i < (unsigned)end; i++)
			playerSounds[i].setVolume(volume);
	}

	//Gets the sound and calculates when to open the mouth base on the sound duration
	sf::Sound getSound(int index, sf::Time tLastTalk)
	{
		sprite.setTexture(talking_texture);
		lastTalk = tLastTalk + playerSoundBuffer[index].getDuration();
		if (index == 2 || index == 7 || index == 8)//Se il suono è AAHH apre la bocca per meno tempo
			lastTalk = tLastTalk + sf::milliseconds(1200);
		playerSounds[index].play();
		return playerSounds[index];
	}

	sf::Vector2f getPos()
	{
		return pos;
	}

	sf::Vector2f getSize()
	{
		return size;
	}

	sf::Sprite getSprite()
	{
		sprite.setPosition(pos);
		return sprite;
	}
};