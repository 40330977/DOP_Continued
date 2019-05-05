#include "kremap.h"
#include "scene_level1.h"
#include "../components/cmp_text.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <SFML/Audio.hpp>
#include "system_resources.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;


static shared_ptr<Entity> text;
static shared_ptr<Entity> text1;
static shared_ptr<Entity> text2;
static shared_ptr<Entity> text3;

//sf::Texture tex;


void Kremap::Load()
{
	

	Vector2f winpass = Vector2f(Engine::GetWindow().getView().getSize().x, Engine::GetWindow().getView().getSize().y);
	winpass.x /= 2.75;
	winpass.y /= 2.5;
	text = makeEntity();
	text->setPosition(Vector2f(0.0f, 0.0f));
	auto t = text->addComponent<TextComponent>(
		"press enter & key to rebind\npress new key\npress space to return to menu");
	t->SetPosition(winpass);


	/*text = makeEntity();
	text->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t = text->addComponent<TextComponent>("New Game");
	t->SetPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) + Vector2f(0.0f, -80.0f));
	t->render();*/

	




	cout << " kremap Load Done" << endl;

	setLoaded(true);
}

void Kremap::UnLoad()
{
	cout << "kremap Unload" << endl;

	Scene::UnLoad();
}

//sf::Event e;
Keyboard::Key transfer;
void Kremap::Update(const double & dt)
{
	//transfer = keybind.update();
	//sf::Window win1 = Engine::GetWindow().
	if (sf::Keyboard::isKeyPressed(Keyboard::Space) || controls.start()) {

		Engine::ChangeScene(&mainmenu);
	}
	//keybind.update();
	if (Keyboard::isKeyPressed(Keyboard::Return)) {
		if (Keyboard::isKeyPressed(keybind.kright)) {
			//cout << "test keybind";		
			keybind.remapright();
			Engine::ChangeScene(&mainmenu);
		}
		if (Keyboard::isKeyPressed(keybind.kleft)) {
			//cout << "test keybind";		
			keybind.remapleft();
			Engine::ChangeScene(&mainmenu);
		}
		if (Keyboard::isKeyPressed(keybind.kjump)) {
			//cout << "test keybind";		
			keybind.remapjump();
			Engine::ChangeScene(&mainmenu);
		}
		if (Keyboard::isKeyPressed(keybind.kshrink)) {
			//cout << "test keybind";		
			keybind.remapshrink();
			Engine::ChangeScene(&mainmenu);
		}
		if (Keyboard::isKeyPressed(keybind.kgrow)) {
			//cout << "test keybind";		
			keybind.remapgrow();
			Engine::ChangeScene(&mainmenu);
		}
		if (Keyboard::isKeyPressed(keybind.kspeed)) {
			//cout << "test keybind";		
			keybind.remapspeed();
			Engine::ChangeScene(&mainmenu);
		}
		if (Keyboard::isKeyPressed(keybind.klowg)) {
			//cout << "test keybind";		
			keybind.remaplowg();
			Engine::ChangeScene(&mainmenu);
		}
	}
	/*if (Keyboard::isKeyPressed(Keyboard::Return)) {
		
	}*/
	Scene::Update(dt);
}

void Kremap::Render()
{
	Scene::Render();
}
