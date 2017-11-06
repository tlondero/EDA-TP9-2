#include "RSS.h"

RSS::RSS(string s)
{
	int i;
	int j;
	int k;
	
	for (i = 0; s[i] != BEGIN_OF_RSS; i++);			//Omito todo lo que se encuentra antes del RSS

	char tempPath[6];

	do
	{
		path.resize(path.size() + 1);
		path[i] = s[i];
		i++;

		for (j = 0; j < END_OF_RSS_SIZE; j++)			//Tomo los siguientes 6 caracteres
		{
			tempPath[j] = s[i + j];
		}

		tempPath[j] = '\0';

	} while (!strcmp(tempPath, END_OF_RSS));			//Chequea si se llego al fin del RSS

	for(k = 0; 0 < END_OF_RSS_SIZE; k++)			//Agrego el final del RSS
	{
		path.resize(path.size() + 1);
		path[i + k] = s[i + k];
	}

	path[i + k] = '\0';

	size = path.size();
	noError = true;
}

std::string RSS::getRSS() { return path; }

unsigned int RSS::RSSSize() { return size; }

bool RSS::succes() { return noError; }