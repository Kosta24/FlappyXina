#include "background.h" //Background and loading screen class
#include "obstacle.h"	//obstacle class
#include "player.h"		//Player class
#include "score.h"		//Score and highscore
#include "settings.h"	//Settings men�
#include <Windows.h>

using namespace sf;
using namespace std;

//PROTOTYPES
void resetGame(Time);	  //Reset Game function
void startGame(void);	  //Starts the game after a Reset
void death(void);		  //Death case function
void drawScore(void);	  //Draws The score
void drawHighScore(void); //Draws The Highscore
void drawSettingsMenu(void);
void manageVolume(void);

//CONSTANTS DEFINITION
const int FPS = 60;

//VARIABLES DEFINITION
//Screen resolution
int screenY = VideoMode::getDesktopMode().height - 120;
//int screenY = 900-120;
int screenX = (int)screenY / 3 * 2;

//COUNTERS
unsigned int i = 0;
unsigned int j = 0;

float floorHeight = 75;

Vector2f floorPos;

Image icon;

Texture floorTexture;
Sprite floorSprite;

SoundBuffer gameMusicBuffer;
SoundBuffer idleMusicBuffer;
SoundBuffer newHighScoreBuffer;
SoundBuffer deathSongBuffer;
SoundBuffer deathSoundBuffer;

Sound gameMusicSong;
Sound idleMusicSong;
Sound newHighScoreSound; //NEw highscore ssng
Sound deathSong;		 //No new highscore song
Sound deathSound;

RenderWindow window(VideoMode(screenX, screenY), "Flappy Xina", Style::Titlebar | Style::Close);
Player player(Vector2f(screenX, screenY), 4); //Create the player object
Obstacle obstacles[2];						  //Create the obstacles array
Score score(Vector2f(screenX, screenY), 0);	  //Creation of the score object and giving it a starting score to count from
Background background(Vector2f(screenX, screenY), FPS);
Settings settings(Vector2f(screenX, screenY));

int main(void)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	window.setFramerateLimit(FPS); //Limits the FPS

	window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - screenX / 2,
		sf::VideoMode::getDesktopMode().height / 2 - screenY / 2 - 30));

	Clock clock; //Creates the base clock for the dt
	Time now = clock.getElapsedTime();
	Time prev_time = now;
	Time dt = now - prev_time; //Time difference between the last frame and the new one. Its used for delta time based physics

	if (!icon.loadFromFile("src/assets/icon.png"))
		cout << "Error loading the icon" << endl;

	//Sets the Icon
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//sets the loading sprite
	background.loadingScreen(window, clock.getElapsedTime());

	if (!floorTexture.loadFromFile("src/assets/floor.png"))
		cout << "Error loading the background" << endl;

	//Loads the sounds

	if (!idleMusicBuffer.loadFromFile("src/music/idleMusic.ogg"))
		cout << "Error loading the maoDrip" << endl;
	idleMusicSong.setBuffer(idleMusicBuffer);
	background.loadingScreen(window, clock.getElapsedTime());

	if (!gameMusicBuffer.loadFromFile("src/music/maoDrip.ogg"))
		cout << "Error loading the maoDrip" << endl;

	background.loadingScreen(window, clock.getElapsedTime());

	if (!newHighScoreBuffer.loadFromFile("src/music/newHighScore.ogg"))
		cout << "Error loading the newHighScoreSound" << endl;

	background.loadingScreen(window, clock.getElapsedTime());

	//DEATH SONG
	if (!deathSongBuffer.loadFromFile("src/music/deathSong.ogg"))//deathSong
		cout << "Error loading the deathSong" << endl;

	background.loadingScreen(window, clock.getElapsedTime());

	//DEATH SOUND
	if (!deathSoundBuffer.loadFromFile("src/music/deathSound.ogg"))
		cout << "Error loading the deathSound" << endl;

	background.loadingScreen(window, clock.getElapsedTime());

	//Sets the floor Texture
	floorSprite.setTexture(floorTexture);
	floorPos.x = 0.0;
	floorPos.y = screenY - floorHeight;
	floorSprite.setPosition(floorPos);

	//Inizialize Player position
	player.setDefaultPos(window.getSize().x / 2 - player.size.x / 2 * 0, window.getSize().y / 2 - player.size.y / 2 * 0);
	player.resetPos();

	//Creation of the obstacles (screen resolutio, XOffset, YOffset, State)
	obstacles[0].setObstacle(Vector2f(screenX, screenY), 0, 300, 0);
	obstacles[1].setObstacle(Vector2f(screenX, screenY), screenX / 2 + 50, ((rand() % ((int)(screenY - 250) - 200)) + 100), 0);

	//Load the sounds
	newHighScoreSound.setBuffer(newHighScoreBuffer);
	deathSong.setBuffer(deathSongBuffer);
	deathSound.setBuffer(deathSoundBuffer);
	gameMusicSong.setBuffer(gameMusicBuffer);

	idleMusicSong.setVolume(settings.musicVolume);
	gameMusicSong.setVolume(settings.musicVolume);
	newHighScoreSound.setVolume(settings.musicVolume);
	deathSong.setVolume(settings.musicVolume);
	deathSound.setVolume(settings.effectsVolume);
	player.setPlayerVolume(settings.effectsVolume);

	clock.restart();
	while (window.isOpen() && background.loadingScreen(window, clock.getElapsedTime()));

	resetGame(clock.getElapsedTime());
	player.resetPlayer();
	//MAIN GAME LOOP
	while (window.isOpen())
	{
		now = clock.getElapsedTime();
		dt = now - prev_time; //Time that the last frame took to render
		prev_time = now;

		/*##########################################################################################*/
		//POLLING
		Event event;
		while (window.pollEvent(event))
		{
			//Closes the window if not focused
			if (event.type == Event::Closed) // || event.type == Event::LostFocus
				window.close();				 //When the X is clicked it closes the Window
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close(); //When escape is pressed it closes the Window

			//Flag used to mute the sound when the window is not focussed
			if (!window.hasFocus())
			{
				//window.close();
				settings.windowFocussed = 0;
			}
			else if (!settings.windowFocussed)
				settings.windowFocussed = 1;

			if (Keyboard::isKeyPressed(Keyboard::Space)) //When space is pressed the player Jumps
			{
				//if the state is playing, jump
				if (player.getState() == 1 || player.getState() == 2 || player.getState() == 4)
				{
					if (player.getState() == 4 && (prev_time - player.lastJump) > milliseconds(375))
						startGame();
					player.jump(prev_time);
				}
				//if the state is falled, reset all
				if (player.getState() == 5)
					resetGame(clock.getElapsedTime());
			}

			if (Mouse::isButtonPressed(Mouse::Left) || Mouse::isButtonPressed(Mouse::Right)) //When the left button is pressed the player Jumps
			{
				if (Mouse::getPosition(window).x > 0 && Mouse::getPosition(window).x < screenX)		//Prevents the mouse from restarting outside the game
					if (Mouse::getPosition(window).y > 0 && Mouse::getPosition(window).y < screenY) //Prevents the mouse from restarting outside the game
					{
						//checks if youre not colliding with the settings button
						if ((Mouse::getPosition(window).x < settings.settingsButtonPos.x || Mouse::getPosition(window).x >(settings.settingsButtonPos.x + settings.buttonSize.x))
							|| (Mouse::getPosition(window).y < settings.settingsButtonPos.y || Mouse::getPosition(window).y >(settings.settingsButtonPos.y + settings.buttonSize.y)))
							if (player.getState() == 4 && (prev_time - player.lastJump) > milliseconds(375))
								startGame();

						//if the state is playing, jump
						if (player.getState() == 1 || player.getState() == 2)
							player.jump(prev_time);

						//if the state is falled, reset all
						if (player.getState() == 5)
						{ //if (!(score.deathScreenSprite.getGlobalBounds()).contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
							resetGame(clock.getElapsedTime());
						}
						if (player.getState() == 6)
							settings.checkSlider(Mouse::getPosition(window));
					}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (player.getState() == 6)
				{
					//settings screen
					if (settings.getState() == 0)
					{ //if collides with the close button
						if (Mouse::getPosition(window).x > (settings.buttonClosePos.x - settings.buttonSize.x / 2) && Mouse::getPosition(window).x < (settings.buttonClosePos.x + settings.buttonSize.x / 2))
							if (Mouse::getPosition(window).y > (settings.buttonClosePos.y - settings.buttonSize.y / 2) && Mouse::getPosition(window).y < (settings.buttonClosePos.y + settings.buttonSize.y / 2))
							{
								player.setState(4);
								//settings.writeSettings(); //salvataggio su registri
							}

						settings.checkCollision(Mouse::getPosition(window));
					}
					else //credits screen
						settings.checkCollision(Mouse::getPosition(window));
				}
				else if (player.getState() == 4)
					if (Mouse::getPosition(window).x > settings.settingsButtonPos.x && Mouse::getPosition(window).x < (settings.settingsButtonPos.x + settings.buttonSize.x))
						if (Mouse::getPosition(window).y > settings.settingsButtonPos.y && Mouse::getPosition(window).y < (settings.settingsButtonPos.y + settings.buttonSize.y))
							player.setState(6);
			}

			if (Keyboard::isKeyPressed(Keyboard::R)) //When R is pressed restarts the game
				resetGame(clock.getElapsedTime());
		}

		//if there has been a change in the settings theyre updated
		if (settings.changed || !settings.windowFocussed)
			manageVolume();

		/*##########################################################################################*/
		//MOVEMENTS CALCULATION
		if (player.getState() == 1 || player.getState() == 2 || player.getState() == 3 || player.getState() == 4)
		{
			player.move(dt.asSeconds()); //Player movement
			//moves the floor if in one of these states
			if (player.getState() == 4 || player.getState() == 1 || player.getState() == 2)
			{
				//moves the floor
				floorPos.x -= obstacles[0].getVel().x * dt.asSeconds();
				if (floorPos.x < -floorSprite.getGlobalBounds().width) //when the sprite scolls too far its resetted
					floorPos.x = 0;
			}
			if (player.getState() == 4)
				background.setClickToJumpPos(dt);

			//###################
			//Moves the obstacles only if the state is play
			if (player.getState() == 1 || player.getState() == 2)
			{
				//Obstacle movement and collision calculation
				for (i = 0; i < (sizeof(obstacles) / sizeof(*obstacles)); i++)
				{
					obstacles[i].move(dt.asSeconds(), now.asMilliseconds(), score.getScore()); //Moves the obstacles

					//###################
					//check for collision only if the player state is 1
					if (player.getState() == 1)
					{
						//Checks for collisions if true do the death
						if (player.checkCollisions(obstacles[i].getPosT(), obstacles[i].getSizeT()) || player.checkCollisions(obstacles[i].getPosB(), obstacles[i].getSizeB()))
						{
							player.setState(3); //state 3  = death*/
							for (j = 0; j < (sizeof(obstacles) / sizeof(*obstacles)); j++)
								obstacles[j].state = 0; //state 0 = stop*/

							idleMusicSong.stop();
							gameMusicSong.stop(); //stop the music
							deathSound.play();	  //plays the death sound
						}
					} //end if(player.getState() == 1)

					//If the obstacle isnt scored yet and it passed the player position it adds to the score
					if (!obstacles[i].scored && score.addScore(player.getPos(), obstacles[i].getPosT(), player.getSize().x))
					{
						//cout << score.getScore() << endl;
						if (!settings.mutePlayerSoundEffects)
							player.getSound(rand() % 10, now);
						obstacles[i].scored = 1; //sets the obstacle flag to 1 so its not counted again
					}
				} // end for obstacles

			} //end if(player.getState() == 1 || player.getState() == 2)
		}
		floorSprite.setPosition(floorPos);

		if (player.getState() == 5 && !score.getDeathScreenFlag())
			death();

		/*##########################################################################################*/
		//RENDERING
		window.clear();

		//Rendering if playing
		if (player.getState() > 0)
		{
			window.draw(background.getBackground_Background());
			if (player.getState() != 6)
				background.rotateBg(dt.asSeconds());

			window.draw(background.getBackground_Foreground());

			//Draws the obstacles
			for (i = 0; i < (sizeof(obstacles) / sizeof(*obstacles)); i++)
			{
				window.draw(obstacles[i].getSprite(0)); //renders the top part
				window.draw(obstacles[i].getSprite(1)); //renders the bottom part
			}

			//Draws the player
			window.draw(player.getSprite());

			//Draws the floor 2 times to that you can use only one sprite
			window.draw(floorSprite);
			floorSprite.setPosition(Vector2f(floorPos.x + floorSprite.getGlobalBounds().width, screenY - floorHeight));
			window.draw(floorSprite);

			if (player.getState() != 3)
			{
				if (player.getState() == 5) //Death Score State
				{
					score.setDeathScreen(dt.asSeconds());
					drawHighScore();

				} //End Death Score State
				if (player.getState() == 4)
				{
					window.draw(background.titleScreenSprite);
					window.draw(background.getClickToJumpSprite());
					window.draw(settings.settingsButtonSprite);
				}
				else if (player.getState() != 6)
					drawScore();
			} //End if (player.getState() != 3)

			if (player.getState() == 6)
			{
				window.draw(background.titleScreenSprite);
				//prints the configuration men�
				drawSettingsMenu();
			}
		}

		window.display();
	}

	return 0;
}

//resets the game to the inizial state
void resetGame(Time Anow)
{
	player.lastJump = Anow; //sets the time to now so that you dont jump on reset
	player.resetPlayer();
	for (i = 0; i < (sizeof(obstacles) / sizeof(*obstacles)); i++)
		obstacles[i].reset();

	score.reset();
	settings.setState(0);

	background.setDaySpeed(75); //75

	newHighScoreSound.stop();
	deathSong.stop();
	deathSound.stop();
	gameMusicSong.stop();
	idleMusicSong.stop();
	idleMusicSong.stop();
	idleMusicSong.play();
	idleMusicSong.setLoop(true);
}

//STARTS THE GAME
void startGame(void)
{
	player.setState(1); //Sets the player state
	for (i = 0; i < (sizeof(obstacles) / sizeof(*obstacles)); i++)
		obstacles[i].setState(1);

	idleMusicSong.stop();
	gameMusicSong.stop();
	gameMusicSong.play();
	gameMusicSong.setLoop(true);
}

void death(void)
{
	//Play the new highscore song
	if (score.getScore() > score.getHighScore())
		newHighScoreSound.play();
	else //play the normal death song
		deathSong.play();

	score.setDeathScreen(0.0);
}

void drawScore(void)
{
	//Draws the score
	window.draw(score.getScoreSprite(1));
	if (score.getScore() >= 10)
		window.draw(score.getScoreSprite(2));
	if (score.getScore() >= 100)
		window.draw(score.getScoreSprite(3));
	if (score.getScore() >= 1000)
		window.draw(score.getScoreSprite(4));
	if (score.getScore() >= 10000)
		window.draw(score.getScoreSprite(5));
	if (score.getScore() >= 100000)
		window.draw(score.getScoreSprite(6));
}

void drawHighScore(void)
{
	window.draw(score.getDeathSprite());

	window.draw(score.scoreSprite);
	window.draw(score.highScoreSprite);

	//Draws the score
	window.draw(score.getHighScoreSprite(1));
	if (score.getHighScore() >= 10)
		window.draw(score.getHighScoreSprite(2));
	if (score.getHighScore() >= 100)
		window.draw(score.getHighScoreSprite(3));
	if (score.getHighScore() >= 1000)
		window.draw(score.getHighScoreSprite(4));
	if (score.getHighScore() >= 10000)
		window.draw(score.getHighScoreSprite(5));
	if (score.getHighScore() >= 100000)
		window.draw(score.getHighScoreSprite(6));
}

void drawSettingsMenu(void)
{
	settings.setSettings();

	if (settings.getState() == 0)
	{
		window.draw(settings.backgroundSprite);

		window.draw(settings.effectsMuteSprite);
		window.draw(settings.musicMuteSprite);
		window.draw(settings.playerMuteSprite);
		window.draw(settings.buttonCloseSprite);
		window.draw(settings.buttonCreditsSprite);

		//Slider Effects
		window.draw(settings.filledSliderEffectsSprite);
		window.draw(settings.unfilledSliderEffectsSprite);
		window.draw(settings.sliderEffectsButtonSprite);

		//Slider Music
		window.draw(settings.filledSliderMusicSprite);
		window.draw(settings.unfilledSliderMusicSprite);
		window.draw(settings.sliderMusicButtonSprite);

		window.draw(settings.musicVolumeTextSprite);
		window.draw(settings.effectsVolumeTextSprite);
		window.draw(settings.playerVolumeTextSprite);
	}
	else
	{
		window.draw(settings.creditsSprite);
		window.draw(settings.buttonCloseSprite);
	}
}

//VOLUME MANAGEMENT
void manageVolume(void)
{

	settings.changed = 0;
	//if music is not muted
	if (!settings.muteMusic)
	{
		gameMusicSong.setVolume(settings.musicVolume);
		idleMusicSong.setVolume(settings.musicVolume);
		newHighScoreSound.setVolume(settings.musicVolume);
		deathSong.setVolume(settings.musicVolume);
	}
	else
	{
		gameMusicSong.setVolume(0.0);
		idleMusicSong.setVolume(0.0);
		newHighScoreSound.setVolume(0.0);
		deathSong.setVolume(0.0);
	}

	if (!settings.muteEffects)
	{
		deathSound.setVolume(settings.effectsVolume);
		player.setPlayerVolume(settings.effectsVolume,0,10);
	}
	else
	{

		deathSound.setVolume(0.0);
	}

	//if the window is not focussed it silences the sounds
	if (!settings.windowFocussed)
	{
		idleMusicSong.setVolume(0.0);
		gameMusicSong.setVolume(0.0);
		newHighScoreSound.setVolume(0.0);
		deathSong.setVolume(0.0);
		deathSound.setVolume(0.0);
		player.setPlayerVolume(0, 0, 10);

		settings.changed = 1;
	}
}