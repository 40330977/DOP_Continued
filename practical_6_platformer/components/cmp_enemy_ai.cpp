#include "cmp_enemy_ai.h"
#include "engine.h"
#include <LevelSystem.h>

using namespace std;
using namespace sf;

float gsim = 0;
float spawner = 0;

void EnemyAIComponent::update(double dt) {
  auto mov = _direction * (float)(dt * _speed);
  mov.x += _direction.x * 16.f;
  //mov += _direction * 16.f;
  if (!validMove(_parent->getPosition() + mov)) {
    _direction.x *= -1.f;
  }

  mov.y += _direction.y * 16.f;
  if (!validMove(_parent->getPosition() + mov)) {
	  _direction.y *= -1.f;
  }


  if (_direction.y<0 && gsim>1000.0f)
  {
	  _direction.y *= -1.f;
	  gsim = 0;
  }
  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);
  gsim++;
  spawner++;
  if (spawner > 5.0f)
  {
	  spawner = 0;
  }
  const auto pos = _parent->getPosition();
  //Teleport to start if we fall off map.
  if (pos.y > ls::getHeight() * ls::getTileSize()) {
	  _parent->setPosition(Vector2f(50.f, 0));//spawner to be used here eventually to allow enemies to spawn in from the top once they fall off
  }

  if (pos.x < 1.0f)
  {
	  _parent->setPosition(Vector2f(50.f, 0));
  }
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p), _player(_parent->scene->ents.find("player")[0]) {
	auto pl = _player.lock();
	//Vector2f chaser = pl->getPosition() - _parent->getPosition();
	 //length(chaser);
 // _direction = Vector2f(chaser.x , 1.0f);
	_direction = Vector2f(1.0f, 1.0f);
  _jumper = Vector2f(1.0f, 0);
  _speed = 100.0f;
}
