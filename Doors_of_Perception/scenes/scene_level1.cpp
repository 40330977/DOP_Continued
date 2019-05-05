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
#include <system_resources.h>


//#include <Sound.hpp>

using namespace std;
using namespace sf;



static shared_ptr<Entity> player;
static shared_ptr<Entity> focus;
static shared_ptr<Entity> snake1;
static shared_ptr<Entity> snake2;
static shared_ptr<Entity> text;
static shared_ptr<Texture> snakesprite;
static shared_ptr<Texture> snakesprite1;




vector<Entity> enemies;
sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp = 0.5f;
const float lerp1 = 1.0f;

void Level1Scene::Load() {
	time1 = timer1.getElapsedTime();
	//Engine::GetWindow().setKeyRepeatEnabled(false);
  cout << " Scene 1 Load" << endl;
  //ls::loadLevelFile("res/level_1.txt", 40.0f);
  ls::loadLevelFile("res/lvl1.txt", 40.0f);
  
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  //ls::setOffset(Vector2f(0, ho));



 /* if (!snakesprite->loadFromFile("res/Images/snake1.png")) {
	  cerr << "Failed to load spritesheet!" << std::endl;
  }*/
  snakesprite = Resources::get<Texture>("snake1.png");
  snakesprite1 = Resources::get<Texture>("snake2.png");

  sound.play();
  
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
  auto t3 = snake1->addComponent<TextComponent>("");
  t3->SetPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(-10.0f, -150.0f));
  t3->SetColour(Color::Green);
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
  auto t2 = snake2->addComponent<TextComponent>("");
  t2->SetPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(-10.0f, -150.0f));
  t2->SetColour(Color::Cyan);
  /*auto w = snake2->addComponent<ShapeComponent>();
  w->setShape<sf::CircleShape>(10.f);
  w->getShape().setFillColor(Color::White);
  w->getShape().setOrigin(30.f, 30.f);
  w->getShape().setOutlineThickness(5);
  w->getShape().setOutlineColor(sf::Color(100, 100, 100));*/

  text = makeEntity();
  text->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));
  auto t = text->addComponent<TextComponent>("");
  t->SetPosition(snake1->getPosition() + Vector2f(20.0f, -50.0f));
  t->SetColour(Color::Green);
  
  //t->render();

  // Create Enemy
  for(int i = 0; i< 10; i++)
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
		  convex.setPoint(1, sf::Vector2f(40,0));
		  convex.setPoint(2, sf::Vector2f(20,40));
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

  //{


	 // auto enemy1 = makeEntity();
	 // enemy1->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[1]) +
		//  Vector2f(0, 24));
	 // // *********************************
	 // // Add HurtComponent
	 // enemy1->addComponent<HurtComponent>();
	 // // Add ShapeComponent, Red 16.f Circle
	 // auto e = enemy1->addComponent<ShapeComponent>();
	 // e->setShape<sf::RectangleShape>(Vector2f(40.f, 40.0f));
	 // e->getShape().setFillColor(Color::White);
	 // e->getShape().setOrigin(20.f, 15.f);



	 // // Add EnemyAIComponent
	 // enemy1->addComponent<EnemyAIComponent>();
	 // //enemy->addComponent<PhysicsComponent>(true,Vector2f(30.f, 30.f));
	 // // *********************************
  //}

  // Add physics colliders to level tiles.
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

  

  //Simulate long loading times
//  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

bool isbigger = false;
bool issmaller = false;
bool speach0 = false;
bool speach1 = false;
double cooldown = 0;
double sounddown = 0;
double sounddown1 = 0;
double sounddown2 = 0;
double speakcool0 = 3;
double speakcool1 = 5;
void Level1Scene::Update(const double& dt) {
	time2 = timer1.getElapsedTime();
	controls.update(dt);
	if (cooldown >= 0) { cooldown -= dt; }
	if (sounddown >= 0) { sounddown -= dt; }
	if (sounddown1 >= 0) { sounddown1 -= dt; }
	if (sounddown2 >= 0) { sounddown2 -= dt; }
	if (speakcool0 >= 0) { speakcool0 -= dt; }
	if (speakcool1 >= 0) { speakcool1 -= dt; }

	if (cooldown <= 0 && Keyboard::isKeyPressed(keybind.kshrink) || cooldown <= 0 && controls.triggers() > 10){
		cooldown = 1.0;
		if (isbigger == false)
		{
			shrink.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(0.5f, 0.5f);
			isbigger = true;

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
			isbigger = false;
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

	if (cooldown <= 0 && Keyboard::isKeyPressed(keybind.kgrow) || cooldown <= 0 && controls.triggers() < -10) {
		cooldown = 1.0;
		if (issmaller == false)
		{
			grow.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(2.0f, 2.0f);
			issmaller = true;

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
			issmaller = false;
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


	view.setCenter(focus->getPosition());

	sf::Vector2f pos1 = snake1->getPosition();

	pos1.x += ((player->getPosition().x-90.0f) - pos1.x)*lerp1*dt;
	pos1.y += ((player->getPosition().y-90.0f) - pos1.y)*lerp1*dt;

	snake1->setPosition(pos1);

	sf::Vector2f pos2 = snake2->getPosition();

	pos2.x += ((player->getPosition().x-90.0f) - pos2.x)*lerp1*dt;
	pos2.y += ((player->getPosition().y-90.0f) - pos2.y)*lerp1*dt;

	snake2->setPosition(pos2);


	if (time2.asSeconds() >= (time1.asSeconds() + 3.0f)) {

		auto t = snake1->get_components<TextComponent>()[0];
		t->SetText("< Use your powers\n to get to the end!");
		t->SetPosition(snake1->getPosition() + Vector2f(100.0f, -18.0f));
		t->render();

		//speach1 = true;

	}
	if (time2.asSeconds() >= (time1.asSeconds() + 6.0f)) {
		//speach0 = true;
		auto t = snake1->get_components<TextComponent>()[0];
		t->SetText("< Your body may be trapped but \n  you can unlock your mind!");
		t->SetPosition(snake1->getPosition() + Vector2f(100.0f, -18.0f));
		//t->SetPosition(Vector2f(0.0f, 0.0f));
	}
	if (time2.asSeconds() >= (time1.asSeconds() + 9.0f)) {
		auto t = snake1->get_components<TextComponent>()[0];
		t->SetText("");
		t->SetPosition(snake1->getPosition() + Vector2f(100.0f, -18.0f));
		auto t1 = snake2->get_components<TextComponent>()[0];
		t1->SetText("  The shapes will try\n< and stop you...");
		t1->SetPosition(snake2->getPosition() + Vector2f(100.0f, -18.0f));
	}
	if (time2.asSeconds() >= (time1.asSeconds() + 12.0f)) {
		auto t = snake2->get_components<TextComponent>()[0];
		t->SetText("...I'm not even sure\n< if they're people anymore!");
		t->SetPosition(snake2->getPosition() + Vector2f(100.0f, -18.0f));
	}
	if (time2.asSeconds() >= (time1.asSeconds() + 15.0f)) {
		auto t = snake2->get_components<TextComponent>()[0];
		t->SetText("");
		t->SetPosition(snake2->getPosition() + Vector2f(100.0f, -18.0f));
	}

	if (sounddown <= 0 && Keyboard::isKeyPressed(keybind.kjump) || sounddown <= 0 && controls.jump() == true) {
		sounddown = 1;
		jump.play();
	}
	if (sounddown1 <= 0 && Keyboard::isKeyPressed(keybind.kspeed) || sounddown1 <= 0 && controls.speed() == true) {
		sounddown1 = 3;
		speed.play();
	}
	if (sounddown2 <= 0 && Keyboard::isKeyPressed(keybind.klowg) || sounddown2 <= 0 && controls.lowg() == true) {
		sounddown2 = 3;
		lowg.play();
	}

  Scene::Update(dt);
  if (ls::getTileAt(player->getPosition()) == ls::END) {
	  saver.save("level2");
	  Engine::ChangeScene((Scene*)&level2);
  }
  else if (!player->isAlive()) {
	  Engine::ChangeScene((Scene*)&level1);
  }
  if (Keyboard::isKeyPressed(Keyboard::P)||controls.start()==true) {
	  sound.stop();
	  Engine::ChangeScene((Scene*)&mainmenu);
  }
}

void Level1Scene::Render() {
	sf::Style::Fullscreen;
	Engine::GetWindow().setView(view);
	//Engine::GetWindow(sf::VideoMode(SEV_WindowWidth, SEV_WindowHeight, 32), SEV_WindowTitle, sf::Style::Fullscreen);
  ls::render(Engine::GetWindow());
  Scene::Render();
}
