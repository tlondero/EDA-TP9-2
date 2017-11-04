#include <iostream>
#include <string>
#include "Channel.h"
#include "expat.h"
#include "RSS.h"

using namespace std;

void STCallback(void * userData, XML_Char * tag, XML_Char ** vars);

int main(int argc, char * argv)
{
	Channel ch( (const char *) argv[1]);

	if (ch.noError())
	{

	}
	else
		cout << "Error" << endl;
	
	return 0;
}

void STCallback(void * userData, XML_Char * tag, XML_Char ** vars)
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

