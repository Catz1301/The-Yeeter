// main.cpp

#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(600, 800), "The yeeter");
	
	while (window.isOpen()) {
		// Event processing
		Event event;
		while (window.pollEvent(event)) {
			// Request for closing the window
       		if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear(Color(255,255,255));
	}
}
