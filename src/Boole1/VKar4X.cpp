/*$T boole/Boole1/VKar4X.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "Main.h"
#include "DinArray.h"
#include "Libreria.h"
#include "NuevoSC.h"
#include "VKar4X.h"
#include "mensajes.inc"
extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TVK4X			*VK4X;

int				numFuncion4X = 1;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TVK4X::TVK4X(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::FormShow(TObject *Sender)
{
	StringGridVK->RowCount = Tabla.NumColumnas() * 4 + 1;

	StringGridVK->Cells[1][0] = "00";
	StringGridVK->Cells[2][0] = "01";
	StringGridVK->Cells[3][0] = "11";
	StringGridVK->Cells[4][0] = "10";

	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		StringGridVK->Cells[0][i * 4 + 1] = "00";
		StringGridVK->Cells[0][i * 4 + 2] = "01";
		StringGridVK->Cells[0][i * 4 + 3] = "11";
		StringGridVK->Cells[0][i * 4 + 4] = "10";
	}

	Label1->Hint = Tabla.LeerEntrada(0);
	Label3->Hint = Tabla.LeerEntrada(2);
	Label5->Hint = Tabla.LeerEntrada(1);
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
						JuntarCadenas(StringGridVK->Cells[j + 1][0], StringGridVK->Cells[0][i + 1]),
						f
					);
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::FuncionLabelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FuncionLabel->Hint = Tabla.LeerSalida(numFuncion4X - 1);
	FuncionLabel->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(numFuncion4X - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posición adecuada
	numFuncion4X = ScrollBar1->Position;
	Funcion->Caption = numFuncion4X;
	StringGridVK->TopRow = (numFuncion4X - 1) * 4 + 1;
	StringGridVK->Row = (numFuncion4X - 1) * 4 + 1;
	StringGridVK->Col = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::StringGridVKKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if((Key == 38) & (ScrollBar1->Position != 1) & (StringGridVK->Row == (numFuncion4X - 1) * 4 + 1))
	{
		ScrollBar1->Position = ScrollBar1->Position - 1;
		StringGridVK->Row = numFuncion4X * 4;
	}
	else if
		(
			(Key == 40) & (ScrollBar1->Position != StringGridVK->RowCount / 4 + 1) &
				(StringGridVK->Row == numFuncion4X * 4)
		)
	{
		ScrollBar1->Position = ScrollBar1->Position + 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::StringGridVKMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda de salida se vayan alternando los
	 * posibles valores que puede tomar £
	 * calculamos la columna y fila sobre la que se encuentra el ratón, empezando a
	 * contar en 0 a partir de la primera comluna y fila válidas
	 */
	int Col = (StringGridVK->LeftCol + (X / (StringGridVK->DefaultColWidth + 1)) - 1);
	int Row = (StringGridVK->TopRow + (Y / (StringGridVK->DefaultRowHeight + 1)) - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	// si estamos sobre una celda la modificamos adecuadamente
	if((Col < 5) & (Col > 0) & (Row >= StringGridVK->TopRow))
	{
		/*~~~~~~~~~~~~~~~*/
		AnsiString	cadena;
		/*~~~~~~~~~~~~~~~*/

		cadena = StringGridVK->Cells[Col][Row];
		cadena = cadena.SubString(1, 1);
		if(cadena == " ")
		{
			StringGridVK->Cells[Col][Row] = '0';
		}
		else if(cadena == "0")
		{
			StringGridVK->Cells[Col][Row] = '1';
		}
		else if(cadena == "1")
		{
			StringGridVK->Cells[Col][Row] = 'X';
		}
		else
		{
			StringGridVK->Cells[Col][Row] = " ";
		}

		StringGridVK->Enabled = false;
		StringGridVK->Enabled = true;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::Button1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~*/
	bool	error = false;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i < StringGridVK->RowCount; i++)
	{
		for(int j = 1; j < StringGridVK->ColCount; j++)
		{
			if(StringGridVK->Cells[j][i] == " ")
			{
				Application->MessageBox(MENSAJE(msgValoresIncorrectos), NULL);
				error = true;
			}

			if(error) break;
		}

		if(error) break;
	}

	if(!error)
	{
		for(int f = 0; f < Tabla.NumColumnas(); f++)
		{
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					Tabla.EscribirDinArray
						(
							JuntarCadenas(StringGridVK->Cells[j + 1][0], StringGridVK->Cells[0][i + 1]),
							f,
							*(StringGridVK->Cells[j + 1][(f * 4) + i + 1]).c_str()
						);
				}
			}
		}

		Application->MessageBox(MENSAJE(msgSCGuardado), "");
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::Button2Click(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 5; j++)
		{
			StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = " ";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::SalirClick(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	VK4X->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::libresClick(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 5; j++)
		{
			if(StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] == " ")
				StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = "X";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::cerosClick(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 5; j++)
		{
			if(StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] == " ")
				StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = "0";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::unosClick(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 5; j++)
		{
			if(StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] == " ")
				StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = "1";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::BitBtn1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~*/
	bool	error = false;
	/*~~~~~~~~~~~~~~~~~~*/

	for(int i = 1; i < StringGridVK->RowCount; i++)
	{
		for(int j = 1; j < StringGridVK->ColCount; j++)
		{
			if(StringGridVK->Cells[j][i] == " ")
			{
				Application->MessageBox(MENSAJE(msgValoresIncorrectos), NULL);
				error = true;
			}

			if(error) break;
		}

		if(error) break;
	}

	if(!error)
	{
		for(int f = 0; f < Tabla.NumColumnas(); f++)
		{
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					Tabla.EscribirDinArray
						(
							JuntarCadenas(StringGridVK->Cells[j + 1][0], StringGridVK->Cells[0][i + 1]),
							f,
							*(StringGridVK->Cells[j + 1][(f * 4) + i + 1]).c_str()
						);
				}
			}
		}

		Application->MessageBox(MENSAJE(msgSCGuardado), "");
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::BitBtn2Click(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 5; j++)
		{
			StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = " ";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4X::BitBtn3Click(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	VK4X->Hide();
}
