#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
//#include <joystickapi.h>
#include <SFML\Window\Joystick.hpp>


using namespace std;
using namespace sf;



void MenuScene::Load() {
	
  cout << "Menu Load \n";
  {
	  //sf::Music music;
	  buffer.loadFromFile("res/sounds/dopst.wav");
	  sound.setBuffer(buffer);
	  sound.setLoop(true);
	  //sound.play();
	  sound.setVolume(50.0f);

	  jumpbuf.loadFromFile("res/sounds/jump.wav");
	  jump.setBuffer(jumpbuf);

	  lowgbuf.loadFromFile("res/sounds/lowg.wav");
	  lowg.setBuffer(lowgbuf);

	  speedbuf.loadFromFile("res/sounds/speed.wav");
	  speed.setBuffer(speedbuf);

	  shrinkbuf.loadFromFile("res/sounds/shrink.wav");
	  shrink.setBuffer(shrinkbuf);
	  shrink.setVolume(200.0f);

	  growbuf.loadFromFile("res/sounds/grow.wav");
	  grow.setBuffer(growbuf);
	  grow.setVolume(200.0f);

	  // Is joystick #0 connected?
	  bool connected = sf::Joystick::isConnected(0);
	  cout << std::noboolalpha << connected;
	  // How many buttons does joystick #0 support?
	  unsigned int buttons = sf::Joystick::getButtonCount(0);
	  // Does joystick #0 define a X axis?
	  bool hasX = sf::Joystick::hasAxis(0, sf::Joystick::X);
	  // Is button #2 pressed on joystick #0?
	  bool pressed = sf::Joystick::isButtonPressed(0, 2);
	  // What's the current position of the Y axis on joystick #0?
	  float position = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	  Vector2f winpass = Vector2f(Engine::GetWindow().getView().getSize().x, Engine::GetWindow().getView().getSize().y);
	  winpass.x /= 2.75;
	  winpass.y /= 2.5;
    auto txt = makeEntity();
	txt->setPosition(Vector2f(500.0f, 500.0f));
    auto t = txt->addComponent<TextComponent>(
        "Doors of Perception\n\n\nPress Space to Start");
	t->SetPosition(winpass);

	
	
	

	 /* sf::Image menuscreen;
	  menuscreen.loadFromFile("res/invaders_sheet.png");
	  sf::Texture tex;
	  tex.loadFromFile("res/invaders_sheet.png");
	  sf::Sprite sprite;
	  sprite.setTexture(tex);
	  Engine::GetWindow().draw(sprite);
	  Engine::GetWindow().display();*/

	  //sf::Text title;
	  //title.setString("The Doors of Perception");
	  ////title.setCharacterSize(24);
	  //title.setFillColor(Color::Red);
	  //title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	  
  }
  
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	controls.update(dt);
  // cout << "Menu Update "<<dt<<"\n";
	//int poser = Joystick::getAxisPosition(0, sf::Joystick::Z);
  if (sf::Keyboard::isKeyPressed(Keyboard::Space)||controls.start()==true/*||poser>10*/) {
	  //int poser = Joystick::getAxisPosition(0, sf::Joystick::X);
    Engine::ChangeScene(&mainmenu);
	//Engine::GetWindow().create(sf::VideoMode::getFullscreenModes()[0], "", sf::Style::Fullscreen);
  }

  Scene::Update(dt);
}

void MenuScene::Render()
{
	//Engine::GetWindow();
	

	Scene::Render();
}


