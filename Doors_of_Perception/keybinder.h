#pragma once
#include <ecm.h>
#include <SFML\Window\Keyboard.hpp>


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

public:
	void remapright();
	void remapleft();
	void remapjump();
	void remapshrink();
	void remapgrow();
	void remapspeed();
	void remaplowg();

};