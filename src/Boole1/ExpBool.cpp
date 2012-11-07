/*$T boole/Boole1/ExpBool.cpp GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "ctype.h"

#include "ExpBool.h"
#include "NuevoSC.h"
#include "DinArray.h"
#include "Libreria.h"
#include "EvaluadorBool.hpp"
#include "mensajes.inc"
extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TExprBooleana	*ExprBooleana;

//
// =======================================================================================================================
//    metemos los datos de la cadena en la matriz B-D => 0100 1100 0110 1110
// =======================================================================================================================
//
void TransformarCadena(AnsiString cadena, int funcion)
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	posicion = "";
	bool		roto = false;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Tabla.NumEntradas(); i++)
	{
		/*~~~~~~*/
		// buscamos la primera variable (letra)
		int z = 1;
		/*~~~~~~*/

		while
		(
			(
				(('A' > (char(*cadena.SubString(z, 1).c_str()))) | ('Z' < (char(*cadena.SubString(z, 1).c_str())))) |
					(
						(
							('A' <= (char(*cadena.SubString(z, 1).c_str()))) &
								('Z' >= (char(*cadena.SubString(z, 1).c_str())))
						) & ((char(*cadena.SubString(z, 1).c_str()) < char('A' + i)))
					)
			) & (z <= cadena.Length())
		)
		{
			z = z + 1;
		}

		if(roto)
			break;
		else if(char(*cadena.SubString(z, 1).c_str()) > ('A' + i))
		{
			if(cadena.SubString(z - 1, 1) == "-")
			{
				cadena.Insert(char('A' + i), z - 1);
				TransformarCadena(cadena, funcion);
				cadena.Insert("-", z - 1);
			}
			else
			{
				cadena.Insert(char('A' + i), z);
				TransformarCadena(cadena, funcion);
				cadena.Insert("-", z);
			}

			TransformarCadena(cadena, funcion);
			roto = true;
			break;
		}
		else if(char(*cadena.SubString(z, 1).c_str()) == ('A' + i))
		{
			if(cadena.SubString(z - 1, 1) == "-")
			{
				posicion = posicion + "0";
			}
			else
			{
				posicion = posicion + "1";
			}
		}
		else if(z > cadena.Length())
		{
			cadena = cadena + char('A' + i);
			TransformarCadena(cadena, funcion);
			cadena.Insert("-", cadena.Length());
			TransformarCadena(cadena, funcion);
			roto = true;
			break;
		}
	}

	if(!roto)
	// meter "posicion" en la posicion del array
	{
		Tabla.EscribirDinArray(binario(posicion), funcion, '1');
		roto = true;
	}
}

//
// =======================================================================================================================
//    7
// =======================================================================================================================
//
void EjecutarExpresion(AnsiString cadena, int funcion)
{
	/*~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	temp1, temp2;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	temp1 = "";
	temp2 = "";

	/*~~~~~~*/
	// transformamos la expresión
	int i = 1;
	/*~~~~~~*/

	while(i <= cadena.Length())
	{
		switch(char(*cadena.SubString(i, 1).c_str()))
		{
		case '(':
			{
				temp1 = "";
				temp2 = "";
				i = i + 1;
				break;
			}

		case ')':
			{
				cadena.Delete(i, 1);
				i = i - 1;
				while(cadena.SubString(i, 1) != "(")
				{
					i = i - 1;
				}

				cadena.Delete(i, 1);
				temp1 = "";
				temp2 = "";
				i = 1;
				break;
			}

		case '+':
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int antes, despues, parentesis;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				parentesis = 0;

				// calculamos el tamaño de la expresion anterior
				i = i - 1;
				antes = 0;
				while
				(
					(((cadena.SubString(i, 1) != "*") & (cadena.SubString(i, 1) != "+")) | (parentesis < 0)) &
						(parentesis <= 0) & (i > 0)
				)
				{
					antes = antes + 1;
					if(cadena.SubString(i, 1) == ")") parentesis = parentesis - 1;
					if(cadena.SubString(i, 1) == "(") parentesis = parentesis + 1;
					i = i - 1;
					if(parentesis > 0) antes = antes - 1;
				}

				i = i + antes + 1;
				if(parentesis > 0) i = i + 1;

				// calculamos el tamaño de la expresión posterior
				i = i + 1;
				despues = 0;
				parentesis = 0;
				while
				(
					(((cadena.SubString(i, 1) != "*") & (cadena.SubString(i, 1) != "+")) | (parentesis > 0)) &
						(parentesis >= 0) & (i <= cadena.Length())
				)
				{
					despues = despues + 1;
					if(cadena.SubString(i, 1) == ")") parentesis = parentesis - 1;
					if(cadena.SubString(i, 1) == "(") parentesis = parentesis + 1;
					i = i + 1;
					if(parentesis < 0) despues = despues - 1;
				}

				i = i - despues - 1;
				if(parentesis < 0) i = i - 1;

				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	cadena2 = cadena;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

				cadena2.Delete(i, despues + 1);
				EjecutarExpresion(cadena2, funcion);
				cadena.Delete(i - antes, antes + 1);
				temp1 = "";
				temp2 = "";
				i = 1;
				break;
			}

		case '*':
			{
				if(cadena.SubString(i + 1, 1) == "(")
				{
					temp1 = "";
					temp2 = "";
					i = i + 1;
				}
				else
				{
					// preparamos los datos
					temp2 = temp1;
					temp1 = "";

					/*~~~~~~~~~~*/
					int c = i + 1;
					/*~~~~~~~~~~*/

					i = i - temp2.Length();

					// metemos la segunda expresión en temp1
					while((isalpha(char(*cadena.SubString(c, 1).c_str()))) | (cadena.SubString(c, 1) == "-"))
					{
						temp1 = temp1 + cadena.SubString(c, 1);
						c = c + 1;
					}

					// se juntan en una sola expresión
					cadena.Delete(i, (temp1.Length() + temp2.Length() + 1));

					/*~~~~~~~~~~~~~~~~~*/
					bool	cero = false;
					/*~~~~~~~~~~~~~~~~~*/

					for(int l = 1; l <= temp2.Length(); l++)
					{
						if((isalpha(char(*temp2.SubString(l, 1).c_str()))) | (temp2.SubString(l, 1) == "0"))
						{
							/*~~~~~~*/
							int k = 1;
							/*~~~~~~*/

							while(k <= temp1.Length())
							{
								if((temp2.SubString(l, 1) == "0") | (temp1.SubString(k, 1) == "0"))
								{
									temp1.Insert(temp2.SubString(l, 1), k);
									k = temp1.Length() + 1;
									break;
								}
								else if(temp2.SubString(l, 1) < temp1.SubString(k, 1))
								{
									if(temp1.SubString(k - 1, 1) == "-") k = k - 1;
									temp1.Insert(temp2.SubString(l, 1), k);
									if(temp2.SubString(l - 1, 1) == "-")
									{
										temp1.Insert("-", k);
									}

									k = temp1.Length() + 1;
									break;
								}
								else if(temp2.SubString(l, 1) == temp1.SubString(k, 1))
								{
									/*~~~~~~~~~~~~~*/
									bool	uno, dos;
									/*~~~~~~~~~~~~~*/

									uno = true;
									dos = true;
									if(temp1.SubString(k - 1, 1) == "-") uno = false;
									if(temp2.SubString(l - 1, 1) == "-") dos = false;
									if((uno & dos) | (!uno &!dos))
									{
										k = temp1.Length() + 1;
									}
									else
									{
										temp1 = 0;
										cero = true;
									}
									break;
								}

								k = k + 1;
							}

							if
							(
								(!cero) & (k > temp1.Length()) &
									(temp1.SubString(temp1.Length(), 1) < temp2.SubString(l, 1))
							)
							{
								temp1 = temp1 + temp2.SubString(l, 1);
								if(temp2.SubString(l - 1, 1) == "-")
								{
									temp1.Insert("-", temp1.Length());
								}
							}
						}

						if(cero) break;
					}

					cadena.Insert(temp1, i);
					temp2 = "";
					i = i + temp1.Length();
					break;
				}
			}

		default:
			{
				// meter expresión en temp1
				while
				(
					(isalpha(char(*cadena.SubString(i, 1).c_str()))) | (cadena.SubString(i, 1) == "-") |
						(cadena.SubString(i, 1) == "0")
				)
				{
					temp1 = temp1 + cadena.SubString(i, 1);
					i = i + 1;
				}
			}
		}
	}

	// si hay algún cero la expresión es nula
	for(int x = 1; x <= cadena.Length(); x++)
	{
		if(cadena.SubString(x, 1) == "0")
		{
			cadena = "0";
			break;
		}
	}

	// tratamiento de las cadenas resultantes en la matriz
	if(cadena != "0") TransformarCadena(cadena, funcion);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TExprBooleana::TExprBooleana(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::FormShow(TObject *Sender)
{
	StringGrid1->ColCount = Tabla.NumColumnas();
	ScrollBar1->Max = Tabla.NumColumnas();
	for(int j = 0; j < Tabla.NumColumnas(); j++) StringGrid1->Cells[j][0] = "";
	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::BorrarClick(TObject *Sender)
{
	for(int j = 0; j < Tabla.NumColumnas(); j++) StringGrid1->Cells[j][0] = "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::SalirClick(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	ExprBooleana->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ScrollBar1->Position = StringGrid1->Col + 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posición adecuada
	Funcion->Caption = ScrollBar1->Position;
	StringGrid1->LeftCol = ScrollBar1->Position - 1;
	StringGrid1->Col = ScrollBar1->Position - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label1->Hint = Tabla.LeerSalida(ScrollBar1->Position - 1);
	Label1->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(ScrollBar1->Position - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::EvaluarClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	bool	todoBien = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	// quitamos todos los espacios y ponemos en mayusculas
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		ScrollBar1->Position = j + 1;

		/*~~~~~~~~~~~~~~~*/
		AnsiString	cadena;
		/*~~~~~~~~~~~~~~~*/

		cadena = "";

		/*~~~~~~*/
		int k = 1;
		/*~~~~~~*/

		while(k <= StringGrid1->Cells[j][0].Length())
		{
			if(StringGrid1->Cells[j][0].SubString(k, 1) != " ")
			{
				cadena = cadena + StringGrid1->Cells[j][0].SubString(k, 1);
			}

			k = k + 1;
		}

		cadena = cadena.UpperCase();
		StringGrid1->Cells[j][0] = cadena;

		/*~~~~~~~~~~~~~~~~~~~~~~~*/
		// comprobar que la función esta bien
		int			estado = 0;
		int			parentesis = 0;
		AnsiString	simbolos = "";
		/*~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 1; i <= cadena.Length(); i++)
		{
			if((cadena == 0) | (cadena == 1))
			{
				estado = 20;
				break;
			}
			else if(cadena.SubString(i, 1) == "(")
			{
				if((estado == 0) | (estado == 1) | (estado == 2) | (estado == 4))
				{
					parentesis = parentesis + 1;
					simbolos = simbolos + "(";
					estado = 1;
				}
				else
				{
					estado = 10;		// error general
					break;
				}
			}
			else if(cadena.SubString(i, 1) == "-")
			{
				if((estado == 0) | (estado == 1) | (estado == 4) | (estado == 2))
				{
					estado = 2;
				}
				else
				{
					estado = 10;		// error general
					break;
				}
			}
			else if(cadena.SubString(i, 1) == ")")
			{
				if((estado == 3) | (estado == 5))
				{
					parentesis = parentesis - 1;
					if(parentesis < 0)
					{
						estado = 11;	// error de parentesis
						break;
					}
					else
					{
						/*~~~~~~~~~~~~~~~~~~~~~~*/
						int i = simbolos.Length();
						/*~~~~~~~~~~~~~~~~~~~~~~*/

						while(simbolos.SubString(i, 1) != "(")
						{
							simbolos.Delete(i, 1);
							i = i - 1;
						}

						simbolos.Delete(i, 1);
						estado = 5;
					}
				}
				else
				{
					estado = 10;		// error
					break;
				}
			}
			else if((cadena.SubString(i, 1) == "*") | (cadena.SubString(i, 1) == "+"))
			{
				if((estado == 3) | (estado == 5))
				{
					if
					(
						(cadena.SubString(i, 1) != simbolos.SubString(simbolos.Length(), 1)) &
							(
								(simbolos.SubString(simbolos.Length(), 1) == "+") |
									(simbolos.SubString(simbolos.Length(), 1) == "*")
							)
					)
					{
						estado = 12;	// faltan parentesis entre operaciones
						break;
					}
					else
					{
						simbolos = simbolos + cadena.SubString(i, 1);
						estado = 4;
					}
				}
				else
				{
					estado = 10;		// error
					break;
				}
			}
			else if(isalpha(char(*cadena.SubString(i, 1).c_str())))
			{
				if((estado == 0) | (estado == 1) | (estado == 2) | (estado == 4))
				{
					if(char(*cadena.SubString(i, 1).c_str()) > 'A' + Tabla.NumEntradas() - 1)
						estado = 13;	// esa variable no existe
					else
						estado = 3;
				}
				else
				{
					estado = 10;		// error general
					break;
				}
			}
		}

		if((estado == 3) | (estado == 5))
		{
			if(parentesis == 0)
				estado = 20;
			else
				estado = 11;			// error de parentesis
		}
		else if(estado < 10)
		{
			estado = 10;				// error
		}

		if(cadena == "") estado = 20;
		if(estado != 20)
		{
			todoBien = false;
			if(estado == 10) ShowMessage("Expresión erronea");
			if(estado == 11) ShowMessage("Error de parentesis");
			if(estado == 12) ShowMessage("La expresión es confusa delimite con parentesis");
			if(estado == 13) ShowMessage("Numero de variables de entrada excedido");
		}
	}

	// introducimos los datos, inicializando antes la matriz
	if(todoBien)
	{
		for(int i = 0; i < Tabla.NumFilas(); i++)
			for(int j = 0; j < Tabla.NumColumnas(); j++) Tabla.EscribirDinArray(i, j, '0');

		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			/*~~~~~~~~~~~~~~~*/
			// convertimos la expresión en una mas sencilla --a*-(a+-b) => a*(-a*b)
			AnsiString	cadena;
			/*~~~~~~~~~~~~~~~*/

			cadena = StringGrid1->Cells[j][0];

			/*~~~~~~*/
			int i = 1;
			/*~~~~~~*/

			while(i <= cadena.Length())
			{
				if((cadena.SubString(i, 1) == "-") & (cadena.SubString(i + 1, 1) == "-"))
				{
					cadena.Delete(i, 2);
				}
				else if((cadena.SubString(i, 1) == "-") & (cadena.SubString(i + 1, 1) == "("))
				{
					cadena.Delete(i, 1);

					/*~~~~~~*/
					int p = 1;
					/*~~~~~~*/

					i = i + 1;
					while(p > 0)
					{
						if(p == 1)
						{
							if((isalpha(char(*cadena.SubString(i, 1).c_str()))))
							{
								cadena.Insert("-", i);
								i = i + 2;
							}
							else if(cadena.SubString(i, 1) == "(")
							{
								cadena.Insert("-", i);
								p = p + 1;
								i = i + 2;
							}
							else if(cadena.SubString(i, 1) == "+")
							{
								cadena.Delete(i, 1);
								cadena.Insert("*", i);
								i = i + 1;
							}
							else if(cadena.SubString(i, 1) == "*")
							{
								cadena.Delete(i, 1);
								cadena.Insert("+", i);
								i = i + 1;
							}
							else if(cadena.SubString(i, 1) == ")")
							{
								p = p - 1;
								i = i + 1;
							}
							else
							{
								i = i + 1;
							}
						}
						else
						{
							if(cadena.SubString(i, 1) == "(") p = p + 1;
							if(cadena.SubString(i, 1) == ")") p = p - 1;
							i = i + 1;
						}
					}

					i = 1;
				}
				else
				{
					i = i + 1;
				}
			}

			// introducimos la cadena en la matriz
			if(cadena == "1")
			{
				cadena = "";
			}
			else if((cadena == "0") | (cadena == ""))
			{
				cadena = "A*-A";
			}

			EjecutarExpresion(cadena, j);
		}

		ShowMessage("Sistema evaluado");
	}

	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::EvaluarExpClick(TObject *Sender)
{
        AnsiString error ="";
        for (int j=0; j<Tabla.NumColumnas(); j++)
        {
                string expresion = StringGrid1->Cells[j][0].c_str();
                if (expresion != "")
                try
                {
                        EvaluadorBool *eval = new EvaluadorBool();

                        for (int i=0; i<Tabla.NumEntradas(); i++)
                        {
                                AnsiString entrada = Tabla.LeerEntrada(i);
                                if(entrada=="")
                                        entrada = AnsiString(char('A' + i));
                                eval->AnyadirEntrada(entrada.c_str());
                        }

                        eval->evaluar(expresion.c_str());

                        if (eval->getNumVars() > Tabla.NumEntradas())
                                error+=ANSIMENSAJE(msgErrorEnFuncion) + " " + AnsiString(j+1) + ": " + ANSIMENSAJE(msgVariableNoExiste)+"n\r";
                        else
                        {
                                for (unsigned int i=0;i<eval->getNumMinterminos();i++)
                                {
                                        AnsiString bin = CalcularBinario(i,eval->getNumVars()).c_str();
                                        for (unsigned int k=0;k<Tabla.NumEntradas();k++)
                                        {
                                                AnsiString entrada = Tabla.LeerEntrada(k);
                                                if(entrada=="")
                                                        entrada = AnsiString(char('A' + k));
                                                eval->SetValorEntrada(entrada.c_str(),bin[k+1]=='0'?false:true);
                                        }
                                        Tabla.EscribirDinArray(i, j, eval->getValor()?'1':'0');
                                }
                                delete eval;
                        }
                }
                catch(exception &e) {
                        error+=ANSIMENSAJE(msgErrorEnFuncion) + " " + AnsiString(j+1) + ": " + ANSIMENSAJE(msgExpErronea)+"n\r";
                }
        }
        if(error!="")
        {
                error += ANSIMENSAJE(msgNoGuardadoFuncError);
                Application->MessageBox(error.c_str(), NULL);
        }
	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::BorrarExpClick(TObject *Sender)
{
	for(int j = 0; j < Tabla.NumColumnas(); j++) StringGrid1->Cells[j][0] = "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::SalirExpClick(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	ExprBooleana->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExprBooleana::BitBtn4Click(TObject *Sender)
{
	Application->MessageBox(MENSAJE(msgAyudaExprBool), "");
}

