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

    auto txt = makeEntity();
	txt->setPosition(Vector2f(500.0f, 500.0f));
    auto t = txt->addComponent<TextComponent>(
        "\n\n\n\n\n\t\t\t\t\t\tDoors of Perception\n\n\n\n\t\t\t\t\t\t\tPress Space to Start");

	
	
	

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
    Engine::ChangeScene(&level1);
  }

  Scene::Update(dt);
}

void MenuScene::Render()
{
	//Engine::GetWindow();
	

	Scene::Render();
}


