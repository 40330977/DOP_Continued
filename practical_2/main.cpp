#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;

//void Load();

const int gameWidth = 800;
const int gameHeight = 600;

void Load() {
	if (!spritesheet.loadFromFile("C:/Users/40330977/Desktop/Games_Engineering_1/res/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
}

void Update(RenderWindow &window) {
	// Update Everything
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window) {
	// Draw Everything
	window.draw(invader);
}


	int main() {
		RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
		Load();
		while (window.isOpen()) {
			window.clear();
			Update(window);
			Render(window);
			window.display();
		}
		return 0;
	}
