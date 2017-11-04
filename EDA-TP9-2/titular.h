#pragma once
#include <string>
using namespace std;
typedef struct
{
	char day[3]; //arreglo de 3 elementos, (2 digitos + terminador)
	char month[3];
	char year[3];
}date_t;
class titular
{
public:
	titular(); //luego de este constructor hay que llamar a los setters de manera explícita
	titular(char * title_, char * day_, char * month_, char * year_); //constructor que hace los setters implicitamente
	char * getTitle(void);
	date_t & getDate(void);
	void setTitle(char * title_);
	void setDate(char * day_, char * month_, char * year_); //da por sentado que cada char * representa una cadena de al menos 2 caracteres. 
	~titular();
private:

	string title;
	date_t date;
};

