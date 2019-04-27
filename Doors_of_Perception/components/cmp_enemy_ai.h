#pragma once

#include "cmp_actor_movement.h"
#include <Box2D/Dynamics/b2Body.h>

class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;
  sf::Vector2f _jumper;
  std::weak_ptr<Entity> _player;
  b2Body* _body;
public:
	bool isGrounded() const;
	void update(double dt) override;

  explicit EnemyAIComponent(Entity* p);



  EnemyAIComponent() = delete;
};
