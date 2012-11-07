/*$T boole/Boole1/TVComple.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "Main.h"
#include <math.h>
#include "DinArray.h"
#include "TVComple.h"
#include "NuevoSC.h"
#include "mensajes.inc"
extern DinArray			Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TTablaVerdadCompleta	*TablaVerdadCompleta;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TTablaVerdadCompleta::TTablaVerdadCompleta(TComponent *Owner) :
	TForm(Owner)
{
}

long	numero = 0;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::SalirClick(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	TablaVerdadCompleta->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::FormShow(TObject *Sender)
{
	// preparamos la matriz que muestra los valores de entrada
	StringGridEntrada->ColCount = Tabla.NumEntradas() + 1;
	StringGridEntrada->RowCount = Tabla.NumFilas() + 1;

	// y la que indica los valores de las funciones de salida
	StringGridSalida->ColCount = Tabla.NumColumnas();
	StringGridSalida->RowCount = Tabla.NumFilas() + 1;

	// colocamos los nombres (simplificados) de las varibles de entrada
	for(int i = 1; i < StringGridEntrada->ColCount; i++)
	{
        	AnsiString nomVarEnt;

                nomVarEnt=Tabla.LeerEntrada(i-1);
                if (nomVarEnt=="")
                	nomVarEnt = char('A' + i - 1);
		StringGridEntrada->Cells[i][0] = nomVarEnt;
	}

	// colocamos el valor decimal de la representación binaria de las var. de entrada
	for(int i = 1; i < StringGridEntrada->RowCount; i++)
	{
		StringGridEntrada->Cells[0][i] = i - 1;
	}

	// colocamos todas las posibles combinaciones de las varibles de entrada
	for(int j = 1; j < StringGridEntrada->ColCount; j++)
	{
		for(int i = 1; i < StringGridEntrada->RowCount; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int valor = (i - 1) / (pow(2, (StringGridEntrada->ColCount - j - 1)));
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			StringGridEntrada->Cells[j][i] = valor % 2;
		}
	}

	// colocamos los nombres (simplificados) de las variables de salida
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	nomVarSal = Tabla.LeerSalida(j);
		/*~~~~~~~~~~~~~~~~~~~~~*/
		if (nomVarSal == "")
                	nomVarSal = "F" + AnsiString(j + 1);
		StringGridSalida->Cells[j][0] = nomVarSal;
	}

	// rellenamos los valores de la tabla de salida
	for(int i = 0; i < Tabla.NumFilas(); i++)
	{
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			StringGridSalida->Cells[j][i + 1] = Tabla.LeerDinArray(i, j);
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::EvaluarClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~*/
	// se comprueba que no hay valores extraños en la matriz
	bool	error = false;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			StringGridSalida->Cells[j][i] = Trim(StringGridSalida->Cells[j][i]);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	*valor = StringGridSalida->Cells[j][i].c_str();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((*valor != '0') & (*valor != '1') & (*valor != 'X'))
			{
				error = true;
				Application->MessageBox(MENSAJE(msgErrorTabla), NULL);

				// si hay algún dato erroneo colocamos el cursor sobre él
				StringGridSalida->Row = i;
				StringGridSalida->Col = j;
				break;
			}
			else
				StringGridSalida->Cells[j][i] = *valor;
		}

		if(error) break;
	}

	// si todos los valores son correctos se guardan en el objeto
	if(!error)
	{
		for(int i = 1; i < StringGridSalida->RowCount; i++)
		{
			for(int j = 0; j < StringGridSalida->ColCount; j++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				char	*valor = StringGridSalida->Cells[j][i].c_str();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				Tabla.EscribirDinArray(i - 1, j, *valor);
			}
		}

		// el objeto se guarda en el fichero
		Application->MessageBox(MENSAJE(msgSCGuardado), "");
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::BorrarClick(TObject *Sender)
{
	// borramos los valores de todas las variables de salida, no el objeto Tabla
	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			StringGridSalida->Cells[j][i] = ' ';
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::libresClick(TObject *Sender)
{
	// rellenamos las celdas no validas de la tabla de salida con 'X'
	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			if((Trim(StringGridSalida->Cells[j][i]) != '0') & (Trim(StringGridSalida->Cells[j][i]) != '1'))
				StringGridSalida->Cells[j][i] = 'X';
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::cerosClick(TObject *Sender)
{
	// rellenamos las celdas no validas de la tabla de salida con '0'
	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			if((Trim(StringGridSalida->Cells[j][i]) != '1') & (Trim(StringGridSalida->Cells[j][i]) != 'X'))
				StringGridSalida->Cells[j][i] = '0';
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::unosClick(TObject *Sender)
{
	// rellenamos las celdas no validas de la tabla de salida con '1'
	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			if((Trim(StringGridSalida->Cells[j][i]) != '0') & (Trim(StringGridSalida->Cells[j][i]) != 'X'))
				StringGridSalida->Cells[j][i] = '1';
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::StringGridSalidaTopLeftChanged(TObject *Sender)
{
	// sincronizamos las barras de scroll de ambos Grids
	StringGridEntrada->TopRow = StringGridSalida->TopRow;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::StringGridEntradaTopLeftChanged(TObject *Sender)
{
	// sincronizamos las barras de scroll de ambos Grids
	StringGridSalida->TopRow = StringGridEntrada->TopRow;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::StringGridEntradaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * calculamos la columna sobre la que se encuentra el ratón, empezando a contar en
	 * 0 desde la primera columna válida de la matriz
	 */
	int posicion = (StringGridEntrada->LeftCol + (X / (StringGridEntrada->DefaultColWidth + 1))) - 2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si la posición corresponde a la fila de varibles de entrada y es valida
	if((Y < StringGridEntrada->DefaultRowHeight) & (posicion >= 0) & (posicion < Tabla.NumEntradas()))
	{
		// asignamos al HINT el texto que le corresponde en función a su posición
		StringGridEntrada->Hint = Tabla.LeerEntrada(posicion);
		StringGridEntrada->ShowHint = true;
	}
	else
	{
		StringGridEntrada->ShowHint = false;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::StringGridSalidaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * calculamos la columna sobre la que se encuentra el ratón, empezando a contar en
	 * 0
	 */
	int posicion = (StringGridSalida->LeftCol + (X / (StringGridSalida->DefaultColWidth + 1)));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si la posición corresponde a la fila de varibles de salida y es valida
	if((Y < StringGridSalida->DefaultRowHeight) & (posicion >= 0) & (posicion < Tabla.NumColumnas()))
	{
		// asignamos al HINT el texto que le corresponde en función a su posición
		StringGridSalida->Hint = Tabla.LeerSalida(posicion);
		StringGridSalida->ShowHint = true;
	}
	else
	{
		StringGridSalida->ShowHint = false;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::StringGridSalidaMouseDown
(
	TObject			*Sender,
	TMouseButton	Button,
	TShiftState		Shift,
	int				X,
	int				Y
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda de salida se vayan alternando los
	 * posibles valores que puede tomar £
	 * calculamos la columna y fila sobre la que se encuentra el ratón, empezando a
	 * contar en 0 a partir de la primera comluna y fila válidas
	 */
	int Col = (StringGridSalida->LeftCol + (X / (40 + 1)));
	int Row = (StringGridSalida->TopRow + (Y / (20 + 1)) - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si estamos sobre una celda la modificamos adecuadamente
	if((Col < Tabla.NumColumnas()) & (Row > 0) & (Row <= Tabla.NumFilas()))
	{
		/*~~~~~~~~~~~~~~~*/
		AnsiString	cadena;
		/*~~~~~~~~~~~~~~~*/

		cadena = StringGridSalida->Cells[Col][Row];
		cadena = cadena.SubString(1, 1);
		if(cadena == " ")
		{
			StringGridSalida->Cells[Col][Row] = '0';
		}
		else if(cadena == '0')
		{
			StringGridSalida->Cells[Col][Row] = '1';
		}
		else if(cadena == '1')
		{
			StringGridSalida->Cells[Col][Row] = 'X';
		}
		else
		{
			StringGridSalida->Cells[Col][Row] = " ";
		}

		StringGridSalida->Enabled = false;
		StringGridSalida->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::BitBtn1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~*/
	// se comprueba que no hay valores extraños en la matriz
	bool	error = false;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			StringGridSalida->Cells[j][i] = Trim(StringGridSalida->Cells[j][i]);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			char	*valor = StringGridSalida->Cells[j][i].c_str();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((*valor != '0') & (*valor != '1') & (*valor != 'X'))
			{
				error = true;
				Application->MessageBox(MENSAJE(msgErrorTabla), NULL);

				// si hay algún dato erroneo colocamos el cursor sobre él
				StringGridSalida->Row = i;
				StringGridSalida->Col = j;
				break;
			}
			else
				StringGridSalida->Cells[j][i] = *valor;
		}

		if(error) break;
	}

	// si todos los valores son correctos se guardan en el objeto
	if(!error)
	{
		for(int i = 1; i < StringGridSalida->RowCount; i++)
		{
			for(int j = 0; j < StringGridSalida->ColCount; j++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				char	*valor = StringGridSalida->Cells[j][i].c_str();
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				Tabla.EscribirDinArray(i - 1, j, *valor);
			}
		}

		// el objeto se guarda en el fichero
		Application->MessageBox(MENSAJE(msgSCGuardado), "");
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::BitBtn3Click(TObject *Sender)
{
	// borramos los valores de todas las variables de salida, no el objeto Tabla
	for(int i = 1; i < StringGridSalida->RowCount; i++)
	{
		for(int j = 0; j < StringGridSalida->ColCount; j++)
		{
			StringGridSalida->Cells[j][i] = ' ';
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TTablaVerdadCompleta::BitBtn2Click(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	TablaVerdadCompleta->Hide();
}
