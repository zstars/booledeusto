/*$T boole/Boole2/Sim2.cpp GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
#include "Sim2.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMealy	*FormMealy;

AnsiString	AFea;
AnsiString	AFs1;
AnsiString	AFs2;
AnsiString	AFs3;
AnsiString	AFs4;
AnsiString	AFs5;
AnsiString	AFe1;
AnsiString	AFe2;
AnsiString	AFe3;
AnsiString	AFe4;
AnsiString	AFe5;
AnsiString	AFe1sin;
AnsiString	AFe2sin;
AnsiString	AFe3sin;
AnsiString	AFe4sin;
AnsiString	AFe5sin;
AnsiString	AFes;

int			cont = 0;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TFormMealy::TFormMealy(TComponent *Owner) :
	TForm(Owner)
{
	FormMealy->Fe1->ReadOnly = false;
	FormMealy->Fe1->Color = clWindow;
	if(Entradas > 1)
	{
		FormMealy->Fe2->ReadOnly = false;
		FormMealy->Fe2->Color = clWindow;
	}

	if(Entradas > 2)
	{
		FormMealy->Fe3->ReadOnly = false;
		FormMealy->Fe3->Color = clWindow;
	}

	if(Entradas > 3)
	{
		FormMealy->Fe4->ReadOnly = false;
		FormMealy->Fe4->Color = clWindow;
	}

	if(Entradas > 4)
	{
		FormMealy->Fe5->ReadOnly = false;
		FormMealy->Fe5->Color = clWindow;
	}

	FormMealy->Fs1->Color = clWindow;
	if(Salidas > 1)
	{
		FormMealy->Fs2->Color = clWindow;
	}

	if(Salidas > 2)
	{
		FormMealy->Fs3->Color = clWindow;
	}

	if(Salidas > 3)
	{
		FormMealy->Fs4->Color = clWindow;
	}

	if(Salidas > 4)
	{
		FormMealy->Fs5->Color = clWindow;
	}

	FormMealy->Button1->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMealy::Button1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	bool	Correcto = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	FormMealy->Button4->Enabled = true;
	AFe1sin = "";
	AFe2sin = "";
	AFe3sin = "";
	AFe4sin = "";
	AFe5sin = "";
	AFe1sin = FormMealy->Fe1->Text;
	for(int i = 1; i <= AFe1sin.Length(); i++)
	{
		if((AFe1sin[i] != '0') & (AFe1sin[i] != '1'))
		{
			Correcto = false;
			i = AFe1sin.Length() + 1;
		}
	}

	if(Entradas > 1)
	{
		AFe2sin = FormMealy->Fe2->Text;
		if(AFe2sin.Length() != AFe1sin.Length())
		{
			Correcto = false;
		}

		for(int i = 1; i <= AFe2sin.Length(); i++)
		{
			if((AFe2sin[i] != '0') & (AFe2sin[i] != '1'))
			{
				Correcto = false;
				i = AFe2sin.Length() + 1;
			}
		}
	}

	if(Entradas > 2)
	{
		AFe3sin = FormMealy->Fe3->Text;
		if(AFe3sin.Length() != AFe2sin.Length())
		{
			Correcto = false;
		}

		for(int i = 1; i <= AFe3sin.Length(); i++)
		{
			if((AFe3sin[i] != '0') & (AFe3sin[i] != '1'))
			{
				Correcto = false;
				i = AFe3sin.Length() + 1;
			}
		}
	}

	if(Entradas > 3)
	{
		AFe4sin = FormMealy->Fe4->Text;
		if(AFe4sin.Length() != AFe3sin.Length())
		{
			Correcto = false;
		}

		for(int i = 1; i <= AFe4sin.Length(); i++)
		{
			if((AFe4sin[i] != '0') & (AFe4sin[i] != '1'))
			{
				Correcto = false;
				i = AFe4sin.Length() + 1;
			}
		}
	}

	if(Entradas > 4)
	{
		AFe5sin = FormMealy->Fe5->Text;
		if(AFe5sin.Length() != AFe4sin.Length())
		{
			Correcto = false;
		}

		for(int i = 1; i <= AFe5sin.Length(); i++)
		{
			if((AFe5sin[i] != '0') & (AFe5sin[i] != '1'))
			{
				Correcto = false;
				i = AFe5sin.Length() + 1;
			}
		}
	}

	if(AFe1sin.Length() > 24)
	{
		Correcto = false;
	}

	if(Correcto == false)
	{
		Application->MessageBox
			(
				"Las entradas deben ser ceros y unos,de la misma longitud y no mayor que 24",
				NULL,
				MB_OK
			);
	}

	if(Correcto == true)
	{
		for(int i = 1; i <= AFe1sin.Length(); i++)
		{
			AFe1 = AFe1 + " " + AFe1sin[i];
			if(Entradas > 1)
			{
				AFe2 = AFe2 + " " + AFe2sin[i];
			}

			if(Entradas > 2)
			{
				AFe3 = AFe3 + " " + AFe3sin[i];
			}

			if(Entradas > 3)
			{
				AFe4 = AFe4 + " " + AFe4sin[i];
			}

			if(Entradas > 4)
			{
				AFe5 = AFe5 + " " + AFe5sin[i];
			}
		}

		FormMealy->Fe1->Text = AFe1;
		FormMealy->Fe2->Text = AFe2;
		FormMealy->Fe3->Text = AFe3;
		FormMealy->Fe4->Text = AFe4;
		FormMealy->Fe5->Text = AFe5;
		FormMealy->Fe1->ReadOnly = true;
		FormMealy->Fe2->ReadOnly = true;
		FormMealy->Fe3->ReadOnly = true;
		FormMealy->Fe4->ReadOnly = true;
		FormMealy->Fe5->ReadOnly = true;
		FormMealy->Button2->Enabled = true;
		FormMealy->Button1->Enabled = false;
		if(Estados[0].Nombre.Length() == 1)
		{
			AFea = AFea + " " + Estados[0].Nombre[1];
		}
		else
		{
			AFea = AFea +
				Estados[0].Nombre[Estados[0].Nombre.Length() - 1] +
				Estados[0].Nombre[Estados[0].Nombre.Length()];
		}

		FormMealy->Fea->Text = AFea;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMealy::Button2Click(TObject *Sender)
{
	/*~~~~~~~*/
	bool	Es;
	/*~~~~~~~*/

	cont++;
	if(cont <= AFe1sin.Length())
	{
		/*~~~~~~*/
		int E = 0;
		/*~~~~~~*/

		for(int j = 0; j < 11; j++)
		{
			if(AFea[cont * 2 - 1] == ' ')
			{
				if(Estados[j].Nombre == AFea[cont * 2])
				{
					E = j;
					j = 11;
				}
			}
			else
			{
				if
				(
					(Estados[j].Nombre[Estados[j].Nombre.Length()] == AFea[cont * 2])
				&&	(Estados[j].Nombre[Estados[j].Nombre.Length() - 1] == AFea[cont * 2 - 1])
				)
				{
					E = j;
					j = 11;
				}
			}
		}

		for(int i = 1; i < 17; i++)
		{
			Es = true;
			if(Estados[E].Enlace[i][1][1] != AFe1[cont * 2])
			{
				Es = false;
			}

			if(Entradas > 1)
			{
				if(Estados[E].Enlace[i][1][2] != AFe2[cont * 2])
				{
					Es = false;
				}
			}

			if(Entradas > 2)
			{
				if(Estados[E].Enlace[i][1][3] != AFe3[cont * 2])
				{
					Es = false;
				}
			}

			if(Entradas > 3)
			{
				if(Estados[E].Enlace[i][1][4] != AFe4[cont * 2])
				{
					Es = false;
				}
			}

			if(Entradas > 4)
			{
				if(Estados[E].Enlace[i][1][5] != AFe5[cont * 2])
				{
					Es = false;
				}
			}

			if(Es == true)
			{
				/*~~~~~~*/
				int I = 0;
				/*~~~~~~*/

				for(int j = 0; j < 11; j++)
				{
					if(Estados[j].Nombre == Estados[E].Enlace[i][3])
					{
						I = j;
						j = 11;
					}
				}

				if(Estados[I].Nombre.Length() == 1)
				{
					AFes = AFes + " " + Estados[I].Nombre;
				}
				else
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					AnsiString	V = Estados[I].Nombre;
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					AFes = AFes + V[V.Length() - 1] + V[V.Length()];
				}

				AFs1 = AFs1 + " " + Estados[E].Enlace[i][2][1];
				if(Salidas > 1)
				{
					AFs2 = AFs2 + " " + Estados[E].Enlace[i][2][2];
				}

				if(Salidas > 2)
				{
					AFs3 = AFs3 + " " + Estados[E].Enlace[i][2][3];
				}

				if(Salidas > 3)
				{
					AFs4 = AFs4 + " " + Estados[E].Enlace[i][2][4];
				}

				if(Salidas > 4)
				{
					AFs5 = AFs5 + " " + Estados[E].Enlace[i][2][5];
				}

				AFea = AFea + AFes[cont * 2 - 1] + AFes[cont * 2];

				//
				// AFs1=AFs1+" "+Estados[I].Salida[1]; if (Salidas>1) {AFs2=AFs2+"
				// "+Estados[I].Salida[2]; } if (Salidas>2) {AFs3=AFs3+" "+Estados[I].Salida[3]; }
				// if (Salidas>3) {AFs4=AFs4+" "+Estados[I].Salida[4]; } if (Salidas>4)
				// {AFs5=AFs5+" "+Estados[I].Salida[5]; }
				//
				FormMealy->Fea->Text = AFea;
				FormMealy->Fs1->Text = AFs1;
				FormMealy->Fs2->Text = AFs2;
				FormMealy->Fs3->Text = AFs3;
				FormMealy->Fs4->Text = AFs4;
				FormMealy->Fs5->Text = AFs5;
				FormMealy->Fes->Text = AFes;
				i = 17;
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMealy::Button4Click(TObject *Sender)
{
	FormMealy->Fea->Text = "";
	FormMealy->Fs1->Text = "";
	FormMealy->Fs2->Text = "";
	FormMealy->Fs3->Text = "";
	FormMealy->Fs4->Text = "";
	FormMealy->Fs5->Text = "";
	FormMealy->Fes->Text = "";
	FormMealy->Fe1->Text = AFe1sin;
	FormMealy->Fe2->Text = AFe2sin;
	FormMealy->Fe3->Text = AFe3sin;
	FormMealy->Fe4->Text = AFe4sin;
	FormMealy->Fe5->Text = AFe5sin;
	AFea = "";
	AFs1 = "";
	AFs2 = "";
	AFs3 = "";
	AFs4 = "";
	AFs5 = "";
	AFe1 = "";
	AFe2 = "";
	AFe3 = "";
	AFe4 = "";
	AFe5 = "";
	AFes = "";
	cont = 0;
	FormMealy->Button2->Enabled = false;
	FormMealy->Button1->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMealy::Button5Click(TObject *Sender)
{
	FormMealy->Fea->Text = "";
	FormMealy->Fs1->Text = "";
	FormMealy->Fs2->Text = "";
	FormMealy->Fs3->Text = "";
	FormMealy->Fs4->Text = "";
	FormMealy->Fs5->Text = "";
	FormMealy->Fes->Text = "";
	FormMealy->Fe1->Text = "";
	FormMealy->Fe2->Text = "";
	FormMealy->Fe3->Text = "";
	FormMealy->Fe4->Text = "";
	FormMealy->Fe5->Text = "";
	AFea = "";
	AFs1 = "";
	AFs2 = "";
	AFs3 = "";
	AFs4 = "";
	AFs5 = "";
	AFes = "";
	cont = 0;
	AFe1 = "";
	AFe2 = "";
	AFe3 = "";
	AFe4 = "";
	AFe5 = "";
	AFe1sin = "";
	AFe2sin = "";
	AFe3sin = "";
	AFe4sin = "";
	AFe5sin = "";
	FormMealy->Button4->Enabled = false;
	FormMealy->Button1->Enabled = true;
	FormMealy->Button2->Enabled = false;

	FormMealy->Fe1->ReadOnly = false;
	FormMealy->Fe1->Color = clWindow;
	if(Entradas > 1)
	{
		FormMealy->Fe2->ReadOnly = false;
		FormMealy->Fe2->Color = clWindow;
	}

	if(Entradas > 2)
	{
		FormMealy->Fe3->ReadOnly = false;
		FormMealy->Fe3->Color = clWindow;
	}

	if(Entradas > 3)
	{
		FormMealy->Fe4->ReadOnly = false;
		FormMealy->Fe4->Color = clWindow;
	}

	if(Entradas > 4)
	{
		FormMealy->Fe5->ReadOnly = false;
		FormMealy->Fe5->Color = clWindow;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMealy::Button3Click(TObject *Sender)
{
	FormMealy->Close();
}
