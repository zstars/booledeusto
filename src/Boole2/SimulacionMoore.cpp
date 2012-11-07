/*$T boole/Boole2/SimulacionMoore.cpp GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#include <V_Boole2.h>
#pragma hdrstop
#include "SimulacionMoore.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMoore	*FormMoore;

/*
 =======================================================================================================================
 =======================================================================================================================
 */
__fastcall TFormMoore::TFormMoore(TComponent *Owner) :
	TForm(Owner)
{
	cont = 0;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMoore::Button1Click(TObject *Sender)
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	bool	Correcto = true;
	/*~~~~~~~~~~~~~~~~~~~~*/

	FormMoore->Button4->Enabled = true;
	AFe1sin = "";
	AFe2sin = "";
	AFe3sin = "";
	AFe4sin = "";
	AFe5sin = "";
	AFe1sin = FormMoore->Fe1->Text;
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
		AFe2sin = FormMoore->Fe2->Text;
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
		AFe3sin = FormMoore->Fe3->Text;
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
		AFe4sin = FormMoore->Fe4->Text;
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
		AFe5sin = FormMoore->Fe5->Text;
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

		FormMoore->Fe1->Text = AFe1;
		FormMoore->Fe2->Text = AFe2;
		FormMoore->Fe3->Text = AFe3;
		FormMoore->Fe4->Text = AFe4;
		FormMoore->Fe5->Text = AFe5;
		FormMoore->Fe1->ReadOnly = true;
		FormMoore->Fe2->ReadOnly = true;
		FormMoore->Fe3->ReadOnly = true;
		FormMoore->Fe4->ReadOnly = true;
		FormMoore->Fe5->ReadOnly = true;
		FormMoore->Button2->Enabled = true;
		FormMoore->Button1->Enabled = false;
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

		FormMoore->Fea->Text = AFea;
		AFs1 = AFs1 + " " + Estados[0].Salida[1];
		FormMoore->Fs1->Text = AFs1;
		if(Salidas > 1)
		{
			AFs2 = AFs2 + " " + Estados[0].Salida[2];
			FormMoore->Fs2->Text = AFs2;
		}

		if(Salidas > 2)
		{
			AFs3 = AFs3 + " " + Estados[0].Salida[3];
			FormMoore->Fs3->Text = AFs3;
		}

		if(Salidas > 3)
		{
			AFs4 = AFs4 + " " + Estados[0].Salida[4];
			FormMoore->Fs4->Text = AFs4;
		}

		if(Salidas > 4)
		{
			AFs5 = AFs5 + " " + Estados[0].Salida[5];
			FormMoore->Fs5->Text = AFs5;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMoore::Button2Click(TObject *Sender)
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

		for(int j = 0; j < 20; j++)
		{
			if(AFea[cont * 2 - 1] == ' ')
			{
				if(Estados[j].Nombre == AFea[cont * 2])
				{
					E = j;
					j = 20;
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
					j = 20;
				}
			}
		}

		for(int i = 1; i < 33; i++)
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

				for(int j = 0; j < 20; j++)
				{
					if(Estados[j].Nombre == Estados[E].Enlace[i][2])
					{
						I = j;
						j = 20;
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

				AFea = AFea + AFes[cont * 2 - 1] + AFes[cont * 2];
				AFs1 = AFs1 + " " + Estados[I].Salida[1];
				if(Salidas > 1)
				{
					AFs2 = AFs2 + " " + Estados[I].Salida[2];
				}

				if(Salidas > 2)
				{
					AFs3 = AFs3 + " " + Estados[I].Salida[3];
				}

				if(Salidas > 3)
				{
					AFs4 = AFs4 + " " + Estados[I].Salida[4];
				}

				if(Salidas > 4)
				{
					AFs5 = AFs5 + " " + Estados[I].Salida[5];
				}

				FormMoore->Fea->Text = AFea;
				FormMoore->Fs1->Text = AFs1;
				FormMoore->Fs2->Text = AFs2;
				FormMoore->Fs3->Text = AFs3;
				FormMoore->Fs4->Text = AFs4;
				FormMoore->Fs5->Text = AFs5;
				FormMoore->Fes->Text = AFes;
				i = 33;
			}
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMoore::Button4Click(TObject *Sender)
{
	FormMoore->Fea->Text = "";
	FormMoore->Fs1->Text = "";
	FormMoore->Fs2->Text = "";
	FormMoore->Fs3->Text = "";
	FormMoore->Fs4->Text = "";
	FormMoore->Fs5->Text = "";
	FormMoore->Fes->Text = "";
	FormMoore->Fe1->Text = AFe1sin;
	FormMoore->Fe2->Text = AFe2sin;
	FormMoore->Fe3->Text = AFe3sin;
	FormMoore->Fe4->Text = AFe4sin;
	FormMoore->Fe5->Text = AFe5sin;
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
	FormMoore->Button2->Enabled = false;
	FormMoore->Button1->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMoore::Button5Click(TObject *Sender)
{
	FormMoore->Fea->Text = "";
	FormMoore->Fs1->Text = "";
	FormMoore->Fs2->Text = "";
	FormMoore->Fs3->Text = "";
	FormMoore->Fs4->Text = "";
	FormMoore->Fs5->Text = "";
	FormMoore->Fes->Text = "";
	FormMoore->Fe1->Text = "";
	FormMoore->Fe2->Text = "";
	FormMoore->Fe3->Text = "";
	FormMoore->Fe4->Text = "";
	FormMoore->Fe5->Text = "";
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
	FormMoore->Button4->Enabled = false;
	FormMoore->Button1->Enabled = false;
	FormMoore->Button2->Enabled = false;
	FormMoore->Fe1->ReadOnly = false;
	FormMoore->Fe1->Color = clWindow;
	if(Entradas > 1)
	{
		FormMoore->Fe2->ReadOnly = false;
		FormMoore->Fe2->Color = clWindow;
	}

	if(Entradas > 2)
	{
		FormMoore->Fe3->ReadOnly = false;
		FormMoore->Fe3->Color = clWindow;
	}

	if(Entradas > 3)
	{
		FormMoore->Fe4->ReadOnly = false;
		FormMoore->Fe4->Color = clWindow;
	}

	if(Entradas > 4)
	{
		FormMoore->Fe5->ReadOnly = false;
		FormMoore->Fe5->Color = clWindow;
	}

	FormMoore->Button1->Enabled = true;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMoore::BitBtn3Click(TObject *Sender)
{
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
	AFe1sin = "";
	AFe2sin = "";
	AFe3sin = "";
	AFe4sin = "";
	AFe5sin = "";
	AFes = "";
	FormMoore->Fe1->Text = "";
	FormMoore->Fe2->Text = "";
	FormMoore->Fe3->Text = "";
	FormMoore->Fe4->Text = "";
	FormMoore->Fe5->Text = "";
	FormMoore->Fs1->Text = "";
	FormMoore->Fs2->Text = "";
	FormMoore->Fs3->Text = "";
	FormMoore->Fs4->Text = "";
	FormMoore->Fs5->Text = "";
	FormMoore->Fea->Text = "";
	FormMoore->Fes->Text = "";

	FormMoore->Fe1->ReadOnly = true;
	FormMoore->Fe2->ReadOnly = true;
	FormMoore->Fe3->ReadOnly = true;
	FormMoore->Fe4->ReadOnly = true;
	FormMoore->Fe5->ReadOnly = true;
	FormMoore->Fe1->Color = clSilver;
	FormMoore->Fe2->Color = clSilver;
	FormMoore->Fe3->Color = clSilver;
	FormMoore->Fe4->Color = clSilver;
	FormMoore->Fe5->Color = clSilver;
	FormMoore->Fs1->Color = clSilver;
	FormMoore->Fs2->Color = clSilver;
	FormMoore->Fs3->Color = clSilver;
	FormMoore->Fs4->Color = clSilver;
	FormMoore->Fs5->Color = clSilver;

	FormMoore->Button1->Enabled = true;
	FormMoore->Button2->Enabled = false;
	FormMoore->Button4->Enabled = false;
	FormMoore->Button5->Enabled = false;
	cont = 0;
	FormMoore->Close();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void __fastcall TFormMoore::FormShow(TObject *Sender)
{
	FormMoore->Fe1->ReadOnly = false;
	FormMoore->Fe1->Color = clWindow;
	if(Entradas > 1)
	{
		FormMoore->Fe2->ReadOnly = false;
		FormMoore->Fe2->Color = clWindow;
	}

	if(Entradas > 2)
	{
		FormMoore->Fe3->ReadOnly = false;
		FormMoore->Fe3->Color = clWindow;
	}

	if(Entradas > 3)
	{
		FormMoore->Fe4->ReadOnly = false;
		FormMoore->Fe4->Color = clWindow;
	}

	if(Entradas > 4)
	{
		FormMoore->Fe5->ReadOnly = false;
		FormMoore->Fe5->Color = clWindow;
	}

	FormMoore->Fs1->Color = clWindow;
	if(Salidas > 1)
	{
		FormMoore->Fs2->Color = clWindow;
	}

	if(Salidas > 2)
	{
		FormMoore->Fs3->Color = clWindow;
	}

	if(Salidas > 3)
	{
		FormMoore->Fs4->Color = clWindow;
	}

	if(Salidas > 4)
	{
		FormMoore->Fs5->Color = clWindow;
	}
}
