#include "player.h"
using namespace sf;
using namespace std;

float directionx = 0.0f;
float directiony = 0.0f;
float xer = 0.0f;
float yer = 0.0f;
//float dtx = dt;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // left
	Keyboard::S,   // Down
	Keyboard::D,  // right
	Keyboard::W // Up
};

void Player::update(double dt) {
	//Move in four directions based on keys
	if (Keyboard::isKeyPressed(controls[0]) /*&& directionx >= -1.0f && directionx <= 1.0f*/) {
		directionx--;
	}
	if (Keyboard::isKeyPressed(controls[2]) /*&& directionx >= -1.0f && directionx <= 1.0f*/) {
		directionx++;
	}
	if (Keyboard::isKeyPressed(controls[1]) /*&& directiony >= -1.0f && directiony <= 1.0f*/) {
		directiony++;
	}
	if (Keyboard::isKeyPressed(controls[3]) /*&& directiony >= -1.0f && directiony <= 1.0f*/) {
		directiony--;
	}

	xer = directionx * _speed * dt;
	yer = directiony * _speed * dt;

	move(sf::Vector2f(xer, yer));

		Entity::update(dt);
}

Player::Player()
	: _speed(1.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}