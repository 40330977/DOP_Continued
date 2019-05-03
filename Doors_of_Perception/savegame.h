#pragma once
#include <ecm.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace sf;
using namespace std;

class Savegame {
protected:
	//string saved;
public:
	void save(string saved);
	string load(string saved);

};