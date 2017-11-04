#include "titular.h"


titular::titular()
{

}
titular::titular(char * title_, char * day_, char * month_, char * year_)
{
	setTitle(title_);
	setDate(day_, month_, year_);
}


titular::~titular()
{
}

char * titular::getTitle(void)
{
	return &((title.c_str())[0]);  //retorna la direccion de memoria del primer caracter del string (de otra forma algunos compiladores se quejarían)
}
date_t & titular::getDate(void)
{
	return date;
}
void titular::setTitle(char * title_)
{
	title = title_;
}
void titular::setDate(char * day_, char * month_, char * year_)
{
	date.day[0] = day_[0];
	date.day[1] = day_[1];
	date.month[0] = month_[0];
	date.month[1] = month_[1];
	date.year[0] = day_[0];
	date.year[1] = year_[1];

}