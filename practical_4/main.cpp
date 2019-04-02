#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;

shared_ptr<Player> player = make_shared<Player>();
//Player *player = new Player();
//shared_ptr<Player> player = make_shared<Player>(new Player());
/*shared_ptr<Ghost> ghost1 = make_shared<Ghost>(new Ghost());
shared_ptr<Ghost> ghost2 = make_shared<Ghost>(new Ghost());
shared_ptr<Ghost> ghost3 = make_shared<Ghost>(new Ghost());
shared_ptr<Ghost> ghost4 = make_shared<Ghost>(new Ghost());*/

//vector<Entity*> entities;
EntityManager em;


const int gameWidth = 1600;
const int gameHeight = 1200;

void Load() {

	em.list.push_back(player);
	/*em.list.push_back(ghost1);
	em.list.push_back(ghost2);
	em.list.push_back(ghost3);
	em.list.push_back(ghost4);*/

	
	em.list[0]->setPosition(sf::Vector2f(400, 300));
	//player->setPosition(sf::Vector2f(400, 300));

	/*ghost1->setPosition(sf::Vector2f(200, 100));
	ghost2->setPosition(sf::Vector2f(200, 200));
	ghost3->setPosition(sf::Vector2f(200, 300));
	ghost4->setPosition(sf::Vector2f(200, 400));*/

	
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

	em.update(dt);

	/*for (auto e : entities)
	{
		e->update(dt);
	}*/
	//player->update(dt);
	/*ghost1->update(dt);
	ghost2->update(dt);
	ghost3->update(dt);
	ghost4->update(dt);*/
}

void Render(RenderWindow &window) {
	// Draw Everything

	em.render(window);

	/*for (auto e : entities)
	{
		e->render(window);
	}*/

	//player->render(window);
	/*ghost1->render(window);
	ghost2->render(window);
	ghost3->render(window);
	ghost4->render(window);*/
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
