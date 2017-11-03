#pragma once

//FALTA:
// titular

#include <string>
#include "expat.h"
#include "RSS.h"

using namespace std;

enum state {CH_TITLE, I_TITLE, I_UPBDATE, CHANNEL, ITEM, IDEL};

class Channel
{
public:
	Channel(const char * l = nullptr) : link(l) {};
	~Channel();
	void fetchTitles();
	bool noError();
	unsigned int getState();
	const char * getErrorSt();
	bool titlesEmpty();
	bool newState(unsigned int newState);
	
	titular getNextTitular();

private:
	XML_Parser parse;
	string chName;
	string link;
	string error;
	unsigned int state;

	titular tempTit;
	vector <titular> titles;
};