#pragma once

#include <string>
#include "expat.h"

using namespace std;

class RSS
{
public:
	RSS(char * link_);
	string & getRSS();
	unsigned int getSize();
	bool succes();
	string & getErrorMessage(void);
private:
	string rss;
	unsigned int size;
	bool noError;
	string errorMessage;
	void translateLink(string & link, string & host, string & route);
	bool finishedWith(char * signalOfEnd, string & str2check);
	string reduceStringFromTheEnd(unsigned int newSize, string & str2change);
	void obtainRssFromWeb(char * link_);
	void filterRSS(string & completeRSS);
};
