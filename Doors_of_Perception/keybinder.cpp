#include "keybinder.h"
#include <engine.h>
#include <SFML\Window\Event.hpp>

using namespace sf;
using namespace std;



//Keyboard::Key Keybinder::update() {
//	//while (window.isOpen()) {
//		
//		while (Engine::GetWindow().pollEvent(event)) {
//			if (event.type == Event::KeyPressed) {
//				return event.key.code;
//			}
//		}
//		
//	//}
//}

void Keybinder::remapright()
{
	//kright = update();
	
	while (_event.type != Event::KeyPressed) {
		
		while (Engine::GetWindow().pollEvent(_event)) {
			if (_event.type == Event::KeyPressed && _event.key.code!= Keyboard::Space||kright) {

				passer = _event.key.code;
				break;

			}
		}
		
	}
	passer = _event.key.code;
	kright = passer;
	
}

void Keybinder::remapleft()
{
	while (_event1.type != Event::KeyPressed) {

		while (Engine::GetWindow().pollEvent(_event1)) {
			if (_event1.type == Event::KeyPressed && _event1.key.code != Keyboard::Space||kleft) {

				passer = _event1.key.code;
				break;

			}
		}

	}
	passer = _event1.key.code;
	kleft = passer;
}

void Keybinder::remapjump()
{
	while (_event2.type != Event::KeyPressed) {

		while (Engine::GetWindow().pollEvent(_event2)) {
			if (_event2.type == Event::KeyPressed && _event2.key.code != Keyboard::Space||kjump) {

				passer = _event2.key.code;
				break;

			}
		}

	}
	passer = _event2.key.code;
	kjump = passer;
}

void Keybinder::remapshrink()
{
	while (_event3.type != Event::KeyPressed) {

		while (Engine::GetWindow().pollEvent(_event3)) {
			if (_event3.type == Event::KeyPressed && _event3.key.code != Keyboard::Space||kshrink) {

				passer = _event3.key.code;
				break;

			}
		}

	}
	passer = _event3.key.code;
	kshrink = passer;
}

void Keybinder::remapgrow()
{
	while (_event4.type != Event::KeyPressed) {

		while (Engine::GetWindow().pollEvent(_event4)) {
			if (_event4.type == Event::KeyPressed && _event4.key.code != Keyboard::Space||kgrow) {

				passer = _event4.key.code;
				break;

			}
		}

	}
	passer = _event4.key.code;
	kgrow = passer;
}

void Keybinder::remapspeed()
{
	while (_event5.type != Event::KeyPressed) {

		while (Engine::GetWindow().pollEvent(_event5)) {
			if (_event5.type == Event::KeyPressed && _event5.key.code != Keyboard::Space||kspeed) {

				passer = _event5.key.code;
				break;

			}
		}

	}
	passer = _event5.key.code;
	kspeed = passer;
}

void Keybinder::remaplowg()
{
	while (_event6.type != Event::KeyPressed) {

		while (Engine::GetWindow().pollEvent(_event6)) {
			if (_event6.type == Event::KeyPressed && _event6.key.code != Keyboard::Space||klowg) {

				passer = _event6.key.code;
				break;

			}
		}

	}
	passer = _event6.key.code;
	klowg = passer;
}
