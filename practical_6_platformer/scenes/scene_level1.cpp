#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> focus;

vector<Entity> enemies;
sf::View view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(1280.0f, 720.0f));
const float lerp = 1.0f;

void Level1Scene::Load() {
	//Engine::GetWindow().setKeyRepeatEnabled(false);
  cout << " Scene 1 Load" << endl;
  //ls::loadLevelFile("res/level_1.txt", 40.0f);
  ls::loadLevelFile("res/lvl1.txt", 40.0f);
  
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(30.f);
    s->getShape().setFillColor(Color::White);
    s->getShape().setOrigin(30.f, 30.f);

    player->addComponent<PlayerPhysicsComponent>(Vector2f(60.f, 60.f));
	player->addTag("player");
  }

  focus = makeEntity();
  focus->setPosition(player->getPosition());
  /*auto s = focus->addComponent<ShapeComponent>();
  s->setShape<sf::CircleShape>(20.f);
  s->getShape().setFillColor(Color::Red);*/

  //sf::Vector2f sets = focus->getPosition();
  //view.setCenter(sets);

  //View::setCenter(player->getPosition());

  // Create Enemy
  for(int i = 0; i< 10; i++)
  {
	  

	  auto enemy = makeEntity();
	  enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[i]) +
		  Vector2f(0, 24));
		  // *********************************
		  // Add HurtComponent
	  enemy->addComponent<HurtComponent>();
	  // Add ShapeComponent, Red 16.f Circle
	  auto e = enemy->addComponent<ShapeComponent>();
	  e->setShape<sf::RectangleShape>(Vector2f(40.f,40.0f));
	  e->getShape().setFillColor(Color::White);
	  e->getShape().setOrigin(20.f, 15.f);



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
double cooldown = 0;
void Level1Scene::Update(const double& dt) {
	if (cooldown >= 0) { cooldown -= dt; }

	if (cooldown <= 0 && Keyboard::isKeyPressed(Keyboard::A)){
		cooldown = 1.0;
		if (isbigger == false)
		{
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(0.5f, 0.5f);
			isbigger = true;

			/* auto p = player->get_components<PlayerPhysicsComponent>()[0];
			 p->Sizer(Vector2f(50.f, 50.f));*/

			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f((30.f), (30.f)));
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
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			isbigger = false;
			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f(60.f, 60.f));

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

	if (cooldown <= 0 && Keyboard::isKeyPressed(Keyboard::Q)) {
		cooldown = 1.0;
		if (issmaller == false)
		{
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(2.0f, 2.0f);
			issmaller = true;

			/* auto p = player->get_components<PlayerPhysicsComponent>()[0];
			 p->Sizer(Vector2f(50.f, 50.f));*/

			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f((2.0f*35.f), (2.0f*35.f)));
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
			auto s = player->get_components<ShapeComponent>()[0];
			s->getShape().setScale(1.0f, 1.0f);
			issmaller = false;
			auto p = player->get_components<PlayerPhysicsComponent>()[0];
			p->changeSize(Vector2f(35.f, 35.f));

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
	
  Scene::Update(dt);
  if (ls::getTileAt(player->getPosition()) == ls::END) {
	  Engine::ChangeScene((Scene*)&level2);
  }
  else if (!player->isAlive()) {
	  Engine::ChangeScene((Scene*)&level1);
  }
}

void Level1Scene::Render() {
	Engine::GetWindow().setView(view);
  ls::render(Engine::GetWindow());
  Scene::Render();
}
