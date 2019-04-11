#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;



void Level1Scene::Load() {
	//Engine::GetWindow().setKeyRepeatEnabled(false);
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/level_1.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(20.f);
    s->getShape().setFillColor(Color::White);
    s->getShape().setOrigin(20.f, 20.f);

    player->addComponent<PlayerPhysicsComponent>(Vector2f(35.f, 35.f));
  }

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
			p->changeSize(Vector2f((0.5f*35.f), (0.5f*35.f)));
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

  Scene::Update(dt);
  if (ls::getTileAt(player->getPosition()) == ls::END) {
	  Engine::ChangeScene((Scene*)&level2);
  }
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
