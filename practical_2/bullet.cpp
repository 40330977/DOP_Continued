//bullet.cpp
#include "bullet.h"
#include "game.h"

using namespace sf;
using namespace std;

Bullet::Bullet() {};


unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];
//Create definition for the constructor
//...
Bullet::Bullet(const sf::Vector2f &pos, const bool mode) 
{

}
void Bullet::_Update(const float & dt)
{
	//move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
}


//void Render(sf::RenderWindow &window);

void Bullet::Update(const float &dt) {
	
	/*if (Keyboard::isKeyPressed(Keyboard::D)) {
		_mode = false;
		Fire(player->getPosition(), _mode);
	}*/
	Bullet b = bullets[bulletPointer];
	
	b.move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
	

}

void Bullet::Render(sf::RenderWindow & window)
{
	//for (const auto b : bullets) {
	Bullet b = bullets[bulletPointer];
		window.draw(b);
	//}
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{
	Bullet b1 = bullets[++bulletPointer];
	b1.setPosition(pos);
	if (mode == false) {
		b1.setTexture(spritesheet);
		b1.setTextureRect(sf::IntRect(64, 32, 32, 32));
	}
	
}
