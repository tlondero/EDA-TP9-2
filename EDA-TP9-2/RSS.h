#pragma once

#include <string>
#include "expat.h"

#define BEGIN_OF_RSS	"<rss"
#define BEGIN_OF_RSS_SIZE 4

#define END_OF_RSS		"</rss>"
#define END_OF_RSS_SIZE 6

using namespace std;

class RSS
{
public:
	RSS(string s);
	string getRSS();
	void takePathToRSS(string s);
	unsigned int getSize();
	bool succes();
private:
	string path;
	unsigned int size;
	bool noError;
};