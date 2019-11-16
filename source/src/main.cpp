#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include "main.h"


using namespace sf;

sf::Texture stick50, objYeetTex, stickJump, obstacleTex;
sf::Sprite player, objYeet, obstacle, obstacle1, obstacle2, objYeet1, objYeet2;
const int ground = 452;
sf::RenderWindow window(VideoMode(800, 600), "The Yeeter"); // Create the window.;
int main() {

	int obstacleXs[3];

	//TODO: Implement a way to decide if a yeetStick should be spawned above obstacleX values.

	//TODO: Implement a way to have the obstacles move to the left, when they disappear, they should be destroyed, and a new one should take it's place.

	//window(VideoMode(800, 600), "The Yeeter"); // Create the window.

	//SoundStream meow();
	
	stick50.loadFromFile("Stickman.png");
	stickJump.loadFromFile("stickmanJump.png");
	objYeetTex.loadFromFile("objYeetTex_ctc.png");
	objYeet.setTexture(objYeetTex);
	objYeet1.setTexture(objYeetTex);
	objYeet2.setTexture(objYeetTex);
	obstacleTex.loadFromFile("obstacleTex.png");
	obstacle.setTexture(obstacleTex);
	obstacle1.setTexture(obstacleTex);
	obstacle2.setTexture(obstacleTex);
	Color status = Color(255,255,255);
	float playerX, playerY;
	playerX = 0;
	playerY = ground;
	float speed = 1;
	int obstacleX = 0;
	int obstacleX1 = 0;
	int obstacleX2 = 0;

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

	srand(time(0));


	while (window.isOpen()) {
		if (firstRun == true) {
			while ((!(obstacleX > playerX) || obstacleX >= 700)) {
				obstacleX = std::rand();
			}
			while ((!(obstacleX1 > playerX) || obstacleX1 >= 700)) {
				obstacleX1 = std::rand();
			}
			while ((!(obstacleX2 > playerX) || obstacleX2 >= 700)) {
				obstacleX2 = std::rand();
				if ((obstacleX2 - obstacleX1) >= abs((long)100)) {
					obstacleX2 = std::rand();
				}
				else {
					break;
				}
			}
			obstacle.setPosition(78 + obstacleX, 575);
			obstacle1.setPosition(78 + obstacleX1, 575);
			obstacle2.setPosition(78 + obstacleX2, 575);
			if (std::rand() % 2 == 0) {
				objYeet.setPosition(obstacleX, 475);
			}
			if (std::rand() % 2 == 0) {
				objYeet1.setPosition(obstacleX1, 475);
			}
			if (std::rand() % 2 == 0) {
				objYeet2.setPosition(obstacleX2, 475);
			}
			firstRun = false;
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
					playerY -= speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (playerY < ground)
						playerY += speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					movingLeft = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					movingRight = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Pause))
				{
					// Reset jump-related flags:
					jump = goingUp = goingDown = false; // Set all flags for jumping to false
					firstTime = true;
					// Reset player:
					playerX = 0; // Resets player's X-coordinate on the window
					playerY = ground; // Resets player's X-coordinate on the window
					player.setTexture(stick50); // Sets player's texture to the one used when not jumping

					firstRun = true;
					obstacleX = 0;
					// Reset window:
					window.clear(Color(255, 255, 0)); // We will use yellow because if seen, we will know that we reset the game.
					window.display(); // Now we update the window and (maybe) show the yellow-colored window. NOTE: If you blink, you WILL miss it, it's that fast. Seriously.
					failed = false;
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
				if (e.key.code == Keyboard::Left)
				{
					movingLeft = false;
				}
				else if (e.key.code == Keyboard::Right)
				{
					movingRight = false;
				}
			}
		}


		/*if (((obstacleX <= playerX) || (obstacleX <= (playerX + 72)))
		&& ((obstacleX + 25 >= playerX) || ((obstacleX + 25) >= (playerX + 72)))) {
			failed = true;
		}	*/

		if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
			// Do function here.
			failed = true;
		}
		if (player.getGlobalBounds().intersects(obstacle1.getGlobalBounds())) {
			// Do function here.
			failed = true;
		}
		if (player.getGlobalBounds().intersects(obstacle2.getGlobalBounds())) {
			// Do function here.
			failed = true;
		}



		// ========= Move ========= MOVE ========= Move ========= MOVE =========
		if (movingLeft == true) {
			if (playerX > 0)
				playerX -= speed;
		}
		else if (movingRight == true) {
			if (playerX < 728)
				if (playerX < 400) {
					playerX += speed;
				}
				else {
					//obstacle.move(Vector2f(-speed, 0));
					obstacle.move(Vector2f(-speed, 0));
					obstacleX -= speed;
					obstacle1.move(Vector2f(-speed, 0));
					obstacle2.move(Vector2f(-speed, 0));
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
			if (std::rand() % 2 == 0) {
				
				while (obstacleX <= 600) {
					obstacleX = std::rand() + 500;
				}
				obstacle.setPosition(obstacleX, 575);
			}
		}

		if (obstacleX1 < 0) {
			if (std::rand() % 2 == 0) {

				while (obstacleX1 <= 600) {
					obstacleX1 = std::rand() + 500;
				}
				obstacle1.setPosition(obstacleX1, 575);
			}
		}

		// ========= WINDOW DRAW ========= WINDOW DRAW ========= WINDOW DRAW

		player.setPosition(playerX, playerY); // Set player's position

		if (failed == false) {
			//status = Color(255, 10, 10);
		//}
			window.clear(Color(255,255,255)); // Clear window with a white background
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
				window.clear(Color(255, 10, 10));
				window.draw(player);
				window.display();
				firstTime = false;
			}
		}
	}
}