#include "ghost.h"
#include <random>
using namespace sf;
using namespace std;

float xerg = 0.0f;
float yerg = 0.0f;
float directionxg;
float directionyg;
int moveswitch;

void Ghost::update(double dt) {
	
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4);

	moveswitch = dist6(rng);

	if (moveswitch == 1) {
		directionxg = -100.0;
		directionyg = 0.0f;
	}
	else if (moveswitch == 2) {
		directionxg = 0.0f;
		directionyg = -100.0f;
	}
	else if (moveswitch == 3) {
		directionxg = 100.0f;
		directionyg = 0.0f;
	}
	else if (moveswitch == 4) {
		directionxg = 0.0f;
		directionyg = 100.0f;
	}

	

	xerg = directionxg * _speed * dt;
	yerg = directionyg * _speed * dt;

	move(sf::Vector2f(xerg, yerg));

	Entity::update(dt);
}

Ghost::Ghost()
	: _speed(50.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Blue);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Ghost::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}