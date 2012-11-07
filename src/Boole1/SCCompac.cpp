/*$T boole/Boole1/SCCompac.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "Libreria.h"
#include "SCCompac.h"
#include "NandNor.h"
#include "NuevoSC.h"
#include "Math.h"
#include "DinArray.h"
#include "mensajes.inc"
// Modificado
#include "Circuito/V_Circuito.h"
#include <vector>
using namespace std;

// Modificado
extern DinArray		Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TSCFormasCompactas	*SCFormasCompactas;

int					numFuncion = 1;

/*
 =======================================================================================================================
    función que dada una expresion logica intoduce el valor corresppondiente en su posición (o posiciones) de la matriz
 =======================================================================================================================
 */
void TratarCadena(AnsiString cadena, int j, char valor)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	ultimaVariable = char(('A' - 1)), ultimoSimbolo = char(('A' - 1));
	int			i = 0, x = 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// calculamos la posición o posiciones que representa la cadena
	while(x < cadena.Length())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	aux1 = cadena, aux2 = cadena;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		// caracteres que no son variables
		if
		(
			(cadena.SubString(x, 1) == "+") | (cadena.SubString(x, 1) == "*") | (cadena.SubString(x, 1) == "~") |
				(cadena.SubString(x, 1) == "(")
		)
		{
			ultimoSimbolo = cadena.SubString(x, 1);
		}
		else if(cadena.SubString(x, 1) == ")")
		{
			// comprobamos si falta alguna variable por detras
			if(char(*ultimaVariable.c_str()) != char('A' - 1 + Tabla.NumEntradas()))
			{
				if(SCFormasCompactas->Disyuntivo->Checked)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	relleno = "+";
					/*~~~~~~~~~~~~~~~~~~~~~~*/

					relleno = relleno + char(*ultimaVariable.c_str() + 1);
					aux1.Insert(relleno, x);
					TratarCadena(aux1, j, valor);
					relleno = "+~";
					relleno = relleno + char(*ultimaVariable.c_str() + 1);
					aux2.Insert(relleno, x);
					TratarCadena(aux2, j, valor);
				}
				else
				{
					/*~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	relleno = "*";
					/*~~~~~~~~~~~~~~~~~~~~~~*/

					relleno = relleno + char(*ultimaVariable.c_str() + 1);
					aux1.Insert(relleno, x);
					TratarCadena(aux1, j, valor);
					relleno = "*~";
					relleno = relleno + char(*ultimaVariable.c_str() + 1);
					aux2.Insert(relleno, x);
					TratarCadena(aux2, j, valor);
				}
			}
		}
		else
		{
			// comprobamos si se ha saltado alguna variable en medio
			if(cadena.SubString(x, 1) == char(*ultimaVariable.c_str() + 1))
			{
				/*
				 * si no ha ocurrido asi se va calculando el valor de la posicion que le
				 * corresponde
				 */
				ultimaVariable = char(*ultimaVariable.c_str() + 1);
				if(ultimoSimbolo != "~") i = i + pow(2, Tabla.NumEntradas() - (*ultimaVariable.c_str() - 64));
			}
			else
			{
				/*
				 * si se ha saltado añadimos las cadenas correspondientes con los posibles valores
				 * de la variable
				 */
				ultimaVariable = char(*ultimaVariable.c_str() + 1);
				if(SCFormasCompactas->Disyuntivo->Checked)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	relleno = "+";
					/*~~~~~~~~~~~~~~~~~~~~~~*/

					relleno = relleno + char(*ultimaVariable.c_str());
					if(ultimoSimbolo != "~")
						aux1.Insert(relleno, x - 1);
					else
						aux1.Insert(relleno, x - 2);
					TratarCadena(aux1, j, valor);
					relleno = "+~";
					relleno = relleno + char(*ultimaVariable.c_str());
					if(ultimoSimbolo != "~")
						aux2.Insert(relleno, x - 1);
					else
						aux2.Insert(relleno, x - 2);
					TratarCadena(aux2, j, valor);
				}
				else
				{
					/*~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	relleno = "*";
					/*~~~~~~~~~~~~~~~~~~~~~~*/

					relleno = relleno + char(*ultimaVariable.c_str());
					if(ultimoSimbolo != "~")
						aux1.Insert(relleno, x - 1);
					else
						aux1.Insert(relleno, x - 2);
					TratarCadena(aux1, j, valor);
					relleno = "*~";
					relleno = relleno + char(*ultimaVariable.c_str());
					if(ultimoSimbolo != "~")
						aux2.Insert(relleno, x - 1);
					else
						aux2.Insert(relleno, x - 2);
					TratarCadena(aux2, j, valor);
				}

				x = cadena.Length();
			}
		}

		// comprobamos que no falten variables por delante
		if(cadena.SubString(x, 1) == "(")
		{
			if((cadena.SubString(x + 1, 1) != "A") & (cadena.SubString(x + 2, 1) != "A"))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	relleno = "A+";
				/*~~~~~~~~~~~~~~~~~~~~~~~*/

				aux1.Insert(relleno, x + 1);
				TratarCadena(aux1, j, valor);
				relleno = "~A+";
				aux2.Insert(relleno, x + 1);
				TratarCadena(aux2, j, valor);
				x = cadena.Length();
			}
		}

		// pasamos al siguiente caracter de la cadena
		x = x + 1;
	}

	// escribimos en el objeto tabla el valor adecuado en la posición correspondiente
	if(x == cadena.Length())
	{
		if((Tabla.LeerDinArray(i, j) != 'X') | ((SCFormasCompactas->Disyuntivo->Checked) & (valor > '0')))
		{
			if(valor == '2')
				Tabla.EscribirDinArray(i, j, '0');
			else
				Tabla.EscribirDinArray(i, j, valor);
		}

		// else ShowMessage("estas sobreescribiendo un valor");// el ,cadena,
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TSCFormasCompactas::TSCFormasCompactas(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::SalirClick(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	SCFormasCompactas->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::Edit1KeyPress(TObject *Sender, char &Key)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	texto, letras, varAnterior, signoAnterior;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si se pulsa el RETURN
	if((Key == 13) && (Edit1->Text != ""))
	{
		texto = "(";
		letras = "";
		varAnterior = char(('A' - 1));
		signoAnterior = char(('A' - 1));

		/*~~~~~~~~~~~~~~~~~~*/
		bool	fallo = false;
		/*~~~~~~~~~~~~~~~~~~*/

		// comprobamos todos los caracteres de la caja de texto
		for(int i = 1; i <= Edit1->Text.Length(); i++)
		{
			// ponemos las letras en mayusculas
			if((Edit1->Text[i] >= 'a') & (Edit1->Text[i] <= 'z'))
				letras = (char((Edit1->Text[i] - 32)));
			else
				letras = char(Edit1->Text[i]);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			// si es una letra
			AnsiString	limite = char(('A' - 1 + Tabla.NumEntradas()));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((letras >= "A") & (letras <= limite))
			{
				// y esta dentro de los parametros correctos
				if(letras > varAnterior)
				{
					// introducir el caracter en el texto y '+' o '.'
					if(Disyuntivo->Checked)
						texto = texto + letras + "+";
					else
						texto = texto + letras + "*";
					varAnterior = letras;
					signoAnterior = letras;
				}
				else
				{
					// error: variable en orden incorrecto o duplicada
					fallo = true;
					ShowMessage("error: variable en orden incorrecto o duplicada");
				}
			}

			// si es un simbolo
			else if(Edit1->Text[i] == '-')
			{
				letras = "-";

				// y esta colocado de forma correcta (solo uno ante cada variable)
				if(signoAnterior != '-')
				{
					// introducir caracter 126 en el texto
					texto = texto + "~";
					signoAnterior = '-';
				}
				else
				{
					// error: sobra un simbolo '-'
					fallo = true;
					ShowMessage("error: sobra un simbolo '-'");
				}
			}
			else
			{
				// error: varible de entrada erronea
				fallo = true;
				ShowMessage("error: varible de entrada erronea");
			}

			if(fallo) break;
		}

		// si el ultimo simbolo es '-' es un error
		if((signoAnterior == '-') & (!fallo))
		{
			fallo = true;
			ShowMessage("error: '-' no esta en un lugar correcto");
		}
		else
		{
			if(Disyuntivo->Checked)
				texto = texto.SubString(1, texto.Length() - 1) + ")*";
			else
				texto = texto.SubString(1, texto.Length() - 1) + ")+";
		}

		// comprobar que la combinación no se encuentra en la lista
		if(!fallo)
		{
			for(int i = 0; i < StringGrid1->RowCount; i++)
			{
				if(StringGrid1->Cells[(StringGrid1->LeftCol)][i] == texto)
				{
					fallo = true;
					ShowMessage("combinación ya existente");
					break;
				}
			}

			// y entonces introducirlo en ella
			if(!fallo)
			{
				StringGrid1->Cells[StringGrid1->LeftCol][StringGrid1->RowCount - 1] = texto;
				if(StringGrid1->RowCount > 3) StringGrid1->TopRow = StringGrid1->RowCount - 4;
				Edit1->Text = "";
				StringGrid1->RowCount = StringGrid1->RowCount + 1;
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::FormShow(TObject *Sender)
{
	Edit1->Text = "";
	Edit2->Text = "";

	if(!Disyuntivo->Checked)
		Label2->Caption = "con miniterminos";
	else
		Label2->Caption = "con maxiterminos";

	StringGrid1->ColCount = Tabla.NumColumnas();
	StringGrid1->RowCount = 1;
	StringGrid2->ColCount = Tabla.NumColumnas();
	StringGrid2->RowCount = 1;
	ScrollBar1->Max = Tabla.NumColumnas();

	// borramos los valores de todas las funciones, no del objeto Tabla
	for(int j = 0; j < (StringGrid1->ColCount); j++)
	{
		StringGrid1->TopRow = 0;
		StringGrid2->TopRow = 0;
		StringGrid1->LeftCol = j;
		StringGrid2->LeftCol = j;

		/*~~~~~~*/
		int i = 1;
		/*~~~~~~*/
		{
			while(StringGrid1->Cells[j][i - 1] != "")
			{
				i = i + 1;
			}

			StringGrid1->RowCount = i;

			i = 1;
			while(StringGrid2->Cells[j][i - 1] != "")
			{
				i = i + 1;
			}

			StringGrid2->RowCount = i;
		}

		while(StringGrid1->Cells[j][0] != "")
		{
			StringGrid1->Cells[j][StringGrid1->RowCount - 2] = "";
			StringGrid1->RowCount = StringGrid1->RowCount - 1;
		}

		while(StringGrid2->Cells[j][0] != "")
		{
			StringGrid2->Cells[j][StringGrid2->RowCount - 2] = "";
			StringGrid2->RowCount = StringGrid2->RowCount - 1;
		}
	}

	// si existe el objeto Tabla lo cargamos
	if(Tabla.LeerDinArray(0, 0) != ' ')
	{
		for(int j = Tabla.NumColumnas() - 1; j >= 0; j--)
		{
			StringGrid1->RowCount = 1;
			StringGrid2->RowCount = 1;

			for(int i = 0; i < Tabla.NumFilas(); i++)
			{
				/*~~~~~~~~~~~~~~*/
				AnsiString	texto;
				/*~~~~~~~~~~~~~~*/

				if(!Disyuntivo->Checked)	// SOP
				{
					if(Tabla.LeerDinArray(i, j) == '1')
					{
						texto = AniadirSimbolos(CalcularCadena(CalcularBinario(i, Tabla.NumEntradas())), false);
						StringGrid1->Cells[j][StringGrid1->RowCount - 1] = texto;
						StringGrid1->RowCount = StringGrid1->RowCount + 1;
					}
					else if(Tabla.LeerDinArray(i, j) == 'X')
					{
						texto = AniadirSimbolos(CalcularCadena(CalcularBinario(i, Tabla.NumEntradas())), false);
						StringGrid2->Cells[j][StringGrid2->RowCount - 1] = texto;
						StringGrid2->RowCount = StringGrid2->RowCount + 1;
					}
				}
				else						// POS
				{
					texto = AniadirSimbolos(CalcularCadena(CalcularBinario(i, Tabla.NumEntradas())), true);
					texto = InvertirVariables(texto);
					if(Tabla.LeerDinArray(i, j) == '0')
					{
						StringGrid1->Cells[j][StringGrid1->RowCount - 1] = texto;
						StringGrid1->RowCount = StringGrid1->RowCount + 1;
					}

					if(Tabla.LeerDinArray(i, j) == 'X')
					{
						StringGrid2->Cells[j][StringGrid2->RowCount - 1] = texto;
						StringGrid2->RowCount = StringGrid2->RowCount + 1;
					}
				}
			}
		}
	}

	// Colocamos el Grid en la posición correcta
	numFuncion = 1;
	ScrollBar1->Position = 1;
	StringGrid1->LeftCol = 0;
	StringGrid2->LeftCol = 0;
	Funcion->Caption = numFuncion;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid1Click(TObject *Sender)
{
	StringGrid1->LeftCol = numFuncion - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid1DblClick(TObject *Sender)
{
	StringGrid1->LeftCol = numFuncion - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posición adecuada
	numFuncion = ScrollBar1->Position;
	Funcion->Caption = numFuncion;
	StringGrid1->TopRow = 0;
	StringGrid2->TopRow = 0;
	StringGrid1->LeftCol = numFuncion - 1;
	StringGrid2->LeftCol = numFuncion - 1;
	StringGrid1->Col = numFuncion - 1;
	StringGrid1->Row = 0;
	StringGrid2->Col = numFuncion - 1;
	StringGrid2->Row = 0;

	/*~~~~~~*/
	int i = 1;
	/*~~~~~~*/

	while(StringGrid1->Cells[numFuncion - 1][i - 1] != "")
	{
		i = i + 1;
	}

	StringGrid1->RowCount = i;

	i = 1;
	while(StringGrid2->Cells[numFuncion - 1][i - 1] != "")
	{
		i = i + 1;
	}

	StringGrid2->RowCount = i;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid2Click(TObject *Sender)
{
	StringGrid2->LeftCol = numFuncion - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid2DblClick(TObject *Sender)
{
	StringGrid2->LeftCol = numFuncion - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::Edit2KeyPress(TObject *Sender, char &Key)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	texto, letras, varAnterior, signoAnterior;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si se pulsa el RETURN
	if(Key == 13)
	{
		texto = '(';
		letras = "";
		varAnterior = char(('A' - 1));
		signoAnterior = char(('A' - 1));

		/*~~~~~~~~~~~~~~~~~~*/
		bool	fallo = false;
		/*~~~~~~~~~~~~~~~~~~*/

		// comprobamos todas los caracteres de la caja de texto
		for(int i = 1; i <= Edit2->Text.Length(); i++)
		{
			// ponemos las letras en mayusculas
			if((Edit2->Text[i] >= 'a') & (Edit2->Text[i] <= 'z'))
				letras = letras + (char((Edit2->Text[i] - 32)));

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			// si es una letra
			AnsiString	limite = char(('A' - 1 + Tabla.NumEntradas()));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((letras.SubString(i, 1) >= "A") & (letras.SubString(i, 1) <= limite))
			{
				// y esta dentro de los parametros correctos
				if(letras.SubString(i, 1) > varAnterior)
				{
					// introducir el caracter en el texto y '+' o '*'
					if(Disyuntivo->Checked)
						texto = texto + letras.SubString(i, 1) + "+";
					else
						texto = texto + letras.SubString(i, 1) + "*";
					varAnterior = letras.SubString(i, 1);
					signoAnterior = letras.SubString(i, 1);
				}
				else
				{
					// error: variable en orden incorrecto o duplicada
					fallo = true;
					ShowMessage("error: variable en orden incorrecto o duplicada");
				}
			}

			// si es un simbolo
			else if(Edit2->Text[i] == '-')
			{
				letras = letras + "-";

				// y esta colocado de forma correcta (solo uno ante cada variable)
				if(signoAnterior != '-')
				{
					// introducir caracter 126 en el texto
					texto = texto + "~";
					signoAnterior = '-';
				}
				else
				{
					// error: sobra un simbolo '-'
					fallo = true;
					ShowMessage("error: sobra un simbolo '-'");
				}
			}
			else
			{
				// error: varible de entrada erronea
				fallo = true;
				ShowMessage("error: varible de entrada erronea");
			}
		}

		// si el ultimo simbolo es '-' es un error
		if((signoAnterior == '-') & (!fallo))
		{
			fallo = true;
			ShowMessage("error: '-' no esta en un lugar correcto");
		}
		else
		{
			if(Disyuntivo->Checked)
				texto = texto.SubString(0, texto.Length() - 1) + ")*";
			else
				texto = texto.SubString(0, texto.Length() - 1) + ")+";
		}

		// comprobar que la combinación no se encuentra en la lista
		if(!fallo)
		{
			for(int i = 0; i < StringGrid2->RowCount; i++)
			{
				if(StringGrid2->Cells[(StringGrid2->LeftCol)][i] == texto)
				{
					fallo = true;
					ShowMessage("combinación ya existente");
					break;
				}
			}

			// y entonces introducirlo en ella
			if(!fallo)
			{
				StringGrid2->Cells[StringGrid2->LeftCol][StringGrid2->RowCount - 1] = texto;
				if(StringGrid2->RowCount > 3) StringGrid2->TopRow = StringGrid2->RowCount - 4;
				Edit2->Text = "";
				StringGrid2->RowCount = StringGrid2->RowCount + 1;
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::EvaluarClick(TObject *Sender)
{
	// inicializamos el objeto Tabla con ceros o unos
	for(int i = 0; i < Tabla.NumFilas(); i++)
	{
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			if(SCFormasCompactas->Disyuntivo->Checked)
			{
				Tabla.EscribirDinArray(i, j, 'X');
			}
			else
				Tabla.EscribirDinArray(i, j, '0');
		}
	}

	/*
	 * introducimos los valores de cada funcion en el objeto Tabla comprobando que tan
	 * solo se asigna un valor a cada posición y sacando una advertencia en caso
	 * contrario, persistiendo la X sobre los unos o ceros
	 */
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~*/
		int i = 0;
		/*~~~~~~*/

		StringGrid2->RowCount = i + 1;
		while(StringGrid2->Cells[j][i] != "")
		{
			if(Disyuntivo->Checked)
			{
				TratarCadena((InvertirVariables(StringGrid2->Cells[j][i])), j, '1');
			}
			else
			{
				TratarCadena((StringGrid2->Cells[j][i]), j, 'X');
			}

			i = i + 1;
			StringGrid2->RowCount = i + 1;
		}
	}

	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~*/
		int i = 0;
		/*~~~~~~*/

		StringGrid1->RowCount = i + 1;
		while(StringGrid1->Cells[j][i] != "")
		{
			if(Disyuntivo->Checked)
				TratarCadena((InvertirVariables(StringGrid1->Cells[j][i])), j, '0');
			else
				TratarCadena((StringGrid1->Cells[j][i]), j, '1');
			i = i + 1;
			StringGrid1->RowCount = i + 1;
		}
	}

	// colocamos el grid en la posicion correcta
	numFuncion = ScrollBar1->Position;
	Funcion->Caption = numFuncion;
	StringGrid1->TopRow = 0;
	StringGrid2->TopRow = 0;
	StringGrid1->LeftCol = numFuncion - 1;
	StringGrid2->LeftCol = numFuncion - 1;

	/*~~~~~~*/
	int i = 1;
	/*~~~~~~*/

	while(StringGrid1->Cells[numFuncion - 1][i - 1] != "")
	{
		i = i + 1;
	}

	StringGrid1->RowCount = i;
	i = 1;
	while(StringGrid2->Cells[numFuncion - 1][i - 1] != "")
	{
		i = i + 1;
	}

	StringGrid2->RowCount = i;

	ShowMessage("Sistema combinacional guardado");
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::BorrarClick(TObject *Sender)
{
	// borramos los valores de todas las funciones, no del objeto Tabla
	for(int j = 0; j < (StringGrid1->ColCount); j++)
	{
		StringGrid1->TopRow = 0;
		StringGrid2->TopRow = 0;
		StringGrid1->LeftCol = j;
		StringGrid2->LeftCol = j;

		/*~~~~~~*/
		int i = 1;
		/*~~~~~~*/
		{
			while(StringGrid1->Cells[j][i - 1] != "")
			{
				i = i + 1;
			}

			StringGrid1->RowCount = i;

			i = 1;
			while(StringGrid2->Cells[j][i - 1] != "")
			{
				i = i + 1;
			}

			StringGrid2->RowCount = i;
		}

		while(StringGrid1->Cells[j][0] != "")
		{
			StringGrid1->Cells[j][StringGrid1->RowCount - 2] = "";
			StringGrid1->RowCount = StringGrid1->RowCount - 1;
		}

		while(StringGrid2->Cells[j][0] != "")
		{
			StringGrid2->Cells[j][StringGrid2->RowCount - 2] = "";
			StringGrid2->RowCount = StringGrid2->RowCount - 1;
		}
	}

	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid1MouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda se borre su contenido y se ajusten el
	 * resto de las celdas £
	 * calculamos la fila sobre la que se encuentra el ratón, empezando a contar en 0
	 * a partir de la primera comluna y fila válidas
	 */
	int row = (StringGrid1->TopRow + (Y / (24 + 1)));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si estamos sobre una celda la borramos
	if((Button==mbRight) &&(row < StringGrid1->RowCount - 1) && (StringGrid1->RowCount > 1))
	{
		StringGrid1->Cells[StringGrid1->LeftCol][row] = "";
		for(int i = row + 1; i < StringGrid1->RowCount; i++)
		{
			StringGrid1->Cells[StringGrid1->LeftCol][i - 1] = StringGrid1->Cells[StringGrid1->LeftCol][i];
		}

		StringGrid1->RowCount = StringGrid1->RowCount - 1;
		StringGrid1->Enabled = false;
		StringGrid1->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid2MouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda se borre su contenido y se ajusten el
	 * resto de las celdas £
	 * calculamos la fila sobre la que se encuentra el ratón, empezando a contar en 0
	 * a partir de la primera comluna y fila válidas
	 */
	int row = (StringGrid2->TopRow + (Y / (24 + 1)));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si estamos sobre una celda la borramos
	if((row < StringGrid2->RowCount - 1) & (StringGrid2->RowCount > 1))
	{
		StringGrid2->Cells[StringGrid2->LeftCol][row] = "";
		for(int i = row + 1; i < StringGrid2->RowCount; i++)
		{
			StringGrid2->Cells[StringGrid2->LeftCol][i - 1] = StringGrid2->Cells[StringGrid2->LeftCol][i];
		}

		StringGrid2->RowCount = StringGrid2->RowCount - 1;
		StringGrid2->Enabled = false;
		StringGrid2->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label1->Hint = Tabla.LeerSalida(numFuncion - 1);
	Label1->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(numFuncion - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 32)
	{
		/*
		 * hacemos que al pulsar el espacio sobre una celda se borre su contenido y se
		 * ajusten el resto de las celdas £
		 * si estamos sobre una celda con contenido la borramos
		 */
		if((StringGrid1->Row < StringGrid1->RowCount - 1) & (StringGrid1->RowCount > 1))
		{
			StringGrid1->Cells[StringGrid1->Col][StringGrid1->Row] = "";
			for(int i = StringGrid1->Row + 1; i < StringGrid1->RowCount; i++)
			{
				StringGrid1->Cells[StringGrid1->Col][i - 1] = StringGrid1->Cells[StringGrid1->Col][i];
			}

			StringGrid1->RowCount = StringGrid1->RowCount - 1;
		}
	}
	else if((Key == 37) & (ScrollBar1->Position != 1))
	{
		ScrollBar1->Position = ScrollBar1->Position - 1;
	}
	else if((Key == 39) & (ScrollBar1->Position != StringGrid1->ColCount))
	{
		ScrollBar1->Position = ScrollBar1->Position + 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	StringGrid1->Col = numFuncion - 1;
	StringGrid2->Col = numFuncion - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == 32)
	{
		/*
		 * hacemos que al pulsar el espacio sobre una celda se borre su contenido y se
		 * ajusten el resto de las celdas £
		 * si estamos sobre una celda con contenido la borramos
		 */
		if((StringGrid2->Row < StringGrid2->RowCount - 1) & (StringGrid2->RowCount > 1))
		{
			StringGrid2->Cells[StringGrid2->Col][StringGrid2->Row] = "";
			for(int i = StringGrid2->Row + 1; i < StringGrid2->RowCount; i++)
			{
				StringGrid2->Cells[StringGrid2->Col][i - 1] = StringGrid2->Cells[StringGrid2->Col][i];
			}

			StringGrid2->RowCount = StringGrid2->RowCount - 1;
		}
	}
	else if((Key == 37) & (ScrollBar1->Position != 1))
	{
		ScrollBar1->Position = ScrollBar1->Position - 1;
	}
	else if((Key == 39) & (ScrollBar1->Position != StringGrid2->ColCount))
	{
		ScrollBar1->Position = ScrollBar1->Position + 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::StringGrid2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	StringGrid1->Col = numFuncion - 1;
	StringGrid2->Col = numFuncion - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::Button1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	extern vector<bool> ocultarNANDNOR;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	NANDyNOR->StringGrid->ColCount = Tabla.NumColumnas();
	NANDyNOR->ScrollBar1->Max = Tabla.NumColumnas();

	// metemos las cadenas en el StringGrid Este tratamiento es las funciones y las "X"
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~*/
		int i = 0;
		/*~~~~~~*/

		NANDyNOR->StringGrid->Cells[j][0] = "";
		NANDyNOR->StringGrid->Cells[j][1] = "";
		while(StringGrid1->Cells[j][i] != "")
		{
			NANDyNOR->StringGrid->Cells[j][0] = NANDyNOR->StringGrid->Cells[j][0] + StringGrid1->Cells[j][i];
			i = i + 1;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	temp = NANDyNOR->StringGrid->Cells[j][0];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		temp.Delete(temp.Length(), 1);
		NANDyNOR->StringGrid->Cells[j][0] = temp;
		NANDyNOR->StringGrid->Cells[j][2] = temp;

		i = 0;
		while(StringGrid2->Cells[j][i] != "")
		{
			NANDyNOR->StringGrid->Cells[j][1] = NANDyNOR->StringGrid->Cells[j][1] + StringGrid2->Cells[j][i];
			i = i + 1;
		}

		temp = NANDyNOR->StringGrid->Cells[j][1];
		temp.Delete(temp.Length(), 1);
		NANDyNOR->StringGrid->Cells[j][1] = temp;
		NANDyNOR->StringGrid->Cells[j][3] = temp;
	}

 	ocultarNANDNOR.clear();

	/*~~~~~~~~~~~~~*/
	AnsiString	temp;
	/*~~~~~~~~~~~~~*/

	if(Disyuntivo->Checked == true)
	{
		// POS
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			temp = NANDyNOR->StringGrid->Cells[j][0];
			if(Trim(temp).AnsiPos("*"))
				ocultarNANDNOR.push_back(false);
			else
				ocultarNANDNOR.push_back(true);
			if(Trim(NANDyNOR->StringGrid->Cells[j][0]) != "")
			{
				// Estas llamadas son para NOR - funciones
				temp = NANDyNOR->StringGrid->Cells[j][0];
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, true);
				temp.Insert("~(", 1);
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][2] = temp;

				// Hacemos el cambio a Expresion NAND - funciones
				temp = NANDyNOR->StringGrid->Cells[j][0];
				temp = InvertirVariables(temp);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, false);
				temp.Insert("~(~(", 1);
				temp.Insert(")", temp.Length());
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][0] = temp;

				// Ahora hay que escribirlo en su formulario
			}
			else
			{
				NANDyNOR->StringGrid->Cells[j][0] = "";
			}

			temp = NANDyNOR->StringGrid->Cells[j][1];
			if(Trim(NANDyNOR->StringGrid->Cells[j][1]) != "")
			{
				// Estas llamadas son para NOR - "X"
				temp = NANDyNOR->StringGrid->Cells[j][1];
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, true);
				temp.Insert("~(", 1);
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][3] = temp;

				//
				// Ahora hay que escribirlo en su formulario
				// Hacemos el cambio a Espresion NAND - "X"
				//
				temp = NANDyNOR->StringGrid->Cells[j][1];
				temp = InvertirVariables(temp);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, false);
				temp.Insert("~(~(", 1);
				temp.Insert(")", temp.Length());
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][1] = temp;
			}
			else
			{
				NANDyNOR->StringGrid->Cells[j][1] = "";
			}
		}
	}
	else	// Ahora hacemos tratamiento de la expresion SOP
	{
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			temp = NANDyNOR->StringGrid->Cells[j][0];
 			if(Trim(temp).AnsiPos("+"))
				ocultarNANDNOR.push_back(false);
			else
				ocultarNANDNOR.push_back(true);
			if(Trim(NANDyNOR->StringGrid->Cells[j][0]) != "")
			{
				// Estas llamadas son para NOR - funciones
				temp = NANDyNOR->StringGrid->Cells[j][0];
				temp = InvertirVariables(temp);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, false);
				temp.Insert("~(~(", 1);
				temp.Insert(")", temp.Length());
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][2] = temp;

				//
				// Ahora hay que escribirlo en su formulario
				// Hacemos el cambio a Espresion NAND - funciones
				//
				temp = NANDyNOR->StringGrid->Cells[j][0];
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, true);
				temp.Insert("~(", 1);
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][0] = temp;

				// Ahora hay que escribirlo en su formulario
			}
			else
			{
				NANDyNOR->StringGrid->Cells[j][0] = "";
			}

			temp = NANDyNOR->StringGrid->Cells[j][1];
			if(Trim(NANDyNOR->StringGrid->Cells[j][1]) != "")
			{
				// Estas llamadas son para NOR - "X"
				temp = NANDyNOR->StringGrid->Cells[j][1];
				temp = InvertirVariables(temp);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, false);
				temp.Insert("~(~(", 1);
				temp.Insert(")", temp.Length());
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][3] = temp;

				// Hacemos el cambio a Espresion NAND - "X"
				temp = NANDyNOR->StringGrid->Cells[j][1];
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, true);
				temp.Insert("~(", 1);
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][1] = temp;
			}
			else
			{
				NANDyNOR->StringGrid->Cells[j][1] = "";
			}
		}
	}

	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		NANDyNOR->StringGrid->Cells[j][0] = NombresCompletos(NANDyNOR->StringGrid->Cells[j][0]);
		NANDyNOR->StringGrid->Cells[j][2] = NombresCompletos(NANDyNOR->StringGrid->Cells[j][2]);
		NANDyNOR->StringGrid->Cells[j][1] = NombresCompletos(NANDyNOR->StringGrid->Cells[j][1]);
		NANDyNOR->StringGrid->Cells[j][3] = NombresCompletos(NANDyNOR->StringGrid->Cells[j][3]);
	}

	NANDyNOR->Exp->Checked = false;
	NANDyNOR->ShowModal();

	// SCFormasCompactas->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::BitBtn1Click(TObject *Sender)
{
	// inicializamos el objeto Tabla con ceros o unos
	for(int i = 0; i < Tabla.NumFilas(); i++)
	{
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			if(SCFormasCompactas->Disyuntivo->Checked)
			{
				Tabla.EscribirDinArray(i, j, '1');
			}
			else
				Tabla.EscribirDinArray(i, j, '0');
		}
	}

	/*
	 * introducimos los valores de cada funcion en el objeto Tabla comprobando que tan
	 * solo se asigna un valor a cada posición y sacando una advertencia en caso
	 * contrario, persistiendo la X sobre los unos o ceros
	 */
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~*/
		int i = 0;
		/*~~~~~~*/

		StringGrid2->RowCount = i + 1;
		while(StringGrid2->Cells[j][i] != "")
		{
			if(Disyuntivo->Checked)
			{
				TratarCadena((InvertirVariables(StringGrid2->Cells[j][i])), j, 'X');
			}
			else
			{
				TratarCadena((StringGrid2->Cells[j][i]), j, 'X');
			}

			i = i + 1;
			StringGrid2->RowCount = i + 1;
		}
	}

	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~*/
		int i = 0;
		/*~~~~~~*/

		StringGrid1->RowCount = i + 1;
		while(StringGrid1->Cells[j][i] != "")
		{
			if(Disyuntivo->Checked)
				TratarCadena((InvertirVariables(StringGrid1->Cells[j][i])), j, '0');
			else
				TratarCadena((StringGrid1->Cells[j][i]), j, '1');
			i = i + 1;
			StringGrid1->RowCount = i + 1;
		}
	}

	// colocamos el grid en la posicion correcta
	numFuncion = ScrollBar1->Position;
	Funcion->Caption = numFuncion;
	StringGrid1->TopRow = 0;
	StringGrid2->TopRow = 0;
	StringGrid1->LeftCol = numFuncion - 1;
	StringGrid2->LeftCol = numFuncion - 1;

	/*~~~~~~*/
	int i = 1;
	/*~~~~~~*/

	while(StringGrid1->Cells[numFuncion - 1][i - 1] != "")
	{
		i = i + 1;
	}

	StringGrid1->RowCount = i;
	i = 1;
	while(StringGrid2->Cells[numFuncion - 1][i - 1] != "")
	{
		i = i + 1;
	}

	StringGrid2->RowCount = i;

	ShowMessage("Sistema combinacional guardado");
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::BitBtn2Click(TObject *Sender)
{
	// borramos los valores de todas las funciones, no del objeto Tabla
	for(int j = 0; j < (StringGrid1->ColCount); j++)
	{
		StringGrid1->TopRow = 0;
		StringGrid2->TopRow = 0;
		StringGrid1->LeftCol = j;
		StringGrid2->LeftCol = j;

		/*~~~~~~*/
		int i = 1;
		/*~~~~~~*/
		{
			while(StringGrid1->Cells[j][i - 1] != "")
			{
				i = i + 1;
			}

			StringGrid1->RowCount = i;

			i = 1;
			while(StringGrid2->Cells[j][i - 1] != "")
			{
				i = i + 1;
			}

			StringGrid2->RowCount = i;
		}

		while(StringGrid1->Cells[j][0] != "")
		{
			StringGrid1->Cells[j][StringGrid1->RowCount - 2] = "";
			StringGrid1->RowCount = StringGrid1->RowCount - 1;
		}

		while(StringGrid2->Cells[j][0] != "")
		{
			StringGrid2->Cells[j][StringGrid2->RowCount - 2] = "";
			StringGrid2->RowCount = StringGrid2->RowCount - 1;
		}
	}

	ScrollBar1->Position = 1;
	StringGrid1->LeftCol = 0;
	StringGrid2->LeftCol = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::BitBtn3Click(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	SCFormasCompactas->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::BitBtn4Click(TObject *Sender)
{
	if(Conjuntivo->Checked == true)
	{
		ShowMessage("Para introducir una combinación tan solo hace falta introducir las letras que representan las variables sin signos ni parentesis usando el guión '-' como simbolo de negación, y aunque no es necesario que aparezcan todas deben escribirse en orden ascendente.	Ej: a-cd => (A*~C*D)");
	}
	else
	{
		ShowMessage("Para introducir una combinación tan solo hace falta introducir las letras que representan las variables sin signos ni parentesis usando el guión '-' como simbolo de negación, y aunque no es necesario que aparezcan todas deben escribirse en orden ascendente.	Ej: a-cd => (A+~C+D)");
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::VisualizarClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// Modificado
	AnsiString	ecuacion = "";
	int			numCol = StringGrid1->RowCount - 1; // estan cambiadas las filas por las columnas.
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for(int i = 0; i < numCol; i++)
		ecuacion = ecuacion + (AnsiString) StringGrid1->Cells[ScrollBar1->Position - 1][i];

	ecuacion = ecuacion.SubString(1, ecuacion.Length() - 1);

	if(ecuacion == "")
	{
		Visualizar->Enabled = false;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	m = "No se puede visualizar un circuito vacío.";
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		MessageDlg(m, mtError, TMsgDlgButtons() << mbOK, 0);
	}
	else
	{
		if(SCFormasCompactas->Conjuntivo->Checked == true)
			FormR->Titulo = "Circuito Combinacional SOP.";
		else if(SCFormasCompactas->Disyuntivo->Checked == true)
			FormR->Titulo = "Circuito Combinacional POS.";

		FormR->ecuacion->Text = Tabla.LeerSalida(ScrollBar1->Position - 1) + "=" + ecuacion;

		// FormR->Lista->Items->Add (FormR->Edit6->Text);
		FormR->tipoCircuito = false;				// Circuito Combinacional.
		FormR->ShowModal();
	}	// end-else
	// Modificado
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TSCFormasCompactas::FormHide(TObject *Sender)
{
	// Modificado
	Visualizar->Enabled = true;

	// Modificado
}
