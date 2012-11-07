#include <list>
#include <deque>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string.h>
#include "claseJedec.h"

#define extFicheroTexto ".lis"
#define extFicheroJedec ".jed"
#define cabecera "BOOLE-DEUSTO \n"

/* Cuenta empezando por 0 donde está el primer nodo en la lista:
   Nodo 0: Si combinacional "c" o secuencial "s"
   Nodo 1: nombre de la señal de entrada
   Nodos 2-n: términos                                        */
#define ORIGENtERMINOS  2

using namespace std;
char *textoFlagError[]={
   "0. No hay errores",
   "1. Tamaño de la lista de fusibles > número de fusibles del dispositivo",
   "2. Cube tiene algo distinto a '0', '1', '-'",
   "3. Ha recorrido todas las patillas y no hay ya disponibles en el device",
   "4. Tamaño de la lista de fusibles != número de fusibles del dispositivo",
   "5. Dispositivo desconocido",
   "6. no es 'c' o 'C' (combinacional) o 's' o 'S' (secuencial)"
   };

//-----------------------  CONSTRUCTOR  -----------------------------------
 Jedec::Jedec(list <list<string> >& listCube,
              Device pal,
              string argSenyalIn[],
              char * fichero)
 {
 // -----------   Convierte la 'lista de listas' de cube a 'deque de deques'.
     list<list<string> >::iterator  iterList;
     list<string>::iterator iterString;
     for (iterList = listCube.begin(); iterList != listCube.end(); iterList++)
     {
         deque<string> *dequeString = new deque<string>;
         copy(iterList->begin(), iterList->end(), back_inserter(*dequeString));
         dequeCube.push_back(*dequeString);
         delete dequeString;
     }

     if (pal.GetType().find("22V10", 0) == -1)
         {flagError = 5; return;}

    // -----------   Inicialización propiedades
    senyalIn = argSenyalIn;
    flagError = 0;
     char ascii[100];
     device = new Device(pal);
     QP   = "QP"; QP += itoa(device->GetQP(), ascii, 10); QP += "*\n";
     QF   = "QF"; QF += itoa(device->GetQF(), ascii, 10); QF += "*\n";
     QV   = "QV0*\n";                  // Vectores de test 0 por defecto
     G    = "G0*\n";                   // Fusible de seguridad 0 por defecto
     F    = "F0*\n";                   // Estado fusible 0 por defecto
     fusePorDefecto = 0;               // Estado fusible 0 por defecto
     fusesChecksum = 0;
     jedecChecksum = 0;
     variablesSal =  dequeCube.size();
     variablesEnt = (dequeCube.size() == 0)? 0 : dequeCube[0][ORIGENtERMINOS].size();

//  Preparación de los fusibles de las Células del chip.
     fusiblesCelulas = new char[pal.GetNumeroFusiblesCelulas() +1];   // tamaño
     memset(fusiblesCelulas, '1', pal.GetNumeroFusiblesCelulas());  // Rellena
     fusiblesCelulas[pal.GetNumeroFusiblesCelulas()] = '\0';     // terminación

// --------------   Proceso y obtención de fusibles para Jdec
     AsignarPatillasAEntradasYSalidas();
     if (flagError) return;
     GenerarFuseList();
     if (flagError) return;
     ModificaAUnosFilasSeparadoras();
     if (flagError) return;
     GenerarFusesChecksum();
     if (flagError) return;
     GenerarLineasL();
     if (flagError) return;
     GenerarJedec();

//  --------------- Escritura resultados
     char *ficheroTxt = new char[strlen(fichero)+strlen(extFicheroTexto)+1];
     strcpy(ficheroTxt, fichero);
     strcat(ficheroTxt, extFicheroTexto);
     ofstream fichJedecTxt(ficheroTxt);
     char *ficheroJed = new char[strlen(fichero)+strlen(extFicheroJedec)+1];
     strcpy(ficheroJed, fichero);
     strcat(ficheroJed, extFicheroJedec);
     ofstream fichJedecJed(ficheroJed);

     ListarDequeCube(fichJedecTxt);   // Escribe los 0 y 1 de la entrada.
     pal.EscribirChip(fichJedecTxt);  // Escribe propeidades de la Pal
     EscribirJedec(fichJedecTxt);     // Escribe contenido Jedec
     EscribirJedec(fichJedecJed);     // Escribe contenido Jedec
 }

//----------------------------------------------------------------------------
 char * Jedec::GetTextoFlagError(void)
     {return textoFlagError[flagError];}

 //----------------------------------------------------------------------------
 int Jedec::GetCodigoFlagError(void)
     {return flagError;}

 //----------------------------------------------------------------------------
void Jedec::AsignarPatillasAEntradasYSalidas()
{
    // Patillas de entrada empiezan en la 2 del chip
    unsigned patilla = 1;            // que realmente es la 2 del chip...
    for (int ve=0; ve < variablesEnt; ve++)             // variables entrada
         device->SetSenyal(patilla++, (char*)senyalIn[ve].c_str());
   // Patillas de salida. Las busca donde puede...
    for (int vs=0; vs < variablesSal; vs++)             // variables salida
    {
       for (patilla = device->GetQP()-1; patilla > 0; patilla--)
       {
           if (strcmp(device->GetFusible(patilla).senyal, "-") != 0)
               continue;
           if ((int)device->GetFusible(patilla).avail > (int)dequeCube[vs].size())
           {   // hay suficientes filas asignadas
               device->SetOrdenCubo(patilla, vs);
               // Añade al comienzo de senyalOt un '*'
               char wSenyalOt[80];
               strcpy(wSenyalOt, "*");
               strcat(wSenyalOt, (char*)dequeCube[vs][ORIGENtERMINOS-1].c_str());
               device->SetSenyal(patilla, wSenyalOt);
               break;
           }
       }
       if (patilla >= device->GetQP())
       {
           flagError = 3;                 // Ha recorrido todas las patillas
           break;                         //  y no patilla hay disponible.
       }
    } // fin for 'vs'
 }

//---------------------------------------------------------------------------
// Construye la lista de todos los fusibles del chip
void Jedec::GenerarFuseList()
{
  unsigned j, i;
  int k, m;
  // Copia y ordena por la fila 'begin' el array de descripción de fusibles
  deque<matrizDispositivo> f;
  for (i=0; i < device->GetQP(); i++)
      f.push_back(device->GetFusible(i));
  sort(f.begin(), f.end());
  // Genera fusibles de la matriz de productos
  for (i=0; i < device->GetQP(); i++)
  {
     if (f[i].begin != -1)                      // Es patilla de salida.
         if (f[i].senyal[0] == '*')              // Salida usandose.
         {
             fuseList += FuseTerminoNoUsado(); // Es la primera fila producto
             for (j = ORIGENtERMINOS; j < dequeCube[f[i].ordenCubo].size(); j++)
             {                                 // Resto filas producto con uso
                    fuseList += FuseTermino(dequeCube[f[i].ordenCubo][j]);
                    device->IncrementarUsed(f[i].indice);
             }
             // Pone bits celula segun sea combinacional o secuencial
             GeneraFusiblesCelulas(dequeCube[f[i].ordenCubo][0], f[i].s0);
             for (k = j-ORIGENtERMINOS; k < f[i].avail-1; k++)
                  // Filas sobrantes de esa salida
                  fuseList += FuseTerminoNoUsado();
         }
         else     // Patilla de Salida sin uso
             for (m = 0; m < f[i].avail; m++)
                 fuseList += FuseTerminoNoUsado();
   }
   // Añade al final los fusibles de las celulas.
   fuseList += fusiblesCelulas;
   if (fuseList.size() != device->GetQF())
       flagError = 4;
}

// -----------------------------------------------------------------------------
// Pone bits celula segun sea combinacional o secuencial.
// Genera fusibles de las celulas. En principio todos están a 1.
void Jedec::GeneraFusiblesCelulas(const string &t, int offset)
{
    fusiblesCelulas[offset] = '1';
    if (t == "c" || t== "C")
        fusiblesCelulas[offset+1] = '1';
    else if (t == "s" || t== "S")
        fusiblesCelulas[offset+1] = '0';
    else
         flagError = 6;
}

//  --------------------------------------------------------------
// Si fila n está toda a 0 y fila n+1 tiene algún 1, cambia la fila n a todos 1.
void Jedec::ModificaAUnosFilasSeparadoras()
{
   int q=0;
   int totalFuses = device->GetQF();
   int fusesColum = device->GetColumnas();
   string fila1, fila2, fila3(fusesColum, '1');

   fila1.assign(fuseList, 0, fusesColum);
   for (q= fusesColum; q < (totalFuses-fusesColum); q += fusesColum)
   {
       fila2.assign(fuseList, q, fusesColum);
      // Si la fila1 es todo 0 y la fila2 tiene algun 1, la fila1 pasa a todo 1
       if (fila1.find('1') == -1 && fila2.find('1') != -1)
           fuseList.replace(q-fusesColum, fusesColum, fila3);
       fila1 = fila2;
   }
}

 //----------------------------------------------------------------------------
 // Genera y devuelve un termino producto con fusibles al valor por defecto
 string Jedec::FuseTerminoNoUsado(void)
 {
    string linea;
    for(unsigned j = 0; j < device->GetColumnas()/2; j++)
          linea += fusePorDefecto == 0 ? "00" : "11";
    return linea;
 }

 //----------------------------------------------------------------------------
 // Genera y devuelve la fila de fusibles del termino producto del argumento.
  string Jedec::FuseTermino(const string& t)
  {
      int col1=0, col2, m;
      unsigned i, j, k=0, n;
      string linea;
      for(i=0; i < t.size(); i++)
          for(j=0; j < device->GetQP(); j++)
              if (strcmp(device->GetSenyal(j), senyalIn[k].c_str()) == 0)
              {
                  col2 = device->GetColumn(j)/2;
                  for (m = col1; m < col2; m++)
                      linea += "11";
                  switch(t[i++])
                  {
                      case ('0'): linea += "10"; break;
                      case ('1'): linea += "01"; break;
                      case ('-'): linea += "11"; break;
                      default: flagError = 2;
                  }
                  k++;
                  col1 = col2+1;
              }
      for (n=col2; n < device->GetColumnas()/2-1; n++)
           linea += "11";
      return linea;
   }

  //----------------------------------------------------------------------------
  // Obtiene el Checksum de la lista completa de fusibles
   void Jedec::GenerarFusesChecksum()
   {
       if (fuseList.size() > device->GetQF())
       {
           flagError = 1;
           return;
       }
       unsigned i = 0, j, w;
       while (i < fuseList.size())
       {
           for (j=0, w=0; j < 8 && i < fuseList.size() ; j++)
                w |= (fuseList[i++] == '0' ? 0 : 1) << j;
           fusesChecksum += w;
       }
      fusesChecksum %= 0xFFFF;
   }

   //--------------------------------------------------------------------------
   // Genera el deque con las lineas tipo L del fichero Jedec.
   // Son los fusibles que van a ir de forma explicita al
   // fichero, a partir del string fuseList que los contiene todos.
   void Jedec::GenerarLineasL()
   {
      char ascii[50];
      unsigned i=0, numlinea= 0, sizeLinea;
      while (i < fuseList.size())
      {
          sizeLinea = device->GetColumnas();  // Tamaño línea =  num. columnas.
          string linea = "L";
          sprintf(ascii, "%04u", sizeLinea*numlinea++);
          linea += ascii;
          linea += ' ';
          for (unsigned j=0; j < sizeLinea && i < fuseList.size() ; j+=2)
          {
                linea += fuseList[i++];
                linea += fuseList[i++];
                linea += ' ';
          }
          linea += "*\n";
          // Si la linea tiene todos los fusibles al valor por defecto
          // no pasa al fichero Jedec, en otro caso si.
          if (find(linea.begin()+5, linea.end(), device->GetQF()==0? '0':'1')
              != linea.end())
          fuseAsciiList.push_back(linea);
      }
    }

//----------------------------------------------------------------------------
// Genera el fichero jedec al completo
   string & Jedec::GenerarJedec()
   {
      char ascii[50];
      // parámetros iniciales
      jedec = 0x02;                                      // Caracter STX
      jedec +=  cabecera;
      jedec += "type: " + device->GetType() + "*\n";
      jedec += QP + QF + QV + G + F;                     // Diversas variables
      // fusibles
      for(unsigned i=0; i < fuseAsciiList.size(); i++)   // Lineas L
          jedec += fuseAsciiList[i];
      jedec += 'C';
      sprintf(ascii, "%04X", fusesChecksum);             //  Checksum fusibles
      jedec += ascii;
      jedec += "*\n";
      // final
      jedec += 0x03;                                     // Caracter ETX
      for(unsigned i = 0; i < jedec.size(); i++)
          jedecChecksum += jedec[i];
      jedecChecksum %= 0xFFFF;
      sprintf(ascii, "%04X", jedecChecksum);             // Checksum final
      jedec += ascii;
      return jedec;
   }

//----------------------------------------------------------------------------
// Escribe los 0 y 1 de la entrada. Usada para debugger
void Jedec::ListarDequeCube(ofstream &fichJedec)
{
  for (unsigned int i=0; i< dequeCube.size(); i++, fichJedec << endl)
      for (unsigned int j=0; j<dequeCube[i].size(); j++)
           fichJedec << '\t' << dequeCube[i][j] << endl;
 }

//----------------------------------------------------------------------------
   void Jedec::EscribirJedec(ostream& ot)
   {
    ot << jedec;
   }
//---------------------------------------------------------------------------


