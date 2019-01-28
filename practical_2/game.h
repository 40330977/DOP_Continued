//game.h
#include "Ship.h"
#include "bullet.h"
#pragma once
#include <SFML/Graphics.hpp>
constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 12;
constexpr uint16_t invaders_columns = 5;

extern sf::Texture spritesheet;
extern std::vector<Ship *> ships;
extern Player *player;
extern Bullet bullets[256];
extern unsigned char bulletpointer;
