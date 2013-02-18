/*$T boole/Circuito/limpiador.h GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef limpiadorH
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define esSimbolo(c)	(((c) == '(') || ((c) == ')') || ((c) == '+') || ((c) == '*') || ((c) == '~'))
class	limpiador
{
	string			*ecuacion;
	vector<string>	*terminos;
	bool			parseado;

	void			parsear(void);
	string::iterator ExtraerTermino(string::iterator i, string & termino, string::iterator & end);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	limpiador(void);
	limpiador(string s);
	~limpiador(void);

	void			setEcuacion(string &s);
	vector<string>	*getTerminos(void);

	string			limpiar(void);
};

#define limpiadorH
#endif
