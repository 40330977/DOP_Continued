//bullet.cpp
#include "bullet.h"
#include "game.h"
#include "Ship.h"
#include <iostream>

using namespace sf;
using namespace std;

Bullet::Bullet() :Sprite() {
	setTexture(spritesheet);
	//setTextureRect(sf::IntRect(0, 0, 32, 32));
	setOrigin(16, 16);
	//setPosition(sf::Vector2f(-64.0f,-64.0f));
	setPosition(sf::Vector2f(200.0f, 200.0f));
};


unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];
//Create definition for the constructor
//...

/*Bullet::Bullet(const sf::Vector2f &pos, const bool mode) : Sprite()
{
	
	//setPosition(pos);
	//_mode = mode;
	
}*/
void Bullet::_Update(const float & dt)
{//git status
	/*auto p = getPosition();
	if(p.y > -16.0f && p.y < (gameHeight+16.0f)){
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
	}*/

	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				//player bulelts don't collide with player
				continue;
			}
			if (_mode && s != player) {
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				//Explode the ship
				s->Explode();
				//warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
}


//void Render(sf::RenderWindow &window);

void Bullet::Update(const float &dt) {
	
	/*if (Keyboard::isKeyPressed(Keyboard::D)) {
		_mode = false;
		Fire(player->getPosition(), _mode);
	}*/
	//Bullet b = bullets[bulletPointer];
	for ( auto &b : bullets) {
		//Bullet b = bullets[bulletpointer];
		//bullets->move(0, dt * 200.0f * (b->_mode ? 1.0f : -1.0f));
		b._Update(dt);
	}
	

}

void Bullet::Render(sf::RenderWindow & window)
{
	for ( auto &b : bullets) {
	//Bullet b = bullets[bulletPointer];
		window.draw(b);
		//cout << "render" << endl;
	}
}
//
void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{
	Bullet* b1 = &bullets[++bulletPointer];
	b1->setPosition(pos);
	b1->_mode = mode;
	//b1->setPosition(sf::Vector2f(500.0f, 500.0f));


	//if (mode == false) {
	//b1._mode = mode;
	//b1.setTexture(spritesheet);
	b1->setTextureRect(sf::IntRect(64, 32, 32, 32));
	cout << "fire" << endl;
	//b1.setTextureRect(IntRect(160, 32, 32, 32));
	//b1.Update(dt);
	//}

	
	
}
void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
	
}
