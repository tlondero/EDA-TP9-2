#include "Channel.h"

Channel::Channel(const char * l)
{
	parse = XML_ParserCreate(NULL);
	state = IDEL;
}

Channel::~Channel()
{
	XML_ParserFree(parse);
}

void Channel::fetchTitles()
{
	XML_SetElementHandler(parse, STCallback, ETCallback); //StartTitleCallback & EndTitleCallback
	XML_SetCharacterDataHandler(parse, CHCallback);
	XML_SetUserData(parse, this);
	RSS r(link);

	if (r.succes())
	{
		XML_Status status;
		XML_Parser(parse, r.getRSS(), r.RSSSize(), true);
		

	}
};

bool Channel::noError()
{
	if (error.empty())
		return true;
	else
		return false;
}

unsigned int Channel::getState() { return state; }

const char * Channel::getErrorSt() { return error.c_str(); }

bool Channel::titlesEmpty()
{
	if (titles.size() == 0)
		return true;
	else
		return false;
}

bool Channel::newState(unsigned int newState) { state = newState; }

titular Channel::getNextTitular()
{


}