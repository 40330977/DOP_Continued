#include "scene_level2.h"
#include "scene_level1.h"
#include "scene_level3.h"
#include "scene_level4.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <system_resources.h>
using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> focus;
static shared_ptr<Entity> snake1;
static shared_ptr<Entity> snake2;
static shared_ptr<Entity> text;
static shared_ptr<Texture> snakesprite;
static shared_ptr<Texture> snakesprite1;
sf::View view41(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp = 0.5f;
const float lerp1 = 1.0f;

void Level4Scene::Load() {
	cout << "Scene 2 Load" << endl;
	//ls::loadLevelFile("res/level_2.txt", 40.0f);
	ls::loadLevelFile("res/lvl4.txt", 40.0f);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));
	snakesprite = Resources::get<Texture>("snake1.png");
	snakesprite1 = Resources::get<Texture>("snake2.png");
	sound.play();
	// Create player
	{
		// *********************************

		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(30.f);
		s->getShape().setFillColor(Color::White);
		s->getShape().setOrigin(30.f, 30.f);
		s->getShape().setOutlineThickness(5);
		s->getShape().setOutlineColor(sf::Color(100, 100, 100));

		player->addComponent<PlayerPhysicsComponent>(Vector2f(62.f, 62.f));
		player->addTag("player");

	}

	focus = makeEntity();
	focus->setPosition(player->getPosition());

	snake1 = makeEntity();
	snake1->setPosition(player->getPosition() - Vector2f(10.0f, 10.0f));
	auto s1 = snake1->addComponent<SpriteComponent>();
	s1->setTexure(snakesprite);
	//auto s = snake1->addComponent<ShapeComponent>();
	/*s->setShape<sf::CircleShape>(10.f);
	s->getShape().setFillColor(Color::White);
	s->getShape().setOrigin(30.f, 30.f);
	s->getShape().setOutlineThickness(5);
	s->getShape().setOutlineColor(sf::Color(100, 100, 100));*/

	snake2 = makeEntity();
	snake2->setPosition(player->getPosition() - Vector2f(10.0f, 10.0f));
	auto s2 = snake2->addComponent<SpriteComponent>();
	s2->setTexure(snakesprite1);
	/*auto w = snake2->addComponent<ShapeComponent>();
	w->setShape<sf::CircleShape>(10.f);
	w->getShape().setFillColor(Color::White);
	w->getShape().setOrigin(30.f, 30.f);
	w->getShape().setOutlineThickness(5);
	w->getShape().setOutlineColor(sf::Color(100, 100, 100));*/

	// Create Enemy
	for (int i = 0; i < 9; i++)
	{

		const float modder = 2.0f;
		auto enemy = makeEntity();
		enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[i]) +
			Vector2f(0, 24));
		// *********************************
		// Add HurtComponent
		enemy->addComponent<HurtComponent>();
		// Add ShapeComponent, Red 16.f Circle
		auto e = enemy->addComponent<ShapeComponent>();
		if (fmod(i, modder) == 0) {

			e->setShape<sf::RectangleShape>(Vector2f(40.f, 40.0f));
		}
		else {
			sf::ConvexShape convex;
			convex.setPointCount(3);
			convex.setPoint(0, sf::Vector2f(0, 0));
			convex.setPoint(1, sf::Vector2f(40, 0));
			convex.setPoint(2, sf::Vector2f(20, 40));
			e->setShape<sf::ConvexShape>(convex);
		}
		e->getShape().setFillColor(Color::White);
		e->getShape().setOrigin(20.f, 15.f);
		e->getShape().setOutlineThickness(5);
		e->getShape().setOutlineColor(sf::Color(100, 100, 100));


		// Add EnemyAIComponent
		enemy->addComponent<EnemyAIComponent>();
		//enemy->addComponent<PhysicsComponent>(true,Vector2f(30.f, 30.f));
		// *********************************
	}



	// Add physics colliders to level tiles.
	{
		// *********************************
		auto walls = ls::findTiles(ls::WALL);
		for (auto w : walls) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(20.f, 20.f); //offset to center
			auto e = makeEntity();
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
		}

		{
			auto blanks = ls::findTiles(ls::BLANKED);
			for (auto b : blanks) {
				auto pos = ls::getTilePosition(b);
				pos += Vector2f(20.f, 20.f); //offset to center
				auto e = makeEntity();
				e->setPosition(pos);
				e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
			}
		}


		// *********************************
	}

	cout << " Scene 2 Load Done" << endl;
	setLoaded(true);
}

void Level4Scene::UnLoad() {
	cout << "Scene 2 UnLoad" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

bool isbigger4 = false;
bool issmaller4 = false;
double cooldown4 = 0;
double sounddown40 = 0;
double sounddown41 = 0;
double sounddown42 = 0;
void Level4Scene::Update(const double& dt) {
	controls.update(dt);
	if (cooldown4 >= 0) { cooldown4 -= dt; }
	if (sounddown40 >= 0) { sounddown40 -= dt; }
	if (sounddown41 >= 0) { sounddown41 -= dt; }
	if (sounddown42 >= 0) { sounddown42 -= dt; }

	if (cooldown4 <= 0 && Keyboard::isKeyPressed(keybind.kshrink) || cooldown4 <= 0 && controls.triggers() > 10) {
		cooldown4 = 1.0;
		if (isbigger4 == false)
		{
			shrink.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(0.5f, 0.5f);
			isbigger4 = true;

			/* auto p = player->get_components<PlayerPhysicsComponent>()[0];
			 p->Sizer(Vector2f(50.f, 50.f));*/

			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f((31.f), (31.f)));
			//p->

		   /* auto s = player->addComponent<ShapeComponent>();
			s->setShape<sf::CircleShape>(float(10.f));
			s->getShape().setFillColor(Color::White);
			s->getShape().setOrigin(10.f, 15.f);*/
			/*player->get_components<ShapeComponent>().swap(s)
			player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));*/

		}
		else
		{
			grow.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			isbigger4 = false;
			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f(62.f, 62.f));

			/* auto p = player->get_components<PlayerPhysicsComponent>()[0];
			 p->Sizer(Vector2f(35.f, 35.f));*/

			 /* auto s = player->get_components<ShapeComponent>();
			  s.resize(1.0f);*/
			  //player.reset();
			  /*auto s = player->addComponent<ShapeComponent>();
			  s->setShape<sf::CircleShape>(float(20.f));
			  s->getShape().setFillColor(Color::White);
			  s->getShape().setOrigin(10.f, 15.f);

			  player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));*/
		}
	}

	if (cooldown4 <= 0 && Keyboard::isKeyPressed(keybind.kgrow) || cooldown4 <= 0 && controls.triggers() < -10) {
		cooldown4 = 1.0;
		if (issmaller4 == false)
		{
			grow.play();
			player->setPosition(player->getPosition() + Vector2f(0.0f, 62.0f));
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(2.0f, 2.0f);
			issmaller4 = true;

			/* auto p = player->get_components<PlayerPhysicsComponent>()[0];
			 p->Sizer(Vector2f(50.f, 50.f));*/

			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f((2.0f*62.f), (2.0f*62.f)));
			//p->

		   /* auto s = player->addComponent<ShapeComponent>();
			s->setShape<sf::CircleShape>(float(10.f));
			s->getShape().setFillColor(Color::White);
			s->getShape().setOrigin(10.f, 15.f);*/
			/*player->get_components<ShapeComponent>().swap(s)
			player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));*/

		}
		else
		{
			shrink.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			issmaller4 = false;
			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f(62.f, 62.f));

			/* auto p = player->get_components<PlayerPhysicsComponent>()[0];
			 p->Sizer(Vector2f(35.f, 35.f));*/

			 /* auto s = player->get_components<ShapeComponent>();
			  s.resize(1.0f);*/
			  //player.reset();
			  /*auto s = player->addComponent<ShapeComponent>();
			  s->setShape<sf::CircleShape>(float(20.f));
			  s->getShape().setFillColor(Color::White);
			  s->getShape().setOrigin(10.f, 15.f);

			  player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));*/
		}
	}
	//sf::Vector2f viewpos = view.getCenter();
	sf::Vector2f pos = focus->getPosition();

	pos.x += (player->getPosition().x - pos.x)*lerp*dt;
	pos.y += (player->getPosition().y - pos.y)*lerp*dt;

	focus->setPosition(pos);

	//focus->setPosition(player->getPosition());
	//view.setCenter(player->getPosition());
	view41.setCenter(focus->getPosition());
	sf::Vector2f pos1 = snake1->getPosition();

	pos1.x += ((player->getPosition().x - 90.0f) - pos1.x)*lerp1*dt;
	pos1.y += ((player->getPosition().y - 90.0f) - pos1.y)*lerp1*dt;

	snake1->setPosition(pos1);

	sf::Vector2f pos2 = snake2->getPosition();

	pos2.x += ((player->getPosition().x - 90.0f) - pos2.x)*lerp1*dt;
	pos2.y += ((player->getPosition().y - 90.0f) - pos2.y)*lerp1*dt;

	snake2->setPosition(pos2);

	if (sounddown40 <= 0 && Keyboard::isKeyPressed(keybind.kjump) || sounddown40 <= 0 && controls.jump() == true) {
		sounddown40 = 1;
		jump.play();
	}
	if (sounddown41 <= 0 && Keyboard::isKeyPressed(keybind.kspeed) || sounddown41 <= 0 && controls.speed() == true) {
		sounddown41 = 3;
		speed.play();
	}
	if (sounddown42 <= 0 && Keyboard::isKeyPressed(keybind.klowg) || sounddown42 <= 0 && controls.lowg() == true) {
		sounddown42 = 3;
		lowg.play();
	}

	Scene::Update(dt);
	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		saver.save("level5");
		Engine::ChangeScene((Scene*)&level4);
	}
	else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level3);
	}
	if (Keyboard::isKeyPressed(Keyboard::P) || controls.start() == true) {
		sound.stop();
		Engine::ChangeScene((Scene*)&mainmenu);
	}
}

void Level4Scene::Render() {
	Engine::GetWindow().setView(view41);
	ls::render(Engine::GetWindow());
	Scene::Render();
}
