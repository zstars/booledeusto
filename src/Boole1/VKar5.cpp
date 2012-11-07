/*$T boole/Boole1/VKar5.cpp GC! 1.116 05/02/01 18:53:23 */


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
#include "VKar5.h"
#include "mensajes.inc"
extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TVK5			*VK5;

int				numFuncion5 = 1;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TVK5::TVK5(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::FormShow(TObject *Sender)
{
	StringGridVK->RowCount = Tabla.NumColumnas() * 4 + 1;

	StringGridVK->Cells[1][0] = "000";
	StringGridVK->Cells[2][0] = "100";
	StringGridVK->Cells[3][0] = "110";
	StringGridVK->Cells[4][0] = "010";
	StringGridVK->Cells[5][0] = "011";
	StringGridVK->Cells[6][0] = "111";
	StringGridVK->Cells[7][0] = "101";
	StringGridVK->Cells[8][0] = "001";

	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		StringGridVK->Cells[0][i * 4 + 1] = "00";
		StringGridVK->Cells[0][i * 4 + 2] = "10";
		StringGridVK->Cells[0][i * 4 + 3] = "11";
		StringGridVK->Cells[0][i * 4 + 4] = "01";
	}

	Panel1->Hint = Tabla.LeerEntrada(0);
	Label1->Hint = Tabla.LeerEntrada(0);
	Panel2->Hint = Tabla.LeerEntrada(0);
	Label2->Hint = Tabla.LeerEntrada(0);
	Panel3->Hint = Tabla.LeerEntrada(2);
	Label3->Hint = Tabla.LeerEntrada(2);
	Panel4->Hint = Tabla.LeerEntrada(4);
	Label4->Hint = Tabla.LeerEntrada(4);
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
			for(int j = 0; j < 8; j++)
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
void __fastcall TVK5::StringGridVKMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
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
	if((Col < 9) & (Col > 0) & (Row >= StringGridVK->TopRow))
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
void __fastcall TVK5::StringGridVKKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if((Key == 38) & (ScrollBar1->Position != 1) & (StringGridVK->Row == (numFuncion5 - 1) * 4 + 1))
	{
		ScrollBar1->Position = ScrollBar1->Position - 1;
		StringGridVK->Row = numFuncion5 * 4;
	}
	else if
		(
			(Key == 40) & (ScrollBar1->Position != StringGridVK->RowCount / 4 + 1) &
				(StringGridVK->Row == numFuncion5 * 4)
		)
	{
		ScrollBar1->Position = ScrollBar1->Position + 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::FuncionLabelMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	FuncionLabel->Hint = Tabla.LeerSalida(numFuncion5 - 1);
	FuncionLabel->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(numFuncion5 - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posici�n adecuada
	numFuncion5 = ScrollBar1->Position;
	Funcion->Caption = numFuncion5;
	StringGridVK->TopRow = (numFuncion5 - 1) * 4 + 1;
	StringGridVK->Row = (numFuncion5 - 1) * 4 + 1;
	StringGridVK->Col = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::Button1Click(TObject *Sender)
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
				for(int j = 0; j < 8; j++)
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
void __fastcall TVK5::Button2Click(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 9; j++)
		{
			StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = " ";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::SalirClick(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	VK5->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::libresClick(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 9; j++)
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
void __fastcall TVK5::cerosClick(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 9; j++)
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
void __fastcall TVK5::unosClick(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 9; j++)
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
void __fastcall TVK5::BitBtn1Click(TObject *Sender)
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
				for(int j = 0; j < 8; j++)
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
void __fastcall TVK5::BitBtn2Click(TObject *Sender)
{
	for(int i = 1; i < 5; i++)
	{
		for(int j = 1; j < 9; j++)
		{
			StringGridVK->Cells[j][StringGridVK->TopRow + i - 1] = " ";
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TVK5::BitBtn3Click(TObject *Sender)
{
	// volvemos al form de creacion de un nuevo sistema combinacional
	SistemaCombinacionalNuevo->Show();
	VK5->Hide();
}
