// main.cpp

#include <SFML/Graphics.hpp>

using namespace sf;

sf::Texture stick50;
Sf::Sprite player;
const int ground = 400;

int main() {
	RenderWindow window(VideoMode(800, 600), "The yeeter");
	
	stick50.loadFromFile("stickman_50.png");
	player.setTexture(stick50);
	int playerX = 0, playerY = 400;
	int speed = 2;
	
	bool jump = false;
	bool goingDown = false;
	
	while (window.isOpen()) {
		// Event processing
		Event event;
		while (window.pollEvent(event)) {
			// Request for closing the window
       		if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == Event::KeyPressd) {
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					playerY -= speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					playerY += speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					playerX -= speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					playerX += speed;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Space)) {
					jump = true;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Pause)) {
					// reset flags...
					jump = false;
					goingDown = false;
					playerX = 0;
					playerY = 400;
					player.setPosition(playerX, playerY);
					window.clear(Color(255,255,0));
					window.display(); // We will not draw the player.
					
			}
		}
		
		if (jump == true) {
			if (goingDown == false) {
				if (playerY <= ground - 150) {
					goingDown = true;
				}
				else {
					playerY -= 1+(0.7*speed);
				}
			}
			else if (goingDown == true) {
				if (playerY >= ground) {
					playerY = ground;
					goingDown = false;
					jump = false;
				}
				else {
					playerY += speed;
				}
			}
		}
		
		player.setPosition(playerX, playerY);
		window.clear(Color(255,255,255));
		//window.draw(bg);
		window.draw(player);
		window.display();
	}
}
