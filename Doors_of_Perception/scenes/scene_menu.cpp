#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
//#include <joystickapi.h>
#include <SFML\Window\Joystick.hpp>
#include "../components/cmp_sprite.h"


using namespace std;
using namespace sf;

static shared_ptr<Entity> txt;

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

	  sf::ConvexShape convex1;
	  convex1.setPointCount(3);
	  convex1.setPoint(0, sf::Vector2f(0, 0));
	  convex1.setPoint(1, sf::Vector2f(40, 0));
	  convex1.setPoint(2, sf::Vector2f(20, 40));

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
    txt = makeEntity();
	txt->setPosition(Vector2f(0.0f, 0.0f));
    auto t = txt->addComponent<TextComponent>(
        "Doors of Perception\n\n\nPress Space or Start");
	t->SetPosition(winpass);
	auto j = txt->addComponent<ShapeComponent>();
	j->setShape<sf::ConvexShape>(convex1);
	j->getShape().setPosition(Vector2f(0.0f,0.0f));
	j->getShape().setFillColor(Color::Black);
	auto j1 = txt->addComponent<ShapeComponent>();
	j1->setShape< sf::CircleShape > (30.f); 
	j1->getShape().setPosition(Vector2f(0.0f, 0.0f));
	j1->getShape().setFillColor(Color::Black);
	auto j2 = txt->addComponent<ShapeComponent>();
	j2->setShape<sf::RectangleShape>(Vector2f(40.f, 40.0f));
	j2->getShape().setPosition(Vector2f(0.0f, 0.0f));
	j2->getShape().setFillColor(Color::Black);
	
	
	
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

bool transition = false;
void MenuScene::Update(const double& dt) {
	controls.update(dt);
  // cout << "Menu Update "<<dt<<"\n";
	//int poser = Joystick::getAxisPosition(0, sf::Joystick::Z);
	if (sf::Keyboard::isKeyPressed(Keyboard::Space) || controls.start() == true/*||poser>10*/) {
		//int poser = Joystick::getAxisPosition(0, sf::Joystick::X);
		/*time1 = timer1.getElapsedTime();
		auto t = txt->get_components<TextComponent>()[0];*/
		Engine::ChangeScene(&mainmenu);

		/*t->SetText("");
		txt->setPosition(Vector2f(640.0f, 360.0f));
		auto triangle = txt->get_components<ShapeComponent>()[0];
		auto circle = txt->get_components<ShapeComponent>()[1];
		auto rect = txt->get_components<ShapeComponent>()[2];
		triangle->getShape().setFillColor(Color::White);
		triangle->getShape().setPosition(Vector2f(640.0f, 360.0f));
		transition = true;*/
	}
	//time2 = timer1.getElapsedTime();
	
	/*if (transition==true&& time2.asSeconds() >= (time1.asSeconds()+2) &&  time2.asSeconds()<= (time1.asSeconds() + 5))
	{
			
	}
	if (transition == true && time2.asSeconds() >= (time1.asSeconds() + 5))
	{
		
	}*/
	  
	//Engine::GetWindow().create(sf::VideoMode::getFullscreenModes()[0], "", sf::Style::Fullscreen);
  

  Scene::Update(dt);
}

void MenuScene::Render()
{
	//Engine::GetWindow();
	

	Scene::Render();
}


