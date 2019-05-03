#include "savegame.h"
#include <string.h>

using namespace std;

void Savegame::save(string saved)
{
	ofstream myfile("res/savegame.txt");
	if (myfile.is_open())
	{
		myfile << saved;
		
		myfile.close();
	}
}

string Savegame::load(string saved)
{
	ifstream myfile("res/savegame.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, saved))
		{
			cout << saved;
		}
		myfile.close();
	}

	return saved;
}
