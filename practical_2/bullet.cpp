//bullet.cpp
#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet::Bullet() {};
//Create definition for the constructor
//...
Bullet::Bullet(const sf::Vector2f &pos, const bool mode) {}
//void Bullet::_Update(const float & dt)
//{
//}


//void Render(sf::RenderWindow &window);

void Bullet::Update(const float &dt) {
	move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
}

void Bullet::Render(sf::RenderWindow & window)
{
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{
}
