/*$T boole/Boole1/FormasN.cpp GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "NuevoSC.h"
#include "Math.h"
#include "DinArray.h"
#include "FormasN.h"
#include "mensajes.inc"
extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TFormasNormales *FormasNormales;

int				numFuncionX = 1;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TFormasNormales::TFormasNormales(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::FormShow(TObject *Sender)
{
	Funcion->Caption = numFuncionX;
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
			if((Tabla.LeerDinArray(i, j) == '1') & (Disyuntivo->Checked == true))
			{
				if(StringGrid1->Cells[j][0] != "") StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0] + ",";
				StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0] + i;
			}
			else if((Tabla.LeerDinArray(i, j) == '0') & (Conjuntivo->Checked == true))
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

	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::SalirClick(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	FormasNormales->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::ScrollBar1Change(TObject *Sender)
{
	// ajustamos el grid a la posición adecuada
	numFuncionX = ScrollBar1->Position;
	Funcion->Caption = numFuncionX;
	StringGrid1->LeftCol = numFuncionX - 1;
	StringGrid2->LeftCol = numFuncionX - 1;
	StringGrid1->Col = numFuncionX - 1;
	StringGrid2->Col = numFuncionX - 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(numFuncionX - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::BorrarClick(TObject *Sender)
{
	// borramos los valores de todas las funciónes
	for(int j = 0; j < StringGrid1->ColCount; j++)
	{
		StringGrid1->Cells[j][0] = "";
		StringGrid2->Cells[j][0] = "";
	}

	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label1->Hint = Tabla.LeerSalida(numFuncionX - 1);
	Label1->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ScrollBar1->Position = StringGrid1->Col + 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::StringGrid2KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ScrollBar1->Position = StringGrid2->Col + 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::EvaluarClick(TObject *Sender)
{
	/*~~~~~~~~~~*/
	int error = 0;
	/*~~~~~~~~~~*/

	// Quitamos todos los blancos
	for(int j = 0; j < StringGrid1->ColCount; j++)
	{
		/*~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	cadena = "";
		int			k = 1;
		/*~~~~~~~~~~~~~~~~~~~~*/

		while(k <= StringGrid1->Cells[j][0].Length())
		{
			if(StringGrid1->Cells[j][0].SubString(k, 1) == " ")
			{
				cadena = StringGrid1->Cells[j][0];
				cadena.Delete(k, 1);
				StringGrid1->Cells[j][0] = cadena;
			}
			else
				k = k + 1;
		}

		/*~~~~~~*/
		int l = 1;
		/*~~~~~~*/

		while(l <= StringGrid2->Cells[j][0].Length())
		{
			if(StringGrid2->Cells[j][0].SubString(l, 1) == " ")
			{
				cadena = StringGrid2->Cells[j][0];
				cadena.Delete(l, 1);
				StringGrid2->Cells[j][0] = cadena;
			}
			else
				l = l + 1;
		}
	}

	//
	// Comprobamos que los valores se encuentran entre los limites establecidos en la
	// función
	//
	for(int j = 0; j < StringGrid1->ColCount; j++)
	{
		StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0].Trim();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	temp, temp2 = "";
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 0; i < StringGrid1->Cells[j][0].Length(); i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	car = StringGrid1->Cells[j][0].SubString(i + 1, 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((car < '0') | (car > '9'))
			{
				if(((car != ",") & (car != ":")) | (temp == ""))
				{
					error = 1;
				}
				else if(temp.ToInt() >= Tabla.NumFilas())
				{
					error = 2;
				}
				else	// si el valor es correcto se borra la var. temporal
				{
					if(car == ":")
					{
						if(temp2 != "")
							error = 3;
						else
							temp2 = temp;
						if(i == StringGrid1->Cells[j][0].Length() - 1) error = 3;
					}
					else
					{
						if((temp2 != "") & (temp2 > temp)) error = 4;
						temp2 = "";
					}

					temp = "";
				}
			}
			else
			{
				temp = temp + car;

				// si es el final no va a haber coma
				if(i == StringGrid1->Cells[j][0].Length() - 1)
				{
					if(temp.ToInt() >= Tabla.NumFilas()) error = 2;
					if((temp2 != "") & (temp2 > temp)) error = 4;
				}
			}

			if(error != 0) break;
		}

		if(error != 0) break;
	}

	// en las X
	for(int j = 0; j < StringGrid2->ColCount; j++)
	{
		StringGrid2->Cells[j][0] = StringGrid2->Cells[j][0].Trim();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	temp, temp2 = "";
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 0; i < StringGrid2->Cells[j][0].Length(); i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	car = StringGrid2->Cells[j][0].SubString(i + 1, 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((car < '0') | (car > '9'))
			{
				if(((car != ",") & (car != ":")) | (temp == ""))
				{
					error = 1;
				}
				else if(temp.ToInt() >= Tabla.NumFilas())
				{
					error = 2;
				}
				else	// si el valor es correcto se borra la var. temporal
				{
					if(car == ":")
					{
						if(temp2 != "")
							error = 3;
						else
							temp2 = temp;
						if(i == StringGrid1->Cells[j][0].Length() - 1) error = 3;
					}
					else
					{
						if((temp2 != "") & (temp2 > temp)) error = 4;
						temp2 = "";
					}

					temp = "";
				}
			}
			else
			{
				temp = temp + car;

				// si es el final no va a haber coma
				if(i == StringGrid2->Cells[j][0].Length() - 1)
				{
					if(temp.ToInt() >= Tabla.NumFilas()) error = 2;
					if((temp2 != "") & (temp2 > temp)) error = 4;
				}
			}

			if(error != 0) break;
		}

		if(error != 0) break;
	}

	if(error == 1) Application->MessageBox(MENSAJE(msgCaracterNoValido), NULL);
	if(error == 2) Application->MessageBox(MENSAJE(msgNoTantasVariables), NULL);
	if(error == 3) Application->MessageBox(MENSAJE(msgCaracterDosPuntos), NULL);
	if(error == 4) Application->MessageBox(MENSAJE(msgRangoErroneo), NULL);

	// si todo esta bien introducimos los valores en el objeto Tabla
	if(error == 0)
	{
		// inicializamos el objeto Tabla con ceros o unos
		for(int i = 0; i < Tabla.NumFilas(); i++)
		{
			for(int j = 0; j < Tabla.NumColumnas(); j++)
			{
				if(FormasNormales->Disyuntivo->Checked)
					Tabla.EscribirDinArray(i, j, '0');
				else
					Tabla.EscribirDinArray(i, j, '1');
			}
		}

		/*
		 * introducimos los valores de cada funcion en el objeto Tabla comprobando que tan
		 * solo se asigna un valor a cada posición y sacando una advertencia en caso
		 * contrario, persistiendo la X sobre los unos o ceros
		 */
		for(int j = 0; j < StringGrid1->ColCount; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	temp, temp2 = "";
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for(int i = 0; i < StringGrid1->Cells[j][0].Length(); i++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	car = StringGrid1->Cells[j][0].SubString(i + 1, 1);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if((car != ",") & (car != ":"))
				{
					temp = temp + car;

					// si es el final no va a haber coma
					if(i == StringGrid1->Cells[j][0].Length() - 1)
					{
						/*~~~~~*/
						int k, l;
						/*~~~~~*/

						if(temp2 == "")
							k = temp.ToInt();
						else
							k = temp2.ToInt();
						l = temp.ToInt();

						for(; k <= l; k++)
						{
							if(FormasNormales->Disyuntivo->Checked)
								Tabla.EscribirDinArray(k, j, '1');
							else
								Tabla.EscribirDinArray(k, j, '0');
						}

						temp = "";
						temp2 = "";
					}
				}
				else if(car == ":")
				{
					temp2 = temp;
					temp = "";
				}
				else
				{
					/*~~~~~*/
					int k, l;
					/*~~~~~*/

					if(temp2 == "")
						k = temp.ToInt();
					else
						k = temp2.ToInt();
					l = temp.ToInt();

					for(; k <= l; k++)
					{
						if(FormasNormales->Disyuntivo->Checked)
							Tabla.EscribirDinArray(k, j, '1');
						else
							Tabla.EscribirDinArray(k, j, '0');
					}

					temp = "";
					temp2 = "";
				}
			}
		}

		// Aqui metemos las X
		for(int j = 0; j < StringGrid2->ColCount; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	temp, temp2 = "";
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for(int i = 0; i < StringGrid2->Cells[j][0].Length(); i++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	car = StringGrid2->Cells[j][0].SubString(i + 1, 1);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if((car != ",") & (car != ":"))
				{
					temp = temp + car;

					// si es el final no va a haber coma
					if(i == StringGrid2->Cells[j][0].Length() - 1)
					{
						if
						(
							((FormasNormales->Disyuntivo->Checked) & (Tabla.LeerDinArray(temp.ToInt(), j) == '1')) |
								(
									(FormasNormales->Conjuntivo->Checked) &
										(Tabla.LeerDinArray(temp.ToInt(), j) == '0')
								)
						)
						{
							Application->MessageBox(MENSAJE(msgSobreescribeConX), NULL);
						}

						/*~~~~~*/
						int k, l;
						/*~~~~~*/

						if(temp2 == "")
							k = temp.ToInt();
						else
							k = temp2.ToInt();
						l = temp.ToInt();

						for(; k <= l; k++)
						{
							Tabla.EscribirDinArray(k, j, 'X');
						}

						temp = "";
						temp2 = "";
					}
				}
				else if(car == ":")
				{
					temp2 = temp;
					temp = "";
				}
				else
				{
					if
					(
						((FormasNormales->Disyuntivo->Checked) & (Tabla.LeerDinArray(temp.ToInt(), j) == 1)) |
							((FormasNormales->Conjuntivo->Checked) & (Tabla.LeerDinArray(temp.ToInt(), j) == 0))
					)
					{
						Application->MessageBox(MENSAJE(msgSobreescribeConX), NULL);
					}

					/*~~~~~*/
					int k, l;
					/*~~~~~*/

					if(temp2 == "")
						k = temp.ToInt();
					else
						k = temp2.ToInt();
					l = temp.ToInt();

					for(; k <= l; k++)
					{
						Tabla.EscribirDinArray(k, j, 'X');
					}

					temp = "";
					temp2 = "";
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
void __fastcall TFormasNormales::BitBtn1Click(TObject *Sender)
{
	/*~~~~~~~~~~*/
	int error = 0;
	/*~~~~~~~~~~*/

	// Quitamos todos los blancos
	for(int j = 0; j < StringGrid1->ColCount; j++)
	{
		/*~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	cadena = "";
		int			k = 1;
		/*~~~~~~~~~~~~~~~~~~~~*/

		while(k <= StringGrid1->Cells[j][0].Length())
		{
			if(StringGrid1->Cells[j][0].SubString(k, 1) == " ")
			{
				cadena = StringGrid1->Cells[j][0];
				cadena.Delete(k, 1);
				StringGrid1->Cells[j][0] = cadena;
			}
			else
				k = k + 1;
		}

		/*~~~~~~*/
		int l = 1;
		/*~~~~~~*/

		while(l <= StringGrid2->Cells[j][0].Length())
		{
			if(StringGrid2->Cells[j][0].SubString(l, 1) == " ")
			{
				cadena = StringGrid2->Cells[j][0];
				cadena.Delete(l, 1);
				StringGrid2->Cells[j][0] = cadena;
			}
			else
				l = l + 1;
		}
	}

	//
	// Comprobamos que los valores se encuentran entre los limites establecidos en la
	// función
	//
	for(int j = 0; j < StringGrid1->ColCount; j++)
	{
		StringGrid1->Cells[j][0] = StringGrid1->Cells[j][0].Trim();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	temp, temp2 = "";
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 0; i < StringGrid1->Cells[j][0].Length(); i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	car = StringGrid1->Cells[j][0].SubString(i + 1, 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((car < '0') | (car > '9'))
			{
				if(((car != ",") & (car != ":")) | (temp == ""))
				{
					error = 1;
				}
				else if(temp.ToInt() >= Tabla.NumFilas())
				{
					error = 2;
				}
				else	// si el valor es correcto se borra la var. temporal
				{
					if(car == ":")
					{
						if(temp2 != "")
							error = 3;
						else
							temp2 = temp;
						if(i == StringGrid1->Cells[j][0].Length() - 1) error = 3;
					}
					else
					{
						if((temp2 != "") & (temp2 > temp)) error = 4;
						temp2 = "";
					}

					temp = "";
				}
			}
			else
			{
				temp = temp + car;

				// si es el final no va a haber coma
				if(i == StringGrid1->Cells[j][0].Length() - 1)
				{
					if(temp.ToInt() >= Tabla.NumFilas()) error = 2;
					if((temp2 != "") & (temp2 > temp)) error = 4;
				}
			}

			if(error != 0) break;
		}

		if(error != 0) break;
	}

	// en las X
	for(int j = 0; j < StringGrid2->ColCount; j++)
	{
		StringGrid2->Cells[j][0] = StringGrid2->Cells[j][0].Trim();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		AnsiString	temp, temp2 = "";
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		for(int i = 0; i < StringGrid2->Cells[j][0].Length(); i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	car = StringGrid2->Cells[j][0].SubString(i + 1, 1);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if((car < '0') | (car > '9'))
			{
				if(((car != ",") & (car != ":")) | (temp == ""))
				{
					error = 1;
				}
				else if(temp.ToInt() >= Tabla.NumFilas())
				{
					error = 2;
				}
				else	// si el valor es correcto se borra la var. temporal
				{
					if(car == ":")
					{
						if(temp2 != "")
							error = 3;
						else
							temp2 = temp;
						if(i == StringGrid1->Cells[j][0].Length() - 1) error = 3;
					}
					else
					{
						if((temp2 != "") & (temp2 > temp)) error = 4;
						temp2 = "";
					}

					temp = "";
				}
			}
			else
			{
				temp = temp + car;

				// si es el final no va a haber coma
				if(i == StringGrid2->Cells[j][0].Length() - 1)
				{
					if(temp.ToInt() >= Tabla.NumFilas()) error = 2;
					if((temp2 != "") & (temp2 > temp)) error = 4;
				}
			}

			if(error != 0) break;
		}

		if(error != 0) break;
	}

	if(error == 1) Application->MessageBox(MENSAJE(msgCaracterNoValido), NULL);
	if(error == 2) Application->MessageBox(MENSAJE(msgNoTantasVariables), NULL);
	if(error == 3) Application->MessageBox(MENSAJE(msgCaracterDosPuntos), NULL);
	if(error == 4) Application->MessageBox(MENSAJE(msgRangoErroneo), NULL);

	// si todo esta bien introducimos los valores en el objeto Tabla
	if(error == 0)
	{
		// inicializamos el objeto Tabla con ceros o unos
		for(int i = 0; i < Tabla.NumFilas(); i++)
		{
			for(int j = 0; j < Tabla.NumColumnas(); j++)
			{
				if(FormasNormales->Disyuntivo->Checked)
					Tabla.EscribirDinArray(i, j, '0');
				else
					Tabla.EscribirDinArray(i, j, '1');
			}
		}

		/*
		 * introducimos los valores de cada funcion en el objeto Tabla comprobando que tan
		 * solo se asigna un valor a cada posición y sacando una advertencia en caso
		 * contrario, persistiendo la X sobre los unos o ceros
		 */
		for(int j = 0; j < StringGrid1->ColCount; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	temp, temp2 = "";
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for(int i = 0; i < StringGrid1->Cells[j][0].Length(); i++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	car = StringGrid1->Cells[j][0].SubString(i + 1, 1);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if((car != ",") & (car != ":"))
				{
					temp = temp + car;

					// si es el final no va a haber coma
					if(i == StringGrid1->Cells[j][0].Length() - 1)
					{
						/*~~~~~*/
						int k, l;
						/*~~~~~*/

						if(temp2 == "")
							k = temp.ToInt();
						else
							k = temp2.ToInt();
						l = temp.ToInt();

						for(; k <= l; k++)
						{
							if(FormasNormales->Disyuntivo->Checked)
								Tabla.EscribirDinArray(k, j, '1');
							else
								Tabla.EscribirDinArray(k, j, '0');
						}

						temp = "";
						temp2 = "";
					}
				}
				else if(car == ":")
				{
					temp2 = temp;
					temp = "";
				}
				else
				{
					/*~~~~~*/
					int k, l;
					/*~~~~~*/

					if(temp2 == "")
						k = temp.ToInt();
					else
						k = temp2.ToInt();
					l = temp.ToInt();

					for(; k <= l; k++)
					{
						if(FormasNormales->Disyuntivo->Checked)
							Tabla.EscribirDinArray(k, j, '1');
						else
							Tabla.EscribirDinArray(k, j, '0');
					}

					temp = "";
					temp2 = "";
				}
			}
		}

		// Aqui metemos las X
		for(int j = 0; j < StringGrid2->ColCount; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			AnsiString	temp, temp2 = "";
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			for(int i = 0; i < StringGrid2->Cells[j][0].Length(); i++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				AnsiString	car = StringGrid2->Cells[j][0].SubString(i + 1, 1);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if((car != ",") & (car != ":"))
				{
					temp = temp + car;

					// si es el final no va a haber coma
					if(i == StringGrid2->Cells[j][0].Length() - 1)
					{
						if
						(
							((FormasNormales->Disyuntivo->Checked) & (Tabla.LeerDinArray(temp.ToInt(), j) == '1')) |
								(
									(FormasNormales->Conjuntivo->Checked) &
										(Tabla.LeerDinArray(temp.ToInt(), j) == '0')
								)
						)
						{
							Application->MessageBox(MENSAJE(msgSobreescribeConX), NULL);
						}

						/*~~~~~*/
						int k, l;
						/*~~~~~*/

						if(temp2 == "")
							k = temp.ToInt();
						else
							k = temp2.ToInt();
						l = temp.ToInt();

						for(; k <= l; k++)
						{
							Tabla.EscribirDinArray(k, j, 'X');
						}

						temp = "";
						temp2 = "";
					}
				}
				else if(car == ":")
				{
					temp2 = temp;
					temp = "";
				}
				else
				{
					if
					(
						((FormasNormales->Disyuntivo->Checked) & (Tabla.LeerDinArray(temp.ToInt(), j) == 1)) |
							((FormasNormales->Conjuntivo->Checked) & (Tabla.LeerDinArray(temp.ToInt(), j) == 0))
					)
					{
						Application->MessageBox(MENSAJE(msgSobreescribeConX), NULL);
					}

					/*~~~~~*/
					int k, l;
					/*~~~~~*/

					if(temp2 == "")
						k = temp.ToInt();
					else
						k = temp2.ToInt();
					l = temp.ToInt();

					for(; k <= l; k++)
					{
						Tabla.EscribirDinArray(k, j, 'X');
					}

					temp = "";
					temp2 = "";
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
void __fastcall TFormasNormales::BitBtn2Click(TObject *Sender)
{
	// borramos los valores de todas las funciónes
	for(int j = 0; j < StringGrid1->ColCount; j++)
	{
		StringGrid1->Cells[j][0] = "";
		StringGrid2->Cells[j][0] = "";
	}

	ScrollBar1->Position = 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::BitBtn3Click(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	FormasNormales->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormasNormales::BitBtn4Click(TObject *Sender)
{
	//ShowMessage("Las variables se deben introducir sin nin");
}
