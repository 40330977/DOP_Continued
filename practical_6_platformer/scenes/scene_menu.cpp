#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
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
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&mainmenu);
  }

  Scene::Update(dt);
}

void MenuScene::Render()
{
	//Engine::GetWindow();
	

	Scene::Render();
}


