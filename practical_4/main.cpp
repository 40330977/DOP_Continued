#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

Player *player = new Player();
Ghost *ghost1 = new Ghost();
Ghost *ghost2 = new Ghost();
Ghost *ghost3 = new Ghost();
Ghost *ghost4 = new Ghost();

const int gameWidth = 1600;
const int gameHeight = 1200;

void Load() {
	player->setPosition(sf::Vector2f(400, 300));

	ghost1->setPosition(sf::Vector2f(200, 300));
	ghost2->setPosition(sf::Vector2f(200, 300));
	ghost3->setPosition(sf::Vector2f(200, 300));
	ghost4->setPosition(sf::Vector2f(200, 300));
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
	ghost1->update(dt);
	ghost2->update(dt);
	ghost3->update(dt);
	ghost4->update(dt);
}

void Render(RenderWindow &window) {
	// Draw Everything
	player->render(window);
	ghost1->render(window);
	ghost2->render(window);
	ghost3->render(window);
	ghost4->render(window);
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
