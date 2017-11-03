#include "Channel.h"

void Channel::fetchTitles()
{
	parse = XML_ParserCreate(NULL);
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

Channel::~Channel()
{
	XML_ParserFree(parse);
}


bool Channel::noError()
{


}

unsigned int Channel::getState() { return state; }

const char * Channel::getErrorSt()
{


}

bool Channel::titlesEmpty()
{


}

bool Channel::newState(unsigned int newState) { state = newState; }

titular Channel::getNextTitular()
{

}