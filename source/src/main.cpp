#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include "main.h"



using namespace sf;
using namespace std;

sf::Texture stick50, objYeetTex, stickJump, obstacleTex;
sf::Sprite player, objYeet, obstacle, obstacle1, obstacle2, objYeet1, objYeet2;
const int ground = 452;
bool programFirstTime = true;
sf::RenderWindow window(VideoMode(800, 600), "The Yeeter"); // Create the window.;
int main() {

	int obstacleXs[3];

	//TODO: Implement a way to decide if a yeetStick should be spawned above obstacleX values.

	//TODO: Implement a way to have the obstacles move to the left, when they disappear, they should be destroyed, and a new one should take it's place.

	//window(VideoMode(800, 600), "The Yeeter"); // Create the window.

	Music meow;
	meow.openFromFile("assets/score.ogg");
	Music fail;
	fail.openFromFile("assets/failed.ogg");

	meow.setVolume(50);
	fail.setVolume(50);
	stick50.loadFromFile("assets/Stickman.png");
	stickJump.loadFromFile("assets/stickmanJump.png");
	objYeetTex.loadFromFile("assets/yeetObjTex_ctc.png");
	obstacleTex.loadFromFile("assets/obstacleTex.png");
	
	objYeet.setTexture(objYeetTex);
	objYeet1.setTexture(objYeetTex);
	objYeet2.setTexture(objYeetTex);
	
	obstacle.setTexture(obstacleTex);
	obstacle1.setTexture(obstacleTex);
	obstacle2.setTexture(obstacleTex);
	
	/*obstacle.setScale(Vector2f(2.3, 2.3));
	obstacle1.setScale(Vector2f(2.3, 2.3));
	obstacle2.setScale(Vector2f(2.3, 2.3));*/
	Color status = Color(255, 255, 255);
	float playerX, playerY;
	float priv_playerX = 0;
	playerX = 0;
	playerY = ground;
	float speed = 1;
	int obstacleX = 0;
	int obstacleX1 = 0;
	int obstacleX2 = 0;
	int objYeetRot = 0;
	int objYeetRot1 = 0;
	float vol = 100;
	player.setTexture(stick50);


	//Clock clock;
	//float lastTime = 0;
	bool jump = false;
	bool reset = false;
	bool failed = false;
	bool goingUp = false;
	bool firstRun = true;
	bool firstTime = true;
	bool goingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
	bool restrictDisp = false;
	bool objYeetMoving = false;
	bool objYeetMoving1 = false;

	meow.setLoop(true);
	meow.play();


	while (window.isOpen()) {
		srand(time(0));
		std::srand(time(0));
		if (firstRun == true) {
			obstacleX = (rand() % 200) + 78;
			obstacleX1 = (rand() % 400) + 78 + std::rand() % 50;
			obstacleX2 = (rand() % 600) + 78 + std::rand() % 50;
			/*if ((obstacleX2 - obstacleX1) >= abs((long)100)) {
				obstacleX2 = std::rand();
			}
			else {
				break;
			}
			}*/

#ifndef size2p3
#define size2p3 542.5
#endif
#ifndef normsize
#define normsize 575
#endif // !normsize

			obstacle.setPosition(78 + obstacleX, normsize);
			obstacle.setColor(Color(255, 0, 0, 255));
			
			obstacle1.setPosition(78 + obstacleX1, normsize);
			obstacle1.setColor(Color(0, 255, 0, 255));
			
			obstacle2.setPosition(78 + obstacleX2, normsize);
			obstacle2.setColor(Color(0, 0, 255, 255));
			
			
			//objYeet.setColor(Color(255,255,255,));
			
			if (std::rand() % 2 == 0) {
				//objYeet.setColor(Color(255,255,255,0));
				objYeet.setPosition(obstacleX, 475);
			}
			//if (std::rand() % 2 == 0) {
				objYeet1.setPosition(obstacleX1, 475);
			//}
			if (std::rand() % 2 == 0) {
				objYeet2.setPosition(obstacleX2, 475);
			}
			firstRun = false;
		}
		if ((meow.getStatus() == meow.Stopped) && failed == false) {
			meow.play();
		}

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up)) {
					if (vol < 100)
						vol += 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (vol > 0)
						vol -= 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
					movingLeft = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
					movingRight = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Pause))
				{
					// Reset jump-related flags:
					jump = goingUp = goingDown = false; // Set all flags for jumping to false
					firstTime = true;
					fail.stop();
					// Reset player:
					playerX = 0; // Resets player's X-coordinate on the window
					playerY = ground; // Resets player's X-coordinate on the window
					player.setTexture(stick50); // Sets player's texture to the one used when not jumping

					objYeet.setPosition(100, 475);

					firstRun = true;
					obstacleX = 0;
					objYeetMoving = false;
					objYeet.setRotation(0);
					objYeetMoving1 = false;
					objYeetRot1 = 0;
					objYeetMoving = false;
					objYeetRot = 0;
					speed = 1;
					// Reset window:
					window.clear(Color(255, 255, 0)); // We will use yellow because if seen, we will know that we reset the game.
					window.display(); // Now we update the window and (maybe) show the yellow-colored window. NOTE: If you blink, you WILL miss it, it's that fast. Seriously.
					failed = false;
				}
				else if (Keyboard::isKeyPressed(Keyboard::T)) {
					if (debug == false)
						debug = true;
					else
						debug = false;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					if (playerY >= ground) {
						jump = true; // Set jump flag to true.
						goingUp = true; // When we jump, we will always gain a little height, (sometimes not much, but still). This flag should be self-explainatory.
					}
				}

			}
			else if (e.type == Event::KeyReleased)
			{
				if ((e.key.code == Keyboard::Left) || (e.key.code == Keyboard::A))
				{
					movingLeft = false;
				}
				else if ((e.key.code == Keyboard::Right) || (e.key.code == Keyboard::D))
				{
					movingRight = false;
				}
			}
		}


		/*if (((obstacleX <= playerX) || (obstacleX <= (playerX + 72)))
		&& ((obstacleX + 25 >= playerX) || ((obstacleX + 25) >= (playerX + 72)))) {
			failed = true;
		}	*/

		/*if (obstacleX < 100) {
			obstacleX = 100;
		}
		if (obstacleX1 < 100) {
			obstacleX1 = 100;
		}
		if (obstacleX2 < 100) {
			obstacleX2 = 100;
		}*/
		if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
			// Do function here.
			if (debug != true)
				failed = true;
		}
		if (player.getGlobalBounds().intersects(obstacle1.getGlobalBounds())) {
			// Do function here.
			if (debug != true)
			failed = true;
		}
		if (player.getGlobalBounds().intersects(obstacle2.getGlobalBounds())) {
			// Do function here.
			if (debug != true)
			failed = true;
		}
		

		if (player.getGlobalBounds().intersects(objYeet.getGlobalBounds())) {
			// Do function here.
			objYeetMoving = false;
		}
		if (player.getGlobalBounds().intersects(objYeet1.getGlobalBounds())) {
			// Do function here.
			objYeetMoving1 = true;
		}
		if (player.getGlobalBounds().intersects(objYeet2.getGlobalBounds())) {
			// Do function here.

		}


		if (objYeetMoving == true) {
			objYeet.move(Vector2f(speed / 2, -2));
			objYeet.rotate(2);
		}

		if (objYeetMoving1 == true) {
			objYeet1.move(Vector2f(speed / 2, -10));
			objYeet1.rotate(1);
		}

		/*if ((int) priv_playerX % 800 == 0) {
			speed += 1;
		}*/
		

		// ========= Move ========= MOVE ========= Move ========= MOVE =========
		if (movingLeft == true) {
			if (playerX > 0)
				playerX -= speed;
			priv_playerX -= speed;
		}
		else if (movingRight == true) {
			if (playerX < 728)
				if (playerX < 400) {
					playerX += speed;
					priv_playerX += speed;
				}
				else {
					//obstacle.move(Vector2f(-speed, 0));
					obstacle.move(Vector2f(-speed, 0));
					obstacleX -= speed;
					priv_playerX += speed;
					obstacle1.move(Vector2f(-speed, 0));
					obstacleX1 -= speed;
					obstacle2.move(Vector2f(-speed, 0));
					obstacleX2 -= speed;
				}
		}

		// ========= JUMP ========= JUMP ========= JUMP ========= JUMP =========

		if (jump == true) {
			// Do jump function in here
			if (goingUp == true) {
				if (playerY <= ground - 150) {
					goingDown = true;
					goingUp = false;
				}
				else
					playerY -= 1.3;
			}
			else if (goingDown == true) {
				if (playerY >= ground) {
					goingDown = false;
					jump = false;
				}
				else
					playerY += 1.7;
			}
			player.setTexture(stickJump);
			// End the jump function
		}
		else {
			player.setTexture(stick50);
		}

		if (obstacleX < 0) {
			int newObstacleX = 0;
			bool NOXAccept = false;
			while (NOXAccept != true) {
				time_t t = time(NULL);
				//struct tm tm = *localtime(&t);
				srand(time(NULL));
				newObstacleX = rand();
				if (newObstacleX > 400) {
					NOXAccept = true;
				}
				else {
					NOXAccept = false;
				}
			}
			if (newObstacleX > 800)
				newObstacleX = 700;
			//if (std::rand() % 2 == 0) {
				//obstacle.setOrigin(playerX, 575);
			obstacleX = (newObstacleX + 300);
			obstacle.setPosition(obstacleX, 575);
			//}
		}

		if (obstacleX1 < 0) {
			int newObstacleX1 = 0;
			bool NOXAccept1 = false;
			while (NOXAccept1 != true) {
				newObstacleX1 = std::rand();
				if (newObstacleX1 > 400) {
					NOXAccept1 = true;
				}
				else {
					NOXAccept1 = false;
				}
			}
			if (newObstacleX1 > 800)
				newObstacleX1 = 700;
			//if (std::rand() % 2 == 0) {
				//obstacle.setOrigin(playerX, 575);
			obstacleX1 = (newObstacleX1 + 300);
			obstacle1.setPosition(obstacleX1, 575);
			//}
		}

		if (obstacleX2 < 0) {
			int newObstacleX2 = 0;
			bool NOXAccept2 = false;
			while (NOXAccept2 != true) {
				newObstacleX2 = std::rand();
				if (newObstacleX2 > 400) {
					NOXAccept2 = true;
				}
				else {
					NOXAccept2 = false;
				}
			}
			if (newObstacleX2 > 800)
				newObstacleX2 = 700;
			//if (std::rand() % 2 == 0) {
				//obstacle.setOrigin(playerX, 575);
			obstacleX2 = (newObstacleX2 + 300);
			obstacle2.setPosition(obstacleX2, 575);
			//}
		}

		

		// ========= WINDOW DRAW ========= WINDOW DRAW ========= WINDOW DRAW

		player.setPosition(playerX, playerY); // Set player's position
		meow.setVolume(vol);
		fail.setVolume(vol);
		if (fail.getStatus() == fail.Stopped) {
			if (meow.getStatus() == meow.Paused) {
				meow.play();
			}
		}

		speed += 0.0005;
		if (failed == false) {
			//status = Color(255, 10, 10);
		//}
			window.clear(Color(255, 255, 255)); // Clear window with a white background
			window.draw(player); // Draw player onto the screen
			window.draw(obstacle);
			window.draw(obstacle1);
			window.draw(obstacle2);
			window.draw(objYeet);
			window.draw(objYeet1);
			window.draw(objYeet2);
			window.display(); // Display the newly prepared screen. This is when everything becomes visible.
		}
		else {
			if (firstTime == true) {
				meow.pause();
				window.clear(Color(255, 10, 10));
				window.draw(player); // Draw player onto the screen
				window.draw(obstacle);
				window.draw(obstacle1);
				window.draw(obstacle2);
				window.draw(objYeet);
				window.draw(objYeet1);
				window.draw(objYeet2);
				window.display(); // Display the newly prepared screen. This is when everything becomes visible.
				fail.play();
				firstTime = false;
			}

		}
	}
}
