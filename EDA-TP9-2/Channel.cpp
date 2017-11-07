#include "Channel.h"

void STCallback(void * userData, const XML_Char * tag, const XML_Char ** vars);
void ETCallback(void * userData, const XML_Char * tag);
void CHCallback(void* userData, const XML_Char*s,int len);

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
		XML_Parse(parse, r.getRSS(), r.RSSSize(), true);
		

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

void STCallback(void * userData, const XML_Char * tag, const XML_Char ** vars)
{
	Channel * ch = (Channel *)userData;
	if (to_string(ch->getNextTitular) == tag)
	{
		if (ch->getState() == CHANNEL)
			ch->newState(CH_TITLE);
		else if (ch->getState() == ITEM)
			ch->newState(I_TITLE);
	}
}