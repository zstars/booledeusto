/*$T boole/Boole1/TVManual.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "NuevoSC.h"
#include "TVManual.h"
#include "DinArray.h"
#include "Math.h"
#include "Libreria.h"
#include "mensajes.inc"
extern DinArray		Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TTablaVerdadManual	*TablaVerdadManual;

//
// =======================================================================================================================
//    devuelve el valor decimal de una cadena binaria
// =======================================================================================================================
//
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
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void FRecursiva(AnsiString cadent, AnsiString cadsal, AnsiString salida, int pos)
{
	if(pos > cadent.Length())
	{
		salida = TrimLeft(salida);

		/*~~~~~~~~~~~~~~~~~~~~*/
		int i = binario(cadsal);
		/*~~~~~~~~~~~~~~~~~~~~*/

		for(int j = 1; j <= salida.Length(); j++)
		{
			if
			(
				(Tabla.LeerDinArray(i, j - 1) != ' ') &
					(Tabla.LeerDinArray(i, j - 1) != *(salida.SubString(j, 1)).c_str())
			) Application->MessageBox(MENSAJE(msgSobreescribeFuncion), NULL);
			Tabla.EscribirDinArray(i, j - 1, *(salida.SubString(j, 1)).c_str());
		}
	}
	else
	{
		if((cadent.SubString(pos, 1) == '0') | (cadent.SubString(pos, 1) == '1'))
		{
			cadsal = cadsal + cadent.SubString(pos, 1);
			FRecursiva(cadent, cadsal, salida, pos + 1);
		}
		else
		{
			/*~~~~~~~~~~~*/
			int cont = pos;
			/*~~~~~~~~~~~*/

			FRecursiva(cadent, cadsal + "0", salida, cont + 1);
			cont = pos;
			FRecursiva(cadent, cadsal + "1", salida, cont + 1);
		}
	};
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TTablaVerdadManual::TTablaVerdadManual(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::EvaluarClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	entrada;
	AnsiString	valorsalida;
	/*~~~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i < StringGrid1->RowCount; i++)
	{
		entrada = ' ';
		for(int j = 0; j <= StringGrid1->ColCount; j++)
		{
			entrada = entrada + StringGrid1->Cells[j][i];
		};

		valorsalida = ' ';
		for(int k = 0; k <= StringGrid2->ColCount; k++)
		{
			valorsalida = valorsalida + StringGrid2->Cells[k][i];
		}

		/*~~~~~~~~~~~~~~~~~~~~~*/
		// mostramos la cadena de salida para ese valor de entrada
		AnsiString	salida = ' ';
		int			posicion = 1;
		/*~~~~~~~~~~~~~~~~~~~~~*/

		entrada = TrimLeft(entrada);
		salida = TrimRight(salida);

		//
		// Aqui tenemos que incluir el manejo de las salidas para copiar los datos al
		// objeto Usaremos un bucle for para cada salida y esa combinación de entrada
		//
		FRecursiva(entrada, salida, valorsalida, posicion);
	};
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::FormShow(TObject *Sender)
{
	// ShowMessage (Tabla.NumEntradas()); ShowMessage (Tabla.NumColumnas());
	StringGrid1->ColCount = Tabla.NumEntradas();
	StringGrid2->ColCount = Tabla.NumColumnas();
	StringGrid1->RowCount = 2;
	StringGrid2->RowCount = 2;

	// colocamos los nombres (simplificados) de las varibles de entrada
	for(int i = 0; i < StringGrid1->ColCount; i++)
	{
        	AnsiString nomVarEnt;

                nomVarEnt=Tabla.LeerEntrada(i);
                if (nomVarEnt=="")
                	nomVarEnt = char('A' + i);
		StringGrid1->Cells[i][0] = nomVarEnt;
	}

	// colocamos los nombres (simplificados) de las variables de salida
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	nomVarSal = Tabla.LeerSalida(j);
		/*~~~~~~~~~~~~~~~~~~~~~*/
		if (nomVarSal == "")
                	nomVarSal = "F" + AnsiString(j + 1);
		StringGrid2->Cells[j][0] = nomVarSal;
	}

	// borramos la basura
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		StringGrid2->Cells[j][1] = " ";
	}

	for(int j = 0; j < Tabla.NumEntradas(); j++)
	{
		StringGrid1->Cells[j][1] = " ";
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::Button1Click(TObject *Sender)
{
	// aumentamos el numero de entradas
	if(StringGrid1->RowCount <= Tabla.NumFilas())
	{
		StringGrid1->RowCount = StringGrid1->RowCount + 1;
		StringGrid2->RowCount = StringGrid2->RowCount + 1;
	}
	else
	{
		Application->MessageBox(MENSAJE(msgNoMasEntradas), NULL);
	};
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::SalirClick(TObject *Sender)
{
	// Vaciamos el Grid de los valores de entrada
	StringGrid1->RowCount = 2;
	for(int i = 0; i < StringGrid1->ColCount; i++)
	{
		StringGrid1->Cells[i][StringGrid1->ColCount - 1] = " ";
	}

	// Vaciamos el Grid de los valores de salida
	StringGrid2->RowCount = 2;
	for(int i = 0; i < StringGrid2->ColCount; i++)
	{
		StringGrid1->Cells[i][StringGrid1->ColCount - 1] = " ";
	}

	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	TablaVerdadManual->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::StringGrid1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * calculamos la columna sobre la que se encuentra el ratón, empezando a contar en
	 * 0 desde la primera columna válida de la matriz
	 */
	int posicion = (StringGrid1->LeftCol + (X / (StringGrid1->DefaultColWidth + 1)));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si la posición corresponde a la fila de varibles de entrada y es valida
	if((Y < StringGrid1->DefaultRowHeight) & (posicion >= 0) & (posicion < Tabla.NumEntradas()))
	{
		// asignamos al HINT el texto que le corresponde en función a su posición
		StringGrid1->Hint = Tabla.LeerEntrada(posicion);
		StringGrid1->ShowHint = true;
	}
	else
	{
		StringGrid1->ShowHint = false;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::StringGrid2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * calculamos la columna sobre la que se encuentra el ratón, empezando a contar en
	 * 0 desde la primera columna válida de la matriz
	 */
	int posicion = (StringGrid2->LeftCol + (X / (StringGrid2->DefaultColWidth + 1)));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si la posición corresponde a la fila de varibles de entrada y es valida
	if((Y < StringGrid2->DefaultRowHeight) & (posicion >= 0) & (posicion < Tabla.NumEntradas()))
	{
		// asignamos al HINT el texto que le corresponde en función a su posición
		StringGrid2->Hint = Tabla.LeerSalida(posicion);
		StringGrid2->ShowHint = true;
	}
	else
	{
		StringGrid2->ShowHint = false;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::StringGrid1MouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda de salida se vayan alternando los
	 * posibles valores que puede tomar £
	 * calculamos la columna y fila sobre la que se encuentra el ratón, empezando a
	 * contar en 0 a partir de la primera comluna y fila válidas
	 */
	int Col = (StringGrid1->LeftCol + (X / (40 + 1)));
	int Row = (StringGrid1->TopRow + (Y / (20 + 1)) - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si estamos sobre una celda la modificamos adecuadamente
	if((Col < Tabla.NumEntradas()) & (Row > 0) & (Row <= Tabla.NumFilas()))
	{
		/*~~~~~~~~~~~~~~~*/
		AnsiString	cadena;
		/*~~~~~~~~~~~~~~~*/

		cadena = StringGrid1->Cells[Col][Row];
		cadena = cadena.SubString(1, 1);
		if(cadena == " ")
		{
			StringGrid1->Cells[Col][Row] = '0';
		}
		else if(cadena == '0')
		{
			StringGrid1->Cells[Col][Row] = '1';
		}
		else if(cadena == '1')
		{
			StringGrid1->Cells[Col][Row] = 'X';
		}
		else
		{
			StringGrid1->Cells[Col][Row] = " ";
		}

		StringGrid1->Enabled = false;
		StringGrid1->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::StringGrid2MouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda de salida se vayan alternando los
	 * posibles valores que puede tomar £
	 * calculamos la columna y fila sobre la que se encuentra el ratón, empezando a
	 * contar en 0 a partir de la primera comluna y fila válidas
	 */
	int Col = (StringGrid2->LeftCol + (X / (40 + 1)));
	int Row = (StringGrid2->TopRow + (Y / (20 + 1)) - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si estamos sobre una celda la modificamos adecuadamente
	if((Col < Tabla.NumColumnas()) & (Row > 0) & (Row <= Tabla.NumFilas()))
	{
		/*~~~~~~~~~~~~~~~*/
		AnsiString	cadena;
		/*~~~~~~~~~~~~~~~*/

		cadena = StringGrid2->Cells[Col][Row];
		cadena = cadena.SubString(1, 1);
		if(cadena == " ")
		{
			StringGrid2->Cells[Col][Row] = '0';
		}
		else if(cadena == '0')
		{
			StringGrid2->Cells[Col][Row] = '1';
		}
		else if(cadena == '1')
		{
			StringGrid2->Cells[Col][Row] = 'X';
		}
		else
		{
			StringGrid2->Cells[Col][Row] = " ";
		}

		StringGrid2->Enabled = false;
		StringGrid2->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::StringGrid1TopLeftChanged(TObject *Sender)
{
	StringGrid2->TopRow = StringGrid1->TopRow;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::StringGrid2TopLeftChanged(TObject *Sender)
{
	StringGrid2->TopRow = StringGrid1->TopRow;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::CompletarUnosClick(TObject *Sender)
{
	// Completamos los valores vacios de la tabla con unos
	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		for(int j = 0; j < Tabla.NumFilas(); j++)
		{
			if(Tabla.LeerDinArray(j, i) == ' ')
			{
				Tabla.EscribirDinArray(j, i, '1');
			}

			//
			// Comprobamos si ese valor de la tabla esta vacio o no y en caso de estarlo lo
			// completamos con unos
			//
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::CompletarCerosClick(TObject *Sender)
{
	// Completamos los valores vacios de la tabla con ceros
	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		for(int j = 0; j < Tabla.NumFilas(); j++)
		{
			if(Tabla.LeerDinArray(j, i) == ' ')
			{
				Tabla.EscribirDinArray(j, i, '0');
			}

			//
			// Comprobamos si ese valor de la tabla esta vacio o no y en caso de estarlo lo
			// completamos con ceros
			//
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::CompletarCondLibresClick(TObject *Sender)
{
	// Completamos los valores vacios de la tabla con condiciones libres
	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		for(int j = 0; j < Tabla.NumFilas(); j++)
		{
			if(Tabla.LeerDinArray(j, i) == ' ')
			{
				Tabla.EscribirDinArray(j, i, 'X');
			}

			//
			// Comprobamos si ese valor de la tabla esta vacio o no y en caso de estarlo lo
			// completamos con condiciones libres
			//
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::BorrarClick(TObject *Sender)
{
	// Vaciamos el Grid de los valores de entrada
	StringGrid1->RowCount = 2;
	for(int i = 0; i < StringGrid1->ColCount; i++)
	{
		StringGrid1->Cells[i][StringGrid1->ColCount - 1] = " ";
	}

	// Vaciamos el Grid de los valores de salida
	StringGrid2->RowCount = 2;
	for(int i = 0; i < StringGrid2->ColCount; i++)
	{
		StringGrid1->Cells[i][StringGrid1->ColCount - 1] = " ";
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::BitBtn1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	AnsiString	entrada;
	AnsiString	valorsalida;
	bool		bien = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	// comprobamos que esta completa
	for(int i = 1; i < StringGrid1->RowCount; i++)
	{
		for(int j = 0; j < StringGrid1->ColCount; j++)
		{
			if(Trim(StringGrid1->Cells[j][i]) == "") bien = false;
		}

		for(int j = 0; j < StringGrid2->ColCount; j++)
		{
			if(Trim(StringGrid2->Cells[j][i]) == "") bien = false;
		}
	}

	if(bien)
	{
		// borramos el objeto tabla
		for(int i = 1; i < Tabla.NumFilas(); i++)
		{
			for(int j = 0; j < Tabla.NumColumnas(); j++)
			{
				Tabla.EscribirDinArray(i, j, ' ');
			}
		}

		for(int i = 1; i < StringGrid1->RowCount; i++)
		{
			entrada = ' ';
			for(int j = 0; j <= StringGrid1->ColCount; j++)
			{
				entrada = entrada + StringGrid1->Cells[j][i];
			};

			valorsalida = ' ';
			for(int k = 0; k <= StringGrid2->ColCount; k++)
			{
				valorsalida = valorsalida + StringGrid2->Cells[k][i];
			}

			/*~~~~~~~~~~~~~~~~~~~~~*/
			// mostramos la cadena de salida para ese valor de entrada
			AnsiString	salida = ' ';
			int			posicion = 1;
			/*~~~~~~~~~~~~~~~~~~~~~*/

			entrada = TrimLeft(entrada);
			salida = TrimRight(salida);

			//
			// Aqui tenemos que incluir el manejo de las salidas para copiar los datos al
			// objeto Usaremos un bucle for para cada salida y esa combinación de entrada
			//
			FRecursiva(entrada, salida, valorsalida, posicion);
		}

		// Completamos los valores vacios de la tabla con lo indicado
		for(int i = 0; i < Tabla.NumColumnas(); i++)
		{
			for(int j = 0; j < Tabla.NumFilas(); j++)
			{
				if(Tabla.LeerDinArray(j, i) == ' ')
				{
					if(RadioButton1->Checked)
						Tabla.EscribirDinArray(j, i, '0');
					else if(RadioButton2->Checked)
						Tabla.EscribirDinArray(j, i, '1');
					else
						Tabla.EscribirDinArray(j, i, 'X');
				}

				//
				// Comprobamos si ese valor de la tabla esta vacio o no y en caso de estarlo lo
				// completamos con lo indicado
				//
			}
		}

		Application->MessageBox(MENSAJE(msgSCGuardado), "");
	}
	else
	{
		Application->MessageBox(MENSAJE(msgDatosNoRellenados), NULL);
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::BitBtn3Click(TObject *Sender)
{
	// Vaciamos el Grid de los valores de entrada
	StringGrid1->RowCount = 2;
	for(int i = 0; i < StringGrid1->ColCount; i++)
	{
		StringGrid1->Cells[i][1] = " ";
	}

	// Vaciamos el Grid de los valores de salida
	StringGrid2->RowCount = 2;
	for(int i = 0; i < StringGrid2->ColCount; i++)
	{
		StringGrid1->Cells[i][1] = " ";
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::BitBtn2Click(TObject *Sender)
{
	// Vaciamos el Grid de los valores de entrada
	StringGrid1->RowCount = 2;
	for(int i = 0; i < StringGrid1->ColCount; i++)
	{
		StringGrid1->Cells[i][1] = " ";
	}

	// Vaciamos el Grid de los valores de salida
	StringGrid2->RowCount = 2;
	for(int i = 0; i < StringGrid2->ColCount; i++)
	{
		StringGrid1->Cells[i][1] = " ";
	}

	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	TablaVerdadManual->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::BitBtn4Click(TObject *Sender)
{
	// aumentamos el numero de entradas
	if(StringGrid1->RowCount <= Tabla.NumFilas())
	{
		StringGrid1->RowCount = StringGrid1->RowCount + 1;
		for(int i = 0; i < StringGrid1->ColCount; i++)
		{
			StringGrid1->Cells[i][StringGrid1->RowCount - 1] = " ";
		}

		StringGrid2->RowCount = StringGrid2->RowCount + 1;
		for(int i = 0; i < StringGrid2->ColCount; i++)
		{
			StringGrid2->Cells[i][StringGrid2->RowCount - 1] = " ";
		}
	}
	else
	{
		Application->MessageBox(MENSAJE(msgNoMasEntradas), NULL);
	};
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadManual::BitBtn5Click(TObject *Sender)
{
	// Vaciamos la ultima linea
	if(StringGrid1->RowCount > 2)
	{
		StringGrid1->RowCount = StringGrid1->RowCount - 1;
		StringGrid2->RowCount = StringGrid2->RowCount - 1;
	}
}
