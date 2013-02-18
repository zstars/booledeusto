//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uKarnaugh.h"
#include "DinArray.h"
#include "reductio\rdsimplificador.h"
#include <vcl\Clipbrd.hpp>
#include "EvaluadorBool.hpp"
#include "Libreria.h"
#include "mensajes.inc"
#include <algorithm>
#include <list>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Karnaugh"
#pragma resource "*.dfm"
TfKarnaugh *fKarnaugh;
extern DinArray Tabla;
//---------------------------------------------------------------------------
__fastcall TfKarnaugh::TfKarnaugh(TComponent* Owner)
	: TForm(Owner)
{
	vectorMint = new vector<set<CuboBool> >;
	vectorMaxt = new vector<set<CuboBool> >;
	vectorTIs = new vector<set<CuboBool> >;
	vectorIPs = new vector<set<CuboBool> >;
	vectorLazo = new vector<set<CuboBool> >;
	vectorIPsDibujados = new vector<set<CuboBool> >;
        vectorIPsLazos = new vector<CuboBool>;
        vectorLiteralesSoluciones = new vector<int>;
}
//---------------------------------------------------------------------------


 __fastcall TfKarnaugh::~TfKarnaugh()
{
	delete vectorMint;
	delete vectorMaxt;
        delete vectorTIs;
        delete vectorIPs;
        delete vectorLazo;
        delete vectorIPsLazos;
        delete vectorIPsDibujados;
        delete vectorLiteralesSoluciones;
}
void __fastcall TfKarnaugh::FormShow(TObject *Sender)
{
	dibujar = false;
	ParametrosIniciales();
        CargarFunciones();
        if(modo == MODO_NOEDITABLE || modo == MODO_APRENDIZAJE_EXPR  || modo == MODO_APRENDIZAJE_LAZOS)
        	CargarSoluciones();
        CambiarTamanyo();
        dibujar = true;
        MostrarFuncion(0);
}
//---------------------------------------------------------------------------

void TfKarnaugh::setNumVars(size numVars)
{
	this->numVars = numVars;
	Mapa->setNumVars(numVars);
}

void TfKarnaugh::setFormato(int formato)
{
	this->formato = formato;
}


void TfKarnaugh::ParametrosIniciales()
{

        string *nombreVars = new string[numVars];
        for(int i=0;i<numVars;i++)
        {
        	string nombreVar = Tabla.LeerEntrada(i).c_str();
                if (nombreVar.empty())
                	nombreVar = string(1,char(65+i));
                nombreVars[i] = nombreVar;
        }
        Mapa->setNombreVars(nombreVars);
        delete[] nombreVars;

        listVarSal->Clear();
	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
        	AnsiString nombreSal = Tabla.LeerSalida(i);
                if(nombreSal == "")
                	nombreSal = "F" + AnsiString(i+1);
        	listVarSal->Items->Append(nombreSal);
	}
	listVarSal->Selected[0] = true;


//        tipoVK->ItemIndex = 0;
//        tipoVisu->ItemIndex = 0;

        Mapa->setTipoVK(tipoVK->ItemIndex);
        Mapa->setTipoVisuVariables(tipoVisu->ItemIndex);
        if (modo == MODO_NOEDITABLE || modo == MODO_APRENDIZAJE_LAZOS)
        {
                ckMostrarLazos->Checked=true;
                Mapa->setMuestraLazos(true);
        }
        else if (modo == MODO_APRENDIZAJE_EXPR)
        {
                ckMostrarLazos->Checked=false;
                Mapa->setMuestraLazos(false);
        }
}

void TfKarnaugh::CargarFunciones()
{
        vectorMint->clear();
        vectorMaxt->clear();
        vectorTIs->clear();
        vectorLazo->clear();
        vectorIPsDibujados->clear();

        vectorMint->resize(Tabla.NumColumnas());
        vectorMaxt->resize(Tabla.NumColumnas());
        vectorTIs->resize(Tabla.NumColumnas());
        vectorLazo->resize(Tabla.NumColumnas());
        vectorIPsDibujados->resize(Tabla.NumColumnas());

	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
		for(int j = 0; j < Tabla.NumFilas(); j++)
		{
			CuboBool cAux=CuboBool(j);
			cAux.literales = numVars;

			if (Tabla.LeerDinArray(j, i) == '1')
                                (*vectorMint)[i].insert(cAux);
			else if(Tabla.LeerDinArray(j, i) == '0')
                                (*vectorMaxt)[i].insert(cAux);
			else if(Tabla.LeerDinArray(j, i) == 'X')
                                (*vectorTIs)[i].insert(cAux);
		}
        }
}

void TfKarnaugh::CargarSoluciones()
{
        vectorIPs->clear();
        vectorIPs->resize(Tabla.NumColumnas());
        vectorLiteralesSoluciones->clear();
        vectorLiteralesSoluciones->resize(Tabla.NumColumnas());

	for(int i = 0; i < Tabla.NumColumnas(); i++)
	{
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

                        if (formato == FORMATO_SOP && Tabla.LeerDinArray(j, i) == '1')
			        simp->AnyadirMint(cAux);
                        else if (formato == FORMATO_POS && Tabla.LeerDinArray(j, i) == '0')
			        simp->AnyadirMint(cAux);
			else if(Tabla.LeerDinArray(j, i) == 'X')
			        simp->AnyadirTI(cAux);
		}
		simp->Simplificar();

		for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
                {
                	(*vectorIPs)[i].insert(*j);
                        (*vectorLiteralesSoluciones)[i] += (*j).literales;
		}


		for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
		{
                	(*vectorIPs)[i].insert(*j);
                        (*vectorLiteralesSoluciones)[i] += (*j).literales;
		}


		for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
		{
                	(*vectorIPs)[i].insert(*j);
                        (*vectorLiteralesSoluciones)[i] += (*j).literales;
		}

                delete simp;
        }
}




void TfKarnaugh::CambiarTamanyo()
{
        int ancho, alto;

        ancho = ((Mapa->celdasSup + 1) * TAMANYO_CELDA) + 2*MARGEN_HOR + Mapa->margenIzq;
        alto = ((Mapa->celdasIzq + 1) * TAMANYO_CELDA)  + 2*MARGEN_VER + Mapa->margenSup;

        Width = ancho + 190;
        //Mapa->Width = max(ancho,350);
        Height = alto + 100;
        //Mapa->Height = alto;
}

void TfKarnaugh::MostrarFuncion(int numFuncion)
{
	Mapa->VaciarListas();
	for (set<CuboBool>::iterator i= (*vectorMint)[numFuncion].begin();i != (*vectorMint)[numFuncion].end();i++)
        {
	       	Mapa->AnyadirMint(*i);
	}

       	for (set<CuboBool>::iterator i= (*vectorMaxt)[numFuncion].begin();i != (*vectorMaxt)[numFuncion].end();i++)
        {
	       	Mapa->AnyadirMaxt(*i);
	}

	for (set<CuboBool>::iterator i= (*vectorTIs)[numFuncion].begin();i != (*vectorTIs)[numFuncion].end();i++)
        {
	       	Mapa->AnyadirTI(*i);
	}

	for (set<CuboBool>::iterator i= (*vectorLazo)[numFuncion].begin();i != (*vectorLazo)[numFuncion].end();i++)
        {
	       	Mapa->AnyadirMintLazo(*i);
	}

        switch(modo)
        {
                case MODO_NOEDITABLE:
                        listLazos->Clear();
                        listLazos->AddItem(ANSIMENSAJE(msgTodos),NULL);
                        (*vectorIPsLazos).clear();
        		for (set<CuboBool>::iterator i= (*vectorIPs)[numFuncion].begin();i != (*vectorIPs)[numFuncion].end();i++)
        	        {
        		       	Mapa->AnyadirIP(*i);
                                (*vectorIPsLazos).push_back(*i);
                                listLazos->AddItem(IP2Expresion(*i),NULL);
        		}
                        listLazos->Selected[0] = true;
                        Mapa->setMostrarTodosLazos(true);
                break;
                case MODO_APRENDIZAJE_EXPR:
        		for (set<CuboBool>::iterator i= (*vectorIPs)[numFuncion].begin();i != (*vectorIPs)[numFuncion].end();i++)
        	        {
        		       	Mapa->AnyadirIP(*i);
         		}
                        Mapa->setMostrarTodosLazos(true);
                case MODO_APRENDIZAJE_LAZOS:
        		for (set<CuboBool>::iterator i= (*vectorIPsDibujados)[numFuncion].begin();i != (*vectorIPsDibujados)[numFuncion].end();i++)
        	        {
        		       	Mapa->AnyadirIP(*i);
         		}
                        Mapa->setMostrarTodosLazos(true);
                break;
        }
        Mapa->Redibujar();
}
void __fastcall TfKarnaugh::tipoVKClick(TObject *Sender)
{
	Mapa->setTipoVK(tipoVK->ItemIndex);
        Mapa->Redibujar();
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::tipoVisuClick(TObject *Sender)
{
	Mapa->setTipoVisuVariables(tipoVisu->ItemIndex);
        Mapa->Redibujar();
}
//---------------------------------------------------------------------------


void __fastcall TfKarnaugh::ckMostrarLazosClick(TObject *Sender)
{
	Mapa->setMuestraLazos(ckMostrarLazos->Checked);
        if(dibujar)
	        Mapa->Redibujar();
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::bAceptarClick(TObject *Sender)
{
        if(modo == MODO_EDITABLE)
        {
        	for(int i =0; i< Tabla.NumColumnas();i++)
                {
                	for(int j=0; j<Tabla.NumFilas();j++)
	                       	Tabla.EscribirDinArray(j, i, '0');

			for (set<CuboBool>::iterator j= (*vectorMint)[i].begin();j != (*vectorMint)[i].end();j++)
                        	Tabla.EscribirDinArray((*j).aInt(), i, '1');

			for (set<CuboBool>::iterator j= (*vectorTIs)[i].begin();j != (*vectorTIs)[i].end();j++)
                        	Tabla.EscribirDinArray((*j).aInt(), i, 'X');
                }
		Application->MessageBox(MENSAJE(msgSCGuardado), "");
        }
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button2Click(TObject *Sender)
{
	TPicture *picture = new TPicture();
        picture->Bitmap->Width= ((Mapa->celdasSup + 1) * TAMANYO_CELDA) + Mapa->margenIzq+1 + MARGEN_HOR;
        picture->Bitmap->Height = ((Mapa->celdasIzq + 1) * TAMANYO_CELDA) + Mapa->margenSup+1 + MARGEN_VER;
	picture->Bitmap->Canvas->CopyRect(
        	TRect(0,0,picture->Bitmap->Width,picture->Bitmap->Height),
                Mapa->Canvas,
                TRect(0,0,MARGEN_HOR+((Mapa->celdasSup + 1) * TAMANYO_CELDA) + Mapa->margenIzq+1,MARGEN_VER+((Mapa->celdasIzq + 1) * TAMANYO_CELDA) + Mapa->margenSup+1));
	Clipboard()->Assign(picture);

        delete picture;
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::listVarSalClick(TObject *Sender)
{
	if (listVarSal->ItemIndex != -1)
		MostrarFuncion(listVarSal->ItemIndex);
}
//---------------------------------------------------------------------------
void TfKarnaugh::setModo(int modo)
{
	this->modo = modo;
        switch(modo)
        {
                case MODO_EDITABLE:
                        pMostrarLazos->Visible = false;
                        gbLazos->Visible = false;
                        gbDibujarLazos->Visible = false;
                        grpCompletar->Visible = true;
                        gbExprBool->Visible = false;
        	        bAceptar->Caption=ANSIMENSAJE(msgGuardar);
                        bCancelar->Visible=true;
                break;
                case MODO_NOEDITABLE:
                        pMostrarLazos->Visible = true;
                        ckMostrarLazos->Checked = false;
                        gbDibujarLazos->Visible = false;
                        gbLazos->Visible = true;
                        grpCompletar->Visible = false;
                        gbExprBool->Visible = false;
                	bAceptar->Caption=ANSIMENSAJE(msgAceptar);
                	bCancelar->Visible=false;
                break;
                case MODO_APRENDIZAJE_EXPR:
                        pMostrarLazos->Visible = true;
                        gbLazos->Visible = false;
                        gbDibujarLazos->Visible = false;
                        grpCompletar->Visible = false;
                        gbExprBool->Visible = true;
                	bAceptar->Caption=ANSIMENSAJE(msgAceptar);
                	bCancelar->Visible=false;
                break;
                case MODO_APRENDIZAJE_LAZOS:
                        pMostrarLazos->Visible = false;
                        gbLazos->Visible = false;
                        gbDibujarLazos->Visible = true;
                        grpCompletar->Visible = false;
                        gbExprBool->Visible = false;
                	bAceptar->Caption=ANSIMENSAJE(msgAceptar);
                	bCancelar->Visible=false;
                break;
        }
}


void __fastcall TfKarnaugh::bCancelarClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfKarnaugh::MapaMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(modo == MODO_EDITABLE)
        {
        	string cubo;
		cubo = Mapa->convertirCasillaACubo(X,Y);

		if (cubo != "")
                {
	                int numFuncion = listVarSal->ItemIndex;
			CuboBool cAux=CuboBool(cubo);
			cAux.literales = numVars;

                        set<CuboBool>::iterator itMint, itTI, itMaxt;
                        bool noEsMint, noEsTI, noEsMaxt;

                        itMint = find((*vectorMint)[numFuncion].begin(), (*vectorMint)[numFuncion].end(),cAux);
                        itMaxt = find((*vectorMaxt)[numFuncion].begin(), (*vectorMaxt)[numFuncion].end(),cAux);
                        itTI = find((*vectorTIs)[numFuncion].begin(), (*vectorTIs)[numFuncion].end(),cAux);

                        noEsMint = (itMint == (*vectorMint)[numFuncion].end());
                        noEsMaxt = (itMaxt == (*vectorMaxt)[numFuncion].end());
                        noEsTI = (itTI == (*vectorTIs)[numFuncion].end());

			if(!noEsMint && noEsTI && noEsMaxt)
			{
                		(*vectorMint)[numFuncion].erase(itMint);
				(*vectorTIs)[numFuncion].insert(cAux);
                        }
	                else if(noEsMint && !noEsTI && noEsMaxt)
			{
				(*vectorTIs)[numFuncion].erase(itTI);
                        	(*vectorMaxt)[numFuncion].insert(cAux);
                        }
                        else if(noEsMint && noEsTI && !noEsMaxt)
			{
                		(*vectorMaxt)[numFuncion].erase(itMaxt);
                        	(*vectorMint)[numFuncion].insert(cAux);
                        }
                        else
                        {
                        	(*vectorMaxt)[numFuncion].insert(cAux);
                        }

	                MostrarFuncion(numFuncion);
        	}
        }
        else if(modo == MODO_APRENDIZAJE_LAZOS)
        {
                int numFuncion = listVarSal->ItemIndex;

                if (Button == mbLeft)
                {
                	string cubo;
        		cubo = Mapa->convertirCasillaACubo(X,Y);

        		if (cubo != "")
                        {
        			CuboBool cAux=CuboBool(cubo);
        			cAux.literales = numVars;

                                set<CuboBool>::iterator itMaxt, itLazo;
                                bool noEsMint, noEsTI, noEsMaxt, enLazo;

                                itMaxt = find((*vectorMaxt)[numFuncion].begin(), (*vectorMaxt)[numFuncion].end(),cAux);
                                itLazo = find((*vectorLazo)[numFuncion].begin(), (*vectorLazo)[numFuncion].end(),cAux);

                                noEsMaxt = (itMaxt == (*vectorMaxt)[numFuncion].end());
                                enLazo = !(itLazo == (*vectorLazo)[numFuncion].end());

        			if(noEsMaxt)
        			{
                                        if(enLazo)
                                        {
                                		(*vectorLazo)[numFuncion].erase(itLazo);
                                        }
                                        else
                                        {
                                		(*vectorLazo)[numFuncion].insert(cAux);
                                        }
                                }

        	                MostrarFuncion(numFuncion);
                	}
                }
                else if (Button == mbRight)
                {
                        CrearLazo();
                        MostrarFuncion(numFuncion);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::FormPaint(TObject *Sender)
{
	Mapa->Redibujar();
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button1Click(TObject *Sender)
{
	int numFuncion = listVarSal->ItemIndex;
	for(int i =0; i< Tabla.NumFilas();i++)
	{
		CuboBool cAux=CuboBool(i);
		cAux.literales = numVars;

                set<CuboBool>::iterator itMint, itTI;
                bool noEsMint, noEsTI;

                itMint = find((*vectorMint)[numFuncion].begin(), (*vectorMint)[numFuncion].end(),cAux);
                itTI = find((*vectorTIs)[numFuncion].begin(), (*vectorTIs)[numFuncion].end(),cAux);

                noEsMint = (itMint == (*vectorMint)[numFuncion].end());
                noEsTI = (itTI == (*vectorTIs)[numFuncion].end());

		if(noEsMint && noEsTI)
			(*vectorMaxt)[numFuncion].insert(cAux);
	}
        MostrarFuncion(numFuncion);
}
//---------------------------------------------------------------------------



void __fastcall TfKarnaugh::Button3Click(TObject *Sender)
{
	int numFuncion = listVarSal->ItemIndex;
	for(int i =0; i< Tabla.NumFilas();i++)
	{
		CuboBool cAux=CuboBool(i);
		cAux.literales = numVars;

                set<CuboBool>::iterator itMaxt, itTI;
                bool noEsMaxt, noEsTI;

                itMaxt = find((*vectorMaxt)[numFuncion].begin(), (*vectorMaxt)[numFuncion].end(),cAux);
                itTI = find((*vectorTIs)[numFuncion].begin(), (*vectorTIs)[numFuncion].end(),cAux);

                noEsMaxt = (itMaxt == (*vectorMaxt)[numFuncion].end());
                noEsTI = (itTI == (*vectorTIs)[numFuncion].end());

		if(noEsMaxt && noEsTI)
			(*vectorMint)[numFuncion].insert(cAux);
	}
        MostrarFuncion(numFuncion);

}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button4Click(TObject *Sender)
{
	int numFuncion = listVarSal->ItemIndex;
	for(int i =0; i< Tabla.NumFilas();i++)
	{
		CuboBool cAux=CuboBool(i);
		cAux.literales = numVars;

                set<CuboBool>::iterator itMint, itMaxt;
                bool noEsMint, noEsMaxt;

                itMint = find((*vectorMint)[numFuncion].begin(), (*vectorMint)[numFuncion].end(),cAux);
                itMaxt = find((*vectorMaxt)[numFuncion].begin(), (*vectorMaxt)[numFuncion].end(),cAux);

                noEsMint = (itMint == (*vectorMint)[numFuncion].end());
                noEsMaxt = (itMaxt == (*vectorMaxt)[numFuncion].end());

		if(noEsMint && noEsMaxt)
			(*vectorTIs)[numFuncion].insert(cAux);
	}
        MostrarFuncion(numFuncion);

}
//---------------------------------------------------------------------------


AnsiString TfKarnaugh::IP2Expresion(CuboBool & c)
{
        string cuboString = c.aString(numVars);
        AnsiString resultado = "";
        for(int i=0; i<numVars; i++)
        {
               	AnsiString nombreVar = Tabla.LeerEntrada(i);
                if (nombreVar.IsEmpty())
                        nombreVar = AnsiString(char(65+i));

                switch(cuboString[i])
                {
                        case '0':
                                if (formato == FORMATO_SOP)
                                {
                                        resultado += "~";
                                        resultado += nombreVar;
                                        resultado += " * ";
                                }
                                else if (formato == FORMATO_POS)
                                {
                                        resultado += nombreVar;
                                        resultado += " + ";
                                }
                        break;
                        case '1':
                                if (formato == FORMATO_SOP)
                                {
                                        resultado += nombreVar;
                                        resultado += " * ";
                                }
                                else if (formato == FORMATO_POS)
                                {
                                        resultado += "~";
                                        resultado += nombreVar;
                                        resultado += " + ";
                                }
                        break;
                        case '-':
                        break;
                }
        }
        resultado = resultado.SubString(0,resultado.Length()-3);

        return resultado;
}
void __fastcall TfKarnaugh::listLazosClick(TObject *Sender)
{
        if (modo == MODO_NOEDITABLE)
        {
                if(listLazos->ItemIndex == 0)
                        Mapa->setMostrarTodosLazos(true);
                else
                {
                        CuboBool IPseleccionado = (*vectorIPsLazos)[listLazos->ItemIndex - 1];
                        Mapa->setMostrarTodosLazos(false);
                        Mapa->setLazoActivo(IPseleccionado);
                }
                Mapa->Redibujar();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::MapaPaint(TObject *Sender)
{
        Mapa->Redibujar();
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button5Click(TObject *Sender)
{
        AnsiString error ="";
        bool coincide = true;
        string expresion = edExprBool->Text.c_str();
	rdSimplificador *simp = new rdSimplificador(numVars);
        // 0 --> Obtención de IPs por el método Q-M
        simp->SetObtenedor(0);
        // 0 --> Seleccion de IPs por método recursivo sesgado
	simp->SetSelector(0);

        if (expresion != "")
        try
        {
                EvaluadorBool *eval = new EvaluadorBool();


                for (int i=0; i<Tabla.NumEntradas(); i++)
                {
                        AnsiString entrada = Tabla.LeerEntrada(i);
                        if(entrada=="")
                                entrada = AnsiString(char('A' + i));
                        eval->AnyadirEntrada(entrada.c_str());
                }

                eval->evaluar(expresion.c_str());

                if (eval->getNumVars() > Tabla.NumEntradas())
                        error+=ANSIMENSAJE(msgVariableNoExiste)+"n\r";
                else
                {
                        for (unsigned int i=0;i<eval->getNumMinterminos();i++)
                        {
                                AnsiString bin = CalcularBinario(i,eval->getNumVars()).c_str();
                                for (unsigned int k=0;k<Tabla.NumEntradas();k++)
                                {
                                        AnsiString entrada = Tabla.LeerEntrada(k);
                                        if(entrada=="")
                                                entrada = AnsiString(char('A' + k));
                                        eval->SetValorEntrada(entrada.c_str(),bin[k+1]=='0'?false:true);
                                }
                                char valorExpr = eval->getValor()==0?'0':'1';
                                char valorTabla = Tabla.LeerDinArray(i,listVarSal->ItemIndex);
                                if (valorExpr != valorTabla && valorTabla != 'X')
                                        coincide = false;
                                if (coincide)
                                {
                			CuboBool cAux=CuboBool(i);
                			cAux.literales = numVars;

                                        if (formato == FORMATO_SOP && valorExpr == '1')
                			        simp->AnyadirMint(cAux);
                                        else if (formato == FORMATO_POS && valorExpr == '0')
                			        simp->AnyadirMint(cAux);
                                }
                        }
                        delete eval;

                }
        }
        catch(exception &e) {
                error+=ANSIMENSAJE(msgExpErronea)+"n\r";
        }
        if(error!="")
        {
                Application->MessageBox(error.c_str(), NULL);
        }
        else
        {
                if(!coincide)
                        Application->MessageBox(MENSAJE(msgNoIdenticos), NULL);
                else
                {
                        bool optima;
                        int literales=0, numIPs=0;

                        // Simplificamos la función introducida
        		simp->Simplificar();

        		for (set<CuboBool>::iterator j= simp->setIPE1sBEGIN();j != simp->setIPE1sEND();j++)
                        {
                                literales += (*j).literales;
                                numIPs++;
        		}


        		for (set<CuboBool>::iterator j= simp->setIPE2sBEGIN();j != simp->setIPE2sEND();j++)
        		{
                                literales += (*j).literales;
                                numIPs++;
        		}


        		for (set<CuboBool>::iterator j= simp->setIPnEsBEGIN();j != simp->setIPnEsEND();j++)
        		{
                                literales += (*j).literales;
                                numIPs++;
        		}

                        delete simp;

                        // Si el numero de literales es mayor, no es optimo
                        if((*vectorIPs)[listVarSal->ItemIndex].size() > numIPs)
                                Application->MessageBox(MENSAJE(msgCorrectoNoMinimo), "ERROR");
                        else if (literales > (*vectorLiteralesSoluciones)[listVarSal->ItemIndex])
                                Application->MessageBox(MENSAJE(msgCorrectoNoMinimo), "ERROR");
                        else
                                Application->MessageBox(MENSAJE(msgCorrectoYMinimo), "");

               }
        }


}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button6Click(TObject *Sender)
{
        int numFuncion = listVarSal->ItemIndex;
        (*vectorIPsDibujados)[numFuncion].clear();
        MostrarFuncion(numFuncion);
}
//---------------------------------------------------------------------------

void TfKarnaugh::CrearLazo()
{
int numFuncion = listVarSal->ItemIndex;
                        set<CuboBool> auxIPs;

                        // Copia-pega del Quine Mc-Cluskey
                        vector< list<CuboBool> > *v1, *v2, *pral, *aux;

		v1 = new vector< list<CuboBool> >(numVars +1, list<CuboBool>() );
		v2 = new vector< list<CuboBool> >(numVars +1, list<CuboBool>() );

		pral = v1;
		aux = v2;

    size subEspacio=0;
    register list<CuboBool>::iterator i,j;
    bool vacioPral;

    for (set<CuboBool>::iterator i=(*vectorLazo)[numFuncion].begin(); i!=(*vectorLazo)[numFuncion].end(); i++)
        (*pral)[(*i).peso].push_back(*i);

    do
    {
        for (register size peso = 0; peso < numVars-subEspacio; peso++)
            if (! ( ((*pral)[peso].empty()) || ((*pral)[peso+1].empty()) ) )
                for(i=(*pral)[peso].begin(); i!=(*pral)[peso].end(); i++)
                {
                    CuboBool c1=(*i);
                    for(j=(*pral)[peso+1].begin(); j!=(*pral)[peso+1].end(); j++)
                    {
                        CuboBool c2=(*j);
                        if (c1 && c2)
                        {
                            (*i).flag = true;
                            (*j).flag = true;
                            if (subEspacio)
                            {
                                if (find((*aux)[peso].begin(), (*aux)[peso].end(), c1+c2) == (*aux)[peso].end())
                                    (*aux)[peso].push_back(c1 + c2);
                            }
                            else
                                (*aux)[peso].push_back(c1 + c2);
                        }
                    }
                }

        for (register size peso = 0; peso <= numVars-subEspacio; peso++)
        {
            for(i=(*pral)[peso].begin(); i!=(*pral)[peso].end(); i++)
                if(!(*i).flag)
                    auxIPs.insert(*i);
            (*pral)[peso].clear();
        }

        swap(pral,aux);

        subEspacio++;

        vacioPral = true;
        for(register vector< list<CuboBool> >::iterator i = (*pral).begin(); i != (*pral).end() && vacioPral; i++)
            vacioPral = (*i).empty();
    }
    while (!vacioPral);

		delete v1;
		delete v2;

                        if (auxIPs.size() == 1)
                        {
                                pair<set<CuboBool>::iterator,bool> resultado = (*vectorIPsDibujados)[numFuncion].insert(*(auxIPs.begin()));

                                if(resultado.second == false)
                                        (*vectorIPsDibujados)[numFuncion].erase(resultado.first);
                                (*vectorLazo)[numFuncion].clear();
                        }
                        else
                        {
                                Application->MessageBox(MENSAJE(msgLazoNoValido), "");
                        }

}
void __fastcall TfKarnaugh::Button8Click(TObject *Sender)
{
        int numFuncion = listVarSal->ItemIndex;
        CrearLazo();
        MostrarFuncion(numFuncion);
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button7Click(TObject *Sender)
{
        bool coincide = true;
        int numFuncion = listVarSal->ItemIndex;
        set<CuboBool>::iterator mint = (*vectorMint)[numFuncion].begin();
        while(coincide && mint != (*vectorMint)[numFuncion].end())
        {
                bool cubreAlgunIP = false;
                set<CuboBool>::iterator ip = (*vectorIPsDibujados)[numFuncion].begin();
                while (!cubreAlgunIP &&  ip != (*vectorIPsDibujados)[numFuncion].end())
                {
                        if ((*ip)>>(*mint))
                                cubreAlgunIP = true;
                        ip++;
                }
                if(!cubreAlgunIP)
                        coincide = false;
                mint++;
        }

        if(!coincide)
                Application->MessageBox(MENSAJE(msgLazosInsuficientes1), NULL);
        else
        {
                        int literales=0, numIPs=0;

        		for (set<CuboBool>::iterator j= (*vectorIPsDibujados)[numFuncion].begin();j != (*vectorIPsDibujados)[numFuncion].end();j++)
                        {
                                literales += (*j).literales;
                                numIPs++;
        		}

                        // Si el numero de literales es mayor, no es optimo
                        if((*vectorIPs)[numFuncion].size() < numIPs)
                                Application->MessageBox(MENSAJE(msgDemasiadosLazos), "ERROR");
                        else if (literales > (*vectorLiteralesSoluciones)[numFuncion])
                                Application->MessageBox(MENSAJE(msgCorrectoNoMinimo), "ERROR");
                        else
                                Application->MessageBox(MENSAJE(msgCorrectoYMinimo), "");
        }
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::Button9Click(TObject *Sender)
{
        int numFuncion = listVarSal->ItemIndex;
        (*vectorMint)[numFuncion].clear();
        (*vectorMaxt)[numFuncion].clear();
        (*vectorTIs)[numFuncion].clear();
        MostrarFuncion(numFuncion);
}
//---------------------------------------------------------------------------

void __fastcall TfKarnaugh::SpeedButton1Click(TObject *Sender)
{
        AnsiString mensaje;

        mensaje = ANSIMENSAJE(msgAyudaDibuLazos1);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos2);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos3);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos4);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos5);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos6);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos7);
        mensaje += "\n\r";
        mensaje += ANSIMENSAJE(msgAyudaDibuLazos8);
        Application->MessageBox(mensaje.c_str(), "");
}
//---------------------------------------------------------------------------

