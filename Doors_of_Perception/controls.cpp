#include "Controls.h"
#include <LevelSystem.h>
#include <engine.h>
#include <iostream>
#include <SFML\Window\Joystick.hpp>

using namespace sf;
using namespace std;



void Controls::update(double dt) 
{
	if (Joystick::isButtonPressed(0, 7) == true) {
		startb = true;
	}
	if (Joystick::isButtonPressed(0, 0) == true) {
		jumpb = true;
	}
	if (Joystick::isButtonPressed(0, 4) == true) {
		lowgb = true;
	}
	if (Joystick::isButtonPressed(0, 5) == true) {
		speedb = true;
	}
	leftstick = Joystick::getAxisPosition(0, sf::Joystick::X);
	trigger = Joystick::getAxisPosition(0, sf::Joystick::Z);
}

bool Controls::start()
{
	return startb;
}

bool Controls::jump()
{
	return jumpb;
}

bool Controls::lowg()
{
	return lowgb;
}

bool Controls::speed()
{
	return speedb;
}

int Controls::stick()
{
	return leftstick;
}

int Controls::triggers()
{
	return trigger;
}





