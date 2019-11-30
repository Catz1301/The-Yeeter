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

sf::Texture stick50, objYeetTex, stickJump, obstacleTex, startBannerTex;
sf::Sprite player, objYeet, obstacle, obstacle1, obstacle2, objYeet1, objYeet2, startBanner;
sf::RenderWindow window(VideoMode(800, 600), "The Yeeter", Style::None); // Create the window.

int main() {
	Music meow, fail;
	meow.openFromFile("assets/sounds/score.ogg");  // Background music
	fail.openFromFile("assets/sounds/failed.ogg"); // failed sound effect
	meow.setLoop(true);
	
	stick50.loadFromFile("assets/textures/Stickman.png");           // Players' texture
	stickJump.loadFromFile("assets/textures/stickmanJump.png");     // players' texture while jumping
	objYeetTex.loadFromFile("assets/textures/yeetObjTex_ctc.png");  // Texture for the stickmen sent to space by the russians
	obstacleTex.loadFromFile("assets/textures/obstacleTex.png");    // Texture for the obstacles
	startBannerTex.loadFromFile("assets/textures/startBanner.png");
	startBanner.setTexture(startBannerTex);
	/*View view = window.getView();
	const float windowRatio = static_cast<float>(window.getSize().x) / window.getSize().y;
	const float newViewWidth = view.getSize().y * windowRatio;
	const float newViewHeight = view.getSize().x * windowRatio;*/

	/* Here we will set objYeet's texture */
	objYeet.setTexture(objYeetTex);
	objYeet1.setTexture(objYeetTex);
	objYeet2.setTexture(objYeetTex);
	

	/*  Here we set the tint of the stickmen that travel to space. */ 
	/* (Only uncomment the content inside the commented curly bracket when debugging/troubleshooting) */
	/* {
	objYeet.setColor(Color(255, 0, 0, 255));
	objYeet1.setColor(Color(0, 255, 0, 255));
	objYeet2.setColor(Color(0, 0, 255, 255));
	// } */

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
	int objYeetRot2 = 0;
	float vol = 100;
	animSize = 1;
	player.setTexture(stick50);
	std::srand(time(0));
	Clock tyme;

	meow.play(); // Start music stuff after loading everything to help with speed and performance
	tyme.getElapsedTime().asMicroseconds();
	Font fnt;
	fnt.loadFromFile("C:/Windows/Fonts/arial.ttf");
	Text txt;
	txt.setFont(fnt);
	while (window.isOpen()) {
		//srand(time(0));
		//cout << time(0) << endl;
		if (firstRun == true)
		{
			// Set up obstacle's position on the X-axis
			obstacleX = (rand() % 200) + 200;
			obstacleX1 = (rand() % 200) + 400;
			obstacleX2 = (rand() % 200) + 600;
			obstacle.setPosition(78 + obstacleX, whenNormal);
			//obstacle.setColor(Color(255, 0, 0, 255));

			obstacle1.setPosition(78 + obstacleX1, whenNormal);
			//obstacle1.setColor(Color(0, 255, 0, 255));

			obstacle2.setPosition(78 + obstacleX2, whenNormal);
			//obstacle2.setColor(Color(0, 0, 255, 255));

			startBanner.setPosition(0, 15);
			// Set up objYeet			
			if (rand() % 2 == 0) {
				objYeet.setPosition(obstacleX, 475);
				objYeet.setColor(visible);
				objYeetHittable = true;
			}
			else {
				objYeet.setPosition(obstacleX, 475);
				objYeet.setColor(invisible);
				objYeetHittable = false;
			}

			// Set up objYeet1
			if (rand() % 2 == 0) {
				objYeet1.setPosition(obstacleX1, 475);
				objYeet1.setColor(visible);
				objYeet1Hittable = true;
			}
			else {
				objYeet1.setPosition(obstacleX1, 475);
				objYeet1.setColor(invisible);
				objYeet1Hittable = false;

			}

			// Set up objYeet2
			if (rand() % 2 == 0) {
				objYeet2.setPosition(obstacleX2, 475);
				objYeet2.setColor(visible);
				objYeet2Hittable = true;
			}
			else {
				objYeet2.setPosition(obstacleX2, 475);
				objYeet2.setColor(invisible);
				objYeet2Hittable = false;
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
				else if (Keyboard::isKeyPressed(Keyboard::Pause) || Keyboard::isKeyPressed(Keyboard::Delete))
				{
					// Reset jump-related flags:

					firstTime = true;
					firstRun = true;

					fail.stop();
					playerX = 0; // Resets player's X-coordinate on the window
					playerY = ground; // Resets player's X-coordinate on the window
					obstacleX = 0;
					obstacleX1 = 0;
					obstacleX2 = 0;

					objYeet.setPosition(0, 0);
					objYeet.setRotation(0);
					objYeetMoving = false;
					objYeetHittable = false;
					objYeetRot = 0;

					objYeet1.setPosition(0, 0);
					objYeet1.setRotation(0);
					objYeetMoving1 = false;
					objYeet1Hittable = false;
					objYeetRot1 = 0;

					objYeet2.setPosition(0, 0);
					objYeet2.setRotation(0);
					objYeetMoving2 = false;
					objYeet2Hittable = false;
					objYeetRot2 = 0;


					speed = 1;
					doReset();
					//srand(time(0));
					//cout << time(0) << endl;

					// Reset window:
					player.setTexture(stick50); // Sets player's texture to the one used when not jumping
					//window.clear(Color(255, 255, 0)); // We will use yellow because if seen, we will know that we reset the game.
					//window.display(); // Now we update the window and (maybe) show the yellow-colored window. NOTE: If you blink, you WILL miss it, it's that fast. Seriously.
					failed = false;
					failed = false;
					resetFailed = true;
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


		if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
		{
			if (debug != true)
				failed = true;
		}

		if (player.getGlobalBounds().intersects(obstacle1.getGlobalBounds()))
		{
			if (debug != true)
				failed = true;
		}

		if (player.getGlobalBounds().intersects(obstacle2.getGlobalBounds()))
		{
			if (debug != true)
				failed = true;
		}



		if (player.getGlobalBounds().intersects(objYeet.getGlobalBounds()))
		{
			if (objYeetHittable == true)
				objYeetMoving = true;
			animEnabled = true;
			animSize = 1;
		}

		if (player.getGlobalBounds().intersects(objYeet1.getGlobalBounds()))
		{
			if (objYeet1Hittable == true)
				objYeetMoving1 = true;
			animEnabled = true;
			animSize = 1;
		}

		if (player.getGlobalBounds().intersects(objYeet2.getGlobalBounds()))
		{
			if (objYeet2Hittable == true)
				objYeetMoving2 = true;
			animEnabled = true;
			animSize = 1;
		}


		if (objYeetMoving == true)
		{
			objYeet.move(Vector2f(speed / 4, -speed));
			objYeet.rotate(1);
		}

		if (objYeetMoving1 == true)
		{
			objYeet1.move(Vector2f(speed / 4, -speed));
			objYeet1.rotate(1);
		}

		if (objYeetMoving2 == true)
		{
			objYeet2.move(Vector2f(speed / 4, -speed));
			objYeet2.rotate(1);
		}



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

					objYeet.move(Vector2f(-speed, 0));
					objYeet1.move(Vector2f(-speed, 0));
					objYeet2.move(Vector2f(-speed, 0));

					startBanner.move(Vector2f(-speed, 0));
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



		if (obstacleX < 0) {				// If obstacle goes offscreen
			int newObstacleX = 0;			// Set up a temporary obstacleX
			bool NOXAccept = false;			// Define a flag for whether or not the newObstacleX should be accepted
			while (NOXAccept != true) {		// While NOX is false
				//srand(time(0));				// Make new seed for rand()
				//cout << time(0) << endl;
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

			obstacleX = (newObstacleX + (rand() % 300));
			obstacle.setPosition(obstacleX, 575);
			//}
		}

		if (obstacleX1 < 0) {
			int newObstacleX1 = 0;
			bool NOXAccept1 = false;
			while (NOXAccept1 != true) {
				//srand(time(0));
				//cout << time(0) << endl;
				newObstacleX1 = rand();
				if (newObstacleX1 > 400) {
					NOXAccept1 = true;
				}
				else {
					NOXAccept1 = false;
				}
			}
			if (newObstacleX1 > 800)
				newObstacleX1 = 700;
			obstacleX1 = (newObstacleX1 + (rand() % 300));
			obstacle1.setPosition(obstacleX1, 575);
			//}
		}

		if (obstacleX2 < 0) {
			int newObstacleX2 = 0;
			bool NOXAccept2 = false;
			while (NOXAccept2 != true) {
				//srand(time(0));
				//cout << time(0) << endl;
				newObstacleX2 = rand();
				if (newObstacleX2 > 400) {
					NOXAccept2 = true;
				}
				else {
					NOXAccept2 = false;
				}
			}
			if (newObstacleX2 > 800)
				newObstacleX2 = 700;

			obstacleX2 = (newObstacleX2 + (rand() % 300));
			obstacle2.setPosition(obstacleX2, 575);
			//}
		}

		if (objYeet.getPosition().y < 0/* && objYeet_out == false*/) {
			if (rand() % 2 == 0) {
				objYeet.setPosition(obstacleX, 475);
				objYeet.setColor(visible);
				objYeetHittable = true;
			}
			else {
				objYeet.setPosition(obstacleX, 475);
				objYeet.setColor(invisible);
				objYeetHittable = false;
			}
		}


		if (objYeet1.getPosition().y < 0/* && objYeet1_out == false*/) {
			if (rand() % 2 == 0) {
				objYeet1.setPosition(obstacleX1, 475);
				objYeet1.setColor(visible);
				objYeet1Hittable = true;
			}
			else {
				objYeet1.setPosition(obstacleX1, 475);
				objYeet1.setColor(invisible);
				objYeet1Hittable = false;
			}
		}


		if (objYeet2.getPosition().y < 0/* && objYeet2_out == false*/) {
			if (rand() % 2 == 0) {
				objYeet2.setPosition(obstacleX2, 475);
				objYeet2.setColor(visible);
				objYeet2Hittable = true;
			}
			else {
				objYeet2.setPosition(obstacleX2, 475);
				objYeet2.setColor(invisible);
				objYeet2Hittable = false;
			}
		}
		

		
		txt.setString(std::string("YEET!!"));
		txt.setFillColor(Color(0, 0, 0, 255));

		//
			//txtAnim anim;
			//anim.fadeInAndGrow(i, "TEST!!", fnt, window);


		//}
		if (animEnabled == true) {
			txt.setCharacterSize(animSize);
			animSize += 0.1;
			if (animSize > 80) {
				animSize = 1;
				animEnabled = false;
			}
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

		if (resetFailed == true) {
			reset = false;
			failed = false;
			resetFailed = false;
		}

		
		//speed += 0.0005;
		if (failed == false) {
			window.clear(Color(255, 255, 255)); // Clear window with a white background
			window.draw(player); // Draw player onto the screen
			window.draw(obstacle);
			window.draw(obstacle1);
			window.draw(obstacle2);
			window.draw(objYeet);
			window.draw(objYeet1);
			window.draw(objYeet2);
			window.draw(startBanner);
			if (animEnabled == true) {
				window.draw(txt);
			}
			window.display(); // Display the newly prepared screen. This is when everything becomes visible.
			reset = false;
		}
		else {
			if (failed == true) {
				if (firstTime == true) {
					fail.play();
					firstTime = false;
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
				}
			}
		}
	}
}


void doReset() {
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
	bool objYeetMoving2 = false;
	bool objYeetHittable = false;
	bool objYeet1Hittable = false;
	bool objYeet2Hittable = false;
	animEnabled = false;
	animSize = 0;
}