#pragma once

//Falta:
// constructor

#include <string>
#include "expat.h"

using namespace std;

class RSS
{
public:
	RSS(string s);
	string getRSS();
	unsigned int RSSSize();
	bool succes();
private:
	string path;
	unsigned int size;
	bool noError;
};