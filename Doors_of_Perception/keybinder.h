#pragma once
#include <ecm.h>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>


using namespace sf;

class Keybinder {
public:
	Keyboard::Key kright = Keyboard::Right;
	Keyboard::Key kleft = Keyboard::Left;
	Keyboard::Key kjump = Keyboard::Up;
	Keyboard::Key kshrink = Keyboard::A;
	Keyboard::Key kgrow = Keyboard::Q;
	Keyboard::Key kspeed = Keyboard::S;
	Keyboard::Key klowg = Keyboard::D;
	sf::Event _event;
	sf::Event _event1;
	sf::Event _event2;
	sf::Event _event3;
	sf::Event _event4;
	sf::Event _event5;
	sf::Event _event6;
	Keyboard::Key passer;

public:
	void remapright();
	void remapleft();
	void remapjump();
	void remapshrink();
	void remapgrow();
	void remapspeed();
	void remaplowg();
	//Keyboard::Key update();

};