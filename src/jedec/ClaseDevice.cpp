#include <iostream>
#include <fstream>
#include <algorithm>
#include "claseDevice.h"
using namespace std;
//--------------------------------------------------------------------------

//  Constructor:  extern matrizDeEntrada GAL22V10_DIP[];
//                Device d("GAL22V10", 24, 5828, 44, GAL22V10_DIP);
 matrizDeEntrada GAL22V10_DIP[24]
                   = {1,  0, -1, -1,   -1,
                      2,  4, -1, -1,   -1,
                      3,  8, -1, -1,   -1,
                      4, 12, -1, -1,   -1,
                      5, 16, -1, -1,   -1,
                      6, 20, -1, -1,   -1,
                      7, 24, -1, -1,   -1,
                      8, 28, -1, -1,   -1,
                      9, 32, -1, -1,   -1,
                     10, 36, -1, -1,   -1,
                     11, 40, -1, -1,   -1,
                     13, 42, -1, -1,   -1,
                     14, 38,122,  9,   18,
                     15, 34,111, 11,   16,
                     16, 30, 98, 13,   14,
                     17, 26, 83, 15,   12,
                     18, 22, 66, 17,   10,
                     19, 18, 49, 17,    8,
                     20, 14, 34, 15,    6,
                     21, 10, 21, 13,    4,
                     22,  6, 10, 11,    2,
                     23,  2,  1,  9,    0,
                     25, -1,  0,  1,   -1,
                     26, -1,131,  1,   -1,};

// Constructor: extern matrizDeEntrada GAL22V10_PLCC[];
//              Device d("GAL22V10", 24, 5828, 44, GAL22V10_PLCC);
 matrizDeEntrada GAL22V10_PLCC[24]
                   = {2,  0, -1, -1,   -1,
                      3,  4, -1, -1,   -1,
                      4,  8, -1, -1,   -1,
                      5, 12, -1, -1,   -1,
                      6, 16, -1, -1,   -1,
                      7, 20, -1, -1,   -1,
                      9, 24, -1, -1,   -1,
                     10, 28, -1, -1,   -1,
                     11, 32, -1, -1,   -1,
                     12, 36, -1, -1,   -1,
                     13, 40, -1, -1,   -1,
                     16, 42, -1, -1,   -1,
                     17, 38,122,  9,   18,
                     18, 34,111, 11,   16,
                     19, 30, 98, 13,   14,
                     20, 26, 83, 15,   12,
                     21, 22, 66, 17,   10,
                     23, 18, 49, 17,    8,
                     24, 14, 34, 15,    6,
                     25, 10, 21, 13,    4,
                     26,  6, 10, 11,    2,
                     27,  2,  1,  9,    0,
                     29, -1,  0,  1,   -1,
                     30, -1,131,  1,   -1,};

//---------------------------------------------------------------------------


Device:: Device(string tipo, unsigned qPuertas, unsigned qMatriz,
                unsigned cols, matrizDeEntrada * chipDeEntrada):
                type(tipo), QP(qPuertas), QF(qMatriz), columnas(cols)
{
   chip = new matrizDispositivo[QP];
   for (unsigned i=0; i < QP; i++)
   {
       chip[i].pin    = chipDeEntrada[i].pin;
       chip[i].column = chipDeEntrada[i].column;
       chip[i].begin  = chipDeEntrada[i].begin;
       chip[i].avail  = chipDeEntrada[i].avail;
       chip[i].s0     = chipDeEntrada[i].s0;
       chip[i].used   = chip[i].avail == -1 ? -1 : 0;
       chip[i].senyal = strdup("-");
       chip[i].indice = i;
  }
   numeroFusiblesCelulas = 0;
   for (unsigned i=0; i < QP; i++)
       if (chip[i].s0 != -1)
           numeroFusiblesCelulas += 2 ;
}

unsigned Device::GetQP()                        { return QP;}
unsigned Device::GetQF()                        { return QF;}
unsigned Device::GetColumnas()                  { return columnas; }
string   Device::GetType()                      { return type;}
matrizDispositivo  Device::GetFusible(int i)    { return chip[i]; }
int      Device::GetColumn(int i)               { return chip[i].column;}
char*    Device::GetSenyal(int i)               { return chip[i].senyal; }
int      Device::GetNumeroFusiblesCelulas()     { return numeroFusiblesCelulas;}
void     Device::SetSenyal(int i, char* c)      { chip[i].senyal = strdup(c);}
void     Device::SetOrdenCubo(int i, int j)     { chip[i].ordenCubo = j;}
void     Device::IncrementarUsed(int i)         { chip[i].used++;}

void     Device::EscribirChip(ofstream & ot)
{
       ot << "\n\n";
       ot << "Pin\tSeñal\tCol\tFila\tHay\tUsadas\n";
       for (unsigned i=0; i < QP; i++)
       {
              ot  << chip[i].pin << '\t';
              if (chip[i].senyal[0] == '*')                // Si empieza por *
                 strcpy(chip[i].senyal, chip[i].senyal+1); // lo elimina.
              ot << chip[i].senyal << '\t';
              if (chip[i].column == -1) ot << '-' << '\t';
              else ot << chip[i].column  << '\t';
              if (chip[i].begin == -1)  ot << '-' << '\t';
              else ot << chip[i].begin  << '\t';
              if (chip[i].avail == -1) ot << '-' << '\t';
              else ot << chip[i].avail  << '\t';
              if (chip[i].used == -1)  ot << '-' << endl;
              else ot << chip[i].used  << endl;
       }
       ot << "\n\n";
}

