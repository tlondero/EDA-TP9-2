#include <iostream>
#include <string>
#include "Channel.h"
#include "expat.h"
#include "RSS.h"
#include <fstream>

using namespace std;

//Funcion que convierte elstring del xml con la pubdate en un date_t
date_t ConvertStringToDate(char*);


//Funcion que traducee un string con el nombre del mes a dos numeros.
//EJ: Jan a 01.
//Pone nullptr como month_res si hubo error.
void getMonth(char* month_res, string& month_word);


void STCallback(void * userData, const XML_Char * tag, const XML_Char ** vars);
static void ETCallback(void * userData, const XML_Char * tag);
static void CHCallback(void* userData, const XML_Char*s, int len);

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

void STCallback(void * userData, const XML_Char * tag, const XML_Char ** vars)
{
	Channel* ch = (Channel*)userData;
	string s(tag);
	titular temp;
	if (s == "channel")
	{
		ch->newState(IDLE);
	}
	else if (s == "item")
	{
		ch->newState(ITEM);
		ch->titles.push_back(temp); //crea un nuevo titular.
		(ch->TitPos)++;

	}
	else if (s == "title")
	{
		if ((ch->getState()) == IDLE)
		{
			ch->newState(CHANNEL_TITLE);
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

void  ETCallback(void * userData, const XML_Char * tag)
{
	Channel* ch = (Channel*)userData;
	string s(tag);
	if (s == "channel")
	{
		ch->TitPos = 0; //Hace que la posicion apunte al comienzo del vector de titulares
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
	else if (s == "pubDate")
	{
		if (ch->getState() == I_PUBDATE) //Sale del pubdate de un item.
		{
			ch->newState(ITEM);
		}
	}
}

void  CHCallback(void* userData, const XML_Char*s, int len)
{
	Channel* ch = (Channel*)userData;
	char* str_temp = new char[len + 1];
	date_t d_temp;
	if (((ch->getState()) == I_TITLE) || ((ch->getState()) == I_PUBDATE) || ((ch->getState()) == CHANNEL_TITLE))
	{
		if ((ch->getState()) == CHANNEL_TITLE)
		{
			//Habria que guardar el titulo del channel en algun lado?
		}
		else if ((ch->getState()) == I_TITLE)
		{
			for (int i = 0; i < len; i++)
			{
				str_temp[i] = s[i];
			}
			str_temp[len] = '\0'; //Agrego el terminador
			((ch->titles)[ch->TitPos]).setTitle(str_temp); //setteo el titulo del ultimo titular.
		}
		else if ((ch->getState()) == I_PUBDATE)
		{
			for (int i = 0; i < len; i++)
			{
				str_temp[i] = s[i];
			}
			str_temp[len] = '\0'; //Agrego el terminador.

			d_temp = ConvertStringToDate(str_temp);

			ch->titles[ch->TitPos].setDate(d_temp.day, d_temp.month, d_temp.year); //setteo la fecha del ultimo titular.
		}
	}

	delete[] str_temp;
}


date_t ConvertStringToDate(char* s)
{
	date_t date;
	string str(s);
	string d;
	string m;
	string y;
	char month_result[3];
	d = str.substr(5, 2); //string con el dia.
	m = str.substr(8, 3); //string con el mes.
	y = str.substr(12, 4); //string con el año.

	date.day[0] = (d.c_str())[0]; //settea el dia.
	date.day[1] = (d.c_str())[1];
	date.day[2] = (d.c_str())[2];

	date.year[0] = (y.c_str())[2]; //settea el año.
	date.year[1] = (y.c_str())[3];
	date.year[2] = (y.c_str())[4];

	getMonth(month_result, m);
	date.month[0] = month_result[0]; //settea el mes.
	date.month[1] = month_result[1];
	date.month[2] = month_result[2];


	return date;
}

void getMonth(char* m, string& s)
{
	if (s == "Jan")
	{
		m = "01";
	}
	else if (s == "Feb")
	{
		m = "02";
	}
	else if (s == "Mar")
	{
		m = "03";
	}
	else if (s == "Apr")
	{
		m = "04";
	}
	else if (s == "May")
	{
		m = "05";
	}
	else if (s == "Jun")
	{
		m = "06";
	}
	else if (s == "Jul")
	{
		m = "07";
	}
	else if (s == "Aug")
	{
		m = "08";
	}
	else if (s == "Sep")
	{
		m = "09";
	}
	else if (s == "Oct")
	{
		m = "10";
	}
	else if (s == "Nov")
	{
		m = "11";
	}
	else if (s == "Dec")
	{
		m = "12";
	}
	else
	{
		m = nullptr;
	}
}