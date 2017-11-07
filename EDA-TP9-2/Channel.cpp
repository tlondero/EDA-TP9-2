#include "Channel.h"

void STCallback(void * userData, const XML_Char * tag, const XML_Char ** vars);
void ETCallback(void * userData, const XML_Char * tag);
void CHCallback(void* userData, const XML_Char*s,int len);

Channel::Channel(const char * l)
{
	parse = XML_ParserCreate(NULL);
	state = IDLE;
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
	string s(tag);
	if (s == "channel")
	{
		ch->newState(IDLE);
	}
	else if (s=="item")
	{
		ch->newState(ITEM);
	}
	else if (s == "title")
	{
		if ((ch->getState()) == IDLE)
		{
			ch->newState(CHANNEL_TITLE);//LLamar a la funcion que imprime en El LCD el titulo de la fuente de datos(En el chcallback).
		}
		else if ((ch->getState()) == ITEM)
		{
			ch->newState(I_TITLE);
		}

	}
	else if (s == "pubDate")
	{
		if (ch->getState() == ITEM)
		{
			ch->newState(I_PUBDATE);
		}
	}
}

void ETCallback(void * userData, const XML_Char * tag)
{
	Channel * ch = (Channel *)userData;
	string s(tag);
	if (s == "channel")
	{
		//Creo que no hace falta nada.
	}
	else if (s == "item") //sale de un item
	{
		ch->newState(IDLE); 
	}
	else if (s == "title") 
	{
		if (ch->getState() == CHANNEL_TITLE) //sale del titulo del channel
		{
			ch->newState(IDLE); 
		}
		else if (ch->getState() == I_TITLE) //sale del titulo de un item
		{
			ch->newState(ITEM);
		}
	}
	else if (s == "item") //sale de un item.
	{
		ch->newState(IDLE);
	}
	else if (s == "pubDate")
	{
		if (ch->getState() == I_PUBDATE) //Sale del pubdate de un item.
		{
			ch->newState(ITEM);
		}
	}
}