#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"


using namespace std;

MenuScene menu;
Main_menu mainmenu;
options option;
Kremap kremap;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

sf::Sound sound;
//bool full;

sf::SoundBuffer buffer;
sf::SoundBuffer jumpbuf;
sf::SoundBuffer lowgbuf;
sf::SoundBuffer speedbuf;
sf::SoundBuffer shrinkbuf;
sf::SoundBuffer growbuf;

sf::Sound jump;
sf::Sound lowg;
sf::Sound speed;
//sf::Sound sound;
sf::Sound shrink;
sf::Sound grow;

Controls controls;

Savegame saver;
string saved;
string savepass;

sf::Clock timer1;
sf::Time time1;
sf::Time time2;

Keybinder keybind;

//sf::Style:Fullscreen
int main() {
  Engine::Start(1280, 720, "Doors of Perception","null",&menu);
  //Engine::Start(1280, 720, "Doors of Perception", "null", &level2);
  //Engine::Start(1280, 720, "Platformer1", "sf::Style:Fullscreen", &menu);
  
}