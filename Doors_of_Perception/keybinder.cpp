#include "keybinder.h"
#include <engine.h>
#include <SFML\Window\Event.hpp>

using namespace sf;
using namespace std;

Event event;

Keyboard::Key Keybinder::update(Window window) {
	//while (window.isOpen()) {
		
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed) {
				return event.key.code;
			}
		}
		
	//}
}

void Keybinder::remapright()
{
	
}

void Keybinder::remapleft()
{
}

void Keybinder::remapjump()
{
}

void Keybinder::remapshrink()
{
}

void Keybinder::remapgrow()
{
}

void Keybinder::remapspeed()
{
}

void Keybinder::remaplowg()
{
}
