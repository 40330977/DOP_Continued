//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed = 10.0f;
float direction1 = 0.0f;
float pspeed = 0.5f;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
	Keyboard::S,   // Player1 Down
	Keyboard::D,  // Player2 UP
	Keyboard::F // Player2 Down
};

void Ship::Update(const float &dt) {}

bool Ship::is_exploded() const
{
	//setTextureRect(sf::IntRect(64, 32, 32, 32));
	return false;
}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

//ship.cpp
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	static float firetime = 0.0f;
	firetime -= dt;

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
		}
	}

	if(firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}
}

//ship.cpp
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);

	static float firetime1 = 0.0f;
	firetime1 -= dt;
	//Move left
	if (Keyboard::isKeyPressed(controls[0])) {
		direction1--;
	}
		//Move Right
	if (Keyboard::isKeyPressed(controls[1])) {
		direction1++;
	}

	
	/*if (Keyboard::isKeyPressed(Keyboard::D)) {
		Bullet::Fire(getPosition(), false);
		
	}*/

	move(direction1 * pspeed * dt, 0);

	if (firetime1 <= 0 && Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(getPosition(), false);
		firetime1 = 0.7f;
	}


}
//void Ship::Explode() {
//	setTextureRect(IntRect(128, 32, 32, 32));
//	_exploded = true;
//}
