#include "scene_level2.h"
#include "scene_level1.h"
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
sf::View view1(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp1 = 1.0f;

void Level2Scene::Load() {
  cout << "Scene 2 Load" << endl;
  //ls::loadLevelFile("res/level_2.txt", 40.0f);
  ls::loadLevelFile("res/lvl2b.txt", 40.0f);
  //auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  //ls::setOffset(Vector2f(0, ho));
  snakesprite = Resources::get<Texture>("snake1.png");
  snakesprite1 = Resources::get<Texture>("snake2.png");
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
  for (int i = 0; i < 7; i++)
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

void Level2Scene::UnLoad() {
  cout << "Scene 2 UnLoad" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

bool isbigger1 = false;
bool issmaller1 = false;
double cooldown1 = 0;
double sounddown20 = 0;
double sounddown21 = 0;
double sounddown22 = 0;
void Level2Scene::Update(const double& dt) {
	controls.update(dt);
	if (cooldown1 >= 0) { cooldown1 -= dt; }
	if (sounddown20 >= 0) { sounddown20 -= dt; }
	if (sounddown21 >= 0) { sounddown21 -= dt; }
	if (sounddown22 >= 0) { sounddown22 -= dt; }

	if (cooldown1 <= 0 && Keyboard::isKeyPressed(Keyboard::A) || cooldown1 <= 0 && controls.triggers() > 10) {
		cooldown1 = 1.0;
		if (isbigger1 == false)
		{
			shrink.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(0.5f, 0.5f);
			isbigger1 = true;

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
			isbigger1 = false;
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

	if (cooldown1 <= 0 && Keyboard::isKeyPressed(Keyboard::Q) || cooldown1 <= 0 && controls.triggers() < -10) {
		cooldown1 = 1.0;
		if (issmaller1 == false)
		{
			grow.play();
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(2.0f, 2.0f);
			issmaller1 = true;

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
			issmaller1 = false;
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

	pos.x += (player->getPosition().x - pos.x)*lerp1*dt;
	pos.y += (player->getPosition().y - pos.y)*lerp1*dt;

	focus->setPosition(pos);

	//focus->setPosition(player->getPosition());
	//view.setCenter(player->getPosition());
	view1.setCenter(focus->getPosition());
	sf::Vector2f pos1 = snake1->getPosition();

	pos1.x += ((player->getPosition().x - 90.0f) - pos1.x)*lerp1*dt;
	pos1.y += ((player->getPosition().y - 90.0f) - pos1.y)*lerp1*dt;

	snake1->setPosition(pos1);

	sf::Vector2f pos2 = snake2->getPosition();

	pos2.x += ((player->getPosition().x - 90.0f) - pos2.x)*lerp1*dt;
	pos2.y += ((player->getPosition().y - 90.0f) - pos2.y)*lerp1*dt;

	snake2->setPosition(pos2);

	if (sounddown20 <= 0 && Keyboard::isKeyPressed(Keyboard::Up) || sounddown20 <= 0 && controls.jump() == true) {
		sounddown20 = 1;
		jump.play();
	}
	if (sounddown21 <= 0 && Keyboard::isKeyPressed(Keyboard::S) || sounddown21 <= 0 && controls.speed() == true) {
		sounddown21 = 3;
		speed.play();
	}
	if (sounddown22 <= 0 && Keyboard::isKeyPressed(Keyboard::D) || sounddown22 <= 0 && controls.lowg() == true) {
		sounddown22 = 3;
		lowg.play();
	}

  Scene::Update(dt);
  const auto pp = player->getPosition();
  if (ls::getTileAt(pp) == ls::END) {
    Engine::ChangeScene((Scene*)&mainmenu);
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level2);
  }
  if (Keyboard::isKeyPressed(Keyboard::P) || controls.start() == true) {
	  sound.stop();
	  Engine::ChangeScene((Scene*)&mainmenu);
  }
}

void Level2Scene::Render() {
	Engine::GetWindow().setView(view1);
  ls::render(Engine::GetWindow());
  Scene::Render();
}
