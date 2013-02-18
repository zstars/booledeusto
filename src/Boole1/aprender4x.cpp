/*$T boole/Boole1/aprender4x.cpp GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "aprender4x.h"
#include "DinArray.h";
#include "app.h";
#include "Libreria.h";
#include "NuevoSC.h";
#include "Unit11.h"
#include "ctype.h"
#include "mensajes.inc"
extern DinArray Tabla;

DinArray		Tabla2 = DinArray();
#pragma link "Grids"
#pragma resource "*.dfm"
Taprender4		*aprender4;

int				numFuncion4XX = 1;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall Taprender4::Taprender4(TComponent *Owner) :
	TForm(Owner)
{
}

//
// =======================================================================================================================
//    metemos los datos de la cadena en la matriz B-D => 0100 1100 0110 1110
// =======================================================================================================================
//
void TransformarCadena4(AnsiString cadena, int funcion)
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	posicion = "";
	bool		roto = false;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 0; i < Tabla2.NumEntradas(); i++)
	{
		/*~~~~~~*/
		// buscamos la primera variable (letra)
		int z = 1;
		/*~~~~~~*/

		while
		(
			(
				(('A' > (char(*cadena.SubString(z, 1).c_str()))) || ('Z' < (char(*cadena.SubString(z, 1).c_str()))))
			||	(
					(('A' <= (char(*cadena.SubString(z, 1).c_str()))) && ('Z' >= (char(*cadena.SubString(z, 1).c_str()))))
				&&	((char(*cadena.SubString(z, 1).c_str()) < char('A' + i)))
				)
			)
		&&	(z <= cadena.Length())
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
				TransformarCadena4(cadena, funcion);
				cadena.Insert("-", z - 1);
			}
			else
			{
				cadena.Insert(char('A' + i), z);
				TransformarCadena4(cadena, funcion);
				cadena.Insert("-", z);
			}

			TransformarCadena4(cadena, funcion);
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
			TransformarCadena4(cadena, funcion);
			cadena.Insert("-", cadena.Length());
			TransformarCadena4(cadena, funcion);
			roto = true;
			break;
		}
	}

	if(!roto)
	// meter "posicion" en la posicion del array
	{
		Tabla2.EscribirDinArray(binario(posicion), funcion, '1');
		roto = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void EjecutarExpresion4(AnsiString cadena, int funcion)
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
					(((cadena.SubString(i, 1) != "*") && (cadena.SubString(i, 1) != "+")) || (parentesis < 0))
				&&	(parentesis <= 0)
				&&	(i > 0)
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
					(((cadena.SubString(i, 1) != "*") && (cadena.SubString(i, 1) != "+")) || (parentesis > 0))
				&&	(parentesis >= 0)
				&&	(i <= cadena.Length())
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
				EjecutarExpresion4(cadena2, funcion);
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
					while((isalpha(char(*cadena.SubString(c, 1).c_str()))) || (cadena.SubString(c, 1) == "-"))
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
						if((isalpha(char(*temp2.SubString(l, 1).c_str()))) || (temp2.SubString(l, 1) == "0"))
						{
							/*~~~~~~*/
							int k = 1;
							/*~~~~~~*/

							while(k <= temp1.Length())
							{
								if((temp2.SubString(l, 1) == "0") || (temp1.SubString(k, 1) == "0"))
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
									if((uno && dos) || (!uno && !dos))
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
								(!cero)
							&&	(k > temp1.Length())
							&&	(temp1.SubString(temp1.Length(), 1) < temp2.SubString(l, 1))
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
					(isalpha(char(*cadena.SubString(i, 1).c_str())))
				||	(cadena.SubString(i, 1) == "-")
				||	(cadena.SubString(i, 1) == "0")
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
	if(cadena != "0") TransformarCadena4(cadena, funcion);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::SalirExpClick(TObject *Sender)
{
	Tabla2.BorrarDinArray();

	// ¿destructor de tabla?
	SistemaCombinacionalNuevo->Show();
	aprender4->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posición adecuada
	numFuncion4XX = ScrollBar1->Position;
	Funcion->Caption = numFuncion4XX;
	Label6->Caption = numFuncion4XX;
	StringGrid1->LeftCol = numFuncion4XX - 1;
	StringGrid2->LeftCol = numFuncion4XX - 1;
	StringGrid1->Col = numFuncion4XX - 1;
	StringGrid2->Col = numFuncion4XX - 1;

	// ajustamos el grid a la posición adecuada
	StringGridVK->TopRow = (numFuncion4XX - 1) * 4 + 1;
	StringGridVK->Row = (numFuncion4XX - 1) * 4 + 1;
	StringGridVK->Col = 1;

	StringGrid3->LeftCol = numFuncion4XX - 1;
	StringGrid3->Col = numFuncion4XX - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label1->Hint = Tabla.LeerSalida(numFuncion4XX - 1);
	Label1->ShowHint = true;
	Label4->Hint = Tabla.LeerSalida(numFuncion4XX - 1);
	Label4->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label6->Hint = Tabla.LeerSalida(numFuncion4XX - 1);
	Label6->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::Label4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label1->Hint = Tabla.LeerSalida(numFuncion4XX - 1);
	Label1->ShowHint = true;
	Label4->Hint = Tabla.LeerSalida(numFuncion4XX - 1);
	Label4->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::Label6MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label6->Hint = Tabla.LeerSalida(numFuncion4XX - 1);
	Label6->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::StringGrid3KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ScrollBar1->Position = StringGrid3->Col + 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::BorrarExpClick(TObject *Sender)
{
	for(int j = 0; j < Tabla.NumColumnas(); j++) StringGrid3->Cells[j][0] = "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::EvaluarExpClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	// Comprobamos que sea una expresión SOP o POS
	bool	todoBien = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	cadena = "";
		int			estado = 0;
		int			k = 1;
		/*~~~~~~~~~~~~~~~~~~~~*/

		if((StringGrid3->Cells[j][0] != "0") && (StringGrid3->Cells[j][0] != "1"))
		{
			while(k <= StringGrid3->Cells[j][0].Length())
			{
				cadena = StringGrid3->Cells[j][0].SubString(k, 1);
				if((estado == 0) && (cadena == "("))
					estado = 1;
				else
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					char	c = char(*cadena.SubString(1, 1).c_str());
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					if((estado == 1) && (cadena == "-"))
						estado = 7;
					else
					{
						if
						(
							((estado == 7) || (estado == 1))
						&&	((((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))))
						) estado = 2;
						else
						{
							if
							(
								((estado == 2) && (cadena == "*") && (Disyuntivo->Checked))
							||	((estado == 2) && (cadena == "+") && (Conjuntivo->Checked))
							) estado = 1;
							else
							{
								if((estado == 2) && (cadena == ")"))
									estado = 3;
								else
								{
									if
									(
										((estado == 3) && (cadena == "+") && (Disyuntivo->Checked))
									||	((estado == 3) && (cadena == "*") && (Conjuntivo->Checked))
									) estado = 0;
									else
										todoBien = false;
								}
							}
						}
					}
				}

				k = k + 1;
				if(!todoBien) break;
			}

			if(estado != 3) todoBien = false;
			if(!todoBien) break;
		}
	}

	if(todoBien)
	{
		// Introducimos los datos en la Tabla2 creandola
		Tabla2.BorrarDinArray();
		Tabla2.DinX("temporal", Tabla.NumEntradas(), Tabla.NumColumnas());

		// quitamos todos los espacios y ponemos en mayusculas
		for(int j = 0; j < Tabla2.NumColumnas(); j++)
		{
			ScrollBar1->Position = j + 1;

			/*~~~~~~~~~~~~~~~*/
			AnsiString	cadena;
			/*~~~~~~~~~~~~~~~*/

			cadena = "";

			/*~~~~~~*/
			int k = 1;
			/*~~~~~~*/

			while(k <= StringGrid3->Cells[j][0].Length())
			{
				if(StringGrid3->Cells[j][0].SubString(k, 1) != " ")
				{
					cadena = cadena + StringGrid3->Cells[j][0].SubString(k, 1);
				}

				k = k + 1;
			}

			cadena = cadena.UpperCase();
			StringGrid3->Cells[j][0] = cadena;

			// comprobar que la función esta bien
			if((cadena != "0") && (cadena != "1"))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~*/
				int			estado = 0;
				int			parentesis = 0;
				AnsiString	simbolos = "";
				/*~~~~~~~~~~~~~~~~~~~~~~~*/

				for(int i = 1; i <= cadena.Length(); i++)
				{
					if((cadena == 0) || (cadena == 1))
					{
						estado = 20;
						break;
					}
					else if(cadena.SubString(i, 1) == "(")
					{
						if((estado == 0) || (estado == 1) || (estado == 2) || (estado == 4))
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
						if((estado == 0) || (estado == 1) || (estado == 4) || (estado == 2))
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
						if((estado == 3) || (estado == 5))
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
					else if((cadena.SubString(i, 1) == "*") || (cadena.SubString(i, 1) == "+"))
					{
						if((estado == 3) || (estado == 5))
						{
							if
							(
								(cadena.SubString(i, 1) != simbolos.SubString(simbolos.Length(), 1))
							&&	(
									(simbolos.SubString(simbolos.Length(), 1) == "+")
								||	(simbolos.SubString(simbolos.Length(), 1) == "*")
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
						if((estado == 0) || (estado == 1) || (estado == 2) || (estado == 4))
						{
							if(char(*cadena.SubString(i, 1).c_str()) > 'A' + Tabla2.NumEntradas() - 1)
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

				if((estado == 3) || (estado == 5))
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
					if(estado == 10) Application->MessageBox(MENSAJE(msgExpErronea), NULL);
					if(estado == 11) Application->MessageBox(MENSAJE(msgErrorParen), NULL);
					if(estado == 12) Application->MessageBox(MENSAJE(msgExprConfusa), NULL);
					if(estado == 13) Application->MessageBox(MENSAJE(msgEntradaExced), NULL);
				}
			}
		}

		// introducimos los datos, inicializando antes la matriz
		if(todoBien)
		{
			for(int i = 0; i < Tabla2.NumFilas(); i++)
				for(int j = 0; j < Tabla2.NumColumnas(); j++) Tabla2.EscribirDinArray(i, j, '0');

			for(int j = 0; j < Tabla2.NumColumnas(); j++)
			{
				/*~~~~~~~~~~~~~~~*/
				// convertimos la expresión en una mas sencilla --a*-(a+-b) => a*(-a*b)
				AnsiString	cadena;
				/*~~~~~~~~~~~~~~~*/

				cadena = StringGrid3->Cells[j][0];

				/*~~~~~~*/
				int i = 1;
				/*~~~~~~*/

				while(i <= cadena.Length())
				{
					if((cadena.SubString(i, 1) == "-") && (cadena.SubString(i + 1, 1) == "-"))
					{
						cadena.Delete(i, 2);
					}
					else if((cadena.SubString(i, 1) == "-") && (cadena.SubString(i + 1, 1) == "("))
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
				else if((cadena == "0") || (cadena == ""))
				{
					cadena = "A*-A";
				}

				EjecutarExpresion4(cadena, j);
			}
		}

		ScrollBar1->Position = 1;

		// Comprobamos si Tabla y Tabla2 son iguales
		for(int i = 0; i < Tabla.NumFilas(); i++)
		{
			for(int j = 0; j < Tabla.NumColumnas(); j++)
			{
				if((Tabla.LeerDinArray(i, j) != Tabla2.LeerDinArray(i, j)) && (Tabla.LeerDinArray(i, j) != 'X'))
				{
					todoBien = false;
					break;
				}
			}

			if(!todoBien) break;
		}

		if(todoBien)
		{
			//
			// Obtenemos la expresión simplificada correspondiente solo nos interesa el número
			// de terminos y literales.
			//
			Form11->NumC->Text = Tabla.NumEntradas();

			// damos el tamaño adecuado a los grids
			StringGrid4->RowCount = Tabla.NumColumnas();

			// Recogemos los valores de la tabla para hacer la simplificacion
			for(int l = 0; l < Tabla.NumColumnas(); l++)
			{
				Form11->Unos->Text = "";
				Form11->Equis->Text = "";
				StringGrid4->Cells[0][l] = "";
				for(int i = 0; i < Tabla.NumFilas(); i++)
				{
					if
					(
						((Tabla.LeerDinArray(i, l) == '1') && (Disyuntivo->Checked == true))
					||	((Tabla.LeerDinArray(i, l) == '0') && (Conjuntivo->Checked == true))
					)
					{
						Form11->Unos->Text = Form11->Unos->Text + i + ",";
					}
					else if(Tabla.LeerDinArray(i, l) == 'X')
					{
						Form11->Equis->Text = Form11->Equis->Text + i + ",";
					}
				}

				Form11->Button1->Click();

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				//
				// Despues de mandar los valores a la función de simplificación los recogemos en
				// el StringGrid de Salida donde se visualizaran
				//
				AnsiString	cadenaSimp = Form11->Solucion->Text;
				AnsiString	cadenaLlena;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				for(int i = 1; i <= Tabla.NumEntradas(); i++)
				{
					cadenaLlena = cadenaLlena + "-";
				}

				if(cadenaSimp == "")
					if(Disyuntivo->Checked)
						cadenaSimp = "1";
					else
						cadenaSimp = "0";
				else if(cadenaSimp == cadenaLlena)
					if(Conjuntivo->Checked)
						cadenaSimp = "0";
					else
						cadenaSimp = "1";
				else
				{
					/*~~~~~~*/
					int x = 1;
					int y = 1;
					/*~~~~~~*/

					// Con esto transformamos la cadena de salida en letras
					while(x <= cadenaSimp.Length())
					{
						if(cadenaSimp.SubString(x, 1) == "1")
						{
							cadenaSimp.Delete(x, 1);
							cadenaSimp.Insert(char('A' - 1 + y), x);
							cadenaSimp.Insert("*", x + 1);
							x = x + 2;
							y = y + 1;
						}
						else if(cadenaSimp.SubString(x, 1) == "0")
						{
							cadenaSimp.Delete(x, 1);
							cadenaSimp.Insert("~*", x);
							cadenaSimp.Insert(char('A' - 1 + y), x + 1);
							x = x + 3;
							y = y + 1;
						}
						else if(cadenaSimp.SubString(x, 1) == "-")
						{
							cadenaSimp.Delete(x, 1);
							y = y + 1;
						}
						else
						{
							cadenaSimp.Delete(x - 1, 2);
							cadenaSimp.Insert(")+(", x - 1);
							x = x + 2;
							y = 1;
						}
					}

					cadenaSimp.Delete(cadenaSimp.Length(), 1);
					cadenaSimp.Insert("(", 1);
					cadenaSimp = cadenaSimp + ")";

					//
					// Si es POS entonces tenemos que invertir las variables y cambiar los operadores
					// tanto internos y externos
					//
					if(Conjuntivo->Checked == true)
					{
						cadenaSimp = InvertirVariables(cadenaSimp);
						cadenaSimp = CambiarSignos(cadenaSimp, false);
						cadenaSimp = CambiarSignos(cadenaSimp, true);
					}
				}

				StringGrid4->Cells[0][l] = cadenaSimp;

				// Escribimos el resultado en el StringGrid para visualizarlo }
			}

			//
			// Comparamos que la expresión introducida sea mínima // 1º Comprobamos que los
			// terminos son mínimos // 2º Comprobamos que los literales son mínimos
			//
			for(int i = 0; i < Tabla.NumColumnas(); i++)
			{
				if
				(
					(NumeroTerminos(StringGrid3->Cells[i][0]) != NumeroTerminos(StringGrid4->Cells[0][i]))
				||	(NumeroLiterales(StringGrid3->Cells[i][0]) != NumeroLiterales(StringGrid4->Cells[0][i]))
				) todoBien = false;
			}

			if(todoBien)
				Application->MessageBox(MENSAJE(msgCorrectoYMinimo), "");
			else if(Tabla.NumColumnas() > 1)
			{
                                AnsiString mensaje = AnsiString(MENSAJE(msgCorrectoNoMinimo)) + AnsiString("\n\n") + AnsiString(MENSAJE(msgRecordatorioVariasVars));
				Application->MessageBox(mensaje.c_str(), "");
			}
			else
				Application->MessageBox(MENSAJE(msgCorrectoNoMinimo), "");
		}
		else if(Tabla.NumColumnas() > 1)
		{
                        AnsiString mensaje = AnsiString(MENSAJE(msgNoIdenticos)) + AnsiString("\n\n") + AnsiString(MENSAJE(msgRecordatorioVariasVars));
	        	Application->MessageBox(mensaje.c_str(), "");
		}
		else
			Application->MessageBox(MENSAJE(msgNoIdenticos), "");
	}
	else if(Tabla.NumColumnas() > 1)
	{
                AnsiString mensaje = AnsiString(MENSAJE(msgExprErronea)) + AnsiString("\n\n") + AnsiString(MENSAJE(msgRecordatorioVariasVars));
        	Application->MessageBox(mensaje.c_str(), "");
	}
	else
		Application->MessageBox(MENSAJE(msgExprErronea), "");
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::FormShow(TObject *Sender)
{
	Funcion->Caption = numFuncion4XX;
	StringGrid1->LeftCol = 0;
	StringGrid2->LeftCol = 0;
	ScrollBar1->Max = Tabla.NumColumnas();

	// damos el tamaño adecuado a los grids
	StringGrid1->ColCount = Tabla.NumColumnas();
	StringGrid2->ColCount = Tabla.NumColumnas();
	StringGrid1->Col = 0;
	StringGrid2->Col = 0;

	// rellenamos los valores de la tabla de salida
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		StringGrid1->Cells[j][0] = "";
		StringGrid2->Cells[j][0] = "";
		for(int i = 0; i < Tabla.NumFilas(); i++)
		{
			if((Tabla.LeerDinArray(i, j) == '1') && (Disyuntivo->Checked == true))
			{
				if(StringGrid1->Cells[j][0] != "") StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0] + ",";
				StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0] + i;
			}
			else if((Tabla.LeerDinArray(i, j) == '0') && (Conjuntivo->Checked == true))
			{
				if(StringGrid1->Cells[j][0] != "") StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0] + ",";
				StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0] + i;
			}
			else if(Tabla.LeerDinArray(i, j) == 'X')
			{
				if(StringGrid2->Cells[j][0] != "") StringGrid2->Cells[j][0] = StringGrid2->Cells[j][0] + ",";
				StringGrid2->Cells[j][0] = StringGrid2->Cells[j][0] + i;
			}
		}
	}

	// llenamos el array
	ScrollBar1->Position = 1;

	StringGridVK->RowCount = Tabla.NumColumnas() * 4 + 1;

	StringGridVK->Cells[1][0] = "00";
	StringGridVK->Cells[2][0] = "10";
	StringGridVK->Cells[3][0] = "11";
	StringGridVK->Cells[4][0] = "01";

	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		StringGridVK->Cells[0][i * 4 + 1] = "00";
		StringGridVK->Cells[0][i * 4 + 2] = "10";
		StringGridVK->Cells[0][i * 4 + 3] = "11";
		StringGridVK->Cells[0][i * 4 + 4] = "01";
	}

	Panel1->Hint = Tabla.LeerEntrada(0);
	Label1->Hint = Tabla.LeerEntrada(0);
	Panel3->Hint = Tabla.LeerEntrada(2);
	Label3->Hint = Tabla.LeerEntrada(2);
	Panel5->Hint = Tabla.LeerEntrada(1);
	Label5->Hint = Tabla.LeerEntrada(1);
	Panel7->Hint = Tabla.LeerEntrada(3);
	Label7->Hint = Tabla.LeerEntrada(3);

	ScrollBar1->Max = Tabla.NumColumnas();

	// cargo el contenido del objeto Tabla en el diagrama
	for(int f = 0; f < Tabla.NumColumnas(); f++)
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				StringGridVK->Cells[j + 1][(f * 4) + i + 1] = Tabla.LeerDinArray
					(
						FusionarCadenas(StringGridVK->Cells[j + 1][0], StringGridVK->Cells[0][i + 1]),
						f
					);
			}
		}
	}

	// creo el array auxiliar
	StringGrid3->ColCount = Tabla.NumColumnas();
	for(int j = 0; j < Tabla.NumColumnas(); j++) StringGrid3->Cells[j][0] = "";
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall Taprender4::BitBtn4Click(TObject *Sender)
{
	if(Conjuntivo->Checked == true)
	{
		Application->MessageBox(MENSAJE(msgAyudaAprenderPOS), "");
	}
	else
	{
		Application->MessageBox(MENSAJE(msgAyudaAprenderSOP), "");
	}
}
