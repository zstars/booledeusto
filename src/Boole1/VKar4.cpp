/*$T boole/Boole1/VKar4.cpp GC! 1.116 05/02/01 18:53:23 */


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
#include "VKar4.h"
#include "mensajes.inc"
extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TVK4			*VK4;

int				numFuncion4 = 1;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TVK4::TVK4(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::FormShow(TObject *Sender)
{
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
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::FuncionLabelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FuncionLabel->Hint = Tabla.LeerSalida(numFuncion4 - 1);
	FuncionLabel->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(numFuncion4 - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posici�n adecuada
	numFuncion4 = ScrollBar1->Position;
	Funcion->Caption = numFuncion4;
	StringGridVK->TopRow = (numFuncion4 - 1) * 4 + 1;
	StringGridVK->Row = (numFuncion4 - 1) * 4 + 1;
	StringGridVK->Col = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::StringGridVKKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if((Key == 38) & (ScrollBar1->Position != 1) & (StringGridVK->Row == (numFuncion4 - 1) * 4 + 1))
	{
		ScrollBar1->Position = ScrollBar1->Position - 1;
		StringGridVK->Row = numFuncion4 * 4;
	}
	else if
		(
			(Key == 40) & (ScrollBar1->Position != StringGridVK->RowCount / 4 + 1) &
				(StringGridVK->Row == numFuncion4 * 4)
		)
	{
		ScrollBar1->Position = ScrollBar1->Position + 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::StringGridVKMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*
	 * hacemos que al pulsar sobre una celda de salida se vayan alternando los
	 * posibles valores que puede tomar �
	 * calculamos la columna y fila sobre la que se encuentra el rat�n, empezando a
	 * contar en 0 a partir de la primera comluna y fila v�lidas
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
void __fastcall TVK4::Button1Click(TObject *Sender)
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
							FusionarCadenas(StringGridVK->Cells[j + 1][0], StringGridVK->Cells[0][i + 1]),
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
void __fastcall TVK4::Button2Click(TObject *Sender)
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
void __fastcall TVK4::SalirClick(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	VK4->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK4::libresClick(TObject *Sender)
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
void __fastcall TVK4::cerosClick(TObject *Sender)
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
void __fastcall TVK4::unosClick(TObject *Sender)
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
void __fastcall TVK4::BitBtn1Click(TObject *Sender)
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
							FusionarCadenas(StringGridVK->Cells[j + 1][0], StringGridVK->Cells[0][i + 1]),
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
void __fastcall TVK4::BitBtn2Click(TObject *Sender)
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
void __fastcall TVK4::BitBtn3Click(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	VK4->Hide();
}
