/*$T boole/Circuito/limpiador.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "limpiador.h"
#pragma package(smart_init)
/*
 =======================================================================================================================
 =======================================================================================================================
 */
limpiador::limpiador(void)
{
	ecuacion = new string;
	terminos = new vector < string > ;
	parseado = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
limpiador::limpiador(string s)
{
	ecuacion = new string;
	*ecuacion = s;
	terminos = new vector < string > ;
	parseado = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
limpiador::~limpiador(void)
{
	delete ecuacion;
	delete terminos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void limpiador::setEcuacion(string &s)
{
	*ecuacion = s;
	parseado = false;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
vector<string> *limpiador::getTerminos(void)
{
	if(!parseado) parsear();
	return terminos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void limpiador::parsear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	string::iterator	i = ecuacion->begin(), end = ecuacion->end();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(i != end)
	{
		if(!esSimbolo(*i))
		{
			/*~~~~~~~~~~~~*/
			string	termino;
			/*~~~~~~~~~~~~*/

			i = ExtraerTermino(i, termino, end);
			terminos->push_back(termino);
		}
		else
			i++;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	vector<string>::iterator	new_end;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	sort(terminos->begin(), terminos->end());
	new_end = unique(terminos->begin(), terminos->end());
	terminos->erase(new_end, terminos->end());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
string limpiador::limpiar(void)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	string	aux = *ecuacion;
	/*~~~~~~~~~~~~~~~~~~~~*/

	if(!parseado) parsear();

	for(vector < string >::iterator i = terminos->begin(); i != terminos->end(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		string	termino = *i, antiguo, nuevo;
		int		sizeAntiguo, sizeNuevo, pos;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		antiguo = "~(~" + termino + ")";
		sizeAntiguo = antiguo.size();
		nuevo = "(" + termino + ")";

		while((pos = aux.find(antiguo)) != -1) aux.replace(pos, sizeAntiguo, nuevo);
	}

	for(vector < string >::iterator i = terminos->begin(); i != terminos->end(); i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		string	termino = *i, antiguo, nuevo;
		int		sizeAntiguo, sizeNuevo, pos;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		antiguo = "~(" + termino + ")";
		sizeAntiguo = antiguo.size();
		nuevo = "(~" + termino + ")";

		while((pos = aux.find(antiguo)) != -1) aux.replace(pos, sizeAntiguo, nuevo);
	}

	return aux;
}

string::iterator limpiador::
ExtraerTermino(string::iterator i, string & termino, string::iterator & end)
{
	while(!esSimbolo(*i) && (i != end)) termino += (*(i++));
	return i;
}
