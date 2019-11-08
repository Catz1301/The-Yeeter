// main.cpp

#include <SFML/Graphics.hpp>

using namespace sf;

sf::Texture stick50;
Sf::Sprite player;

int main() {
	RenderWindow window(VideoMode(800, 600), "The yeeter");
	
	stick50.loadFromFile("stickman_50.png");
	player.setTexture(stick50);
	int playerX, playerY;
	playerX = 0;
	playerY = 400;
	
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
					playerY -= 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down)) {
					playerY += 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left)) {
					playerX -= 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right)) {
					playerX += 1;
				}
			}
		}
		
		
		player.setPosition(playerX, playerY)
		window.clear(Color(255,255,255));
		//window.draw(bg);
		window.draw(player);
		window.display();
	}
}
