#include "Channel.h"


Channel::Channel(const char * l)
{
	parse = XML_ParserCreate(NULL);
	state = IDLE;
	TitPos = 0;

}
Channel::~Channel()
{
	XML_ParserFree(parse);
}

void Channel::fetchTitles()
{
	XML_SetElementHandler(parse, STCallback, ETCallback); //StartTitleCallback & EndTitleCallback
	XML_SetCharacterDataHandler(parse, CHCallback);
	XML_SetUserData(parse, (void*)this); //Habria que cmbiar el userdaa por un basicld referencia.
	RSS r((char*)link.c_str());

	if (r.succes())
	{
		XML_Status status;
		status = XML_Parse(parse, r.getRSS().c_str(), r.getSize(), true);
		

	}
}

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

bool Channel::newState(unsigned int newState)
{ 
	state = newState; 
	return true;
}

titular Channel::getNextTitular()
{
	return titles[TitPos++];

}

