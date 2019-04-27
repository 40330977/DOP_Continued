
#pragma once
#include <ecm.h>
#include <SFML\Window\Joystick.hpp>

class Controls  {
protected:
	 int leftstick=0;
	 int trigger=0;
	 bool startb=false;
	 bool jumpb = false;
	 bool lowgb = false;
	 bool speedb = false;
	
public:
	void update(double dt);
	
	
	bool start();
	bool jump();
	bool lowg();
	bool speed();
	int stick();
	int triggers();
	
};
