#include "main_menu.h"
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

static shared_ptr<Entity> player;
static shared_ptr<Entity> focus;
static shared_ptr<Entity> snake1;
static shared_ptr<Entity> snake2;
static shared_ptr<Entity> text;
static shared_ptr<Entity> text1;
//sf::Texture tex;

sf::SoundBuffer buffer00;
sf::SoundBuffer jumpbuf00;
sf::SoundBuffer lowgbuf00;
sf::SoundBuffer speedbuf00;
sf::SoundBuffer shrinkbuf00;
sf::SoundBuffer growbuf00;

sf::Sound jump00;
sf::Sound lowg00;
sf::Sound speed00;
sf::Sound sound00;
sf::Sound shrink00;
sf::Sound grow00;

sf::View view00(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp0 = 0.5f;
const float lerp01 = 1.0f;

void options::Load()
{
	ls::loadLevelFile("res/optionsmenu.txt", 40.0f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	ls::setOffset(Vector2f(0, ho));

	/*buffer0.loadFromFile("res/sounds/dopst.wav");
	sound0.setBuffer(buffer0);
	sound0.setLoop(true);
	sound0.play();
	sound0.setVolume(50.0f);*/

	//auto txt = makeEntity();

	/*auto t = txt->addComponent<TextComponent>(
		"Play");
	auto y = txt->addComponent<SpriteComponent>();
		y->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) + Vector2f(0.0f, -10.0f));*/

		//sf::Font font;
		//font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
		//sf::Text playt;
		//playt.setFont(font);
		//playt.setColor(Color::Red);
		//playt.setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) /*+ Vector2f(0.0f, -10.0f)*/);
		//playt.setString("Play");
		//Engine::GetWindow().draw(playt);

	jumpbuf00.loadFromFile("res/sounds/jump.wav");
	jump00.setBuffer(jumpbuf00);

	lowgbuf00.loadFromFile("res/sounds/lowg.wav");
	lowg00.setBuffer(lowgbuf00);

	speedbuf00.loadFromFile("res/sounds/speed.wav");
	speed00.setBuffer(speedbuf00);

	shrinkbuf00.loadFromFile("res/sounds/shrink.wav");
	shrink00.setBuffer(shrinkbuf00);
	shrink00.setVolume(200.0f);

	growbuf00.loadFromFile("res/sounds/grow.wav");
	grow00.setBuffer(growbuf00);
	grow00.setVolume(200.0f);



	text = makeEntity();
	text->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t = text->addComponent<TextComponent>("Play");
	t->SetPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) + Vector2f(0.0f, -50.0f));
	t->render();

	text1 = makeEntity();
	text1->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t1 = text1->addComponent<TextComponent>("Options");
	t1->SetPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[0]) + Vector2f(0.0f, -50.0f));
	t1->render();




	// Create player
	{
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
	auto s = snake1->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(10.f);
	s->getShape().setFillColor(Color::White);
	s->getShape().setOrigin(30.f, 30.f);
	s->getShape().setOutlineThickness(5);
	s->getShape().setOutlineColor(sf::Color(100, 100, 100));

	snake2 = makeEntity();
	snake2->setPosition(player->getPosition() - Vector2f(10.0f, 10.0f));
	auto w = snake2->addComponent<ShapeComponent>();
	w->setShape<sf::CircleShape>(10.f);
	w->getShape().setFillColor(Color::White);
	w->getShape().setOrigin(30.f, 30.f);
	w->getShape().setOutlineThickness(5);
	w->getShape().setOutlineColor(sf::Color(100, 100, 100));

	{
		auto walls = ls::findTiles(ls::WALL);
		for (auto w : walls) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(20.f, 20.f); //offset to center
			auto e = makeEntity();
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
		}
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

	cout << " menu Load Done" << endl;

	setLoaded(true);
}

void options::UnLoad()
{
	cout << "Scene 1 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}
bool isbigger00 = false;
bool issmaller00 = false;
double cooldown00 = 0;
double sounddown00 = 0;
double sounddown010 = 0;
double sounddown020 = 0;
void options::Update(const double & dt)
{
	if (cooldown00 >= 0) { cooldown00 -= dt; }
	if (sounddown00 >= 0) { sounddown00 -= dt; }
	if (sounddown010 >= 0) { sounddown010 -= dt; }
	if (sounddown020 >= 0) { sounddown020 -= dt; }

	if (cooldown00 <= 0 && Keyboard::isKeyPressed(Keyboard::A)) {
		cooldown00 = 1.0;
		if (isbigger00 == false)
		{
			shrink00.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(0.5f, 0.5f);
			isbigger00 = true;

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
			grow00.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			isbigger00 = false;
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

	if (cooldown00 <= 0 && Keyboard::isKeyPressed(Keyboard::Q)) {
		cooldown00 = 1.0;
		if (issmaller00 == false)
		{
			grow00.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(2.0f, 2.0f);
			issmaller00 = true;

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
			shrink00.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			issmaller00 = false;
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

	pos.x += (player->getPosition().x - pos.x)*lerp0*dt;
	pos.y += (player->getPosition().y - pos.y)*lerp0*dt;

	focus->setPosition(pos);

	//focus->setPosition(player->getPosition());
	//view.setCenter(player->getPosition());


	view00.setCenter(focus->getPosition());

	sf::Vector2f pos1 = snake1->getPosition();

	pos1.x += ((player->getPosition().x - 30.0f) - pos1.x)*lerp01*dt;
	pos1.y += ((player->getPosition().y - 30.0f) - pos1.y)*lerp01*dt;

	snake1->setPosition(pos1);

	sf::Vector2f pos2 = snake2->getPosition();

	pos2.x += ((player->getPosition().x - 5.0f) - pos2.x)*lerp01*dt;
	pos2.y += ((player->getPosition().y - 5.0f) - pos2.y)*lerp01*dt;

	snake2->setPosition(pos2);

	if (sounddown00 <= 0 && Keyboard::isKeyPressed(Keyboard::Up)) {
		sounddown00 = 1;
		jump00.play();
	}
	if (sounddown010 <= 0 && Keyboard::isKeyPressed(Keyboard::S)) {
		sounddown010 = 3;
		speed00.play();
	}
	if (sounddown020 <= 0 && Keyboard::isKeyPressed(Keyboard::D)) {
		sounddown020 = 3;
		lowg00.play();
	}

	Scene::Update(dt);
	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&mainmenu);
	}
	else if (ls::getTileAt(player->getPosition()) == ls::OPT) {
		Engine::ChangeScene((Scene*)&level2);
	}
	/*else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level1);
	}*/

}

void options::Render()
{
	Engine::GetWindow().setView(view00);
	ls::render(Engine::GetWindow());
	Scene::Render();
}
