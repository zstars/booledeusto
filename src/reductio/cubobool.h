/***************************************************************************
                          cubobool.h  -  description
                             -------------------
    begin                : Thu Apr 12 2001
    copyright            : (C) 2001 by Borja Sotomayor
    email                : borja@borjanet.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CUBOBOOL_H
#define CUBOBOOL_H


/**
  *@author Borja Sotomayor
  */

#include <string>
using namespace std;


// La clase CuboBool obtiene su velocidad
// codificando los cubos como numeros enteros sin signo.
// Por ello, antes deberemos averiguar cual es el numero de bits
// que el compilador utiliza para codificar internamente un entero
// sin signo (unsigned int). Para ello, inspeccionamos la
// definicion estandar ULONG_MAX definida en <climits>. Segun
// el tamaño de ULONG_MAX, se definira el numero maximo de
// variables de los cubos.
#include <climits>
#ifndef ULONG_MAX
    #error ULONG_MAX no definido.
#else
    // Segun el valor de ULONG_MAX, definimos el numero maximo
    // de variables
    #if ULONG_MAX >= 4294967295UL
        #define MAXVAR 32
    #elif ULONG_MAX >= 65535
        #define MAXVAR 16
    #else
        #define MAXVAR 8
    #endif

    // Definimos ciertas macros que van a ser necesarias
    #define set_bit(b,i) (b |= (1ul<<i))
    #define reset_bit(b,i) (b &= ~(1ul<<i))
    #define test_bit(b,i) (b & (1ul<<i))

    // Definimos ciertos tipos de datos
    typedef unsigned long bitInt; // Utilizado para codificar cubos booleanos
    typedef unsigned char size; // Utilizado para expresar tamaños [0..MAXVAR]
#endif


/// Macro para encontrar el minimo entre dos valores.
#define minimo(A,B) ((A)<(B)?(A):(B))


/**
	* Clase que encapsula un cubo booleano y que permite realizar varias
	* operaciones sobre ellos.
	*/
class CuboBool
{
public:


/*#########-  CONSTRUCTORES  -#########*/

    /// Constructor por defecto. Inicializa el cubo sin literales.
    CuboBool();

    /// Construye el cubo con el 0-subcubo representado por n
    /// (numero entero sin signo)
    CuboBool(const bitInt n);

    /// Construye el cubo a partir de un array de caracteres (terminado en
    /// NULL que represente el cubo en notacion cubica
    /// (p.Ej: "1010", "1-0", "1-01--11-0", etc.)
    CuboBool(const char *s);

    /// Igual que el constructor CuboBool(const char *s), excepto que recibe un string (STL)
    CuboBool(const string &s);

    /// Constructor Copy
    CuboBool(const CuboBool &c);


/*#########-  MIEMBROS PUBLICOS  -#########*/

    /// Peso del cubo booleano (numero de 1s)
    size peso;

    /// Flag booleano. No tiene ninguna funcion especifica.
    /// El usuario de CuboBool puede utilizarlo como desee.
    bool flag;

    /// Numero de literales del cubo booleano.
    size literales;


/*#########-  CONVERSORES  -#########*/
    /// @name Conversores
		//@{

    /// Convierte el cubo booleano a string (representado en notacion cubica)
    string aString(const size numVar) const;

    /// Convierte el cubo booleano a un entero (siempre y cuando sea un
    /// 0-subcubo).
    bitInt aInt(void) const;

		//@}


/*#########-  SOBRECARGA DE OPERADORES PARA OPERACIONES CUBICAS  -#########*/
    /// @name Sobrecarga de Operadores
		//@{

    /// Operador de cobertura.
    /// A << B equivale a "¿A es cubierto por B?"
    inline bool operator<<(const CuboBool &c) const {return (Cubre(c, *this));}

    /// Operador de cobertura.
    /// A >> B equivale a "¿A cubre a B?"
    inline bool operator>>(const CuboBool &c) const {return (Cubre(*this, c));}

    /// Operador de combinabilidad.
    /// A && B equivale a "¿A es combinable con B?"
    inline bool operator&&(const CuboBool &c) const {return (Combinables(*this, c));}

    /// Operador de combinacion.
    /// A + B devuelve la combinacion de A y B, siempre y cuando sean combinables
    inline CuboBool operator+(const CuboBool &c) const {return (Combinar(*this, c));}

    /// Operador de combinacion.
    /// A += B deposita en A la combinacion de A y B (siempre y cuando
    /// A y B sean combinables).
    inline CuboBool operator+=(const CuboBool &c) {*this = Combinar(*this, c); return *this;}


/*#########-  SOBRECARGA DE OPERADORES PARA OPERACIONES LOGICAS  -#########*/

// La mayoria de estos operadores no son necesarios para el
// programador (salvo, quizas, los de igualdad y desigualdad).
// Sobre todo, son necesarios para poder utilizar CuboBool con aquellos
// contenedores de la STL que requieren establecer una relacion de orden
// entre sus elementos (como el contenedor 'set').

    /// Operador de igualdad
    inline bool operator==(const CuboBool &c) const {return ((this->unos == c.unos) && (this->ceros == c.ceros));}

    /// Operador de desigualdad
    inline bool operator!=(const CuboBool &c) const {return (!(*this == c));}

    /// Operador "estrictamente menor que"
    inline bool operator<(const CuboBool &c) const {return ((unos < c.unos)? true : (ceros < c.ceros) ? true : false);};

		/// Operador "estrictamente mayor que"
    inline bool operator>(const CuboBool &c) const {return (!((*this < c) || (*this == c)));}

    /// Operador "menor o igual que"
    inline bool operator<=(const CuboBool &c) const {return (!(*this > c));}

    /// Operador "mayor o igual que"
    inline bool operator>=(const CuboBool &c) const {return (!(*this < c));}


/*#########-  SOBRECARGA DEL OPERADOR DE ASIGNACION  -#########*/

		/// Operador de asignación
    CuboBool operator=(const CuboBool &c);

		//@}


/*#########-  OTRAS FUNCIONES MIEMBRO  -#########*/

    /// Pone el flag del cubo booleano a true
    inline void setFlag(void) {flag = true;}

    /// Comprueba si n-esima variable existe (si tiene un literal)
    inline bool existe(const size n) const {return ((test_bit(unos,n)) || (test_bit(ceros,n)));}



private:

/*#########-  MIEMBROS PRIVADOS  -#########*/

    /// @name Representación interna del cubo booleano
		//@{
		/** Los atributos privados "unos" y "ceros" se utilizan para representar
    	* internamente un codigo booleano.
			*/
    bitInt unos;
		/** Los atributos privados "unos" y "ceros" se utilizan para representar
    	* internamente un codigo booleano.
			*/
    bitInt ceros;
		//@}


/*#########-  CONSTRUCTORES PRIVADOS  -#########*/

    /// Constructor privado que recibe varios de los atributos, tanto publicos
    /// como privados del cubo. Solo es utilizado por las funciones miembro de
    /// CuboBool.
    CuboBool(const bitInt unosP, const bitInt cerosP, const size pesoP, const size literalesP);


/*#########-  METODOS PRIVADOS  -#########*/

    /// Funcion estatica que devuelve el peso de un dato de tipo BitInt
    /// (es decir, el numero de unos del numero)
    static size Peso(bitInt b);

    /// Devuelve true si 'a' y 'b' son combinables. Utilizado por el operador &&
    inline static bool Combinables(const CuboBool &a, const CuboBool &b) {return ( ( (a.unos ^ b.unos) == (a.ceros ^ b.ceros) ) && (Peso(a.unos ^ b.unos) == 1) );}
    /// Devuelve true si 'a' cubre a 'b'. Utilizado por los operadores >> y <<
    inline static bool Cubre(const CuboBool &a, const CuboBool &b) {return ( ( (a.unos | b.unos) ==  b.unos ) &&  ( (a.ceros | b.ceros) ==  b.ceros ) );}
    /// Devuelve el cubo resultante de combinar 'a' y 'b'. Utilizado por los operadores + y +=
    inline static CuboBool Combinar(const CuboBool &a, const CuboBool &b) {return CuboBool(a.unos & b.unos, a.ceros & b.ceros, minimo(a.peso,b.peso), a.literales-1);}
};

#endif
