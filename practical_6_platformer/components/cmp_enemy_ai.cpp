#include "cmp_enemy_ai.h"

using namespace std;
using namespace sf;

float gsim = 0;

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
  }
  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);
  gsim++;
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
  _direction = Vector2f(1.0f, 0);
  _jumper = Vector2f(1.0f, 0);
  _speed = 100.0f;
}
