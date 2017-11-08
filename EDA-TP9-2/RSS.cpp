#include "RSS.h"
#include "webHandler.h"


#define CANT_MAX_OF_TRIES_TO_READ_RSS 100
#define MAX_MARGEN_TO_END_RSS 100


#define PORT_HTTP 80
#define PORT_HTTP_STR "80"

#define CR 13
#define LF 10

RSS::RSS(char * link_)
{
	noError = true;
	errorMessage = "there is no error, IT´S ALL OK!";
	obtainRssFromWeb(link_); //en caso de que no se logre esta función, se cambia internamente el estado de noError y errorMessage
	if (noError)
	{
		filterRSS(rss);
	}
	
	size = (unsigned int)rss.size();
	
}

void RSS::obtainRssFromWeb(char * link_)
{
	char enter[2] = { CR, LF };
	string link = link_;
	string host;
	string route;

	translateLink(link, host, route);


	string hostWrapped = "Host: " + host;
	string messageProtocol = "GET " + route + " HTTP/1.1";

	webHandler httpHandler;
	//pido el rss
	httpHandler.conect_to_host(host.c_str(), PORT_HTTP_STR);
	httpHandler.set_bufClen((unsigned int)messageProtocol.size());
	httpHandler.send_msg((char *)messageProtocol.c_str()); //GET /.....
	httpHandler.set_bufClen(sizeof(enter));
	httpHandler.send_msg(enter); //enter
	httpHandler.set_bufClen((unsigned int)hostWrapped.size());
	httpHandler.send_msg((char *)hostWrapped.c_str());  // Host: .....
	httpHandler.set_bufClen(sizeof(enter));
	httpHandler.send_msg(enter); //enter
	httpHandler.send_msg(enter); //enter

								 //ahora escucho
	string mergeBuf;
	unsigned int tries = 0;
	bool firstTime = true;
	do								//leo hasta obtener todo el archivo que termina con "</rss>"
	{
		tries++;
		httpHandler.read_from_port();
		mergeBuf += httpHandler.get_buf();
		if (firstTime)
		{
			if (rssWasNotFound(httpHandler.get_buf()))
			{
				tries = CANT_MAX_OF_TRIES_TO_READ_RSS; //fuerzo irme
			}
			firstTime = false;
		}
	} while ((!finishedWith("</rss>", mergeBuf)) && (tries < CANT_MAX_OF_TRIES_TO_READ_RSS));


	if (tries >= CANT_MAX_OF_TRIES_TO_READ_RSS)
	{
		noError = false;
		errorMessage = "error obtaining rss from web";
	}
	else
	{
		//creo rss
		rss = mergeBuf;

	}

}

void RSS::filterRSS(string & completeRSS)
{
	int contadorString = 0;		//Contador del string

	int contadorPath = 0;		//Contador exclusivo del path
	int contadorPathAuxiliar;

	char tempPathBegin[BEGIN_OF_RSS_SIZE + 1];

	for (contadorPathAuxiliar = 0; strcmp(tempPathBegin, BEGIN_OF_RSS); contadorPathAuxiliar++, contadorString++)
		//Omito todo lo que se encuentra antes del RSS
	{
		tempPathBegin[contadorPathAuxiliar] = completeRSS[contadorString];

		if (contadorPathAuxiliar >= BEGIN_OF_RSS_SIZE)
		{
			contadorPathAuxiliar = -1;
			tempPathBegin[BEGIN_OF_RSS_SIZE] = '\0';
			contadorString -= BEGIN_OF_RSS_SIZE;
		}
	}

	contadorString -= 3;		//Arreglo el corrimiento del "<rs"

	rss = completeRSS.substr(contadorString, completeRSS.size());

	for (unsigned int i = 0; i < rss.size(); i++)
	{
		switch (rss[i])
		{
		case'á':
			rss[i] = 'a';
			break;
		case'é':
			rss[i] = 'e';
			break;
		case'í':
			rss[i] = 'i';
			break;
		case'ó':
			rss[i] = 'o';
			break;
		case'ú':
			rss[i] = 'u';
			break;
		case'ü':
			rss[i] = 'u';
			break;
		case'ñ':
			rss[i] = 'n';
			rss.insert(++i, 1, 'i');
			break;
		case'Á':
			rss[i] = 'A';
			break;
		case'É':
			rss[i] = 'E';
			break;
		case'Í':
			rss[i] = 'I';
			break;
		case'Ó':
			rss[i] = 'O';
			break;
		case'Ú':
			rss[i] = 'U';
			break;
		case'Ü':
			rss[i] = 'U';
			break;
		case'Ñ':
			rss[i] = 'N';
			rss.insert(++i, 1, 'I');
			break;
		default:
			if (rss[i] >= 128)
				rss[i] = '?';
		}
	}

	size = rss.size();


}

string & RSS::getRSS() { return rss; }

unsigned int RSS::getSize() { return size; }

bool RSS::succes() { return noError; }

string & RSS::getErrorMessage(void)
{
	return errorMessage;
}

void RSS::translateLink(string & link, string & host, string & route)
{
	int n = link.find_first_of("/"); //se le podrian agregar mas caracteres segun cuales usan otros sistemas operativos

	if (n > 0)
	{
		size_t distance2end = link.size() - n;
		host = link.substr(0, n);
		route = link.substr(n, distance2end);
	}
	else
	{
		host = link;
	}

}

bool RSS::finishedWith(char * signalOfEnd, string & str2check)
{
	bool ret = false;
	string strReduced = reduceStringFromTheEnd(100, str2check);
	size_t state = strReduced.find(signalOfEnd);
	if (state != (string::npos))
	{
		ret = true;
	}

	return ret;
}


string RSS::reduceStringFromTheEnd(unsigned int newSize, string & str2change)
{
	size_t oldLen = str2change.size();
	if (oldLen > newSize)
	{
		return str2change.substr(oldLen - newSize, newSize);
	}
	else
	{
		return str2change;
	}
}

bool RSS::rssWasNotFound(char * buf)
{
	bool ret = false;
	string strAux = buf;
	int n = strAux.find_first_of('\n');
	string firstLine = strAux.substr(0, n);
	int found01 = firstLine.find("NOT FOUND");
	int found02 = firstLine.find("Not Found");
	int found03 = firstLine.find("not found");
	if ((found01 != string::npos) || (found02 != string::npos) || (found03 != string::npos))
	{
		ret = true;
	}
	return ret;
}
