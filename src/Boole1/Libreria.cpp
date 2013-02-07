/*$T boole/Boole1/Libreria.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include <stdlib.h>

#include "Math.h"
#include "DinArray.h"
#include "libreria.h"

#include <string>
#include <algorithm>

extern DinArray Tabla;

/*
 =======================================================================================================================
    devuelve el valor decimal de una cadena binaria ejemplo: 10011 => 19
 =======================================================================================================================
 */
int binario(AnsiString cadena)
{
	/*~~~~~~~~~~~*/
	int contador;
	int numero = 0;
	/*~~~~~~~~~~~*/

	contador = cadena.Length();
	for(contador; contador >= 1; contador--)
	{	// hacemos un bucle para buscar su valor en binario
		numero = numero + (cadena.SubString(contador, 1) * pow(2, cadena.Length() - contador));
	};
	return numero;
};

/*
 =======================================================================================================================
    devuelve el valor decimal de la cadena binaria resultante de la mezcla alternada de dos cadenas ejemplo: 101 01 =>
    10011 => 19
 =======================================================================================================================
 */
int FusionarCadenas(AnsiString x, AnsiString y)
{
	/*~~~~~~~~~~~~~~~~~~*/
	AnsiString	temp = "";
	/*~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i <= x.Length(); i++)
	{
		temp = temp + x.SubString(i, 1);
		if((i != x.Length()) | (x.Length() == y.Length())) temp = temp + y.SubString(i, 1);
	}

	return binario(temp);
};

/*
 =======================================================================================================================
    devuelve el valor decimal de la cadena binaria resultante de la union de dos cadenas ejemplo: 10 011 => 10011 => 19
 =======================================================================================================================
 */
int JuntarCadenas(AnsiString x, AnsiString y)
{
	/*~~~~~~~~~~~~~*/
	AnsiString	temp;
	/*~~~~~~~~~~~~~*/

	temp = x + y;
	return binario(temp);
};

/*
 =======================================================================================================================
    devulve la cadena binaria correspondiente al número introducido y los demas ceros dependiendo del número de
    variables ejemplo: 19,7 => 0010011
 =======================================================================================================================
 */
AnsiString CalcularBinario(int x, int y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	resultado = "";
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	do
	{	// insertar al principio
		resultado.Insert(div(x, 2).rem, 1);
		x = div(x, 2).quot;
	} while(x > 1);
	if(x == 1) resultado.Insert("1", 1);
	for(int i = y - resultado.Length(); i > 0; i--)
	{
		resultado.Insert("0", 1);
	}

	return(resultado);
};

/*
 =======================================================================================================================
    devuelve la cadena binaria de letras correspondiente a la cadena binaria ejemplo: 10011101 => A~B~CDEF~GH
 =======================================================================================================================
 */
AnsiString CalcularCadena(AnsiString cifra)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	resultado = "";
	/*~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i <= cifra.Length(); i++)
	{
		if(cifra.SubString(i, 1) == "0") resultado = resultado + "~";
		resultado = resultado + char('A' - 1 + i);
	}

	return(resultado);
};

/*
 =======================================================================================================================
    devuelve la cadena sustituyendo las variables generales por los nombres que se les ha dado o por ellas mismas en
    mayusculas.

    Cuando los nombres tienen paréntesis, se sustityen por corchetes, para evitar errores que de otro modo suceden,
    por ejemplo, en gráficos.
 =======================================================================================================================
 */
AnsiString NombresCompletos(AnsiString cadena, bool reemplazarParentesis)
{
	/*~~~~~~*/
	int i = 1;
	/*~~~~~~*/

	cadena.UpperCase();
	while(i <= cadena.Length())
	{
		//if(isalpha(char(*(cadena.SubString(i, 1)).c_str())))
                if(isalpha(cadena[i]))
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	nombre = Tabla.LeerEntrada(cadena[i] - 'A');
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			// Asegurarse de que el nombre no contiene paréntesis.
			if(reemplazarParentesis)
			{
				std::string nom = nombre.c_str();
				std::replace(nom.begin(), nom.end(), '(', '[');
				std::replace(nom.begin(), nom.end(), ')', ']');
				nombre = nom.c_str();
			}

			if(nombre != "")
			{
				cadena.Delete(i, 1);
				cadena.Insert(nombre, i);
				i = i + nombre.Length();
			}
			else
				i = i + 1;
		}
		else
			i = i + 1;
	}

	return cadena;
}

/*
 =======================================================================================================================
    función que niega las variables, si son negadas dos veces se simplifica ejemplo: A+~C+D+E+~F => ~A+C+~D+~E+F
 =======================================================================================================================
 */
AnsiString InvertirVariables(AnsiString cadena)
{
	/*~~~~~~*/
	int x = 1;
	/*~~~~~~*/

	while(x < cadena.Length())
	{
		if(isalpha(*(cadena.SubString(x, 1)).c_str()))
		{
			cadena.Insert("~", x);
			x = x + 1;
		}
		else if(cadena.SubString(x, 1) == "~")
		{
			cadena.Delete(x, 1);
		}

		x = x + 1;
	}

	return cadena;
}

/*
 =======================================================================================================================
    función que cambia los simbolos fuera (true) o dentro de las expresiones ejemplo: (A+B)*(B+~D),true => (A+B)+(B+~D)
    (A+B)*(B+~D),false => (A*B)*(B*~D)
 =======================================================================================================================
 */
AnsiString CambiarSignos(AnsiString cadena, bool tipo)
{
	/*~~~~~~*/
	int x = 1;
	/*~~~~~~*/

	while(x < cadena.Length())
	{
		if((cadena.SubString(x, 1) == "(") | (cadena.SubString(x, 1) == ")"))
		{
			tipo = !tipo;
		}
		else if(tipo)
		{
			if(cadena.SubString(x, 1) == "+")
			{
				cadena.Delete(x, 1);
				cadena.Insert("*", x);
			}
			else if(cadena.SubString(x, 1) == "*")
			{
				cadena.Delete(x, 1);
				cadena.Insert("+", x);
			}
		}

		x = x + 1;
	}

	return cadena;
}

/*
 =======================================================================================================================
    función que niega todas las expresiones (pone "~" delante de cada parentesis ejemplo: (A+B)*(B+~D) =>
    ~(A+B)*~(B+~D)
 =======================================================================================================================
 */
AnsiString InvertirExpresiones(AnsiString cadena)
{
	/*~~~~~~*/
	int x = 1;
	/*~~~~~~*/

	while(x < cadena.Length())
	{
		if(cadena.SubString(x, 1) == "(")
		{
			cadena.Insert("~", x);
			x = x + 1;
		}

		x = x + 1;
	}

	return cadena;
}

/*
 =======================================================================================================================
    función que añade los simbolos de una expresión POS(true) o SOP ejemplo: A~BCD,true => (A+~B+C+D)* A~BCD,false =>
    (A*~B*C*D)+
 =======================================================================================================================
 */
AnsiString AniadirSimbolos(AnsiString cadena, bool tipo)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	resultado = "(";
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i <= cadena.Length(); i++)
	{
		resultado = resultado + cadena.SubString(i, 1);
		if(isalpha(*(cadena.SubString(i, 1)).c_str()))
		{
			if(tipo)
				resultado = resultado + "+";
			else
				resultado = resultado + "*";
		}
	}

	resultado.Delete(resultado.Length(), 1);
	if(tipo)
		resultado = resultado + ")*";
	else
		resultado = resultado + ")+";

	return(resultado);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int NumeroTerminos(AnsiString cadena)
{
	/*~~~~~~~~~~~*/
	int numero = 0;
	/*~~~~~~~~~~~*/

	for(int i = 1; i <= cadena.Length(); i++)
	{
		if(cadena.SubString(i, 1) == ")") numero++;
	}

	return(numero);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int NumeroLiterales(AnsiString cadena)
{
	/*~~~~~~~~~~~*/
	int numero = 0;
	/*~~~~~~~~~~~*/

	for(int i = 1; i <= cadena.Length(); i++)
	{
		if((isalpha(char(*cadena.SubString(i, 1).c_str())))) numero++;
	}

	return(numero);
}
