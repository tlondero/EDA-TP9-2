#include "RSS.h"

RSS::RSS(string s)
{
	takePathToRSS(s);
	size = (unsigned int) path.size();
	noError = true;
}

void RSS::takePathToRSS(string s)
{
	int contadorString = 0;		//Contador del string

	int contadorPath = 0;		//Contador exclusivo del path
	int contadorPathAuxiliar;

	char tempPathBegin[BEGIN_OF_RSS_SIZE + 1];
	char tempPathEnd[END_OF_RSS_SIZE + 1];

	for (contadorPathAuxiliar = 0; strcmp(tempPathBegin, BEGIN_OF_RSS); contadorPathAuxiliar++, contadorString++)
	//Omito todo lo que se encuentra antes del RSS
	{
		tempPathBegin[contadorPathAuxiliar] = s[contadorString];

		if (contadorPathAuxiliar >= BEGIN_OF_RSS_SIZE)
		{
			contadorPathAuxiliar = -1;
			tempPathBegin[BEGIN_OF_RSS_SIZE] = '\0';
			contadorString -= BEGIN_OF_RSS_SIZE;
		}
	}

	contadorString -= 3;		//Arreglo el corrimiento del "<rs"

	do
	{
		path.resize(path.size() + 1);
		path[contadorPath] = s[contadorString];
		contadorPath++;

		for (contadorPathAuxiliar = 0; contadorPathAuxiliar < END_OF_RSS_SIZE; contadorPathAuxiliar++)			//Tomo los siguientes 6 caracteres
		{
			tempPathEnd[contadorPathAuxiliar] = s[contadorString + contadorPathAuxiliar];
		}
		tempPathEnd[contadorPathAuxiliar] = '\0';
		contadorString++;

	} while (strcmp(tempPathEnd, END_OF_RSS));			//Chequea si se llego al fin del RSS

	for (contadorPathAuxiliar = 0; contadorPathAuxiliar < END_OF_RSS_SIZE; contadorPathAuxiliar++)			//Agrego el final del RSS
	{
		path.resize(path.size() + 1);
		path[contadorPath + contadorPathAuxiliar] = s[contadorString + contadorPathAuxiliar];
	}

	path[contadorPath + contadorPathAuxiliar] = '\0';
}

string RSS::getRSS() { return path; }

unsigned int RSS::getSize() { return size; }

bool RSS::succes() { return noError; }