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
static shared_ptr<Entity> text2;
static shared_ptr<Entity> text3;
static shared_ptr<Texture> snakesprite;
static shared_ptr<Texture> snakesprite1;

//sf::Texture tex;

//sf::SoundBuffer buffer00;
//sf::SoundBuffer jumpbuf00;
//sf::SoundBuffer lowgbuf00;
//sf::SoundBuffer speedbuf00;
//sf::SoundBuffer shrinkbuf00;
//sf::SoundBuffer growbuf00;
//
//sf::Sound jump00;
//sf::Sound lowg00;
//sf::Sound speed00;
//sf::Sound sound00;
//sf::Sound shrink00;
//sf::Sound grow00;

sf::View view00(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp0 = 0.5f;
const float lerp01 = 1.0f;
bool full1 = false;
Vector2f fullcheck;
Vector2f wincheck;
void options::Load()
{
	
	ls::loadLevelFile("res/optionsmenu.txt", 40.0f);

	//auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
	//ls::setOffset(Vector2f(0, ho));

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

	//fullcheck = ls::getTilePosition(ls::findTiles(ls::FULL)[0]);
	//wincheck = ls::getTilePosition(ls::findTiles(ls::WIN)[0]);

	/*jumpbuf00.loadFromFile("res/sounds/jump.wav");
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
	grow00.setVolume(200.0f);*/



	text = makeEntity();
	text->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t = text->addComponent<TextComponent>("Return to Main Menu");
	t->SetPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) + Vector2f(-100.0f, -80.0f));
	t->render();

	text1 = makeEntity();
	text1->setPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[0]));
	auto t1 = text1->addComponent<TextComponent>("Full Screen");
	t1->SetPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[0]) + Vector2f(0.0f, -50.0f));
	t1->render();

	text2 = makeEntity();
	text2->setPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[1]));
	auto t2 = text2->addComponent<TextComponent>("Windowed");
	t2->SetPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[1]) + Vector2f(0.0f, -50.0f));
	t2->render();

	text3 = makeEntity();
	//text2->setPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[1]));
	auto t3 = text3->addComponent<TextComponent>("Instructions:\nP = return to menu\n<-/-> = move left and right\nUp = jump\nQ = grow\nA = shrink\nS = increase speed\nD = lower gravity");
	t3->SetPosition(Vector2f(500.0f, 300.0f));
	t3->render();

	snakesprite = Resources::get<Texture>("snake1.png");
	snakesprite1 = Resources::get<Texture>("snake2.png");
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
	auto s1 = snake1->addComponent<SpriteComponent>();
	s1->setTexure(snakesprite);
	/*auto s = snake1->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(10.f);
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
	controls.update(dt);
	if (cooldown00 >= 0) { cooldown00 -= dt; }
	if (sounddown00 >= 0) { sounddown00 -= dt; }
	if (sounddown010 >= 0) { sounddown010 -= dt; }
	if (sounddown020 >= 0) { sounddown020 -= dt; }

	if (cooldown00 <= 0 && Keyboard::isKeyPressed(Keyboard::A) || cooldown00 <= 0 && controls.triggers() > 10) {
		cooldown00 = 1.0;
		if (isbigger00 == false)
		{
			shrink.play();
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
			grow.play();
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

	if (cooldown00 <= 0 && Keyboard::isKeyPressed(Keyboard::Q) || cooldown00 <= 0 && controls.triggers() < -10) {
		cooldown00 = 1.0;
		if (issmaller00 == false)
		{
			grow.play();
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
			shrink.play();
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

	pos1.x += ((player->getPosition().x - 90.0f) - pos1.x)*lerp01*dt;
	pos1.y += ((player->getPosition().y - 90.0f) - pos1.y)*lerp01*dt;

	snake1->setPosition(pos1);

	sf::Vector2f pos2 = snake2->getPosition();

	pos2.x += ((player->getPosition().x - 90.0f) - pos2.x)*lerp01*dt;
	pos2.y += ((player->getPosition().y - 90.0f) - pos2.y)*lerp01*dt;

	snake2->setPosition(pos2);

	if (sounddown00 <= 0 && Keyboard::isKeyPressed(Keyboard::Up) || sounddown00 <= 0 && controls.jump() == true) {
		sounddown00 = 1;
		jump.play();
	}
	if (sounddown010 <= 0 && Keyboard::isKeyPressed(Keyboard::S) || sounddown010 <= 0 && controls.speed() == true) {
		sounddown010 = 3;
		speed.play();
	}
	if (sounddown020 <= 0 && Keyboard::isKeyPressed(Keyboard::D) || sounddown020 <= 0 && controls.lowg() == true) {
		sounddown020 = 3;
		lowg.play();
	}
	/*if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {

		Engine::GetWindow().create(sf::VideoMode::getFullscreenModes()[0], "", sf::Style::Fullscreen);
	}*/

	Scene::Update(dt);
	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&mainmenu);
	}
	if (/*player->getPosition() == fullcheck*/Keyboard::isKeyPressed(Keyboard::V)&&full1 ==false) {
		Engine::GetWindow().create(sf::VideoMode::getFullscreenModes()[0], "Doors of Perception", sf::Style::Fullscreen);
		full1 = true;
		//Engine::fullscreen(full, 1280, 720, "Doors of Perception");
	}
	if (/*player->getPosition()==wincheck*/Keyboard::isKeyPressed(Keyboard::V)&&full1 ==true) {
		
		Engine::GetWindow().create(VideoMode(1280, 720), "Doors of Perception");
		full1 = false;
	}
	/*else if (ls::getTileAt(player->getPosition()) == ls::OPT) {
		Engine::ChangeScene((Scene*)&level2);
	}*/
	/*else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level1);
	}*/
	//Engine::GetWindow().close();
	

}

void options::Render()
{
	
	Engine::GetWindow().setView(view00);
	ls::render(Engine::GetWindow());
	Scene::Render();
}
