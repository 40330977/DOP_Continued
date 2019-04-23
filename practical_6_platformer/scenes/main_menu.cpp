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
static shared_ptr<Entity> snakespeak1;
static shared_ptr<Entity> snakespeak2;
//sf::Texture tex;

sf::SoundBuffer buffer0;
sf::SoundBuffer jumpbuf0;
sf::SoundBuffer lowgbuf0;
sf::SoundBuffer speedbuf0;
sf::SoundBuffer shrinkbuf0;
sf::SoundBuffer growbuf0;

sf::Sound jump0;
sf::Sound lowg0;
sf::Sound speed0;
sf::Sound sound0;
sf::Sound shrink0;
sf::Sound grow0;

sf::View view0(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp0 = 0.5f;
const float lerp01 = 1.0f;

void Main_menu::Load()
{
	ls::loadLevelFile("res/mainmenu.txt", 40.0f);

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

	jumpbuf0.loadFromFile("res/sounds/jump.wav");
	jump0.setBuffer(jumpbuf0);

	lowgbuf0.loadFromFile("res/sounds/lowg.wav");
	lowg0.setBuffer(lowgbuf0);

	speedbuf0.loadFromFile("res/sounds/speed.wav");
	speed0.setBuffer(speedbuf0);

	shrinkbuf0.loadFromFile("res/sounds/shrink.wav");
	shrink0.setBuffer(shrinkbuf0);
	shrink0.setVolume(200.0f);

	growbuf0.loadFromFile("res/sounds/grow.wav");
	grow0.setBuffer(growbuf0);
	grow0.setVolume(200.0f);



	text = makeEntity();
	text->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t = text->addComponent<TextComponent>("Play");
	t->SetPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) + Vector2f(0.0f, -180.0f));
	t->render();

	text1 = makeEntity();
	text1->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t1 = text1->addComponent<TextComponent>("Options");
	t1->SetPosition(ls::getTilePosition(ls::findTiles(ls::OPT)[0]) + Vector2f(0.0f, -180.0f));
	t1->render();
	
	text2 = makeEntity();
	text2->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t2 = text2->addComponent<TextComponent>("Menu");
	t2->SetPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(-10.0f, -250.0f));
	t2->render();

	
	

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
	//snakespeak1 = makeEntity();
	//snakespeak1->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
	auto t3 = snake1->addComponent<TextComponent>("");
	t3->SetPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(-10.0f, -150.0f));
	t3->SetColour(Color::Magenta);
	//t2->render();

	snake2 = makeEntity();
	snake2->setPosition(player->getPosition() - Vector2f(10.0f, 10.0f));
	auto w = snake2->addComponent<ShapeComponent>();
	w->setShape<sf::CircleShape>(10.f);
	w->getShape().setFillColor(Color::White);
	w->getShape().setOrigin(30.f, 30.f);
	w->getShape().setOutlineThickness(5);
	w->getShape().setOutlineColor(sf::Color(100, 100, 100));
	auto t4 = snake2->addComponent<TextComponent>("");
	t4->SetPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(-10.0f, -150.0f));
	t4->SetColour(Color::Cyan);

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

void Main_menu::UnLoad()
{
	cout << "Scene 1 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}
bool isbigger0 = false;
bool issmaller0 = false;
//bool speach0 = false;
double cooldown0 = 0;
double sounddown0 = 0;
double sounddown01 = 0;
double sounddown02 = 0;
double ospeakcool0 = 3;
double ospeakcool1 = 7;
double ospeakcool2 = 10;
double ospeakcool3 = 14;
void Main_menu::Update(const double & dt)
{
	if (cooldown0 >= 0) { cooldown0 -= dt; }
	if (sounddown0 >= 0) { sounddown0 -= dt; }
	if (sounddown01 >= 0) { sounddown01 -= dt; }
	if (sounddown02 >= 0) { sounddown02 -= dt; }
	if (ospeakcool0 >= 0) { ospeakcool0 -= dt; }
	if (ospeakcool1 >= 0) { ospeakcool1 -= dt; }
	if (ospeakcool2 >= 0) { ospeakcool2 -= dt; }
	if (ospeakcool3 >= 0) { ospeakcool3 -= dt; }

	if (cooldown0 <= 0 && Keyboard::isKeyPressed(Keyboard::A)) {
		cooldown0 = 1.0;
		if (isbigger0 == false)
		{
			shrink0.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(0.5f, 0.5f);
			isbigger0 = true;

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
			grow0.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			isbigger0 = false;
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

	if (cooldown0 <= 0 && Keyboard::isKeyPressed(Keyboard::Q)) {
		cooldown0 = 1.0;
		if (issmaller0 == false)
		{
			grow0.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(2.0f, 2.0f);
			issmaller0 = true;

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
			shrink0.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			issmaller0 = false;
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


	view0.setCenter(focus->getPosition());

	sf::Vector2f pos1 = snake1->getPosition();

	pos1.x += ((player->getPosition().x - 30.0f) - pos1.x)*lerp01*dt;
	pos1.y += ((player->getPosition().y - 50.0f) - pos1.y)*lerp01*dt;

	snake1->setPosition(pos1);

	sf::Vector2f pos2 = snake2->getPosition();

	pos2.x += ((player->getPosition().x - 5.0f) - pos2.x)*lerp01*dt;
	pos2.y += ((player->getPosition().y - 30.0f) - pos2.y)*lerp01*dt;

	snake2->setPosition(pos2);

	if (ospeakcool0 <= 0 /*&& speach0 == false*/) {

		auto t = snake1->get_components<TextComponent>()[0];
		t->SetText("< to your left the \n adventure begins");
		t->SetPosition(snake1->getPosition() + Vector2f(20.0f, -50.0f));
		t->render();

		//speach1 = true;

	}
	if (ospeakcool1 <= 0 /*&& speach1 == true*/) {
		//speach0 = true;
		auto t = snake1->get_components<TextComponent>()[0];
		t->SetText("< ... and to the right the \n mysterious land of options");
		t->SetPosition(snake1->getPosition() + Vector2f(20.0f, -50.0f));
		//t->SetPosition(Vector2f(0.0f, 0.0f));
	}
	if (ospeakcool2 <= 0) {
		auto t = snake1->get_components<TextComponent>()[0];
		t->SetText("");
		t->SetPosition(snake1->getPosition() + Vector2f(20.0f, -50.0f));
		auto t1 = snake2->get_components<TextComponent>()[0];
		t1->SetText("< I think they \n know how to read...");
		t1->SetPosition(snake2->getPosition() + Vector2f(20.0f, -50.0f));
	}
	if (ospeakcool3 <= 0) {
		auto t = snake2->get_components<TextComponent>()[0];
		t->SetText("");
		t->SetPosition(snake2->getPosition() + Vector2f(20.0f, -50.0f));
	}

	if (sounddown0 <= 0 && Keyboard::isKeyPressed(Keyboard::Up)) {
		sounddown0 = 1;
		jump0.play();
	}
	if (sounddown01 <= 0 && Keyboard::isKeyPressed(Keyboard::S)) {
		sounddown01 = 3;
		speed0.play();
	}
	if (sounddown02 <= 0 && Keyboard::isKeyPressed(Keyboard::D)) {
		sounddown02 = 3;
		lowg0.play();
	}

	Scene::Update(dt);
	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&level1);
	}
	else if (ls::getTileAt(player->getPosition()) == ls::OPT) {
		Engine::ChangeScene((Scene*)&option);
	}
	/*else if (!player->isAlive()) {
		Engine::ChangeScene((Scene*)&level1);
	}*/

}

void Main_menu::Render()
{
	Engine::GetWindow().setView(view0);
	ls::render(Engine::GetWindow());
	Scene::Render();
}
