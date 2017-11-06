#include <iostream>
#include <string>
#include "Channel.h"
#include "expat.h"
#include "RSS.h"
#include <fstream>

using namespace std;

void STCallback(void * userData, XML_Char * tag, XML_Char ** vars);

int main(int argc, char * argv)
{
	/*
	fstream src("putty.log");		//Toma el archivo rss de la pagina
	string line;

	int j = 0;

	while (src.good())				//Se pasa el archivo a un string
	{
		line.resize(line.size() + 1);
		src.get(line[j]);
		j++;
	}

	RSS rssprueba(line);

	ofstream dest("RSSOut.txt");		//Se genera un archivo de salida con el rss
	string exp = rssprueba.getRSS();

	unsigned int p = rssprueba.getSize();

	for (unsigned int i = 0; i < p; i++)
	{
		dest << exp[i];
	}
	*/
		
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