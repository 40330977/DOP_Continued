#include "kremap.h"
#include "scene_level1.h"
#include "../components/cmp_text.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
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
		"press key to rebind\npress new key\n press space to return to menu");
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

void Kremap::Update(const double & dt)
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Space) || controls.start()) {

		Engine::ChangeScene(&mainmenu);
	}
	if (Keyboard::isKeyPressed(keybind.kright)) {
		keybind.remapright();
	}

	Scene::Update(dt);
}

void Kremap::Render()
{
	Scene::Render();
}
