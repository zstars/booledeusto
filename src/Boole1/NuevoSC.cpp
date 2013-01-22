//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <shellapi.h>

#include <printers.hpp>

#include "NuevoSC.h"
#include "Libreria.h"
#include "Main.h"
#include "calc.h"
#include "TVComple.h"
#include "FormSimp.h"
#include "TVManual.h"
#include "SCCompac.h"
#include "FormasN.h"
#include "DinArray.h"
#include "VKar6.h"
#include "VKar6X.h"
#include "VKar5.h"
#include "VKar5X.h"
#include "VKar4.h"
#include "VKar4X.h"
#include "VKar3.h"
#include "VKar3X.h"
#include "ExpBool.h"
#include "app.h"

#include "Unit11.h"
#include "V_Circuito.h"

#include <vcl\Clipbrd.hpp>
#include "uTextoAsoc.h"
#include "mensajes.inc"
#include "uKarnaugh.h"


#include "Weblab.h"

#include "claseJedec.h"

extern DinArray Tabla;
//Invocamos al constructor de la tabla
DinArray Tabla = DinArray();

//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma resource "*.dfm"
TSistemaCombinacionalNuevo *SistemaCombinacionalNuevo;
//--------------------------------------------------------------------

bool ComprobarVariables ()
{
  	// comprobamos que haya algun valor válido en los números de variables
  	if ((SistemaCombinacionalNuevo->TablaEntrada->Enabled == true)
    	&& (SistemaCombinacionalNuevo->TablaSalida->Enabled == true))
	{
        AnsiString cadena;

	    /* si han cambiado el número de variables borramos la matriz
	    	anterior y creamos una nueva */
	    if ( (Tabla.NumEntradas() != SistemaCombinacionalNuevo->NEntradas->Text)
	    	|| (Tabla.NumColumnas() != SistemaCombinacionalNuevo->NSalidas->Text) )
	    {
	    	Tabla.BorrarDinArray();
	        Tabla.DinX(SistemaCombinacionalNuevo->Edit1->Text.SubString(0,40),
	        			(SistemaCombinacionalNuevo->TablaEntrada->RowCount),
	                    (SistemaCombinacionalNuevo->TablaSalida->RowCount) );
    	}
	    else
        /* sino solo volvemos a escribir los nombres de las varibales por si los
        	han cambiado */
        {
            Tabla.BorrarEntradas();
            Tabla.BorrarSalidas();
        }
        //Reescribimos los identificativos del Sistema Combinacional
        cadena = SistemaCombinacionalNuevo->Edit1->Text;
        Tabla.EscribirNombre(cadena);
        for (int i=0; i<(Tabla.NumEntradas()); i++)
        {
		    cadena = SistemaCombinacionalNuevo->TablaEntrada->Cells[1][i] + "                              ";
	        Tabla.AnadirEntrada(cadena.SubString(1, 30));
	    }
	   	for (int i=0; i<(Tabla.NumColumnas()); i++)
	    {
	        cadena = SistemaCombinacionalNuevo->TablaSalida->Cells[1][i] + "                              ";
	     	Tabla.AnadirSalida(cadena.SubString(1, 30));
	    }

        if (Trim(SistemaCombinacionalNuevo->Edit1->Text) != "")
        {
    		return true;
        }
        else
        {
            Application->MessageBox(MENSAJE(msgNombreCircuito), NULL);
        	return false;
        }
    }
    else
    {
     	return false;
    }
}


//---------------------------------------------------------------------------
__fastcall TSistemaCombinacionalNuevo::TSistemaCombinacionalNuevo(TComponent* Owner)
        : TForm(Owner)
{
    // ajustamos el tamaño de las celdas para los nombre de las variables
	TablaEntrada->ColWidths[1] = TablaEntrada->Width - TablaEntrada->ColWidths[0];
    TablaSalida->ColWidths[1] = TablaSalida->Width - TablaSalida->ColWidths[0];
}

//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::NEntradasChange(TObject *Sender)
{
    AnsiString cadena;
    cadena = NEntradas->Text;
    long numero = atol(cadena.c_str());

    /* si el número de var. de entrada es aceptable activamos la tabla de
    	variables y le damos el tamño adecuado*/
    if ((numero>0) & (numero<27))
    {
    	TablaEntrada->Enabled = true;
        TablaEntrada->Color = clWindow;
        TablaEntrada->ColCount = 2;
        TablaEntrada->RowCount = numero;
        TablaEntrada->EditorMode = true;
        for (char caracter = 'A'; caracter < ('A' + numero); caracter++)
        {
        	TablaEntrada->Cells[0][caracter - 'A'] = caracter;
        }
    }
	else
    {
		TablaEntrada->Enabled = false;
        TablaEntrada->Color = clInactiveCaption;
        TablaEntrada->RowCount = 1;
		TablaEntrada->Cells[0][0] = ' ';
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::NSalidasChange(TObject *Sender)
{
    AnsiString cadena;
    cadena = NSalidas->Text;
    long numero = atol(cadena.c_str());

/* si el número de var. de salida es aceptable activamos la tabla de
    	variables y le damos el tamño adecuado*/
    if (numero>0)
    {
    	TablaSalida->Enabled = true;
        TablaSalida->Color = clWindow;
        TablaSalida->RowCount = numero;

        for (int i = 1; i <= numero; i++)
        {
        	TablaSalida->Cells[0][i-1] = i;
        }
    }
	else
    {
		TablaSalida->Enabled = false;
        TablaSalida->Color = clInactiveCaption;
        TablaSalida->RowCount = 1;
		TablaSalida->Cells[0][0] = ' ';
    }
}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::TVManualClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
		TablaVerdadCompleta->Show();
	    //SistemaCombinacionalNuevo->Hide();
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
  }
	//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::SalirClick(TObject *Sender)
{
    for(int i=0; i < TablaEntrada->RowCount; i++)
    {
    	TablaEntrada->Cells[1][i] = "";
    }
    TablaEntrada->RowCount = 1;
    TablaEntrada->Enabled = false;
    TablaEntrada->Color = clInactiveCaption;

    for(int i=0; i < TablaSalida->RowCount; i++)
    {
    	TablaSalida->Cells[1][i] = "";
    }
	TablaSalida->RowCount = 1;
    TablaSalida->Enabled = false;
    TablaSalida->Color = clInactiveCaption;

    Tabla.BorrarDinArray();
    Edit1->Text = "";
    NEntradas->Text = "";
    NSalidas->Text = "";

    Principal->Show();
	SistemaCombinacionalNuevo->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::FNPOSClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
        SCFormasCompactas->Caption = MENSAJE(msgExpresionPOS);
		SCFormasCompactas->Conjuntivo->Checked = false;
        SCFormasCompactas->Conjuntivo->Enabled = false;
        SCFormasCompactas->Disyuntivo->Checked = true;
        SCFormasCompactas->Disyuntivo->Enabled = true;
		SCFormasCompactas->Show();
	    //SistemaCombinacionalNuevo->Hide();
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::FNSOPClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
        SCFormasCompactas->Caption = MENSAJE(msgExpresionSOP);
		SCFormasCompactas->Conjuntivo->Checked = true;
        SCFormasCompactas->Conjuntivo->Enabled = true;
        SCFormasCompactas->Disyuntivo->Checked = false;
        SCFormasCompactas->Disyuntivo->Enabled = false;
		SCFormasCompactas->Show();
	    //SistemaCombinacionalNuevo->Hide();
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------


void __fastcall TSistemaCombinacionalNuevo::TVCompactaClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
        if (Tabla.LeerDinArray(0,0) == ' ')
    	{
			TablaVerdadManual->Show();
		    //SistemaCombinacionalNuevo->Hide();
        }
        else
        	Application->MessageBox(MENSAJE(msgYaExisteNoVerCompacta), "");
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::FormShow(TObject *Sender)
{
  fTextoAsoc->txAsociado->Clear();
 	NEntradas->Text = Tabla.NumEntradas();
	NSalidas->Text = Tabla.NumColumnas();
    Edit1->Text = Tabla.LeerNombre();
    for (int i = 0; i < Tabla.NumEntradas(); i++)
    {
        TablaEntrada->Cells[1][i] = Tabla.LeerEntrada(i);
    }
    for (int i = 0; i < Tabla.NumColumnas(); i++)
    {
        TablaSalida->Cells[1][i] = Tabla.LeerSalida(i);
    }

    //QuitarSeleccionTablas();
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::ExpBooleanaClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
		if (Tabla.LeerDinArray(0,0) == ' ')
    	{
            ExprBooleana->Show();
		    //SistemaCombinacionalNuevo->Hide();
        }
        else
        	//ShowMessage ("El sistema ya existe, elija las expresiones simplificadas SOP o POS");


/*            Calculando->Label2->Caption="\nEl sistema ya existe.\nSi introduce una nueva ecuación booleana el sistema se borrará.";
            Calculando->B1->Visible=true;
            Calculando->B2->Visible=true;
            Calculando->ShowModal();
            Calculando->B1->Visible=false;
            Calculando->B2->Visible=false;
*/


            if (Application->MessageBox(MENSAJE(msgNuevaEcBooleana), NULL, MB_YESNO)==IDYES){
                ExprBooleana->Show();
            }







    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::GuardarClick(TObject *Sender)
{
	AnsiString temp="";
	TStringList *Lista = new TStringList;
	//Invocamos a una función para comprobar que se ha creado el objeto
	if (ComprobarVariables())
        if (Tabla.LeerDinArray(0,0) != ' ')
        {
	    	/* guardamos el objeto en un fichero, es decir guardamos los valores
               que nos interesan en un fichero */
            if (Guardador->Execute())
            {
            	Lista->Add(Tabla.LeerNombre());

                Lista->Add(Tabla.NumEntradas());
				for(int i=0; i < Tabla.NumEntradas();i++)
                	{
						Lista->Add(Tabla.LeerEntrada(i));
                	}

                Lista->Add(Tabla.NumColumnas());
                for(int i=0; i < Tabla.NumColumnas();i++)
                	{
						Lista->Add(Tabla.LeerSalida(i));
                	}
                for (int i=0; i< Tabla.NumColumnas(); i++)
                	{
                        for (int j=0; j< Tabla.NumFilas(); j++)
                        	{
								temp = temp + Tabla.LeerDinArray(j,i);
                            }
                        Lista->Add(temp);
                        temp = "";
                	}
	           	Application->MessageBox(MENSAJE(msgSCGuardadoFichero), "");
                Lista->SaveToFile(Guardador->FileName);

            }
//Ahora funciona cojonudamente sin utilizar el control TMemo y usando un
//objeto de tipo TStringList
        }
        else
        	Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
    else
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::btApExprBoolClick(TObject *Sender)
{
    if ( ComprobarVariables() )
    {
        if (Tabla.LeerDinArray(0,0) != ' ')
        {
                ap->ShowModal();
        }
        else
			Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::Button2Click(TObject *Sender)
{
    if (ComprobarVariables())
    {
        FormasNormales->Caption = MENSAJE(msgFormaDisyun);
		FormasNormales->Conjuntivo->Checked = false;
        FormasNormales->Conjuntivo->Enabled = false;
        FormasNormales->Disyuntivo->Checked = true;
        FormasNormales->Disyuntivo->Enabled = true;
		FormasNormales->Show();
	    //SistemaCombinacionalNuevo->Hide();
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::Button3Click(TObject *Sender)
{
    if (ComprobarVariables())
    {
        FormasNormales->Caption = MENSAJE(msgFormaConjun);
		FormasNormales->Conjuntivo->Checked = true;
        FormasNormales->Conjuntivo->Enabled = true;
        FormasNormales->Disyuntivo->Checked = false;
        FormasNormales->Disyuntivo->Enabled = false;
		FormasNormales->Show();
	    //SistemaCombinacionalNuevo->Hide();
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::CargarClick(TObject *Sender)
{
TStringList *Lista = new TStringList;
AnsiString Prueba;
//int numerofilas;
int numerocolumnas;

 	if (Cargador->Execute())
    {	//Capturamos interrupcion en caso de que exista un error
    	try	{
			Lista->LoadFromFile(Cargador->FileName);
    		}//Ahora el sistema esta en el objeto de tipo TStringList
    	catch(...)
    		{
    		Application->MessageBox(MENSAJE(msgErrorCargar), NULL);
    		}
    }
    Edit1->Text = Lista->Strings[0];
    NEntradas->Text = Lista->Strings[1];
    int j = atol(NEntradas->Text.c_str()) + 2;
    for ( int i = 2; i <  j; i++)
    {
        //Escribimos en el grid los nombres de las variables de entrada
        TablaEntrada->Cells[1][i-2] = Lista->Strings[i];
    }
    NSalidas->Text = Lista->Strings[j];
    int i = j +1;
    int paso = i;
    j = j + atol(NSalidas->Text.c_str());
    //int i = j;
    for (i ; i <= j;i++)
    {	//Escribimos en el grid los nombres de las variables de salida
        TablaSalida->Cells[1][i-paso] = Lista->Strings[i];
    }
    // La variable i contiene la posicion donde empiezan los valores de
    // la tabla
    //Ahora escribimos los datos en el objeto
    Tabla.DinX(Edit1->Text.SubString(0,40),
	        			(TablaEntrada->RowCount),
	                    (TablaSalida->RowCount) );
    //Y por ultimo escribimos los datos de la(s) salida(s)
  //  numerofilas = atol(NEntradas->Text.c_str());
    numerocolumnas = atol(NSalidas->Text.c_str());
	//Ahora tenemos que coger las cadenas que contienen los datos y
    //escribirlas en la Tabla
    AnsiString temp;
    for (int  k=1 ; (k <= numerocolumnas); k++ )
    {
    	for (int l = 1; l <= Tabla.NumFilas(); l++)
        {
            temp= Lista->Strings[i].SubString(l,1).c_str();
            char *valor = temp.c_str();
        	Tabla.EscribirDinArray(l-1, k-1, *valor);
        }
        i= i +1;
    }
    Application->MessageBox(MENSAJE(msgSCCargadoFichero), "");
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::SOPSimpClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
        if (Tabla.LeerDinArray(0,0) != ' ')
    	{

            ExpresionSimp->POS->Checked = false;
            ExpresionSimp->btKarnaugh->Visible=true;
            ExpresionSimp->Caption = MENSAJE(msgExprSOPSimpl);
            ExpresionSimp->Show();

        }
        else
        	Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::POSSimpClick(TObject *Sender)
{
    if (ComprobarVariables())
    {
        if (Tabla.LeerDinArray(0,0) != ' ')
    	{
            //Calculando->Label2->Caption="\nCalculando expresión simplificada POS.";
            //Calculando->Show();

            ExpresionSimp->POS->Checked = true;
            ExpresionSimp->btKarnaugh->Visible=true;
            //Calculando->Repaint();
            ExpresionSimp->Caption = MENSAJE(msgExprPOSSimpl);
			ExpresionSimp->Show();
            //ShowMessage->Hide();
//		    SistemaCombinacionalNuevo->Hide();
		}
        else
        	Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::ImprimirClick(TObject *Sender)
{
int m = 10;
TStringList *Lista = new TStringList;

if ( ComprobarVariables() )
{
	Lista->Add(ANSIMENSAJE(msgNombreSC)+" : " + Tabla.LeerNombre());
    Lista->Add("");
    Lista->Add(ANSIMENSAJE(msgVarsEntrada)+" : ");
	//Escribimos las cabeceras de la hoja diciendo cuales son la variable de entrada
	AnsiString temp = "";
    for ( int i = 0; i < Tabla.NumEntradas() ; i++)
	{
    	temp = "     ";
		temp = temp + char('A' + i);
        temp = temp + " = ";
		temp = temp + Tabla.LeerEntrada(i);
        Lista->Add(temp);
	}
    Lista->Add("");
    Lista->Add(ANSIMENSAJE(msgVarsSalida)+" : ");
	for ( int i = 0; i < Tabla.NumColumnas() ; i++)
	{
		temp = "     F";
        temp = temp + (i + 1);
        temp = temp + " = ";
		temp = temp + Tabla.LeerSalida(i);
		Lista->Add(temp);
    }
	Lista->Add("");
    //Ahora escribimos los nombres genericos de las vbles. de entrada y salida
    temp = "";
	for ( int i = 0 ; i < Tabla.NumEntradas(); i++ )
    {
    	temp = temp + char('A' + i);
        temp = temp + " ";
    }
    temp = temp + "     ";

    for ( int i = 0 ; i < Tabla.NumColumnas(); i++ )
    {
    	temp = temp + "F";
        temp = temp + (i+1);
        temp = temp + " ";
    }
    Lista->Add(temp);

	//Accedemos al objeto para leer sus verdaderos valores
	for ( int i=0; i < Tabla.NumFilas(); i++ )
    {
        temp = "";
        AnsiString paso = CalcularBinario(i,Tabla.NumEntradas());

    	for ( int j=1 ; j <= paso.Length(); j++ )
        {
        	temp = temp + paso.SubString(j,1);
            temp = temp + " ";
        }
        temp = temp + "        ";

        for ( int j=0 ;j < Tabla.NumColumnas(); j++ )
        {
        	temp = temp + Tabla.LeerDinArray(i,j);
            temp = temp + "    ";
        }
        Lista->Add(temp);
    }
	//Pasamos el contenido del StringList al control TMemo para poder imprimirlo
	CTexto->Text = Lista->Text;
    ShowMessage(Lista->Text);
	if ( impresora->Execute())
	{
		Printer()->Title = Tabla.LeerNombre();
    	Printer()->BeginDoc();

    	for ( int n = 0; n < CTexto->Lines->Count; n++ )
        {
        	Printer()->Canvas->TextOut(10, m, CTexto->Lines->Strings[n]);
            m += Printer()->Canvas->TextHeight("XXX");
            if ( m + Printer()->Canvas->TextHeight("XXX") > Printer()->PageHeight )
            {
            	Printer()->NewPage();
                m = 10;
            }
        }
        Printer()->EndDoc();
	}

}
else
	Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::GuardarPLDClick(TObject *Sender)
{
//Guardamos los datos del sistema en formato PLD para escribirse en un CI
//Tendrá extension *.pld y se escribira en forma de funciones booleanas
//simplificadas SOP
	AnsiString temp="";
	TStringList *Lista = new TStringList;
	//Invocamos a una función para comprobar que se ha creado el objeto
	if (ComprobarVariables())
        if (Tabla.LeerDinArray(0,0) != ' ')
        {
	    	/* guardamos el objeto en un fichero, es decir guardamos los valores
               que nos interesan en un fichero */
            GuardaPLD->Filter=MENSAJE(msgFiltroPLD);

            if (GuardaPLD->Execute())
            {
            	Lista->Add("|?"); //Escribimos cabecera del fichero
				//preparamos para escribir los nombres de todas las variables
                temp = "|in:(";
                for ( int i = 0; i < Tabla.NumEntradas(); i ++)
                {
                    //Si la entrada no tiene nombre se le asigna uno genérico
					if (Tabla.LeerEntrada(i) == "")
                    {
						temp = temp + char('A' + i);
                    }
                	temp = temp + Tabla.LeerEntrada(i);
                    temp = temp + ",";
                }
                temp.Delete(temp.Length(),1);
                temp.Insert(")",temp.Length()+1);
                //despues de escribir las varables de entrada escribimos las
                //de las salidas

                temp = temp + ",out:(";
                for (int i=0; i < Tabla.NumColumnas();i++)
                {
					//Esto no funciona correctamente
                	if (Tabla.LeerSalida(i) == "")
                    {
                    	temp = temp + "F";
                        temp = temp + (i+1);
                    }

                	temp = temp + Tabla.LeerSalida(i);
                    temp = temp + ",";
                }
                temp.Delete(temp.Length(),1);
                temp.Insert(")",temp.Length()+1);
				Lista->Add(temp);

		//Ahora escribimos las funciones simplificadas

        ExpresionSimp->StringGrid1->RowCount = Tabla.NumColumnas();
        ExpresionSimp->POS->Checked = false;

    	// Recogemos los valores de la tabla para hacer la simplificacion
    	for (int l=0; l<Tabla.NumColumnas(); l++)
    	{
            Form11->Unos->Text = "";
            Form11->Equis->Text = "";
        	ExpresionSimp->StringGrid1->Cells[0][l] = "";
    		for (int i = 0; i<Tabla.NumFilas(); i++)
        	{
        		if ( ((Tabla.LeerDinArray(i,l) == '1') & (ExpresionSimp->POS->Checked == false)) |
            	 ((Tabla.LeerDinArray(i,l) == '0') & (ExpresionSimp->POS->Checked == true)) )
            		{
             			Form11->Unos->Text = Form11->Unos->Text + i + ",";
            		}
            	else if (Tabla.LeerDinArray(i,l) == 'X')
            		{
            			Form11->Equis->Text = Form11->Equis->Text + i + ",";
		            }
        	}
    	Form11->Button1->Click();

        //Despues de mandar los valores a la función de simplificación
        //los recogemos en el StringGrid de Salida donde se visualizaran
		AnsiString cadenaSimp = Form11->Solucion->Text;
        int x = 1;
        int y = 1;

        //Ahora completamos los resultados con ceros para que tengan la misma
        //longitud
        while ( x <= cadenaSimp.Length() )
        {
        	if ( cadenaSimp.SubString(x,1) == "," )
            {
            	if ( (x-y) < Tabla.NumEntradas() )
                {
            		for ( int i=0; i < (x-y);i++)
                    {
                    	cadenaSimp.Insert("0",y);
                        x = x +1;
                    }
                }
                x = x + 1;
                y = x;
            }
            else
            	x = x + 1;
        }

        x = 1;
        y = 1;
        //Con esto transformamos la cadena de salida en letras
		//tenemos que coger los verdaderos nombres de las variables
        while ( x <= cadenaSimp.Length() )
        {
            if ( cadenaSimp.SubString(x,1) == "1" )
            {
            	cadenaSimp.Delete(x,1);
                cadenaSimp.Insert(char('A' - 1 + y),x);
                cadenaSimp.Insert("&",x +1);
                x = x + 2;
                y = y + 1;
            }
            else if (cadenaSimp.SubString(x,1) == "0")
            {
				cadenaSimp.Delete(x,1);
                cadenaSimp.Insert("!&",x);
                cadenaSimp.Insert(char('A' - 1 + y),x+1);
                x = x + 3;
                y = y + 1;
            }

            else if (cadenaSimp.SubString(x,1) == "-")
            {
            	cadenaSimp.Delete(x,1);
                y = y + 1;
            }
            else
            {
            	cadenaSimp.Delete(x-1,2);
               	cadenaSimp.Insert(")#(",x-1);
                x = x + 2;
                y = 1;
            }
        }
        cadenaSimp.Delete(cadenaSimp.Length(),1);
        cadenaSimp.Insert("(" , 1);
        cadenaSimp = cadenaSimp + ")";
        temp = "";
        temp = "|";
       	if ( Tabla.LeerSalida(l) == "" )
        {
           	temp = temp + "F";
            temp = temp + (l+1);
        }
        else
        {
           	temp = temp + Tabla.LeerSalida(l);
        }
        temp = temp + "=" + cadenaSimp;
        temp = NombresCompletos(temp);
        Lista->Add(temp);
	}

        Lista->SaveToFile(GuardaPLD->FileName);
   }
  }
  else
        Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
  else
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);

}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::SalvarSCOClick(TObject *Sender)
{
	AnsiString temp="";
	TStringList *Lista = new TStringList;
	//Invocamos a una función para comprobar que se ha creado el objeto
	if (ComprobarVariables())
        if (Tabla.LeerDinArray(0,0) != ' ')
        {
	    	/* guardamos el objeto en un fichero, es decir guardamos los valores
               que nos interesan en un fichero */
            if (Guardador->Execute())
            {
            	Lista->Add(Tabla.LeerNombre());

                Lista->Add(Tabla.NumEntradas());
				for(int i=0; i < Tabla.NumEntradas();i++)
                	{
						Lista->Add(Tabla.LeerEntrada(i));
                	}

                Lista->Add(Tabla.NumColumnas());
                for(int i=0; i < Tabla.NumColumnas();i++)
                	{
						Lista->Add(Tabla.LeerSalida(i));
                	}
                for (int i=0; i< Tabla.NumColumnas(); i++)
                	{
                        for (int j=0; j< Tabla.NumFilas(); j++)
                        	{
								temp = temp + Tabla.LeerDinArray(j,i);
                            }
                        Lista->Add(temp);
                        temp = "";
                	}
	           	Application->MessageBox(MENSAJE(msgSCGuardadoFichero), "");
                Lista->SaveToFile(Guardador->FileName);
                fTextoAsoc->txAsociado->Lines->SaveToFile(Guardador->FileName + ".txt");

            }
//Ahora funciona cojonudamente sin utilizar el control TMemo y usando un
//objeto de tipo TStringList
        }
  else
        Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
  else
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);

}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::ImprimirDocClick(TObject *Sender)
{
  Imprimir(IMPRESORA);
}

void Imprimir(int destino)
{

int m = 10;
TStringList *Lista = new TStringList;//StringList para tabla de verdad
TStringList *Lista2 = new TStringList;//StringList para diagramas VK
TStringList *Lista3 = new TStringList;//StringList para expresiones simplificadas
TStringList *Lista4 = new TStringList;//StringList para formas normales

if ( ComprobarVariables() )
{
	//Lista->Add("NOMBRE DEL SISTEMA COMBINACIONAL: " + Tabla.LeerNombre());
    Lista->Add("");
    Lista->Add(fTextoAsoc->txAsociado->Lines->Text);
    Lista->Add("");
    Lista->Add(ANSIMENSAJE(msgVarsEntrada)+" : ");
    Lista->Add("");    
	//Escribimos las cabeceras de la hoja diciendo cuales son la variable de entrada
	AnsiString temp = "";
    for ( int i = 0; i < Tabla.NumEntradas() ; i++)
	{
    	temp = "     ";
		temp = temp + char('A' + i);
        temp = temp + " = ";
		temp = temp + Tabla.LeerEntrada(i);
        Lista->Add(temp);
	}
    Lista->Add("");
    Lista->Add(ANSIMENSAJE(msgVarsSalida)+" : ");
    Lista->Add("");
	for ( int i = 0; i < Tabla.NumColumnas() ; i++)
	{
		temp = "     F";
        temp = temp + (i + 1);
        temp = temp + " = ";
		temp = temp + Tabla.LeerSalida(i);
		Lista->Add(temp);
    }
	Lista->Add("");
    Lista->Add("");
    Lista->Add(ANSIMENSAJE(msgTablaVerdad));
    Lista->Add("");
    //Ahora escribimos los nombres genericos de las vbles. de entrada y salida
    temp = "";
	for ( int i = 0 ; i < Tabla.NumEntradas(); i++ )
    {
    	temp = temp + char('A' + i);
        temp = temp + " ";
    }
    temp = temp + "     ";

    for ( int i = 0 ; i < Tabla.NumColumnas(); i++ )
    {
    	temp = temp + "F";
        temp = temp + (i+1);
        temp = temp + " ";
    }
    Lista->Add(temp);

	//Accedemos al objeto para leer sus verdaderos valores
	for ( int i=0; i < Tabla.NumFilas(); i++ )
    {
        temp = "";
        AnsiString paso = CalcularBinario(i,Tabla.NumEntradas());

    	for ( int j=1 ; j <= paso.Length(); j++ )
        {
        	temp = temp + paso.SubString(j,1);
            temp = temp + " ";
        }
        temp = temp + "      ";  ///////<<--

        for ( int j=0 ;j < Tabla.NumColumnas(); j++ )
        {
        	temp = temp + Tabla.LeerDinArray(i,j);
            temp = temp + "  ";
        }
        Lista->Add(temp);
	}

//Aqui empieza el tratamiento para sacar los diagramas de Veitch-Karnaugh

    Lista->Add("");
    Lista->Add("");
    Lista->Add(ANSIMENSAJE(msgDiagramasVK));
    Lista->Add("");
	temp = "";
	switch (Tabla.NumEntradas())
	{
    	case 3 :
        {
            AnsiString comb="000010110100001011111101";
            AnsiString funcion;
            for ( int f= 0; f<Tabla.NumColumnas(); f++)
            {
            	int posicion = 1;
   ///////////////////////////////////////////////////////////////////
				funcion = "F";
                funcion = funcion + (f+1) + " - " + Tabla.LeerSalida(f);
                Lista2->Add(funcion);
                Lista2->Add("");
   ///////////////////////////////////////////////////////////////////
				//Para cada funcion de salida escribimos las cabeceras
            	Lista2->Add("   AB");
            	Lista2->Add("C      00  01  11  10");
        		temp = "    0   ";
            	for (int i=0; i < 4; i++)
            	{
                    temp = temp + Tabla.LeerDinArray(binario(comb.SubString(posicion,3)),f );
                    temp = temp + "   ";
                    posicion = posicion + 3;
            	}

                Lista2->Add(temp);
				temp = "    1   ";
                //posicion = 1;
            	for (int i=0; i < 4; i++)
            	{
                    temp = temp + Tabla.LeerDinArray(binario(comb.SubString(posicion,3)),f );
                    temp = temp + "   ";
                    posicion = posicion + 3;
            	}
                Lista2->Add(temp);
                Lista2->Add("");
                Lista2->Add("");
            }
			break;

        }
    	case 4 :
        {
        	AnsiString filas = "00011110";
            AnsiString cols = "00011110";
            AnsiString funcion;

            for ( int f= 0; f<Tabla.NumColumnas(); f++)
            {
            	funcion = "F";
                funcion = funcion + (f+1) + " - " + Tabla.LeerSalida(f);
                Lista2->Add(funcion);
                Lista2->Add("");
                //
            	AnsiString temp;
                AnsiString valor;
            	int posicion = 1;
				//Para cada funcion de salida escribimos las cabeceras
            	Lista2->Add("    AB");
            	Lista2->Add("CD      00  01  11  10");

            	for (int i=1; i <= 8; i=i+2)
            	{
					temp = "    " + cols.SubString(i,2);////<<<----
                    for (int j=1; j <=8; j=j+2)
					{
                        valor = filas.SubString(j,2) + cols.SubString(i,2);
                    	temp = temp + "   ";
                    	temp = temp + Tabla.LeerDinArray(binario(valor),f );
                    }
                    Lista2->Add(temp);
            	}
                Lista2->Add("");
   	            Lista2->Add("");
            }

			break;
        }

    	case 5 :
        {
        	AnsiString filas = "000001011010110111101100";
            AnsiString cols = "00011110";
            AnsiString funcion;

            for ( int f= 0; f<Tabla.NumColumnas(); f++)
            {
        		funcion = "F";
                funcion = funcion + (f+1) + " - " + Tabla.LeerSalida(f);
                Lista2->Add(funcion);
                Lista2->Add("");
                //
            	AnsiString temp;
                AnsiString valor;
            	int posicion = 1;
				//Para cada funcion de salida escribimos las cabeceras
            	Lista2->Add("    ABC");
            	Lista2->Add("DE      000  001  011  010  110  111  101  100");

            	for (int i=1; i <= 8; i=i+2)
            	{
					temp = "   " + cols.SubString(i,2);  ////<<<<------
                    for (int j=1; j <=24; j=j+3)
					{
                        valor = filas.SubString(j,3) + cols.SubString(i,2);
                    	temp = temp + "    ";
                    	temp = temp + Tabla.LeerDinArray(binario(valor),f );
                    }
                    Lista2->Add(temp);
            	}
                Lista2->Add("");
                Lista2->Add("");
            }

            break;
        }
    	case 6 :
        {
        	AnsiString filas = "000001011010110111101100";
            AnsiString cols = "000001011010110111101100";
            AnsiString funcion;

            for ( int f= 0; f<Tabla.NumColumnas(); f++)
            {
            	funcion = "F";
                funcion = funcion + (f+1) + " - " + Tabla.LeerSalida(f);
                Lista2->Add(funcion);
                Lista2->Add("");
                //
            	AnsiString temp;
                AnsiString valor;
            	int posicion = 1;
				//Para cada funcion de salida escribimos las cabeceras
            	Lista2->Add("    ABC");
            	Lista2->Add("DEF      000  001  011  010  110  111  101  100");

            	for (int i=1; i <= 24; i=i+3)
            	{
					temp = cols.SubString(i,3) + "   ";
                    for (int j=1; j <=24; j=j+3)
					{
                        valor = filas.SubString(j,3) + cols.SubString(i,3);
                    	temp = temp + "    ";
                    	temp = temp + Tabla.LeerDinArray(binario(valor),f );
                    }
                    Lista2->Add(temp);
            	}
                Lista2->Add("");
                Lista2->Add("");
            }
            break;
        }
    }
//Aqui termina el codigo para imprimir los diagramas de Veitch-Karnaugh

//Aqui empieza el codigo para imprimir las formas normales

Lista4->Add(ANSIMENSAJE(msgFormasNormales));
Lista4->Add("");
Lista4->Add(ANSIMENSAJE(msgFormaDisyun));
Lista4->Add("");
char paso = ' ';
String funcion = " ";
String cadenaForma = " ";
    for (int j=0; j<Tabla.NumColumnas(); j++)
    {
      	funcion = "F";
        funcion = funcion + (j+1) + ": ";
        cadenaForma = funcion;

    	for (int i = 0; i<Tabla.NumFilas(); i++)
        {
        	 if ((Tabla.LeerDinArray(i,j) == '1'))
             {
             //Esta condicion es para incluir comas entre los numeros
                if (paso != ' '){
					cadenaForma = cadenaForma + ", ";
                }
                paso = '-';
				cadenaForma = cadenaForma + i;
             }
        }
        paso = ' ';
        Lista4->Add(cadenaForma);
	}
Lista4->Add("");
Lista4->Add(ANSIMENSAJE(msgFormaConjun));
Lista4->Add("");


    for (int j=0; j<Tabla.NumColumnas(); j++)
    {
      	funcion = "F";
        funcion = funcion + (j+1) + ": ";
        cadenaForma = funcion;

    	for (int i = 0; i<Tabla.NumFilas(); i++)
        {
        	 if ((Tabla.LeerDinArray(i,j) == '0'))
             {
             //Esta condicion es para incluir comas entre los numeros
                if (paso != ' '){
                    cadenaForma = cadenaForma + ", ";
                }
                cadenaForma = cadenaForma + i;
                paso = '-';
             }
        }
        paso = ' ';
        Lista4->Add(cadenaForma);
	}

Lista4->Add("");


Lista4->Add("");
Lista4->Add(ANSIMENSAJE(msgTerminosIrrelevantes));
Lista4->Add("");

	for (int j=0; j<Tabla.NumColumnas(); j++)
    {
      	funcion = "F";
        funcion = funcion + (j+1) + ": ";
		cadenaForma = funcion;

    	for (int i = 0; i<Tabla.NumFilas(); i++)
        {
        	 if ((Tabla.LeerDinArray(i,j) == 'X'))
             {
             //Esta condicion es para incluir comas entre los numeros
                if (paso != ' '){
                    cadenaForma = cadenaForma + ", ";
                }
				paso = '-';
               	cadenaForma = cadenaForma + i;
             }
        }
        paso = ' ';
        Lista4->Add(cadenaForma);
	}

//Aqui acaba el codigo para imprimir las formas normales



//Aqui empieza el código para imprimir las expresiones simplificadas SOP

    TStringList *ListaSOP = new TStringList;
    Form11->NumC->Text = Tabla.NumEntradas();
    ListaSOP->Add("");
    ListaSOP->Add("");
	ListaSOP->Add(ANSIMENSAJE(msgExprsSOPSimpl));
    ListaSOP->Add("");

    // Recogemos los valores de la tabla para hacer la simplificacion
    for (int l=0; l<Tabla.NumColumnas(); l++)
    {
	    Form11->Unos->Text = "";
        Form11->Equis->Text = "";
    	for (int i = 0; i<Tabla.NumFilas(); i++)
        {
        	if (Tabla.LeerDinArray(i,l) == '1')
            {
             	Form11->Unos->Text = Form11->Unos->Text + i + ",";
            }
            else if (Tabla.LeerDinArray(i,l) == 'X')
            {
            	Form11->Equis->Text = Form11->Equis->Text + i + ",";
            }
        }
    	Form11->Button1->Click();

        //Despues de mandar los valores a la función de simplificación
        //los recogemos en el StringGrid de Salida donde se visualizaran
		AnsiString cadenaSimp = Form11->Solucion->Text;
        AnsiString cadenaLlena;
        for (int i=1; i<=Tabla.NumEntradas(); i++)
        {
        	cadenaLlena = cadenaLlena + "-";
        }

        if (cadenaSimp == "")
            	cadenaSimp = "0";
        else if (cadenaSimp == cadenaLlena)
            	cadenaSimp = "1";
        else
        {
           	int x = 1;
	        int y = 1;

	        //  Con esto transformamos la cadena de salida en letras
	        while ( x <= cadenaSimp.Length() )
	        {
	            if ( cadenaSimp.SubString(x,1) == "1" )
	            {
	            	cadenaSimp.Delete(x,1);
    	            cadenaSimp.Insert(char('A' - 1 + y),x);
	                cadenaSimp.Insert("*",x +1);
	                x = x + 2;
	                y = y + 1;
	            }
	            else if (cadenaSimp.SubString(x,1) == "0")
	            {
					cadenaSimp.Delete(x,1);
	                cadenaSimp.Insert("~*",x);
	                cadenaSimp.Insert(char('A' - 1 + y),x+1);
	                x = x + 3;
	                y = y + 1;
	            }

	            else if (cadenaSimp.SubString(x,1) == "-")
	            {
	            	cadenaSimp.Delete(x,1);
	                y = y + 1;
	            }
    	        else
	            {
	            	cadenaSimp.Delete(x-1,2);
	               	cadenaSimp.Insert(")+(",x-1);
    	            x = x + 2;
	                y = 1;
	            }
	        }
	        cadenaSimp.Delete(cadenaSimp.Length(),1);
	        cadenaSimp.Insert("(" , 1);
    	    cadenaSimp = cadenaSimp + ")";
        }
        AnsiString funcion;
        funcion = "F";
        funcion = funcion + l + " : ";
		cadenaSimp =  funcion + cadenaSimp;
	    ListaSOP->Add(cadenaSimp);
        ListaSOP->Add("");
	    //Escribimos el resultado en el StringGrid para visualizarlo
    }

//Aqui termina el codigo para imprimir las expresiones simplificadas SOP


//Aqui empieza el codigo para imprimir las expresiones simplificadas POS

    TStringList *ListaPOS = new TStringList;
    Form11->NumC->Text = Tabla.NumEntradas();
    ListaPOS->Add("");
	ListaPOS->Add(ANSIMENSAJE(msgExprsPOSSimpl));
    ListaPOS->Add("");

    // Recogemos los valores de la tabla para hacer la simplificacion
    for (int l=0; l<Tabla.NumColumnas(); l++)
    {
	    Form11->Unos->Text = "";
        Form11->Equis->Text = "";
    	for (int i = 0; i<Tabla.NumFilas(); i++)
        {
        	if (Tabla.LeerDinArray(i,l) == '0')
            {
             	Form11->Unos->Text = Form11->Unos->Text + i + ",";
            }
            else if (Tabla.LeerDinArray(i,l) == 'X')
            {
            	Form11->Equis->Text = Form11->Equis->Text + i + ",";
            }
        }
    	Form11->Button1->Click();

        //Despues de mandar los valores a la función de simplificación
        //los recogemos en el StringGrid de Salida donde se visualizaran
		AnsiString cadenaSimp = Form11->Solucion->Text;
        AnsiString cadenaLlena;
        for (int i=1; i<=Tabla.NumEntradas(); i++)
        {
        	cadenaLlena = cadenaLlena + "-";
        }

        if (cadenaSimp == "")
        	cadenaSimp = "1";
        else if (cadenaSimp == cadenaLlena)
           	cadenaSimp = "0";
        else
        {
        	int x = 1;
	        int y = 1;

	        //  Con esto transformamos la cadena de salida en letras
	        while ( x <= cadenaSimp.Length() )
	        {
	            if ( cadenaSimp.SubString(x,1) == "1" )
	            {
	            	cadenaSimp.Delete(x,1);
    	            cadenaSimp.Insert(char('A' - 1 + y),x);
	                cadenaSimp.Insert("*",x +1);
	                x = x + 2;
	                y = y + 1;
	            }
	            else if (cadenaSimp.SubString(x,1) == "0")
	            {
					cadenaSimp.Delete(x,1);
	                cadenaSimp.Insert("~*",x);
	                cadenaSimp.Insert(char('A' - 1 + y),x+1);
	                x = x + 3;
	                y = y + 1;
	            }

	            else if (cadenaSimp.SubString(x,1) == "-")
	            {
	            	cadenaSimp.Delete(x,1);
	                y = y + 1;
	            }
    	        else
	            {
	            	cadenaSimp.Delete(x-1,2);
	               	cadenaSimp.Insert(")+(",x-1);
    	            x = x + 2;
	                y = 1;
	            }
	        }
	        cadenaSimp.Delete(cadenaSimp.Length(),1);
	        cadenaSimp.Insert("(" , 1);
    	    cadenaSimp = cadenaSimp + ")";

    	    //Si es POS entonces tenemos que invertir las variables y cambiar los
	        //operadores tanto internos y externos
        	cadenaSimp = InvertirVariables(cadenaSimp);
            cadenaSimp = CambiarSignos(cadenaSimp,false);
            cadenaSimp = CambiarSignos(cadenaSimp,true);
        }
        AnsiString funcion;
        funcion = "F";
        funcion = funcion + l + " : ";
		cadenaSimp =  funcion + cadenaSimp;
	    ListaPOS->Add(cadenaSimp);
        ListaPOS->Add("");
	    //Escribimos el resultado en el StringGrid para visualizarlo
    }
//Aqui termina el codigo para imprimir las expresiones simplificadas POS

//	CTexto->Text = Lista->Text + Lista2->Text + Lista4->Text + ListaSOP->Text + ListaPOS->Text;

    TStringList *l=new TStringList;

  //	CTexto->Text = Lista->Text + Lista2->Text + Lista4->Text + ListaSOP->Text + ListaPOS->Text;

    for ( int n = 0; n < Lista->Count; n++ ){
        l->Add (Lista->Strings[n]);
    }
    for ( int n = 0; n < Lista2->Count; n++ ){
        l->Add (Lista2->Strings[n]);
    }
    for ( int n = 0; n < Lista4->Count; n++ ){
        l->Add (Lista4->Strings[n]);
    }
    for ( int n = 0; n < ListaSOP->Count; n++ ){
        l->Add (ListaSOP->Strings[n]);
    }
    for ( int n = 0; n < ListaPOS->Count; n++ ){
        l->Add (ListaPOS->Strings[n]);
    }

  if (destino == IMPRESORA)
  {

   	if ( SistemaCombinacionalNuevo->impresora->Execute())
  	{

  		Printer()->Title = Tabla.LeerNombre();
      	Printer()->BeginDoc();
  		Printer()->Canvas->Font->Name = "Courier";
          m = 60;
          Printer()->Canvas->Font->Size=14;
          Printer()->Canvas->TextOut(100,m,ANSIMENSAJE(msgSistemaCombi));
          m += Printer()->Canvas->TextHeight("XXX");
          Printer()->Canvas->Font->Size=9;
          Printer()->Canvas->TextOut(100,m,ANSIMENSAJE(msgNombreSC)+" : " + SistemaCombinacionalNuevo->Edit1->Text);
          m += Printer()->Canvas->TextHeight("XXX");
          Printer()->Canvas->Font->Size=9;
         	for ( int n = 0; n < l->Count; n++ )
        {
                if (l->Strings[n]!="")
        	    Printer()->Canvas->TextOut(100, m,l->Strings[n]);
              m += Printer()->Canvas->TextHeight("XXX");
                if ( m + Printer()->Canvas->TextHeight("XXX") > Printer()->PageHeight )
              {
              	Printer()->NewPage();
                  m = 40;
              }
          }


          Printer()->EndDoc();

   	}
  }
  else if (destino == PORTAPAPELES)
  {
    l->Insert(0, ANSIMENSAJE(msgNombreSC)+" : " + SistemaCombinacionalNuevo->Edit1->Text);
    l->Insert(0, "");
    l->Insert(0, ANSIMENSAJE(msgSistemaCombi));

    Clipboard()->Clear();
    Clipboard()->SetTextBuf(l->Text.c_str());
  }
}
else
	Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::CargarSistemaClick(TObject *Sender)
{
TStringList *Lista = new TStringList;
AnsiString Prueba;
TFileStream *lectorTexto;

//int numerofilas;
int numerocolumnas;

 	if (Cargador->Execute())
	{	//Capturamos interrupcion en caso de que exista un error
    	try	{
			  Lista->LoadFromFile(Cargador->FileName);
 	   		}//Ahora el sistema esta en el objeto de tipo TStringList
	   	catch(...)
	   		{
	   		Application->MessageBox(MENSAJE(msgErrorCargar), NULL);
	   		}
      AnsiString nombreAsoc = Cargador->FileName + ".txt";
      if (FileExists(nombreAsoc))
        fTextoAsoc->txAsociado->Lines->LoadFromFile(nombreAsoc);
      else
        fTextoAsoc->txAsociado->Clear();
    }
	if (Lista->Text != "")
	{
	    Edit1->Text = Lista->Strings[0];
	    NEntradas->Text = Lista->Strings[1];
	    int j = atol(NEntradas->Text.c_str()) + 2;
	    for ( int i = 2; i <  j; i++)
	    {
    	    //Escribimos en el grid los nombres de las variables de entrada
	        TablaEntrada->Cells[1][i-2] = Lista->Strings[i];
		    }
    	NSalidas->Text = Lista->Strings[j];
	    int i = j +1;
	    int paso = i;
	    j = j + atol(NSalidas->Text.c_str());
	    //int i = j;
    	for (i ; i <= j;i++)
	    {	//Escribimos en el grid los nombres de las variables de salida
	        TablaSalida->Cells[1][i-paso] = Lista->Strings[i];
	   	}
	    // La variable i contiene la posicion donde empiezan los valores de
	    // la tabla
    	//Ahora escribimos los datos en el objeto
	    Tabla.DinX(Edit1->Text.SubString(0,40),
		        			(TablaEntrada->RowCount),
		                    (TablaSalida->RowCount) );
	    //Y por ultimo escribimos los datos de la(s) salida(s)
    	//Quitamos esta vble
	    //numerofilas = atol(NEntradas->Text.c_str());
	    numerocolumnas = atol(NSalidas->Text.c_str());
		//Ahora tenemos que coger las cadenas que contienen los datos y
	    //escribirlas en la Tabla
	    AnsiString temp;
	    for (int  k=1 ; (k <= numerocolumnas); k++ )
    	{
	    	for (int l = 1; l <= Tabla.NumFilas(); l++)
	        {
	            temp= Lista->Strings[i].SubString(l,1).c_str();
	            char *valor = temp.c_str();
	        	Tabla.EscribirDinArray(l-1, k-1, *valor);
	        }
    	    i= i +1;
	    }
	    Application->MessageBox(MENSAJE(msgSCCargadoFichero), "");
    }
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::CerrarClick(TObject *Sender)
{
    for(int i=0; i < TablaEntrada->RowCount; i++)
    {
    	TablaEntrada->Cells[1][i] = "";
    }
    TablaEntrada->RowCount = 1;
    TablaEntrada->Enabled = false;
    TablaEntrada->Color = clInactiveCaption;

    for(int i=0; i < TablaSalida->RowCount; i++)
    {
    	TablaSalida->Cells[1][i] = "";
    }
	TablaSalida->RowCount = 1;
    TablaSalida->Enabled = false;
    TablaSalida->Color = clInactiveCaption;

    Tabla.BorrarDinArray();
    Edit1->Text = "";
    NEntradas->Text = "";
    NSalidas->Text = "";

    Principal->Visible = true;
	SistemaCombinacionalNuevo->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TSistemaCombinacionalNuevo::Button4Click(TObject *Sender)
{
    if ( ComprobarVariables() )
    {
        if (Tabla.LeerDinArray(0,0) != ' ')
        {
                AnsiString cadena;
        	cadena = NEntradas->Text;
        	long numVars = atol(cadena.c_str());
                fKarnaugh->setFormato(FORMATO_SOP);
                fKarnaugh->setNumVars(numVars);
                fKarnaugh->setModo(MODO_APRENDIZAJE_LAZOS);

        	fKarnaugh->ShowModal();
        }
        else
			Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);
    }

}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::SOPSimpExit(TObject *Sender)
{
    ExpresionSimp->nnor->Checked = false;

}
//---------------------------------------------------------------------------


void __fastcall TSistemaCombinacionalNuevo::Button5Click(TObject *Sender)
{
		FormR->Titulo = MENSAJE(msgVisuCircuitos);
		FormR->ecuacion->Text = "";

		FormR->tipoCircuito = false;
    FormR->ListaSol->Visible = false;
    FormR->Lista->Visible = false;				// Circuito Combinacional.
		FormR->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TSistemaCombinacionalNuevo::Button6Click(TObject *Sender)
{
  Application->MessageBox(MENSAJE(msgReductio), "");
  ShellExecute(Handle, "open", "reductio.exe", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::BitBtn1Click(TObject *Sender)
{
  Imprimir(PORTAPAPELES);  
}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::Edit1Change(TObject *Sender)
{
  Tabla.EscribirNombre(Edit1->Text);
}
//---------------------------------------------------------------------------


void __fastcall TSistemaCombinacionalNuevo::BitBtn2Click(TObject *Sender)
{
  fTextoAsoc->Show();
}
//---------------------------------------------------------------------------

AnsiString NombreVHDL(AnsiString st)
{
	st = st.Trim();
	for(int i=1; i<=st.Length(); i++)
        	if (st[i]==' ')
                	st[i]='_';
        return st;
}


void __fastcall TSistemaCombinacionalNuevo::BitBtn3Click(TObject *Sender)
{
	AnsiString temp="";
	TStringList *Lista = new TStringList;
        AnsiString Titulo = Tabla.LeerNombre();
	//Invocamos a una función para comprobar que se ha creado el objeto
	if (ComprobarVariables())
	        if (Tabla.LeerDinArray(0,0) != ' ')
        	{
                    GuardaPLD->Filter=MENSAJE(msgFiltroVHDL);
	            if (GuardaPLD->Execute())
	            {
		        // Cabecera
	       	        Lista->Add("library IEEE;");
		        Lista->Add("use IEEE.STD_LOGIC_1164.ALL;");
		        Lista->Add("use IEEE.STD_LOGIC_ARITH.ALL;");
		        Lista->Add("use IEEE.STD_LOGIC_UNSIGNED.ALL;");

		        Lista->Add("");

		        // Nombre de la entidad
			Lista->Add("entity " + Titulo + " is");
			Lista->Add("\tPort (");
			for (int i=0; i<Tabla.NumEntradas();i++)
                        {
                        	AnsiString nombre =  Tabla.LeerEntrada(i);
                                nombre=(nombre==""?AnsiString(char('A'+i)):nombre);
				Lista->Add("\t\t" + NombreVHDL(nombre) + ": in std_logic;");
                        }
			for (int i=0; i<Tabla.NumColumnas();i++)
                        {
                        	AnsiString nombre =  Tabla.LeerSalida(i);
                                nombre=(nombre==""?"S"+AnsiString(i):nombre);
				Lista->Add("\t\t" + NombreVHDL(nombre) + ": out std_logic" + ((i==Tabla.NumColumnas()-1)?"":";"));
                        }
			Lista->Add("\t\t);");
			Lista->Add("end " + Titulo + ";");

		        Lista->Add("");

		        Lista->Add("architecture behavioral of " + Titulo + " is");
		        Lista->Add("begin");

		        ExpresionSimp->StringGrid1->RowCount = Tabla.NumColumnas();
		        ExpresionSimp->POS->Checked = false;
                        ExpresionSimp->calcularSimplificada(NULL);

			for (int i=0; i<Tabla.NumColumnas();i++)
                        {
                        	AnsiString formula = ExpresionSimp->StringGrid1->Cells[0][i];
                                AnsiString formulaVHDL;

                        	if(formula == "0" || formula == "1")
                                	formulaVHDL = "'" + formula + "'";
                                else
                                {
	                        	formula = NombresCompletos(formula);
	                                formulaVHDL = "(";

	                                bool faltaCerrarNot = false;
	                                for(int j = 1; j <= formula.Length(); j++)
	                                {

	                                	switch(formula[j])
	                                        {
	                                        	case '~':
	                                                	formulaVHDL += "not(";
								faltaCerrarNot = true;
	                                                break;
	                                                case '*':
	                                                	if (faltaCerrarNot)
                                                                {
	                                                        	formulaVHDL += ")";
		 							faltaCerrarNot = false;
                                                                }
	                                                	formulaVHDL += " and ";
	                                                break;
	                                                case '+':
	                                                	if (faltaCerrarNot)
                                                                {
	                                                        	formulaVHDL += ")";
		 							faltaCerrarNot = false;
                                                                }
	                                                	formulaVHDL += " or ";
	                                                break;
	                                                case '(':
		                                                formulaVHDL += "(";
	                                                break;
	                                                case ')':
	                                                	if (faltaCerrarNot)
                                                                {
	                                                        	formulaVHDL += ")";
		 							faltaCerrarNot = false;
                                                                }
	                                                	formulaVHDL += ")";
	                                                break;
	                                                default:
		                                               	formulaVHDL += formula[j];
	                                        }
	                                }
					formulaVHDL += ")";
                                }
                        	AnsiString nombre =  Tabla.LeerSalida(i);
                                nombre=(nombre==""?"S"+AnsiString(i):nombre);

				// MOD: Semicolon wasn't being added to end the statement. ~lrg
				Lista->Add("\t" + NombreVHDL(nombre) + "<=" + formulaVHDL+ ";");
                        }

		        Lista->Add("end behavioral;");
                        Lista->SaveToFile(GuardaPLD->FileName);
                    }
                }
  else
        Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
  else
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);
}
			/*
		    	// Recogemos los valores de la tabla para hacer la simplificacion
		    	for (int l=0; l<Tabla.NumColumnas(); l++)
		    	{
                        	Form11->Unos->Text = "";
		        	Form11->Equis->Text = "";
			       	ExpresionSimp->StringGrid1->Cells[0][l] = "";
				for (int i = 0; i<Tabla.NumFilas(); i++)
		        	{
		        		if ( ((Tabla.LeerDinArray(i,l) == '1') && (ExpresionSimp->POS->Checked == false)) ||
	            			 ((Tabla.LeerDinArray(i,l) == '0') && (ExpresionSimp->POS->Checked == true)) )
        		    		{
             					Form11->Unos->Text = Form11->Unos->Text + i + ",";
		            		}
			            	else if (Tabla.LeerDinArray(i,l) == 'X')
		            		{
		            			Form11->Equis->Text = Form11->Equis->Text + i + ",";
					}
		        	}
			    	Form11->Button1->Click();

			        //Despues de mandar los valores a la función de simplificación
			        //los recogemos en el StringGrid de Salida donde se visualizaran
				AnsiString cadenaSimp = Form11->Solucion->Text;
	/*
        int x = 1;
        int y = 1;

        //Ahora completamos los resultados con ceros para que tengan la misma
        //longitud
        while ( x <= cadenaSimp.Length() )
        {
        	if ( cadenaSimp.SubString(x,1) == "," )
            {
            	if ( (x-y) < Tabla.NumEntradas() )
                {
            		for ( int i=0; i < (x-y);i++)
                    {
                    	cadenaSimp.Insert("0",y);
                        x = x +1;
                    }
                }
                x = x + 1;
                y = x;
            }
            else
            	x = x + 1;
        }

        x = 1;
        y = 1;
        //Con esto transformamos la cadena de salida en letras
		//tenemos que coger los verdaderos nombres de las variables
        while ( x <= cadenaSimp.Length() )
        {
            if ( cadenaSimp.SubString(x,1) == "1" )
            {
            	cadenaSimp.Delete(x,1);
                cadenaSimp.Insert(char('A' - 1 + y),x);
                cadenaSimp.Insert("&",x +1);
                x = x + 2;
                y = y + 1;
            }
            else if (cadenaSimp.SubString(x,1) == "0")
            {
				cadenaSimp.Delete(x,1);
                cadenaSimp.Insert("!&",x);
                cadenaSimp.Insert(char('A' - 1 + y),x+1);
                x = x + 3;
                y = y + 1;
            }

            else if (cadenaSimp.SubString(x,1) == "-")
            {
            	cadenaSimp.Delete(x,1);
                y = y + 1;
            }
            else
            {
            	cadenaSimp.Delete(x-1,2);
               	cadenaSimp.Insert(")#(",x-1);
                x = x + 2;
                y = 1;
            }
        }
        cadenaSimp.Delete(cadenaSimp.Length(),1);
        cadenaSimp.Insert("(" , 1);
        cadenaSimp = cadenaSimp + ")";
        temp = "";
        temp = "|";
       	if ( Tabla.LeerSalida(l) == "" )
        {
           	temp = temp + "F";
            temp = temp + (l+1);
        }
        else
        {
           	temp = temp + Tabla.LeerSalida(l);
        }
        temp = temp + "=" + cadenaSimp;
        temp = NombresCompletos(temp);
        Lista->Add(temp);
	}

        Lista->SaveToFile(GuardaPLD->FileName);
   }
  }
  else
        	ShowMessage("el sistema combinacional no ha sido creado todavia");
  else
    	ShowMessage("numero incorrecto de variables");
        */
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::DiagramaVKClick(
      TObject *Sender)
{
    if (ComprobarVariables())
    {
	AnsiString cadena;
	cadena = NEntradas->Text;
	long numVars = atol(cadena.c_str());
        fKarnaugh->setNumVars(numVars);
        fKarnaugh->setModo(MODO_EDITABLE);


	fKarnaugh->ShowModal();
    }
    else
    {
    	Application->MessageBox(MENSAJE(msgNumeroVariables), NULL);
    }


}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::BitBtn4Click(TObject *Sender)
{

     // Este botón genera codigo Jedec PLCC (Todo el código de este método
     // es idéntico al codigo del método para generar Jedec DIP, salvo el
     // tipo de encapsulado, por lo que cualquier cambio en uno de ellos
     // debe ser hecho también el el otro: BitBtn5Click)

 	if (ComprobarVariables())
	        if (Tabla.LeerDinArray(0,0) != ' ')
        	{
                    GuardaPLD->Filter=MENSAJE(msgFiltroJEDEC);
	            if (GuardaPLD->Execute())
	            {
                    	list <list<string> > listFunciones;
			AnsiString cadena;
			cadena = NEntradas->Text;
			long numVars = atol(cadena.c_str());

			for(int i = 0; i < Tabla.NumColumnas(); i++)
			{
                        	list<string> listCubos;

                                listCubos.push_back(string("c"));
                                AnsiString nombre =  Tabla.LeerSalida(i);
                                nombre=(nombre==""?"S"+AnsiString(i):nombre);
                                listCubos.push_back(string(nombre.c_str()));

				rdSimplificador *simp;
			        simp = new rdSimplificador(numVars);
		        	// 0 --> Obtención de IPs por el método Q-M
			        simp->SetObtenedor(0);
			        // 0 --> Seleccion de IPs por método recursivo sesgado
				simp->SetSelector(0);
				for(int j = 0; j < Tabla.NumFilas(); j++)
				{
					CuboBool cAux=CuboBool(j);
					cAux.literales = numVars;

					if (Tabla.LeerDinArray(j, i) == '1')
		                                simp->AnyadirMint(cAux);
					else if(Tabla.LeerDinArray(j, i) == 'X')
		                                simp->AnyadirTI(cAux);
				}
				simp->Simplificar();

                                for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
		                {
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}

                		delete simp;
                                for(list<string>::iterator i=listCubos.begin(); i!= listCubos.end(); i++)
                                {
                                	string s = *i;
                                }
                                listFunciones.push_back(listCubos);
		        }

                        string entradas[100];
                        for (int i=0; i<Tabla.NumEntradas();i++)
                        {
                        	AnsiString nombre =  Tabla.LeerEntrada(i);
                                nombre=(nombre==""?AnsiString(char('A'+i)):nombre);
				entradas[i]=string(NombreVHDL(nombre).c_str());
                                string nombre2 = entradas[i];
                        }

                        Device dev("GAL22V10", 24, 5828, 44, GAL22V10_PLCC);
                        // Device dev("GAL22V10", 24, 5828, 44, GAL22V10_DIP);
			Jedec jedec(listFunciones, dev, entradas, GuardaPLD->FileName.SubString(1,GuardaPLD->FileName.Length()-4).c_str());
			if(jedec.GetCodigoFlagError())
				Application->MessageBox(jedec.GetTextoFlagError(), NULL);
                    }
                }
  else
        Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
  else
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);


}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::BitBtn5Click(TObject *Sender)
{

     // Este botón genera codigo Jedec DIP (Todo el código de este método
     // es idéntico al codigo del método para generar Jedec PLCC, salvo el
     // tipo de encapsulado, por lo que cualquier cambio en uno de ellos
     // debe ser hecho también el el otro: BitBtn4Click)


       	if (ComprobarVariables())
	        if (Tabla.LeerDinArray(0,0) != ' ')
        	{
                    GuardaPLD->Filter=MENSAJE(msgFiltroJEDEC);
	            if (GuardaPLD->Execute())
	            {
                    	list <list<string> > listFunciones;
			AnsiString cadena;
			cadena = NEntradas->Text;
			long numVars = atol(cadena.c_str());

			for(int i = 0; i < Tabla.NumColumnas(); i++)
			{
                        	list<string> listCubos;

                                listCubos.push_back(string("c"));
                                AnsiString nombre =  Tabla.LeerSalida(i);
                                nombre=(nombre==""?"S"+AnsiString(i):nombre);
                                listCubos.push_back(string(nombre.c_str()));

				rdSimplificador *simp;
			        simp = new rdSimplificador(numVars);
		        	// 0 --> Obtención de IPs por el método Q-M
			        simp->SetObtenedor(0);
			        // 0 --> Seleccion de IPs por método recursivo sesgado
				simp->SetSelector(0);
				for(int j = 0; j < Tabla.NumFilas(); j++)
				{
					CuboBool cAux=CuboBool(j);
					cAux.literales = numVars;

					if (Tabla.LeerDinArray(j, i) == '1')
		                                simp->AnyadirMint(cAux);
					else if(Tabla.LeerDinArray(j, i) == 'X')
		                                simp->AnyadirTI(cAux);
				}
				simp->Simplificar();

                                for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
		                {
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}


				for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
				{
                                	listCubos.push_back((*j).aString(numVars));
				}

                		delete simp;
                                for(list<string>::iterator i=listCubos.begin(); i!= listCubos.end(); i++)
                                {
                                	string s = *i;
                                }
                                listFunciones.push_back(listCubos);
		        }

                        string entradas[100];
                        for (int i=0; i<Tabla.NumEntradas();i++)
                        {
                        	AnsiString nombre =  Tabla.LeerEntrada(i);
                                nombre=(nombre==""?AnsiString(char('A'+i)):nombre);
				entradas[i]=string(NombreVHDL(nombre).c_str());
                                string nombre2 = entradas[i];
                        }


                        // Device dev("GAL22V10", 24, 5828, 44, GAL22V10_PLCC);
                        Device dev("GAL22V10", 24, 5828, 44, GAL22V10_DIP);
			Jedec jedec(listFunciones, dev, entradas, GuardaPLD->FileName.SubString(1,GuardaPLD->FileName.Length()-4).c_str());
			if(jedec.GetCodigoFlagError())
				Application->MessageBox(jedec.GetTextoFlagError(), NULL);
                    }
                }
  else
        Application->MessageBox(MENSAJE(msgSCTodaviaNoCreado), NULL);
  else
    	Application->MessageBox(MENSAJE(msgNumVarsIncorrecto), NULL);


}


//---------------------------------------------------------------------------




void __fastcall TSistemaCombinacionalNuevo::btWeblabClick(TObject *Sender)
{
    WeblabForm->ShowModal();        
}
//---------------------------------------------------------------------------



void __fastcall TSistemaCombinacionalNuevo::OnTablaEntradaSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
        if(ACol == 1)
        {
                InicializarEntradasSalidasWeblab();
                comboBox->Clear();
                for(int i = 0; i < mEntradasWeblab.size(); ++i)
                        comboBox->Items->Add(mEntradasWeblab[i].c_str());

                TRect R = TablaEntrada->CellRect(ACol, ARow);
                R.Left += TablaEntrada->Left;
                R.Right += TablaEntrada->Left;
                R.Top += TablaEntrada->Top;
                R.Bottom += TablaEntrada->Top;

                comboBox->Left = R.Left + 10;
                comboBox->Top = R.Top + 50;
                comboBox->Width = (R.Right + 1) - R.Left;
                comboBox->Height = (R.Bottom + 1) - R.Top;

                tablaActual = TablaEntrada;

                comboBox->Visible = true;
                comboBox->SetFocus();
        }
}
//---------------------------------------------------------------------------



void __fastcall TSistemaCombinacionalNuevo::OnTablaSalidaSelectCell(
      TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
        if(ACol == 1)
        {
                InicializarEntradasSalidasWeblab();
                comboBox->Clear();
                for(int i = 0; i < mSalidasWeblab.size(); ++i)
                        comboBox->Items->Add(mSalidasWeblab[i].c_str());

                TRect R = TablaSalida->CellRect(ACol, ARow);
                R.Left += TablaSalida->Left;
                R.Right += TablaSalida->Left;
                R.Top += TablaSalida->Top;
                R.Bottom += TablaSalida->Top;

                comboBox->Left = R.Left + 10;
                comboBox->Top = R.Top + 50;
                comboBox->Width = (R.Right + 1) - R.Left;
                comboBox->Height = (R.Bottom + 1) - R.Top;

                tablaActual = TablaSalida;

                comboBox->Visible = true;
                comboBox->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::OnComboBoxExit(TObject *Sender)
{
        comboBox->Visible = false;
        tablaActual->Cells[tablaActual->Col][tablaActual->Row] =
                comboBox->Text;
        tablaActual->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::OnComboBoxChange(
      TObject *Sender)
{
  // Change goes here
}
//---------------------------------------------------------------------------

void __fastcall TSistemaCombinacionalNuevo::OnTablaEntradaSetEditText(
      TObject *Sender, int ACol, int ARow, const AnsiString Value)
{
 // set Edit
}
//---------------------------------------------------------------------------


void TSistemaCombinacionalNuevo::QuitarSeleccionTablas()
{
        TGridRect r;
        r.Left = -1;
        r.Right = -1;
        r.Bottom = -1;
        r.Top = -1;
        TablaEntrada->Selection = r;
        TablaSalida->Selection = r;
}



void TSistemaCombinacionalNuevo::InicializarEntradasSalidasWeblab()
{
        mEntradasWeblab.clear();
        mSalidasWeblab.clear();

        mEntradasWeblab.push_back("Switches<0>");
        mEntradasWeblab.push_back("Switches<1>");
        mEntradasWeblab.push_back("Switches<2>");
        mEntradasWeblab.push_back("Switches<3>");
        mEntradasWeblab.push_back("Switches<4>");
        mEntradasWeblab.push_back("Switches<5>");
        mEntradasWeblab.push_back("Switches<6>");
        mEntradasWeblab.push_back("Switches<7>");
        mEntradasWeblab.push_back("Switches<8>");
        mEntradasWeblab.push_back("Switches<9>");
        mEntradasWeblab.push_back("Buttons<0>");
        mEntradasWeblab.push_back("Buttons<1>");
        mEntradasWeblab.push_back("Buttons<2>");
        mEntradasWeblab.push_back("Buttons<3>");

        mSalidasWeblab.push_back("Leds<0>");
        mSalidasWeblab.push_back("Leds<1>");
        mSalidasWeblab.push_back("Leds<2>");
        mSalidasWeblab.push_back("Leds<3>");
        mSalidasWeblab.push_back("Leds<4>");
        mSalidasWeblab.push_back("Leds<5>");
        mSalidasWeblab.push_back("Leds<6>");
        mSalidasWeblab.push_back("Leds<7>");
        mSalidasWeblab.push_back("SevenSeg<0>");
        mSalidasWeblab.push_back("SevenSeg<1>");
        mSalidasWeblab.push_back("SevenSeg<2>");
        mSalidasWeblab.push_back("SevenSeg<3>");
        mSalidasWeblab.push_back("SevenSeg<4>");
        mSalidasWeblab.push_back("SevenSeg<5>");
        mSalidasWeblab.push_back("SevenSeg<6>");
        mSalidasWeblab.push_back("Dot");
        mSalidasWeblab.push_back("EnableSegOut<0>");
        mSalidasWeblab.push_back("EnableSegOut<1>");
        mSalidasWeblab.push_back("EnableSegOut<2>");
        mSalidasWeblab.push_back("EnableSegOut<3>");
}


// Por algún motivo, esta función se llama pero la inicialización de las
// entradas no permanece.
void __fastcall TSistemaCombinacionalNuevo::OnCreate(TObject *Sender)
{
        InicializarEntradasSalidasWeblab();
}
//---------------------------------------------------------------------------

