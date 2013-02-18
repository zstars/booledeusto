/*$T boole/Boole1/Libreria.h GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef libreriaH
#define libreriaH

int			binario(AnsiString);
int			FusionarCadenas(AnsiString, AnsiString);
int			JuntarCadenas(AnsiString, AnsiString);
AnsiString	CalcularBinario(int, int);
AnsiString	CalcularCadena(AnsiString);
AnsiString	NombresCompletos(AnsiString cadena, bool reemplazarParentesis = false);
AnsiString	InvertirVariables(AnsiString);
AnsiString	CambiarSignos(AnsiString, bool);
AnsiString	InvertirExpresiones(AnsiString);
AnsiString	AniadirSimbolos(AnsiString, bool);
int			NumeroTerminos(AnsiString);
int			NumeroLiterales(AnsiString);
AnsiString      PonerNombresVariables(AnsiString);
#endif
