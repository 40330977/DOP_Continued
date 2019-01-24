#include <iostream>
#include <SFML/Graphics.hpp>
#include "ship.h"

using namespace sf;
using namespace std;


sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship *> ships;


//void Load();

const int gameWidth = 800;
const int gameHeight = 600;
int invaders_rows;
int invaders_columns;
//float r1, c1;

void Load() {
	if (!spritesheet.loadFromFile("C:/Users/40330977/Desktop/Games_Engineering_1/res/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

	/*Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
	ships.push_back(inv);*/

	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			/*r1 = r;
			c1 = c;*/
			Vector2f position = Vector2f(r+100, c+100);
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
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

	for (auto &s : ships) {
		s->Update(dt);
	}
}

void Render(RenderWindow &window) {
	// Draw Everything
	//window.draw(invader);
	for (const auto s : ships) {
		window.draw(*s);
	}
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
