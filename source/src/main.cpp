// main.cpp

#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(800, 600), "The yeeter");
	
	while (window.isOpen()) {
		// Event processing
		Event event;
		while (window.pollEvent(event)) {
			// Request for closing the window
       		if (event.type == sf::Event::Closed)
				window.close();
		}
		
		Texture playerTex, bgTex;
		playerTex.loadFromFile("../assets/player.png");
		bgTex.loadFromFile("../assets/bg.jpeg");
		Sprite player, bg;
		player.texture(playerTex);
		bg.texture(bgTex);
		window.clear(Color(255,255,255));
		window.draw(bg);
		window.draw(player);
	}
}
