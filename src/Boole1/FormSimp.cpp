/*$T boole/Boole1/FormSimp.cpp GC! 1.116 05/02/01 18:53:23 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl/vcl.h>
#pragma hdrstop
#include "FormSimp.h"
#include <stdlib.h>
#include "DinArray.h"
#include "Libreria.h"
#include "NuevoSC.h"
#include "Unit11.h"
#include "NandNor.h"
#include "calc.h"
#include "Circuito/V_Circuito.h"
#include <vector>
#include "uKarnaugh.h"
using namespace std;

extern DinArray Tabla;
#pragma link "Grids"
#pragma resource "*.dfm"
TExpresionSimp	*ExpresionSimp;

vector<bool>	ocultarNANDNOR;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TExpresionSimp::TExpresionSimp(TComponent *Owner) :
	TForm(Owner)
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::FormShow(TObject *Sender)
{
	calcularSimplificada(Sender);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::calcularSimplificada(TObject *Sender)
{
	// if (!nnor->Checked) { Cursor = crHourGlass;
	Memo1->Text = " ";
	Funcion->Caption = 1;
	ScrollBar1->Max = Tabla.NumColumnas();
	Form11->NumC->Text = Tabla.NumEntradas();

	// damos el tamaño adecuado a los grids
	StringGrid1->RowCount = Tabla.NumColumnas();

	// Recogemos los valores de la tabla para hacer la simplificacion
	for(int l = 0; l < Tabla.NumColumnas(); l++)
	{
		Form11->Unos->Text = "";
		Form11->Equis->Text = "";
		StringGrid1->Cells[0][l] = "";
                int x =  Tabla.NumFilas();
		for(int i = 0; i < Tabla.NumFilas(); i++)
		{
			if
			(
				((Tabla.LeerDinArray(i, l) == '1') && (POS->Checked == false))
			||	((Tabla.LeerDinArray(i, l) == '0') && (POS->Checked == true))
			)
			{
				Form11->Unos->Text = Form11->Unos->Text + i + ",";
			}
			else if(Tabla.LeerDinArray(i, l) == 'X')
			{
				Form11->Equis->Text = Form11->Equis->Text + i + ",";
			}
		}

		// Form11->Visible=true;
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
			if(POS->Checked)
				cadenaSimp = "1";
			else
				cadenaSimp = "0";
		else if(cadenaSimp == cadenaLlena)
			if(POS->Checked)
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
			if(POS->Checked == true)
			{
				cadenaSimp = InvertirVariables(cadenaSimp);
				cadenaSimp = CambiarSignos(cadenaSimp, false);
				cadenaSimp = CambiarSignos(cadenaSimp, true);
			}
		}


		StringGrid1->Cells[0][l] = cadenaSimp;

		// Escribimos el resultado en el StringGrid para visualizarlo
	}

	ScrollBar1->Position = 1;
	while(Memo1->Text == " ")
	{
		Memo1->Text = NombresCompletos(StringGrid1->Cells[0][0], true);
	}

	// SistemaCombinacionalNuevo->Hide();
	nnor->Checked = false;

	// }
	//Calculando->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::SalirClick(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	ExpresionSimp->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::ScrollBar1Change(TObject *Sender)
{
	StringGrid1->TopRow = ScrollBar1->Position - 1;
	Funcion->Caption = ScrollBar1->Position;
	Memo1->Text = NombresCompletos(StringGrid1->Cells[0][ScrollBar1->Position - 1]);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::StringGrid1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	ScrollBar1->Position = StringGrid1->Col + 1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if((Key == 38) & (ScrollBar1->Position != 1))
	{
		ScrollBar1->Position = ScrollBar1->Position - 1;
	}
	else if((Key == 40) & (ScrollBar1->Position != StringGrid1->RowCount + 1))
	{
		ScrollBar1->Position = ScrollBar1->Position + 1;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::FuncionMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Funcion->Hint = Tabla.LeerSalida(ScrollBar1->Position - 1);
	Funcion->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::Label1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	Label1->Hint = Tabla.LeerSalida(ScrollBar1->Position - 1);
	Label1->ShowHint = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::BitBtn1Click(TObject *Sender)
{
	SistemaCombinacionalNuevo->Show();
	ExpresionSimp->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::Button1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	extern vector<bool> ocultarNANDNOR;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	NANDyNOR->StringGrid->ColCount = Tabla.NumColumnas();
	NANDyNOR->ScrollBar1->Max = Tabla.NumColumnas();

	// metemos las cadenas en el StringGrid
	for(int j = 0; j < Tabla.NumColumnas(); j++)
	{
		NANDyNOR->StringGrid->Cells[j][0] = "";
		NANDyNOR->StringGrid->Cells[j][2] = "";
		NANDyNOR->StringGrid->Cells[j][1] = "";
		NANDyNOR->StringGrid->Cells[j][3] = "";
	}

	ocultarNANDNOR.clear();

	/*~~~~~~~~~~~~~*/
	AnsiString	temp;
	/*~~~~~~~~~~~~~*/

	if(POS->Checked == true)
	{
		// POS
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			temp = Trim(StringGrid1->Cells[0][j]);
			if(temp.AnsiPos("*"))
				ocultarNANDNOR.push_back(false);
			else
				ocultarNANDNOR.push_back(true);
			if
			(
				(Trim(StringGrid1->Cells[0][j]) != "") & (Trim(StringGrid1->Cells[0][j]) != "0") &
					(Trim(StringGrid1->Cells[0][j]) != "1")
			)
			{
				// Estas llamadas son para NOR - funciones
				temp = Trim(StringGrid1->Cells[0][j]);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, true);
				temp.Insert("~(", 1);
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][2] = NombresCompletos(temp);

				// Hacemos el cambio a Espresion NAND - funciones
				temp = Trim(StringGrid1->Cells[0][j]);
				temp = InvertirVariables(temp);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, false);
				temp.Insert("~(~(", 1);
				temp.Insert(")", temp.Length());
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][0] = NombresCompletos(temp);

				// Ahora hay que escribirlo en su formulario
			}
			else
			{
				if(Trim(StringGrid1->Cells[0][j]) == "")
				{
					NANDyNOR->StringGrid->Cells[j][0] = "";
					NANDyNOR->StringGrid->Cells[j][2] = "";
				}
				else
				{
					NANDyNOR->StringGrid->Cells[j][0] = Trim(StringGrid1->Cells[0][j]);
					NANDyNOR->StringGrid->Cells[j][2] = Trim(StringGrid1->Cells[0][j]);
				}
			}
		}
	}
	else	// Ahora hacemos tratamiento de la expresion SOP
	{
		for(int j = 0; j < Tabla.NumColumnas(); j++)
		{
			temp = Trim(StringGrid1->Cells[0][j]);
			if(temp.AnsiPos("+"))
				ocultarNANDNOR.push_back(false);
			else
				ocultarNANDNOR.push_back(true);

			if
			(
				(Trim(StringGrid1->Cells[0][j]) != "") & (Trim(StringGrid1->Cells[0][j]) != "0") &
					(Trim(StringGrid1->Cells[0][j]) != "1")
			)
			{
				// Estas llamadas son para NOR - funciones
				temp = Trim(StringGrid1->Cells[0][j]);
				temp = InvertirVariables(temp);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, false);
				temp.Insert("~(~(", 1);
				temp.Insert(")", temp.Length());
				temp.Insert(")", temp.Length());
				NANDyNOR->StringGrid->Cells[j][2] = NombresCompletos(temp);

				//
				// Ahora hay que escribirlo en su formulario
				// Hacemos el cambio a Espresion NAND - funciones
				//
				temp = Trim(StringGrid1->Cells[0][j]);
				temp = InvertirExpresiones(temp);
				temp = CambiarSignos(temp, true);
				temp.Insert("~(", 1);
				temp.Insert(")", temp.Length());

				// Ahora hay que escribirlo en su formulario
				NANDyNOR->StringGrid->Cells[j][0] = NombresCompletos(temp);
			}
			else
			{
				if(Trim(StringGrid1->Cells[0][j]) == "")
				{
					NANDyNOR->StringGrid->Cells[j][0] = "";
					NANDyNOR->StringGrid->Cells[j][2] = "";
				}
				else
				{
					NANDyNOR->StringGrid->Cells[j][0] = Trim(StringGrid1->Cells[0][j]);
					NANDyNOR->StringGrid->Cells[j][2] = Trim(StringGrid1->Cells[0][j]);
				}
			}
		}
	}

	NANDyNOR->Exp->Checked = true;

  NANDyNOR->Label3->Visible =false;
  NANDyNOR->Label4->Visible =false;
  NANDyNOR->Label5->Visible =false;
  NANDyNOR->Edit3->Visible =false;
  NANDyNOR->Edit4->Visible =false;

	NANDyNOR->ShowModal();

  NANDyNOR->Label3->Visible =true;
  NANDyNOR->Label4->Visible =true;
  NANDyNOR->Label5->Visible =true;
  NANDyNOR->Edit3->Visible =true;
  NANDyNOR->Edit4->Visible =true;

	// ExpresionSimp->Hide();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TExpresionSimp::VisualizarClick(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	// Modificado.
	AnsiString	salida = Tabla.LeerSalida(ScrollBar1->Position - 1);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	FormR->Titulo = " Circuito simplificado.";
  FormR->tipoCircuito = false; // Combinacional.
	FormR->ecuacion->Text = salida + "=" + ExpresionSimp->Memo1->Text;
	FormR->Show();

	// Modificado.
}
void __fastcall TExpresionSimp::btKarnaughClick(TObject *Sender)
{
	AnsiString cadena;
	cadena = SistemaCombinacionalNuevo->NEntradas->Text;
	long numVars = atol(cadena.c_str());
        fKarnaugh->setFormato(POS->Checked?FORMATO_POS:FORMATO_SOP);
        fKarnaugh->setNumVars(numVars);
        fKarnaugh->setModo(MODO_NOEDITABLE);


	fKarnaugh->ShowModal();
}
//---------------------------------------------------------------------------

