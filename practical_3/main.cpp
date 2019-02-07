#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"

using namespace sf;
using namespace std;

Player *player = new Player();
const int gameWidth = 1600;
const int gameHeight = 1200;

void Load() {
	player->setPosition(sf::Vector2f(400, 300));
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

	player->update(dt);
}

void Render(RenderWindow &window) {
	// Draw Everything
	player->render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Game");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
