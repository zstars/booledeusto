#ifndef ClaseJedecH
#define ClaseJedecH
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string.h>
#include "ClaseDevice.h"

//--------------------------------------------------------------------------
class Jedec
{
  deque <deque<string> >dequeCube;  // cuboboole
  Device *device;          // dispositivo a programar
  int variablesEnt;        // número de variables de Entrada.
  int variablesSal;        // número de variables de Salida.
  string* senyalIn;        // Array de apuntadores a string con
                           // los nombres de las señales de entrada

  // variables para fusibles
  string fuseList;               // lista de fusibles total sin formato.
  deque<string> fuseAsciiList;   // Lineas de fusibles formateada tipo L.
  char * fusiblesCelulas;        // Fusibles de las células
  unsigned fusesChecksum;        // cheksum de la lista de fusibles.

  string QF;            // número de fusibles
  string QP;            // número de patillas
  string QV;            // número máximo de vectores de test
  string G;             // conservar G0 o fundir G1 fusible seguridad
  string F;             // estado F0/F1 de los fusibles no especificados
  int fusePorDefecto;   // Valor de los fusibles que no salen en JEDEC

  string jedec;         // fichero final JEDEC.
  unsigned jedecChecksum;  // checksum final de todo el fichero Jedec
  int   flagError;      // posibles errores. Ver relación en .cpp

   // Escribe los 0 y 1 de la entrada. Usada para debugger
   void ListarDequeCube(ofstream &fichJedec);

    // Genera y devuelve un termino producto con fusibles al valor por defecto
   string FuseTerminoNoUsado(void);

   // Genera y devuelve el termino t como fusibles
   string FuseTermino(const string & t);

   // Construye la lista de todos los fusibles del chip
   void GenerarFuseList();

   // Genera fusibles de las celulas.    // Por ahora todos a 1.
   void GeneraFusiblesCelulas(const string& t, int offset);

   void GenerarFusesChecksum();

   // Si fila n está toda a 0 y fila n+1 tiene algún 1, cambia la fila n a todos 1.
   void ModificaAUnosFilasSeparadoras();

   // Genera un deque con todas las lineas tipo L de fusibles
   void GenerarLineasL();

   // Genera el fichero jedec al completo
   string & GenerarJedec();

   void AsignarPatillasAEntradasYSalidas();

 public:
   Jedec(list <list<string> >& listCube,     // lista de lista de términos
    Device d,                                // Dispositivo a fundir
    string* senyalIn,                        // Nombres señales de entrada
    char * fichero);                         // Nombre del fichero de salida

   void  EscribirJedec(ostream& ot);
   char* GetTextoFlagError(void);            // retorna dirección texto error
   int   GetCodigoFlagError(void);           // retorna dirección texto error
};
#endif
