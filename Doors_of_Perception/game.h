
#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_level4.h"
#include "scenes/scene_level5.h"
#include "scenes/scene_menu.h"
#include "scenes/main_menu.h"
#include "scenes/options.h"
#include "scenes/kremap.h"
#include <SFML/Audio.hpp>
#include "controls.h"
#include "savegame.h"
#include "keybinder.h"
#include <string.h>



using namespace sf;

extern MenuScene menu;
extern Main_menu mainmenu;
extern options option;
extern Kremap kremap;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
extern Level4Scene level4;
extern Level5Scene level5;

extern sf::Sound sound;
//extern bool full;
extern sf::SoundBuffer buffer;
extern sf::SoundBuffer jumpbuf;
extern sf::SoundBuffer lowgbuf;
extern sf::SoundBuffer speedbuf;
extern sf::SoundBuffer shrinkbuf;
extern sf::SoundBuffer growbuf;

extern sf::Sound jump;
extern sf::Sound lowg;
extern sf::Sound speed;
//sf::Sound sound;
extern sf::Sound shrink;
extern sf::Sound grow;


extern Controls controls;

extern Savegame saver;
extern string saved;
extern string savepass;
extern Keybinder keybind;

extern sf::Clock timer1;
extern sf::Time time1;
extern sf::Time time2;

