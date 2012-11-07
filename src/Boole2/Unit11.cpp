/*$T boole/Boole2/Unit11.cpp GC! 1.116 05/02/01 18:53:25 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include <Alloc.h>

#include "Unit11.h"
#include "V_Boole2.h"

using namespace std;
#include "reductio/rdsimplificador.h"

#pragma link "Grids"
#pragma resource "*.dfm"
TForm11		*Form11;
int			numcaracteres;
AnsiString	Ini = "";
AnsiString	Sol = "";
AnsiString	Mejor = "";
AnsiString	CadIni = "";

long		ImpliSol = 0;

struct TRegistro
{
	int Col, Row;
	int *Tab;		// Tabla(i,j) grandota con las 'X's
	int *Mini;		// Tabla(i) con los miniterminos
	int *Impli;		// Tabla(j) con los implicados
	int *NumVar;	// Tabla(j) con el numero de variables de los impli

	int Poda;		// Posicion del Impli que suponemos esencial
} Registro;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TForm11::TForm11(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString DevuelveCombinaciones(AnsiString A)
// De un string devuelve la parte de los parentesis el string no esta vacio y tiene los ()
{
	/*~~~~~~*/
	int c = 1;
	/*~~~~~~*/

	// busco el parentesis de cerrar
	while(A[c] != ')')
	{
		c++;
	}

	// atencion devuelve los parentesis
	return A.SubString(1, c);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString MezclaCombinaciones(AnsiString A1, AnsiString A2)
// junta dos combinaciones en una sola es decir (1,2)(2,8) -> (1,2,2,8)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	Cadena1, Cadena2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

	Cadena1 = "";
	Cadena2 = "";
	Cadena1 += A1;
	Cadena2 += A2;
	Cadena1.Delete(Cadena1.Length(), 1);	// Quita el parentesis de cerrar de la primera combinacion
	Cadena2.Delete(1, 1);					// Quita el parentesis de abrir de la segunda combinacion

	Cadena1 += ",";
	Cadena1 += Cadena2;
	return Cadena1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString DevuelveBin(AnsiString A)
// De un string me devuelve el binario el string no esta vacio y tiene los ()
{
	/*~~~~~~*/
	int c = 1;
	/*~~~~~~*/

	// busco el parentesis de cerrar
	while(A[c] != ')')
	{
		c++;

		// Modificado.
		if(c > A.Length()) return "x";

		// Modificado.
	}

	return A.SubString(c + 1, A.Length());
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString PonCombinaciones(AnsiString Comb, AnsiString Bin)
// añade a un binario los parentesis de las combinaciones
{
	/*~~~~~~~~~~~~*/
	AnsiString	Aux;
	/*~~~~~~~~~~~~*/

	Aux = "";
	Aux += Comb;
	Aux += Bin;
	return Aux;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CuentaUnos(AnsiString Numero)	// Cuenta el numero de 1s de un string Binario
{
	/*~~~~~~~~~*/
	int unos = 0;
	/*~~~~~~~~~*/

	for(int i = 1; i <= Numero.Length(); i++)
	{
		if(Numero[i] == '1') unos++;
	}

	return unos;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Original2Aux(void)
// copia la tabla original en aux
{
	Form11->Aux->Items->Clear();
	for(int i = 0; i < Form11->Original->Items->Count; i++)
	{
		Form11->Aux->Items->Add(Form11->Original->Items->Strings[i]);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Resultado2Aux(void)
// copia la tabla resultado en aux
{
	Form11->Aux->Items->Clear();
	for(int i = 0; i < Form11->Resultado->Items->Count; i++)
	{
		Form11->Aux->Items->Add(Form11->Resultado->Items->Strings[i]);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Resultado2Implicados(void)
// copia la tabla resultado en Implicados
{
	Form11->Implicados->Items->Clear();
	for(int i = 0; i < Form11->Resultado->Items->Count; i++)
	{
		Form11->Implicados->Items->Add(Form11->Resultado->Items->Strings[i]);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int ComparaBinarios(AnsiString A1, AnsiString A2)
// Compara dos binarios y devuelve el numero de caracteres en que difieren se supone que los dos strings son de la misma longitud
{
	/*~~~~~~~~~~~~~*/
	int difieren = 0;
	/*~~~~~~~~~~~~~*/

	for(int i = 1; i <= A1.Length(); i++)
	{
		if(A1[i] != A2[i])
		{
			difieren++;
		}
	}

	return difieren;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString PonGuion(AnsiString A1, AnsiString A2)
// pone guiones en el string en los caracteres que difiere
{
	/*~~~~~~~~~~~~~~*/
	AnsiString	Guion;
	/*~~~~~~~~~~~~~~*/

	Guion = "";
	Guion += A1;
	for(int i = 1; i <= A1.Length(); i++)
	{
		if(A1[i] != A2[i])
		{
			Guion[i] = '-';
		}
	}

	return Guion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void DividirBloques(void)	// Se supone que Aux ya esta ordenada y que tiene las comb delante
{
	// borro las tablas de indices
	Form11->IndicesInicial->Items->Clear();
	Form11->IndicesFinal->Items->Clear();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int NumUnos = CuentaUnos(DevuelveBin(Form11->Aux->Items->Strings[0]));			// Calcula el nº de 1s de la
																					///primera linea
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for(int k = 0; k < NumUnos; k++)
	{
		Form11->IndicesInicial->Items->Add("N");
	}

	Form11->IndicesInicial->Items->Add(0);

	/*~~~~~~~~~~~~~~~~*/
	// El primero siempre empieza en el indice 0
	int NumUnosSgte = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Aux->Items->Count - 1; i++)
	{
		NumUnos = CuentaUnos(DevuelveBin(Form11->Aux->Items->Strings[i]));			// Calcula el nº de 1s de la linea
																					///actual
		NumUnosSgte = CuentaUnos(DevuelveBin(Form11->Aux->Items->Strings[i + 1]));	// Calcula el nº de 1s de la sgte
																					///linea

		if(NumUnos != NumUnosSgte)
		{
			if(NumUnos == NumUnosSgte - 1)
			{
				Form11->IndicesInicial->Items->Add(i + 1);
			}
			else
			{
				// ponemos el nº de n's segun el numero de 1's que se lleven
				for(int j = 0; j < (NumUnosSgte - NumUnos) - 1; j++)
				{
					Form11->IndicesInicial->Items->Add("N");
				}

				Form11->IndicesInicial->Items->Add(i + 1);
			}
		}
	}

	//
	// nos hacemos la tabla indicefinal a partir de la indiceinicial Rellenamos de Ns,
	// tantas como valores en el inicial
	//
	for(int i = 0; i < Form11->IndicesInicial->Items->Count; i++)
	{
		Form11->IndicesFinal->Items->Add("N");
	}

	// Generamos los valores finales
	for(int i = 0; i < Form11->IndicesInicial->Items->Count - 1; i++)
	{
		/*~~~~~~~~~~~~~~~~~*/
		AnsiString	Actual;
		int			cont = 0;
		/*~~~~~~~~~~~~~~~~~*/

		if(Form11->IndicesInicial->Items->Strings[i] != "N")
		{
			cont = i + 1;
			while(Form11->IndicesInicial->Items->Strings[cont] == "N")
			{
				cont++;
			}

			Actual = Form11->IndicesInicial->Items->Strings[cont];
			Form11->IndicesFinal->Items->Strings[i] = Actual.ToInt() - 1;
		}
	}

	Form11->IndicesFinal->Items->Strings[Form11->IndicesFinal->Items->Count - 1] = Form11->Aux->Items->Count - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BorrarRepetidos(void)
// borra las lineas repetidas de la tabla resultado si encuentro algo repetido lo pongo a x y despues en otra pasada lo borro
{
	/*~~~~~~~~~~~~~~~*/
	AnsiString	actual;
	/*~~~~~~~~~~~~~~~*/

	// recorro la tabla y borro los que son iguales
	for(int i = 0; i < Form11->Resultado->Items->Count; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	r2 = Form11->Resultado->Items->Strings[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		actual = "";
		actual += DevuelveBin(Form11->Resultado->Items->Strings[i]);
		for(int j = i + 1; j < Form11->Resultado->Items->Count; j++)
		{
			if(actual != "x")
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	r = DevuelveBin(Form11->Resultado->Items->Strings[j]);	// Modificado.
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if(actual == DevuelveBin(Form11->Resultado->Items->Strings[j]))
				{
					Form11->Resultado->Items->Strings[j] = "x";
				}
			}
		}
	}

	// utilizo la tabla aux
	Resultado2Aux();
	Form11->Resultado->Items->Clear();
	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		if(Form11->Aux->Items->Strings[i] != "x")
		{
			Form11->Resultado->Items->Add(Form11->Aux->Items->Strings[i]);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Cuadrado(int num)
// devuelve 2 a la num
{
	/*~~~~~~~~*/
	int cua = 1;
	/*~~~~~~~~*/

	for(int i = 0; i < num; i++)
	{
		cua = 2 * cua;
	}

	return cua;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString Dec2Bin(int Dec, int NumCar)
// convierte un decimal en binario NumCar es el numero de caracteres que tendra el binario
{
	/*~~~~~~~~~~~~~~~~~~~*/
	AnsiString	Binario, b;
	/*~~~~~~~~~~~~~~~~~~~*/

	Binario = "";

	/*~~~~~~*/
	int resto;
	/*~~~~~~*/

	resto = 0;
	for(int j = 0; j < NumCar; j++)
	{
		// calculamos el nuero en binario
		resto = Dec % 2;
		Dec = Dec / 2;
		Binario += resto;
	}

	// pero lo guarda al reves asi que lo doy la vuelta
	for(int j = 0; j < NumCar; j++)
	{
		b += "p";
	}

	// con lo cual que damos la vuelta a lo de lo cual
	for(int j = 1; j <= NumCar; j++)
	{
		b[j] = Binario[(NumCar + 1) - j];
	}

	return b;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Bin2Dec(AnsiString Bin)
// convierte un binario en decimal
{
	/*~~~~~~~~~~*/
	int valor = 0;
	/*~~~~~~~~~~*/

	for(int i = Bin.Length(); i > 0; i--)
	{
		if(Bin[i] == '1')
		{
			valor = valor + Cuadrado(Bin.Length() - i);
		}
	}

	return valor;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void IniciaTablaOriginal(void)
// pone la tabal original con sus combinaciones a la izq
{
	/*~~~~~~~~~~~~*/
	AnsiString	Aux;
	/*~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Original->Items->Count; i++)
	{
		Aux = "(";
		Aux += Bin2Dec(Form11->Original->Items->Strings[i]);
		Aux += ")";
		Aux += Form11->Original->Items->Strings[i];
		Form11->Original->Items->Strings[i] = Aux;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int NumeroComas(AnsiString Comb)
// cuenta el nº de comas en un sting de combinaciones (sabiendo el nº de comas tb se sabe el nº de elementos = nº comas +1
{
	/*~~~~~~~~~~~~~*/
	int numcomas = 0;
	/*~~~~~~~~~~~~~*/

	for(int k = 1; k < Comb.Length(); k++)
	{
		if(Comb[k] == ',') numcomas++;
	}

	return numcomas;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BuscarNoComparados(void)
// Busca en Resultado los numeros que existen en aux pero no en resultado
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	val, val1, val2;	// val es el numero que busco
	// y val1 y val2 con los que comparo en resultado
	bool		encontrado = false;
	int			numcomas;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		val = "";
		val += DevuelveCombinaciones(Form11->Aux->Items->Strings[i]);

		encontrado = false;
		for(int j = 0; j < Form11->Resultado->Items->Count; j++)
		{
			val1 = "";
			val2 = "";
			val1 += DevuelveCombinaciones(Form11->Resultado->Items->Strings[j]);
			val2 += DevuelveCombinaciones(Form11->Resultado->Items->Strings[j]);

			// cuento las comas que hay y se como lo debo de dividir
			numcomas = NumeroComas(val1);
			numcomas = (numcomas / 2) + 1;

			/*~~~~~~~~*/
			// ahora ya se hasta que coma debo llegar pa dividir
			int c = 0;
			int pos = 1;
			/*~~~~~~~~*/

			// convierto (3,4) a (3) (4) por ej
			while(c < numcomas)
			{
				if(val1[pos] == ',')
				{
					c++;
				}

				pos++;
			}

			pos--;
			val1 = val1.SubString(1, pos);
			val1[val1.Length()] = ')';
			val2 = val2.SubString(pos, val2.Length());
			val2[1] = '(';
			if(val == val1)
			{
				encontrado = true;
			}

			if(val == val2)
			{
				encontrado = true;
			}
		}

		if(encontrado == false)
		{
			Form11->Implicados->Items->Add(Form11->Aux->Items->Strings[i]);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Dec2Car(int num)
// devuelve el numero de caracteres que tendra el binario sobre un valor decimal
{
	/*~~~~~~*/
	int Rango;
	/*~~~~~~*/

	Rango = 1;

	/*~~~~~~~~~~~~~~~~~~~~*/
	int c = Cuadrado(Rango);
	/*~~~~~~~~~~~~~~~~~~~~*/

	while(num >= c)
	{
		Rango++;
		c = Cuadrado(Rango);
	}

	return Rango;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int NumeroDigitos(void)
// calcula el numero mayor el los arrays unos y equis pra saber el numero de caracteres que debe tener el nºbinario
{
	/*~~~~~~~~*/
	// recorro los dos arrays
	int max = 0;
	int maxaux;
	/*~~~~~~~~*/

	// string unos
	if(Form11->Unos->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~~~~~*/
		AnsiString	AnsiAux;
		/*~~~~~~~~~~~~~~~~*/

		AnsiAux = "";
		AnsiAux += Form11->Unos->Text;

		/*~~~~~~~~*/
		int numunos;
		/*~~~~~~~~*/

		numunos = NumeroComas(AnsiAux) + 1;
		AnsiAux += ","; // añado una coma al final
		for(int i = 0; i < numunos; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(AnsiAux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			maxaux = AnsiAux.SubString(1, digitos - 1).ToInt();			// cojo lo que me importa del AnsiString (el
																		///numero)
			if(maxaux > max)
			{
				max = maxaux;
			}

			AnsiAux = AnsiAux.SubString(digitos + 1, AnsiAux.Length()); // recorto el AnsiString
		}
	}					// fin if (Form11->Unos->Text.Length()>0)

	// string equis
	if(Form11->Equis->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~~~~~*/
		AnsiString	AnsiAux;
		/*~~~~~~~~~~~~~~~~*/

		AnsiAux = Form11->Equis->Text;

		/*~~~~~~~~~*/
		int numequis;
		/*~~~~~~~~~*/

		numequis = NumeroComas(AnsiAux) + 1;
		AnsiAux += ","; // añado una coma al final
		for(int i = 0; i < numequis; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(AnsiAux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			maxaux = AnsiAux.SubString(1, digitos - 1).ToInt();			// cojo lo que me importa del AnsiString (el
																		///numero)
			if(maxaux > max)
			{
				max = maxaux;
			}

			AnsiAux = AnsiAux.SubString(digitos + 1, AnsiAux.Length()); // recorto el AnsiString
		}
	}	// fin if (Form11->Equis->Text.Length()>0)
	return Dec2Car(max);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void CompararBloques(void)
{
	// borro la tabla resultados
	Form11->Resultado->Items->Clear();

	// comparo tantos bloques entre si como numero de indices tengo menos 1
	for(int i = 0; i < Form11->IndicesInicial->Items->Count - 1; i++)
	{
		//
		// Form11->Resultado->Items->Add(" "); bucle que recoorre el bloque que se compara
		// bloque 1
		//
		if(Form11->IndicesInicial->Items->Strings[i] != "N")
		{
			for
			(
				int j = Form11->IndicesInicial->Items->Strings[i].ToInt();
				j <= Form11->IndicesFinal->Items->Strings[i].ToInt();
				j++
			)
			{
				// bucle que recorre con los que se comparan bloque2
				if(Form11->IndicesInicial->Items->Strings[i + 1] != "N")
				{
					for
					(
						int k = Form11->IndicesInicial->Items->Strings[i + 1].ToInt();
						k <= Form11->IndicesFinal->Items->Strings[i + 1].ToInt();
						k++
					)
					{
						/*
						 * AnsiString a; a="comparo "; a+=Form11->Aux->Items->Strings[j]; a+=" con ";
						 * a+=Form11->Aux->Items->Strings[k]; Form11->Resultado->Items->Add(a); £
						 * comparo las cadenas de binarios
						 */
						if
						(
							ComparaBinarios
								(
									DevuelveBin(Form11->Aux->Items->Strings[j]),
									DevuelveBin(Form11->Aux->Items->Strings[k])
								) == 1
						)
						{
							/*~~~~~~~~~~*/
							AnsiString	a;
							/*~~~~~~~~~~*/

							// Cojo los valores (comb) de los dos y los mezclo
							a = MezclaCombinaciones
								(
									DevuelveCombinaciones(Form11->Aux->Items->Strings[j]),
									DevuelveCombinaciones(Form11->Aux->Items->Strings[k])
								);

							// Pongo los guiones al binario
							a += PonGuion
								(
									DevuelveBin(Form11->Aux->Items->Strings[j]),
									DevuelveBin(Form11->Aux->Items->Strings[k])
								);
							Form11->Resultado->Items->Add(a);
						}
					}	// fin if !="N" bloque2
				}		// fin bloque2
			}			// fin bloque1
		}				// fin if !="N" bloque1
	}					// fin numero de indices -1
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RellenaUnos(void)
// se supone que es un string de numeros separados de comas
{
	if(Form11->Unos->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~*/
		AnsiString	Aux;
		/*~~~~~~~~~~~~*/

		Aux = Form11->Unos->Text;

		/*~~~~~~~~*/
		int numunos;
		/*~~~~~~~~*/

		numunos = NumeroComas(Aux) + 1;
		Aux += ","; // añado una coma al final
		for(int i = 0; i < numunos; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(Aux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			Form11->Original->Items->Add(Dec2Bin(Aux.SubString(1, digitos - 1).ToInt(), numcaracteres));	// cojo lo
																											///que me
																											///importa
																											///del
																											///AnsiString
																											///  (el
																											///numero)
			Aux = Aux.SubString(digitos + 1, Aux.Length()); // recorto el AnsiString
		}
	}	// fin if (Form11->Unos->Text.Length()>0)
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RellenaEquis(void)
{
	if(Form11->Equis->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~*/
		AnsiString	Aux;
		/*~~~~~~~~~~~~*/

		Aux = Form11->Equis->Text;

		/*~~~~~~~~~*/
		int numequis;
		/*~~~~~~~~~*/

		numequis = NumeroComas(Aux) + 1;
		Aux += ","; // añado una coma al final
		for(int i = 0; i < numequis; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(Aux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			Form11->Original->Items->Add(Dec2Bin(Aux.SubString(1, digitos - 1).ToInt(), numcaracteres));	// cojo lo
																											///que me
																											///importa
																											///del
																											///AnsiString
																											///  (el
																											///numero)
			Aux = Aux.SubString(digitos + 1, Aux.Length()); // recorto el AnsiString
		}
	}	// fin if (Form11->Equis->Text.Length()>0)
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RellenaOriginal(void)
// rellena la lista original segun el AnsiString Unos y Equis
{
	Form11->Original->Items->Clear();
	RellenaUnos();
	RellenaEquis();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FiltraImplicados(void)
// quita los implcados primos que solo dependen de las x
{
	/*~~~~~~~~~~~~~*/
	//
	// utilizo la tabla aux que pa algo esta recorro toda la tabla de implicados y
	// cuando encuentro alguno que depende de 1 lo dejo
	//
	AnsiString	Comb;
	/*~~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Implicados->Items->Count; i++)
	{
		/*~~~~~~~~*/
		int numcomb;
		/*~~~~~~~~*/

		Comb = DevuelveCombinaciones(Form11->Implicados->Items->Strings[i]);
		numcomb = NumeroComas(Comb);

		// quito los parentesis a comb y le pongo una coma al final
		Comb = Comb.SubString(2, Comb.Length());
		Comb[Comb.Length()] = ',';

		// el numero de combinaciones
		numcomb++;
		for(int j = 0; j < numcomb; j++)
		{
			/*~~~~~~~~~~~~~~*/
			int numequi;	// el numero de xs
			int numcomparar;	// el numero acomparar
			// cojo el primer numero
			int digitos = 1;
			/*~~~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(Comb[digitos] != ',')
			{
				digitos++;
			}

			numcomparar = Comb.SubString(1, digitos - 1).ToInt();	// cojo lo que me importa del AnsiString (el numero)
			Comb = Comb.SubString(digitos + 1, Comb.Length());

			/*~~~~~~~~~~~*/
			// recorto el AnsiString

			//
			// ahora el numero que tengo en numcomparar lo tengo que comparar con todos los de
			// el ansistring unos y si existe alguno entonces me vale
			//
			AnsiString	Eq;
			/*~~~~~~~~~~~*/

			numequi = NumeroComas(Form11->Unos->Text);
			numequi++;
			Eq = Form11->Unos->Text;

			// le añado una coma al final
			Eq += ",";
			for(int k = 0; k < numequi; k++)
			{
				/*~~~~~~~~~~~~*/
				// saco los valores de Eq y los comparo con numcomparar
				int numeq;
				int digitos = 1;
				/*~~~~~~~~~~~~*/

				// recorro el AnsiString hasta encontrar una coma
				while(Eq[digitos] != ',')
				{
					digitos++;
				}

				numeq = Eq.SubString(1, digitos - 1).ToInt();		// cojo lo que me importa del AnsiString (el numero)

				//
				// comparo numcomparar que es uno de los comb con todas los unos, si esta quiere
				// decir que nos vale
				//
				if(numeq == numcomparar)
				{
					Form11->Resultado->Items->Add(Form11->Implicados->Items->Strings[i]);
				}

				// recorto Eq
				Eq = Eq.SubString(digitos + 1, Eq.Length());		// recorto el AnsiString
			}
		}
	}

	// Quito los repetidos
	BorrarRepetidos();
	Resultado2Implicados();
	Form11->Resultado->Items->Clear();
	Form11->Aux->Items->Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void OrdenaOriginal(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int NumCar = Form11->Original->Items->Strings[0].Length();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// Ordena la tabla por numero de '1's usando la lista Aux como ayuda
	for(int j = 0; j <= NumCar; j++)
	{
		for(int i = 0; i < Form11->Original->Items->Count; i++)
		{
			if(CuentaUnos(Form11->Original->Items->Strings[i]) == j)
			{
				Form11->Aux->Items->Add(Form11->Original->Items->Strings[i]);
			}
		}
	}

	Form11->Original->Items->Clear();
	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		Form11->Original->Items->Add(Form11->Aux->Items->Strings[i]);
	}

	Form11->Aux->Items->Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BorrarColumna(int col)
{
	/*~~~~~~~~~~~~~*/
	AnsiString	Dest;
	/*~~~~~~~~~~~~~*/

	for(int j = 0; j < Form11->Tabla->RowCount; j++)
	{
		Dest = Form11->Tabla->Cells[Form11->Tabla->ColCount - 1][j];
		Form11->Tabla->Cells[col][j] = Dest;
		Form11->Tabla->Cells[Form11->Tabla->ColCount - 1][j] = "";
	}

	Form11->Tabla->ColCount--;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void BorrarFila(int fila)
{
	/*~~~~~~~~~~~~~*/
	AnsiString	Dest;
	/*~~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Tabla->ColCount; i++)
	{
		Dest = Form11->Tabla->Cells[i][Form11->Tabla->RowCount - 1];
		Form11->Tabla->Cells[i][fila] = Dest;
		Form11->Tabla->Cells[i][Form11->Tabla->RowCount - 1] = "";
	}

	Form11->Tabla->RowCount--;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void MiniTerminos(void)
// Coge los miniterminos de la tabla implicados, que son los que se usan
{
	/*~~~~~~~~~~~~~~~~*/
	AnsiString	AnsiAux;
	/*~~~~~~~~~~~~~~~~*/

	Form11->Aux->Items->Clear();
	for(int i = 0; i < Form11->Implicados->Items->Count; i++)
	{
		AnsiAux = DevuelveCombinaciones(Form11->Implicados->Items->Strings[i]);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int num = NumeroComas(AnsiAux) + 1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		AnsiAux = AnsiAux.SubString(2, AnsiAux.Length());
		AnsiAux[AnsiAux.Length()] = ',';
		for(int j = 0; j < num; j++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(AnsiAux[digitos] != ',')
			{
				digitos++;
			}

			Form11->Aux->Items->Add(AnsiAux.SubString(1, digitos - 1).ToInt()); // cojo lo que me importa del
																				///AnsiString (el numero)
			AnsiAux = AnsiAux.SubString(digitos + 1, AnsiAux.Length());			// recorto el AnsiString
		}
	}

	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		AnsiAux = Form11->Aux->Items->Strings[i];
		if(AnsiAux != "x")
		{
			for(int j = i; j < Form11->Aux->Items->Count; j++)
			{
				if(j != i)
				{
					if(AnsiAux == Form11->Aux->Items->Strings[j]) Form11->Aux->Items->Strings[i] = "x";
				}
			}
		}
	}

	Form11->Resultado->Items->Clear();
	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		AnsiAux = Form11->Aux->Items->Strings[i];
		if(AnsiAux != "x") Form11->Resultado->Items->Add(AnsiAux);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RellenaEquisEnAux2(void)
{
	if(Form11->Equis->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~*/
		AnsiString	Aux;
		/*~~~~~~~~~~~~*/

		Aux = Form11->Equis->Text;

		/*~~~~~~~~~*/
		int numequis;
		/*~~~~~~~~~*/

		numequis = NumeroComas(Aux) + 1;
		Aux += ","; // añado una coma al final
		for(int i = 0; i < numequis; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(Aux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			Form11->Aux2->Items->Add(Aux.SubString(1, digitos - 1).ToInt());	// cojo lo que me importa del
																				///AnsiString (el numero)
			Aux = Aux.SubString(digitos + 1, Aux.Length());						// recorto el AnsiString
		}
	}	// fin if (Form11->Equis->Text.Length()>0)
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void GenerarTabla(void)
{
	// Averiguar cuales de los implicados son 'x' para no usarlos en las columnas!!!!!
	Form11->Tabla->ColCount = numcaracteres + Form11->Resultado->Items->Count;
	Form11->Tabla->RowCount = Form11->Implicados->Items->Count + 1;

	for(int i = 0; i < Form11->Tabla->ColCount; i++)
		for(int j = 0; j < Form11->Tabla->RowCount; j++) Form11->Tabla->Cells[i][j] = "";

	/*~~~~~~~~~~~~~~~~*/
	AnsiString	AnsiAux;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < numcaracteres; i++)
	{
		/*~~~~~~~~~~*/
		AnsiString	e;
		/*~~~~~~~~~~*/

		e = "e";
		e += i;
		Form11->Tabla->Cells[i][0] = e;
	}

	for(int i = numcaracteres; i < Form11->Resultado->Items->Count + numcaracteres; i++)
	{
		Form11->Tabla->Cells[i][0] = Form11->Resultado->Items->Strings[i - numcaracteres];
	}

	for(int i = 0; i < Form11->Implicados->Items->Count; i++)
	{
		AnsiAux = DevuelveBin(Form11->Implicados->Items->Strings[i]);

		for(int j = 1; j <= numcaracteres; j++)
		{
			Form11->Tabla->Cells[j - 1][i + 1] = AnsiAux[j];
		}
	}

	/*~~~~~~~~~~~~~~*/
	AnsiString	Impli;
	/*~~~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Implicados->Items->Count; i++)
	{
		AnsiAux = DevuelveCombinaciones(Form11->Implicados->Items->Strings[i]);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int num = NumeroComas(AnsiAux) + 1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		AnsiAux = AnsiAux.SubString(2, AnsiAux.Length());
		AnsiAux[AnsiAux.Length()] = ',';
		for(int j = 0; j < num; j++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(AnsiAux[digitos] != ',')
			{
				digitos++;
			}

			Impli = AnsiAux.SubString(1, digitos - 1);					// cojo lo que me importa del AnsiString
			for(int k = numcaracteres; k < Form11->Tabla->ColCount; k++)
			{
				if(Form11->Tabla->Cells[k][0] == Impli) Form11->Tabla->Cells[k][i + 1] = "X";
			}

			AnsiAux = AnsiAux.SubString(digitos + 1, AnsiAux.Length()); // recorto el AnsiString
		}
	}

	// Elimino los que pertenecen a las Equis
	Form11->Aux2->Items->Clear();
	RellenaEquisEnAux2();

	/*~~~~~~~*/
	int fin, i;
	/*~~~~~~~*/

	fin = Form11->Tabla->ColCount;

	i = numcaracteres;
	while(i < fin)
	// for (int i=numcaracteres;i<Form11->Tabla->ColCount;i++)
	{
		/*~~~~~~~~~~~*/
		AnsiString	eq;
		/*~~~~~~~~~~~*/

		eq = Form11->Tabla->Cells[i][0];

		/*~~~~~~~~*/
		int numi, j;
		/*~~~~~~~~*/

		numi = Form11->Aux2->Items->Count;
		j = 0;
		while(j < numi)
		{
			if(eq == Form11->Aux2->Items->Strings[j])
			{
				BorrarColumna(i);
				i--;
				j = numi + 1;
			}

			j++;
		}

		i++;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Elemento(int i, int j, int r)
{
	return(j * r + i);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int CuentaVar(AnsiString A)
{
	/*~~~~~~*/
	int n = 0;
	/*~~~~~~*/

	for(int i = 1; i <= A.Length(); i++)
	{
		if(A[i] != '-') n++;
	}

	return n;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TRegistro RellenaRegistro(TRegistro Registro)
{
	Registro.Poda = 0;

	Registro.Col = Form11->Tabla->ColCount - numcaracteres;
	Registro.Row = Form11->Tabla->RowCount - 1;

	Registro.Tab = (int *) malloc(Registro.Col * Registro.Row * sizeof (int));
	Registro.Mini = (int *) malloc(Registro.Col * sizeof (int));
	Registro.Impli = (int *) malloc(Registro.Row * sizeof (int));
	Registro.NumVar = (int *) malloc(Registro.Row * sizeof (int));

	// rellenamos la tabla tab
	for(int i = 0; i < Registro.Col; i++)
	{
		for(int j = 0; j < Registro.Row; j++)
		{
			if(Form11->Tabla->Cells[i + numcaracteres][j + 1] == "X")
				Registro.Tab[Elemento(i, j, Registro.Col)] = 7; // !!!!!!!! LOS '7's son las 'X's
			else
				Registro.Tab[Elemento(i, j, Registro.Col)] = 0; // nada es 0
		}
	}

	for(int i = 0; i < Registro.Col; i++)
	{
		Registro.Mini[i] = Form11->Tabla->Cells[i + numcaracteres][0].ToInt();
	}

	/*~~~~~~~~~~~~~~~~*/
	AnsiString	AnsiAux;
	/*~~~~~~~~~~~~~~~~*/

	for(int j = 0; j < Registro.Row; j++)
	{
		AnsiAux = "";
		for(int k = 0; k < numcaracteres; k++)
		{
			AnsiAux += Form11->Tabla->Cells[k][j + 1];
		}

		for(int k = 0; k < Form11->Implicados->Items->Count; k++)
		{
			if(AnsiAux == DevuelveBin(Form11->Implicados->Items->Strings[k])) Registro.Impli[j] = k;
		}
	}

	// contar el numero de varibles de cada impli
	for(int i = 0; i < Registro.Row; i++)
	{
		Registro.NumVar[i] = CuentaVar(DevuelveBin(Form11->Implicados->Items->Strings[Registro.Impli[i]]));
	}

	return Registro;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TRegistro Reg2Reg(TRegistro Re)
{
	/*~~~~~~~~~~~~~~*/
	TRegistro	ReAux;
	/*~~~~~~~~~~~~~~*/

	ReAux.Poda = Re.Poda;
	ReAux.Col = Re.Col;
	ReAux.Row = Re.Row;

	ReAux.Tab = (int *) malloc(Re.Col * Re.Row * sizeof (int));
	ReAux.Mini = (int *) malloc(Re.Col * sizeof (int));
	ReAux.Impli = (int *) malloc(Re.Row * sizeof (int));
	ReAux.NumVar = (int *) malloc(Re.Row * sizeof (int));

	// rellenamos la tabla tab
	for(int i = 0; i < Re.Col; i++)
	{
		for(int j = 0; j < Re.Row; j++)
		{
			ReAux.Tab[Elemento(i, j, Registro.Col)] = Re.Tab[Elemento(i, j, Registro.Col)];
		}
	}

	for(int i = 0; i < Re.Col; i++)
	{
		ReAux.Mini[i] = Re.Mini[i];
	}

	for(int i = 0; i < Re.Row; i++)
	{
		ReAux.Impli[i] = Re.Impli[i];
	}

	for(int i = 0; i < Re.Row; i++)
	{
		ReAux.NumVar[i] = Re.NumVar[i];
	}

	return ReAux;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TRegistro BorrarColumnaReg(TRegistro R, int c)
{
	//
	// hay que pasar los elementos de Tab el ultimo elemento es RCOL-1 por que va de 0
	// a 2 y ese nº es 3
	//
	for(int j = 0; j < R.Row; j++)
	{
		R.Tab[Elemento(c, j, R.Col)] = R.Tab[Elemento(R.Col - 1, j, R.Col)];
	}

	// hay que pasar los elemtos de mini
	R.Mini[c] = R.Mini[R.Col - 1];

	/*~~~~~~~~~*/
	//
	// hay que redimensionar el array lineal coje el ultimo y lo borra
	// sobreescribiendo los que quedan por detras
	//
	int cont = 1;
	/*~~~~~~~~~*/

	for(int i = 0; i < R.Row * R.Col; i++)
	{
		if(((i + cont) % R.Col) == 0)
		{
			for(int j = i; j < ((R.Row * R.Col) - 1); j++)
			{
				R.Tab[j] = R.Tab[j + 1];
			}

			cont++;
		}
	}

	R.Col = R.Col - 1;

	return R;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
TRegistro BorrarFilaReg(TRegistro R, int f)
{
	if(f != R.Row - 1)
	{
		for(int j = f; j < R.Row; j++)
		{
			for(int i = 0; i < R.Col; i++)
			{
				R.Tab[Elemento(i, j, R.Col)] = R.Tab[Elemento(i, j + 1, R.Col)];
			}

			R.Impli[j] = R.Impli[j + 1];
			R.NumVar[j] = R.NumVar[j + 1];
		}
	}

	R.Row--;
	return R;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void VerReg(TRegistro Reg)
// muestra el formato de registro Tregistro en un TStringGrid llamado Ver
{
	// Introduzco las "X"s que son 7's
	Form11->Ver->ColCount = Reg.Col + numcaracteres + 1;
	Form11->Ver->RowCount = Reg.Row + 1;
	for(int i = 0; i < Reg.Col; i++)
	{
		for(int j = 0; j < Reg.Row; j++)
		{
			if(Reg.Tab[Elemento(i, j, Reg.Col)] == 7)
				Form11->Ver->Cells[i + numcaracteres + 1][j + 1] = "X";
			else
				Form11->Ver->Cells[i + numcaracteres + 1][j + 1] = "";
		}
	}

	/*~~~~~~~~~~~~~~~~*/
	AnsiString	AnsiAux;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < numcaracteres; i++)
	{
		AnsiAux = "e";
		AnsiAux += i;
		Form11->Ver->Cells[i + 1][0] = AnsiAux;
	}

	for(int i = 0; i < Reg.Col; i++)
	{
		Form11->Ver->Cells[i + numcaracteres + 1][0] = Reg.Mini[i];
	}

	/*~~~~*/
	// AnsiString AnsiAux;
	int ind;
	/*~~~~*/

	for(int j = 0; j < Reg.Row; j++)
	{
		ind = Reg.Impli[j];
		Form11->Ver->Cells[0][j + 1] = ind;
		AnsiAux = DevuelveBin(Form11->Implicados->Items->Strings[ind]);
		for(int k = 0; k < numcaracteres; k++)
		{
			Form11->Ver->Cells[k + 1][j + 1] = AnsiAux[k + 1];
		}
	}

	// falta contar el numero de varibles de cada impli
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int MinimoVar(int n)	// cuenta el numero minimo de variables con n implicados
{
	/*~~~~~~~~*/
	int dev = 0;
	/*~~~~~~~~*/

	for(int i = Form11->Implicados->Items->Count - n; i < Form11->Implicados->Items->Count; i++)
	{
		dev += CuentaVar(DevuelveBin(Form11->Implicados->Items->Strings[i]));
	}

	return dev;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int Longitud(AnsiString A)
{
	/*~~~~~~*/
	int c = 0;
	/*~~~~~~*/

	for(int i = 0; i < A.Length(); i++)
	{
		if(A[i + 1] == ',') c++;
	}

	return c;

	/* int c=0; for(int i=1;i<A.Length();i++) { if (A[i+1]==',') c++; } return c; */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int DevNumPos(AnsiString A, int p)	// ER (4)
{
	/*~~~~~~~~~~~*/
	int c = 0;
	int p1, p2 = 0;
	/*~~~~~~~~~~~*/

	p -= 1;

	// for(int i=0;i<A.Length();i++) Modificado. la i=0 por i=1.
	for(int i = 1; i < A.Length(); i++)
	{
		if(A[i] == ',') c++;
		if(c == p - 1) p1 = i + 1;
		if(c == p) p2 = i + 1;
	}

	if(p == 0)
	{
		p1 = 0;
	}

	return A.SubString(p1 + 1, p2 - p1 - 1).ToInt();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString QuitarUltimo(AnsiString A)
{
	/*~~~~~~~*/
	int c = 0;
	int p;
	int p1 = 0;
	/*~~~~~~~*/

	p = Longitud(A);

	// for(int i=0;i<A.Length();i++)
	for(int i = 1; i < A.Length(); i++) // Modificado. la i=0 por i=1. //ER (4).
	{
		if(A[i] == ',') c++;
		if(c == p - 2) p1 = i + 1;
	}

	if(p == 0)
	{
		return "";
	}

	return A.SubString(1, p1);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Podar(AnsiString Camino)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	// Acordarse de poner comas
	AnsiString	Actual = "";
	int			ImpliActual = 0;
	TRegistro	Reg2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Reg2 = Reg2Reg(Registro);

	for(int i = 1; i <= Longitud(Camino); i++)
	{
		if(Reg2.Col > 0)
		{
			/*~~~~~~~~~*/
			int cont = 0;
			/*~~~~~~~~~*/

			while(cont < Reg2.Col)
			{
				// if (Reg2.Tab[Elemento(cont,Camino.SubString(i,1).ToInt(),Reg2.Col)]==7)
				if(Reg2.Tab[Elemento(cont, DevNumPos(Camino, i), Reg2.Col)] == 7)
				{
					Reg2 = BorrarColumnaReg(Reg2, cont);
				}
				else
					cont++;
			}

			// borramos la fila poda Reg2=BorrarFilaReg(Reg2,Camino.SubString(i,1).ToInt());
			Reg2 = BorrarFilaReg(Reg2, DevNumPos(Camino, i));
			Actual += DevNumPos(Camino, i);
			Actual += ",";

			//
			// ImpliActual+=CuentaVar(DevuelveBin(Form11->Implicados->Items->Strings[Reg2.Impli[Camino.SubString(i,1).ToInt()]]));
			//
			ImpliActual += Reg2.NumVar[DevNumPos(Camino, i)];
		}

		if(Reg2.Col == 0)
		{
			if(Longitud(Actual) < Longitud(Mejor))
			{
				Mejor = "";
				Mejor += Actual;
				ImpliSol = ImpliActual;

				// Form11->Original->Items->Add(ImpliActual); Form11->Original->Items->Add(Mejor);
			}

			if(Longitud(Actual) == Longitud(Sol))
			{
				if(ImpliActual < ImpliSol)
				{
					Mejor = "";
					Mejor += Actual;
					ImpliSol = ImpliActual;

					// Form11->Original->Items->Add(ImpliActual); Form11->Original->Items->Add(Mejor);
				}
			}
		}
	}

	free(Reg2.NumVar);
	free(Reg2.Impli);
	free(Reg2.Mini);
	free(Reg2.Tab);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Recursiva(AnsiString Act1)
// La recursiva
{
	for(int i = 0; i < Longitud(Act1); i++)
	{
		/*~~~~~~~~~~~~~~~~~~*/
		AnsiString	Act2 = "";
		/*~~~~~~~~~~~~~~~~~~*/

		Act2 += Act1;

		if(Longitud(Act2) > 0)				// caso recursivo
		{
			// Form11->Aux->Items->Add(i);
			Sol += DevNumPos(Ini, i + 1);	// Sol+=Ini[i+1];
			Sol += ",";

			/*~~~~~~~~~~~~~*/
			AnsiString	Act3;
			/*~~~~~~~~~~~~~*/

			for(int j = 0; j < Longitud(Act2); j++)
			{
				if(j != i)
				{
					Act3 += DevNumPos(Act2, j + 1);
					Act3 += ",";
				}
			}

			//
			// Si he descendido en el arbol mas de lo que tiene Mejor no tiene sentido seguir
			// procesando ese subarbol
			//
			if(Longitud(Sol) <= Longitud(Mejor))
			{
				Recursiva(Act3);

				if(Mejor == CadIni)
				{
					if(Longitud(Sol) == Registro.Row)
					{
						Podar(Sol);
					}						// Solo valen los caminos completos
				}
				else
				{
					if(Longitud(Sol) == Longitud(Mejor))
					{
						Podar(Sol);
					}						// Solo valen los caminos completos
				}
			}

			Sol = QuitarUltimo(Sol);		// Sol=Sol.SubString(1,Sol.Length()-1);

			//
			// Form11->Aux->Items->Clear(); Form11->Aux->Items->Add(Sol);
			// Form11->Aux->Repaint();
			//
		}
		else	// caso base
		{
		}
	}			// fin del for
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SacarEsenciales(void)
{
	/*~~~~~*/
	int numx;
	/*~~~~~*/

	Form11->Aux->Items->Clear();

	//
	// guarda en resul el indice de los esenciales y su binario recorre cada columna
	// para ver cuantas equis tiene
	//
	for(int i = numcaracteres; i < Form11->Tabla->ColCount; i++)
	{
		numx = 0;

		/*~~~~~~~~~~~~*/
		int estalax = 0;
		/*~~~~~~~~~~~~*/

		for(int j = 0; j < Form11->Tabla->RowCount; j++)
		{
			if(Form11->Tabla->Cells[i][j + 1] == "X")
			{
				estalax = j;
				numx++;
			}
		}

		if(numx == 1) Form11->Aux->Items->Add(estalax);
	}

	/*~~~~~~~~~~~~~~~~*/
	// quitamos los repetidos
	AnsiString	AnsiAux;
	/*~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		AnsiAux = Form11->Aux->Items->Strings[i];
		if(AnsiAux != "x")
		{
			for(int j = i; j < Form11->Aux->Items->Count; j++)
			{
				if(j != i)
				{
					if(AnsiAux == Form11->Aux->Items->Strings[j]) Form11->Aux->Items->Strings[i] = "x";
				}
			}
		}
	}

	// ponemos los esenciales en resultado
	Form11->Resultado->Items->Clear();
	for(int i = 0; i < Form11->Aux->Items->Count; i++)
	{
		AnsiAux = Form11->Aux->Items->Strings[i];
		if(AnsiAux != "x") Form11->Resultado->Items->Add(AnsiAux);
	}

	/*~~~~~*/
	// borra las columnas de los esenciales que tienen equis
	int cont;
	int fila;
	/*~~~~~*/

	for(int i = 0; i < Form11->Resultado->Items->Count; i++)
	{
		cont = numcaracteres;
		fila = Form11->Resultado->Items->Strings[i].ToInt() + 1;

		while(cont < Form11->Tabla->ColCount)
		{
			if(Form11->Tabla->Cells[cont][fila] == "X")
			{
				BorrarColumna(cont);
				cont--;
			}

			cont++;
		}
	}

	//
	// una vez borradas las columnas con 'X's de los esenciales borramos las filas de
	// los esenciales hacia atras para que no cambie el indice
	//
	for(int i = Form11->Resultado->Items->Count - 1; i >= 0; i--)
	{
		BorrarFila(Form11->Resultado->Items->Strings[i].ToInt() + 1);
	}

	// una vez realizada la tabla con los no esenciales haremos la funcion recursiva
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString UltimaPoda(AnsiString A)
{
	/*~~~~~~~~~~~~~~~~~*/
	AnsiString	Dev = "";
	/*~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i <= Longitud(A); i++)
	{
		Dev += Registro.Impli[DevNumPos(A, i)];
		Form11->Resultado->Items->Add(Registro.Impli[DevNumPos(A, i)]);

		Registro = BorrarFilaReg(Registro, DevNumPos(A, i));
	}

	return Dev;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
AnsiString TForm11::Simplifica(AnsiString U, AnsiString E, int nc)
{
	Form11->Unos->Text = U;
	Form11->Equis->Text = E;

	numcaracteres = nc;

	if(numcaracteres < NumeroDigitos()) numcaracteres = NumeroDigitos();

	Form11->NumC->Text = numcaracteres;

	Button1->Click();

	return Form11->Solucion->Text;

	/*
	 * if (numcaracteres<NumeroDigitos()) numcaracteres=NumeroDigitos();
	 * Form11->Aux->Items->Clear(); Form11->Original->Items->Clear();
	 * Form11->Resultado->Items->Clear(); Form11->IndicesInicial->Items->Clear();
	 * Form11->IndicesFinal->Items->Clear(); Form11->Implicados->Items->Clear();
	 * //numcaracteres=NumeroDigitos(); //paso de los ANsiString unos y equis a la
	 * tabla original RellenaOriginal(); if (Form11->Original->Items->Count>0) { //Hay
	 * que Ordenar la tabla Original OrdenaOriginal(); //La tabla original debe tener
	 * algun item y que este en binario (sin comb) //calculo el numero de tablas que
	 * tengo que sacar //el nº de veces que hay que hacerlo es el numero de caracteres
	 * -1 //que son las tablas que salen int
	 * veces=(Form11->Original->Items->Strings[0].Length()); IniciaTablaOriginal();
	 * //pone los valores en decimal entre parentesis Original2Aux();
	 * Form11->Implicados->Items->Clear(); for (int i=0;i<=veces;i++) // Modificado,
	 * parece que soluciona cuando usas todos los unos!!! { if
	 * (Form11->Aux->Items->Count>0) { DividirBloques();//Divide la lista en bloques
	 * segun el nº de 1s CompararBloques();//compara los bloques de una tabla
	 * BuscarNoComparados(); BorrarRepetidos(); Resultado2Aux(); } } //si me pasan
	 * f(x) y f(1) entonces si filtro if
	 * ((Form11->Equis->Text.Length()>0)&&(Form11->Unos->Text.Length()>0))
	 * FiltraImplicados(); //si solo me han pasado f(x) entonces no hay resultado if
	 * ((Form11->Equis->Text.Length()>0)&&(Form11->Unos->Text.Length()==0))
	 * Form11->Implicados->Items->Clear(); MiniTerminos(); GenerarTabla();
	 * SacarEsenciales(); //hay que mirar si la tabla queda vacia (no hay columnas)
	 * Form11->Aux->Items->Clear(); if (Form11->Tabla->ColCount>numcaracteres) {
	 * Registro=RellenaRegistro(Registro); //Registro=BorrarColumnaReg(Registro,0); //
	 * VerReg(Registro); Ini=""; Mejor=""; CadIni=""; Sol=""; ImpliSol=999999; for
	 * (int i=0;i<Registro.Row;i++) { Ini+=i; Ini+=","; } for (int
	 * i=0;i<Registro.Row+1;i++) { Mejor+="-,"; //La mejor solucion al principio es
	 * mas larga CadIni+="-,"; } Recursiva(Ini); UltimaPoda(Mejor);
	 * free(Registro.NumVar); free(Registro.Impli); free(Registro.Mini);
	 * free(Registro.Tab); }//fin si no hay columnas }//fin if
	 * (Form11->Original->Items->Count>0) AnsiString dev; dev=""; for (int
	 * i=0;i<Form11->Resultado->Items->Count;i++) {
	 * dev+=DevuelveBin(Form11->Implicados->Items->Strings[
	 * Form11->Resultado->Items->Strings[i].ToInt() ]); if
	 * (i<Form11->Resultado->Items->Count-1) dev+=","; } return dev;
	 */
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TForm11::Button1Click(TObject *Sender)
{
	/// El simplificador.
        rdSimplificador *simp;

	if(Form11->NumC->Text == "") Form11->NumC->Text = "0";

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int numVars = Form11->NumC->Text.ToInt();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

        simp = new rdSimplificador(numVars);
        // 0 --> Obtención de IPs por el método Q-M
	simp->SetObtenedor(0);
        // 0 --> Seleccion de IPs por método recursivo sesgado
	simp->SetSelector(0);

	if(Form11->Unos->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~*/
		AnsiString	Aux;
		/*~~~~~~~~~~~~*/

		Aux = Form11->Unos->Text;

		/*~~~~~~~~*/
		int numunos;
		/*~~~~~~~~*/

		numunos = NumeroComas(Aux) + 1;
		Aux += ","; // añado una coma al final
		for(int i = 0; i < numunos; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(Aux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			simp->AnyadirMint(CuboBool(Aux.SubString(1, digitos - 1).ToInt()));
			Aux = Aux.SubString(digitos + 1, Aux.Length()); // recorto el AnsiString
		}
	}				// fin if (Form11->Unos->Text.Length()>0)

	if(Form11->Equis->Text.Length() > 0)
	{
		/*~~~~~~~~~~~~*/
		AnsiString	Aux;
		/*~~~~~~~~~~~~*/

		Aux = Form11->Equis->Text;

		/*~~~~~~~~~*/
		int numequis;
		/*~~~~~~~~~*/

		numequis = NumeroComas(Aux) + 1;
		Aux += ","; // añado una coma al final
		for(int i = 0; i < numequis; i++)
		{
			/*~~~~~~~~~~~~*/
			int digitos = 1;
			/*~~~~~~~~~~~~*/

			// recorro el AnsiString hasta encontrar una coma
			while(Aux[digitos] != ',')
			{
				digitos++;
			}

			// digitos-1; //se cuantos digitos ocupa el primer numero
			simp->AnyadirTI(CuboBool(Aux.SubString(1, digitos - 1).ToInt()));
			Aux = Aux.SubString(digitos + 1, Aux.Length()); // recorto el AnsiString
		}
	}	// fin if (Form11->Equis->Text.Length()>0)

	simp->Simplificar();

	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	SolucionStr("");
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(set < CuboBool >::iterator i = simp->setIPE1sBEGIN(); i != simp->setIPE1sEND(); i++)
	{
		SolucionStr += (*i).aString((size) numVars).c_str();
		SolucionStr += ",";
	}

	for(set < CuboBool >::iterator i = simp->setIPE2sBEGIN(); i != simp->setIPE2sEND(); i++)
	{
		SolucionStr += (*i).aString((size) numVars).c_str();
		SolucionStr += ",";
	}

	for(set < CuboBool >::iterator i = simp->setIPnEsBEGIN(); i != simp->setIPnEsEND(); i++)
	{
		SolucionStr += (*i).aString((size) numVars).c_str();
		SolucionStr += ",";
	}

	Form11->Solucion->Text = SolucionStr.SubString(1, SolucionStr.Length() - 1);	// Simplifica(Form11->Unos->Text,Form11->Equis->Text,Form11->NumC->Text.ToInt());
																					///

	delete simp;
}
