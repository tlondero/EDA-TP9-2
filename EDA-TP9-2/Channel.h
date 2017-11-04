#pragma once
#include <string>
#include <vector>
#include "expat.h"
#include "RSS.h"
#include "titular.h"

using namespace std;

enum state {CH_TITLE, I_TITLE, I_UPBDATE, CHANNEL, ITEM, IDEL};

class Channel
{
public:
	Channel(const char * l = nullptr);
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