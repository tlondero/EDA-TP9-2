#include "Channel.h"

//Funcion que convierte elstring del xml con la pubdate en un date_t
date_t ConvertStringToDate(char*);


//Funcion que traducee un string con el nombre del mes a dos numeros.
//EJ: Jan a 01.
//Pone nullptr como month_res si hubo error.
void getMonth(char* month_res, string& month_word);

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
	XML_SetElementHandler(parse, this->STCallback, this->ETCallback); //StartTitleCallback & EndTitleCallback
	XML_SetCharacterDataHandler(parse, this->CHCallback);
	XML_SetUserData(parse, nullptr); //Habria que cmbiar el userdaa por un basicld referencia.
	RSS r(link);

	if (r.succes())
	{
		XML_Status status;
		XML_Parse(parse, r.getRSS().c_str(), r.getSize(), true);
		

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

void Channel::STCallback(void * userData, const XML_Char * tag, const XML_Char ** vars)
{
	string s(tag);
	titular temp;
	if (s == "channel")
	{
		this->newState(IDLE);
	}
	else if (s=="item")
	{
		this->newState(ITEM);
		this->titles.push_back(temp); //crea un nuevo titular.
		TitPos++;

	}
	else if (s == "title")
	{
		if ((this->getState()) == IDLE)
		{
			this->newState(CHANNEL_TITLE);
		}
		else if ((this->getState()) == ITEM)
		{
			this->newState(I_TITLE);
		}

	}
	else if (s == "pubDate")
	{
		if (this->getState() == ITEM)
		{
			this->newState(I_PUBDATE);
		}
	}
}

void  Channel::ETCallback(void * userData, const XML_Char * tag)
{
	string s(tag);
	if (s == "channel")
	{
		TitPos = 0; //Hace que la posicion apunte al comienzo del vector de titulares
	}
	else if (s == "item") //sale de un item
	{
		this->newState(IDLE);
	}
	else if (s == "title") 
	{
		if (this->getState() == CHANNEL_TITLE) //sale del titulo del channel
		{
			this->newState(IDLE);
		}
		else if (this->getState() == I_TITLE) //sale del titulo de un item
		{
			this->newState(ITEM);
		}
	}
	else if (s == "pubDate")
	{
		if (this->getState() == I_PUBDATE) //Sale del pubdate de un item.
		{
			this->newState(ITEM);
		}
	}
}

void  Channel::CHCallback(void* userData, const XML_Char*s, int len)
{
	char* str_temp = new char[len+1];
	date_t d_temp;
	if (((this->getState()) == I_TITLE) || ((this->getState()) == I_PUBDATE) || ((this->getState()) == CHANNEL_TITLE))
	{
		if ((this->getState()) == CHANNEL_TITLE)
		{
			//Habria que guardar el titulo del channel en algun lado?
		}
		else if ((this->getState()) == I_TITLE)
		{
			for (int i = 0; i < len; i++)
			{
				str_temp[i] = s[i];
			}
			str_temp[len] = '\0'; //Agrego el terminador
			((this->titles)[TitPos]).setTitle(str_temp); //setteo el titulo del ultimo titular.
		}
		else if ((this->getState()) == I_PUBDATE)
		{
			for (int i = 0; i < len; i++)
			{
				str_temp[i] = s[i];
			}
			str_temp[len] = '\0'; //Agrego el terminador.

			d_temp= ConvertStringToDate(str_temp);

			this->titles[TitPos].setDate(d_temp.day, d_temp.month, d_temp.year); //setteo la fecha del ultimo titular.
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
	if (s=="Jan")
	{
		m = "01";
	}
	else if (s == "Feb")
	{
		m = "02";
	}
	else if (s== "Mar")
	{
		m = "03";
	}
	else if (s=="Apr")
	{
		m = "04";
	}
	else if (s=="May")
	{
		m = "05";
	}
	else if (s=="Jun")
	{
		m = "06";
	}
	else if (s=="Jul")
	{
		m = "07";
	}
	else if (s=="Aug")
	{
		m = "08";
	}
	else if (s=="Sep")
	{
		m = "09";
	}
	else if (s== "Oct")
	{
		m = "10";
	}
	else if (s=="Nov")
	{
		m = "11";
	}
	else if (s== "Dec")
	{
		m = "12";
	}
	else 
	{
		m = nullptr;
	}
}