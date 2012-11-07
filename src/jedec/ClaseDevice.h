#ifndef ClaseDeviceH
#define ClaseDeviceH
#include <iostream>
using namespace std;


  struct matrizDispositivo
  {
     int indice;         // Número de orden de la fila, de 0 a n-1
     int pin;            // Número de pin del chip
     int column;         // columna origen en la matriz de fusibles
     int begin;          // Número de fila en la matriz de fusibles
     int avail;          // filas disponibes a partir de 'begin'
     int used;           // filas usadas del conjunto de 'avail'
     int s0;             // Numero del fusible S0 de la célula. S1 = S0+1.
     char* senyal;       // Identificación de las señales de entrada y salida
     int ordenCubo;      // Lugar de orden, empezando por 0, del deque del
                         // cubo que contiene los productos para esta señal.
     bool operator<(const matrizDispositivo & f) const
         {return begin < f.begin;}
  };

  struct matrizDeEntrada
  {
     int pin;            // Número de pin del chip
     int column;         // columna origen en la matriz de fusibles
     int begin;          // Número de fila en la matriz de fusibles
     int avail;          // filas disponibes a partir de 'begin'
     int s0;             // Numero del fusible S0 de la célula. S1 = S0+1,
 };                      // relativo a origen del primero. Se supone que todos
                         // van seguidos. Ej: en 22v10 pin 23 el 0 (que en
                         // realidad corresponde al 5808)

class Device
{
  string type;           // dispositivo
  unsigned QP;           // número de patillas dispositivo
  unsigned QF;           // número de fusibles
  unsigned columnas;     // numero de columnas en el array fusibles.
  unsigned numeroFusiblesCelulas;   // Número de fusibles para las células
  matrizDispositivo*  chip;         // array de la estructura del chip

  public:
    Device(string tipo, unsigned qPuertas, unsigned qmatriz,
                        unsigned cols, matrizDeEntrada * f);
    unsigned GetQP();
    unsigned GetQF();
    unsigned GetColumnas();
    string   GetType();
    matrizDispositivo   GetFusible(int i);

    int      GetColumn(int i);
    char *   GetSenyal(int i);
    int      GetNumeroFusiblesCelulas();
    void     SetSenyal(int i, char *c);
    void     SetOrdenCubo(int patilla, int indice);
    void     IncrementarUsed(int i);
    void     EscribirChip(ofstream& ot);
 };

extern matrizDeEntrada GAL22V10_DIP[];
extern matrizDeEntrada GAL22V10_PLCC[];
#endif
