//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Karnaugh.h"
#include <stdlib>
#include <bitset>
#include <queue>
#include <list>
using namespace std;
#include "VKLazo.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TKarnaugh *)
{
	new TKarnaugh(NULL);
}
//---------------------------------------------------------------------------
__fastcall TKarnaugh::TKarnaugh(TComponent* Owner)
	: TPaintBox(Owner)
{
        setMint = new set<CuboBool>();
        setMaxt = new set<CuboBool>();
        setTIs = new set<CuboBool>();
        setIPs = new set<CuboBool>();
        setMintLazo = new set<CuboBool>();
}

__fastcall TKarnaugh::~TKarnaugh()
{
delete setMint;
delete setMaxt;
delete setTIs;
delete setIPs;
delete setMintLazo;
}

//---------------------------------------------------------------------------
namespace Karnaugh
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TKarnaugh)};
		RegisterComponents("Samples", classes, 0);
	}
}
//---------------------------------------------------------------------------
void TKarnaugh::setNumVars(size numVars)
{
        this->numVars = numVars;
        if (numVars%2==0)
        {
                celdasIzq = celdasSup = (1u<<(numVars/2));
                numVarsIzq = numVarsSup = numVars/2;
        }
        else
        {
                int cociente = div(numVars,2).quot;
                celdasIzq = (1u<<cociente);
                celdasSup = (1u<<(cociente+1));
                numVarsIzq = cociente;
                numVarsSup = cociente + 1;
        }

        margenIzq = max(0, (numVarsIzq*DISTANCIA_LINEAS + 5)- TAMANYO_CELDA);
        margenSup = max(0, (numVarsSup*DISTANCIA_LINEAS + 5)- TAMANYO_CELDA);

        codIzq.clear();
        codSup.clear();

        bitset<32> gray=bitset<32>(0);
	for(unsigned int i = 0; i<celdasSup; i++)
        {
		pair<int,int> coordenadas;
                string grayString = gray.template to_string<char, char_traits<char>, allocator<char> >().substr(32-numVarsSup,31);
                codSup.push_back(grayString);
                bitset<32> binaryI=bitset<32>((unsigned long) i);
                bitset<32> binaryIplus1=bitset<32>((unsigned long) i+1);
                bitset<32> binaryChanged=(binaryI ^ binaryIplus1);
                gray = gray ^(binaryChanged ^(binaryChanged >> 1));
        }
        gray=bitset<32>(0);
        for(unsigned int i = 0; i<celdasIzq; i++)
        {
		pair<int,int> coordenadas;
                string grayString = gray.template to_string<char, char_traits<char>, allocator<char> >().substr(32-numVarsIzq,31);
                codIzq.push_back(grayString);
                bitset<32> binaryI=bitset<32>((unsigned long) i);
                bitset<32> binaryIplus1=bitset<32>((unsigned long) i+1);
                bitset<32> binaryChanged=(binaryI ^ binaryIplus1);
                gray = gray ^(binaryChanged ^(binaryChanged >> 1));
        }
}

void TKarnaugh::Redibujar(void)
{
	Dibujar(this->Canvas);
}

void TKarnaugh::Dibujar(TCanvas *canvas)
{
        BorrarMapa(canvas);
        if(muestraLazos)
	        DibujarLazos(canvas);
        DibujarMatriz(canvas);
        DibujarVariables(canvas);
        DibujarTerminos(canvas);
}

void TKarnaugh::setNombreVars(string nombreVars[])
{
        this->nombreVars.clear();
        for(int i=0;i<numVars;i++)
                this->nombreVars.push_back(string(nombreVars[i]));
}


void TKarnaugh::BorrarMapa(TCanvas *canvas)
{
        canvas->Brush->Style = bsSolid;
        canvas->Brush->Color = clWhite;
        canvas->Pen->Style = psSolid;
        canvas->Pen->Color = clWhite;
        canvas->Font->Color = clBlack;
        canvas->Rectangle(0, 0, Width, Height);
        setFontHorizontal(canvas);
}


void TKarnaugh::DibujarMatriz(TCanvas *canvas)
{
        canvas->Brush->Style = bsClear;
        canvas->Pen->Color = clBlack;
        canvas->Pen->Width = 1;

        for(unsigned int i=0;i<celdasSup;i++)
                for(unsigned int j=0;j<celdasIzq;j++)
                {
                        pair<int,int> coordenadas;
                        coordenadas = convertirCasillaACoordenadas(i,j);
                        canvas->Rectangle(coordenadas.first,coordenadas.second,coordenadas.first + TAMANYO_CELDA+1,coordenadas.second + TAMANYO_CELDA+1);

                }

        canvas->MoveTo(MARGEN_HOR+margenIzq,MARGEN_VER+margenSup);
        canvas->LineTo(MARGEN_HOR+margenIzq + TAMANYO_CELDA,MARGEN_VER+margenSup + TAMANYO_CELDA);

}


void TKarnaugh::DibujarVariables(TCanvas *canvas)
{
	string nombreVarsIzq="", nombreVarsSup="";
        switch(getTipoVisuVariables())
        {
                case BINARIO:
                        for(unsigned int i = 0; i<celdasSup; i++)
                        {
                            pair<int,int> coordenadas;
                            coordenadas = convertirCasillaACoordenadas(i,-1);
                            EscribirCentrado(coordenadas.first + TAMANYO_CELDA/2, coordenadas.second + TAMANYO_CELDA/2, AnsiString(codSup[i].c_str()),canvas);
                        }
                        for(unsigned int i = 0; i<celdasIzq; i++)
                        {
                            pair<int,int> coordenadas;
                            coordenadas = convertirCasillaACoordenadas(-1,i);
                            EscribirCentrado(coordenadas.first + TAMANYO_CELDA/2, coordenadas.second + TAMANYO_CELDA/2, AnsiString(codIzq[i].c_str()),canvas);
                        }
                        for(size i=0;i<numVarsSup;i++)
				nombreVarsSup += varsSup[i] + "  ";
                        for(size i=0;i<numVarsIzq;i++)
				nombreVarsIzq += varsIzq[i] + "  ";
                        canvas->TextOut(MARGEN_HOR + margenIzq + 10, 5, AnsiString(nombreVarsSup.c_str()));
			setFontVertical(canvas);
			canvas->TextOut(5, MARGEN_VER + margenSup + 10 + canvas->TextWidth(AnsiString(nombreVarsIzq.c_str())), AnsiString(nombreVarsIzq.c_str())); // output the rotated font
			setFontHorizontal(canvas);
                        break;
                case LINEAS:
                	int *comienzoLinea = new int[numVarsSup];
                	for(unsigned int i = 1; i<=celdasSup; i++)
                        {
                        	pair<int,int> coordenadas = convertirCasillaACoordenadas(i,0);
                                string codActual;
                                string codAnt;
                                if (i<celdasSup)
                                {
	                        	codActual = codSup[i];
	                        	codAnt = codSup[i-1];
                                }
                                else
                                {
	                        	codActual = codSup[0];
	                        	codAnt = codSup[celdasSup-1];
                                }

                        	for(size j = 0; j < numVarsSup; j++)
                                {
                                	size indiceVar = numVarsSup - 1 - j;
                                        int yLinea = coordenadas.second - 5 - j*DISTANCIA_LINEAS;
                                	if(codActual[indiceVar] == '0' && codAnt[indiceVar] == '0')
                                        {
                                        	// Nada
                                        }
                                        else if(codActual[indiceVar] == '0' && codAnt[indiceVar] == '1')
                                        {
                                        	// Termina linea. Escribimos nombre var y linea
                                                canvas->MoveTo(comienzoLinea[indiceVar], yLinea);
                                                canvas->LineTo(coordenadas.first, yLinea);

                                                string nombreVar = varsSup[indiceVar];
                                                EscribirCentrado((comienzoLinea[indiceVar]+coordenadas.first)/2, yLinea - 8, AnsiString(nombreVar.c_str()),canvas);
                                        }
                                        else if(codActual[indiceVar] == '1' && codAnt[indiceVar] == '0')
                                        {
                                        	// Comienza linea
                                                comienzoLinea[indiceVar] = coordenadas.first;

                                        }
                                        else if(codActual[indiceVar] == '1' && codAnt[indiceVar] == '1')
                                        {
                                        	// Linea continua. Nada.
                                        }
                                }
                        }
                        delete comienzoLinea;

                	comienzoLinea = new int[numVarsIzq];
                	for(unsigned int i = 1; i<=celdasIzq; i++)
                        {
                        	pair<int,int> coordenadas = convertirCasillaACoordenadas(0,i);
                                string codActual;
                                string codAnt;
                                if (i<celdasIzq)
                                {
	                        	codActual = codIzq[i];
	                        	codAnt = codIzq[i-1];
                                }
                                else
                                {
	                        	codActual = codIzq[0];
	                        	codAnt = codIzq[celdasIzq-1];
                                }

                        	for(size j = 0; j < numVarsIzq; j++)
                                {
                                	size indiceVar = numVarsIzq - 1 - j;
                                        int xLinea = coordenadas.first - 5 - j*DISTANCIA_LINEAS;
                                	if(codActual[indiceVar] == '0' && codAnt[indiceVar] == '0')
                                        {
                                        	// Nada
                                        }
                                        else if(codActual[indiceVar] == '0' && codAnt[indiceVar] == '1')
                                        {
                                        	// Termina linea. Escribimos nombre var y linea
                                                canvas->MoveTo(xLinea, comienzoLinea[indiceVar]);
                                                canvas->LineTo(xLinea, coordenadas.second);

                                                string nombreVar = varsIzq[indiceVar];
                                                EscribirCentradoVertical(xLinea - 8, (comienzoLinea[indiceVar]+coordenadas.second)/2, AnsiString(nombreVar.c_str()),canvas);
                                        }
                                        else if(codActual[indiceVar] == '1' && codAnt[indiceVar] == '0')
                                        {
                                        	// Comienza linea
                                                comienzoLinea[indiceVar] = coordenadas.second;

                                        }
                                        else if(codActual[indiceVar] == '1' && codAnt[indiceVar] == '1')
                                        {
                                        	// Linea continua. Nada.
                                        }
                                }
                        }

                        delete comienzoLinea;
                        break;
        }
}


void TKarnaugh::DibujarTerminos(TCanvas *canvas)
{
        for(set<CuboBool>::iterator i = setMint->begin();i!=setMint->end();i++)
        {
                pair<int,int> aux;
                set<CuboBool>::iterator itLazo;
                bool enLazo;

                string cubo = (*i).aString(numVars);
                aux = encontrarCasilla(cubo);
                aux = convertirCasillaACoordenadas(aux.first,aux.second);

                itLazo = find(setMintLazo->begin(), setMintLazo->end(),(*i));
                enLazo = !(itLazo == setMintLazo->end());
                if (enLazo)
                {
                        canvas->Font->Color = clRed;
                }
                else
                {
                        canvas->Font->Color = clBlack;
                }

                EscribirCentrado(aux.first + TAMANYO_CELDA/2, aux.second + TAMANYO_CELDA/2, "1",canvas);
        }
        canvas->Font->Color = clBlack;
        for(set<CuboBool>::iterator i = setMaxt->begin();i!=setMaxt->end();i++)
        {
                pair<int,int> aux;
                string cubo = (*i).aString(numVars);
                aux = encontrarCasilla(cubo);
                aux = convertirCasillaACoordenadas(aux.first,aux.second);
                EscribirCentrado(aux.first + TAMANYO_CELDA/2, aux.second + TAMANYO_CELDA/2, "0",canvas);
        }
        for(set<CuboBool>::iterator i = setTIs->begin();i!=setTIs->end();i++)
        {
                pair<int,int> aux;
                set<CuboBool>::iterator itLazo;
                bool enLazo;

                string cubo = (*i).aString(numVars);
                aux = encontrarCasilla(cubo);
                aux = convertirCasillaACoordenadas(aux.first,aux.second);

                itLazo = find(setMintLazo->begin(), setMintLazo->end(),(*i));
                enLazo = !(itLazo == setMintLazo->end());
                if (enLazo)
                {
                        canvas->Font->Color = clRed;
                }
                else
                {
                        canvas->Font->Color = clBlack;
                }

                EscribirCentrado(aux.first + TAMANYO_CELDA/2, aux.second + TAMANYO_CELDA/2, "X",canvas);
        }

}


void TKarnaugh::DibujarLazos(TCanvas *canvas)
{
	canvas->Pen->Color = clRed;
        canvas->Brush->Style = bsClear;
        for(set<CuboBool>::iterator i = setIPs->begin();i!=setIPs->end();i++)
        {
                if (mostrarTodosLazos || (!mostrarTodosLazos && lazoActivo == *i))
                {
        	list<Lazo> listaLazos;
                list<int> minX, maxX, minY, maxY;
		set<string> cubosCubiertos = descombinarCubo((*i).aString(numVars));
                set<int> indiceX, indiceY;
                //pair<int,int> indiceMin, indiceMax;
                bool saleX = false, saleY=false;
                int discontinuidadesX = 0, discontinuidadesY=0;
                //int numLazos, numLazosX, numLazosY;

                for(set<string>::iterator j = cubosCubiertos.begin();j!=cubosCubiertos.end();j++)
                {
			pair<int,int> coordenadas = encontrarCasilla((*j));
                        indiceX.insert(coordenadas.first);
                        indiceY.insert(coordenadas.second);
                }

		/*indiceMin.first=(*(indiceX.begin()));
		indiceMin.second=(*(indiceY.begin()));
		indiceMax.first=(*(indiceX.rbegin()));
		indiceMax.second=(*(indiceY.rbegin()));*/


                int xAnterior = *(indiceX.begin());
                for(set<int>::iterator j = ++(indiceX.begin());j!=indiceX.end() && !saleX;j++)
                {
                	if (*j != xAnterior+1)
                        {
                        	/*indiceMin.first = *j;
                                indiceMax.first = xAnterior;*/
                                minX.push_back(*j);
                                maxX.push_back(xAnterior);
				discontinuidadesX++;
                                xAnterior = *j;
                        }
                        else
                        {
                        	xAnterior = *j;
                        }
                }
                if(*(indiceX.begin()) == 0 && *(indiceX.rbegin()) == celdasSup - 1 && discontinuidadesX > 0)
                {
                	saleX = true;
                        minX.push_front(minX.back());
                        minX.pop_back();
                        //maxX.push_front(maxX.back());
                        //maxX.pop_back();
                }
                if(discontinuidadesX==0 || (discontinuidadesX > 0 && !saleX))
                {
                	minX.push_front(*(indiceX.begin()));
                	maxX.push_back(*(indiceX.rbegin()));
                }


                int yAnterior = *(indiceY.begin());
                for(set<int>::iterator j = ++(indiceY.begin());j!=indiceY.end() && !saleY;j++)
                {
                	if (*j != yAnterior+1)
                        {
                        	/*indiceMin.second = *j;
                                indiceMax.second = yAnterior;*/
                                minY.push_back(*j);
                                maxY.push_back(yAnterior);
				discontinuidadesY++;
                                yAnterior = *j;
                        }
                        else
                        {
                        	yAnterior = *j;
                        }
                }
                if(*(indiceY.begin()) == 0 && *(indiceY.rbegin()) == celdasIzq - 1 && discontinuidadesY > 0)
                {
                	saleY = true;
                        minY.push_front(minY.back());
                        minY.pop_back();
                        //maxY.push_front(maxY.back());
                        //maxY.pop_back();
                }
                if(discontinuidadesY==0 || (discontinuidadesY > 0 && !saleY))
                {
                	minY.push_front(*(indiceY.begin()));
                	maxY.push_back(*(indiceY.rbegin()));
                }

                list<int>::iterator i_minX = minX.begin();
                list<int>::iterator i_maxX = maxX.begin();
                while(i_minX != minX.end())
                {
        	        list<int>::iterator i_minY = minY.begin();
	                list<int>::iterator i_maxY = maxY.begin();
	                while(i_minY != minY.end())
        	        {
                        	Lazo l;
                                l.comienzoLazo.first = *i_minX;
                                l.comienzoLazo.second = *i_minY;
                                l.finLazo.first = *i_maxX;
                                l.finLazo.second = *i_maxY;

                                if(i_minX == minX.begin() && saleX)
                                {
                                	l.tamanyoX = (*i_maxX + 1) + (celdasSup - *i_minX);
                                	l.saleX = true;
                                }
                                else
                                	l.tamanyoX = *i_maxX - *i_minX + 1;

                                if(i_minY == minY.begin() && saleY)
                                {
                                	l.tamanyoY = (*i_maxY + 1) + (celdasIzq - *i_minY);
                                	l.saleY = true;
                                }
                                else
                                	l.tamanyoY = *i_maxY - *i_minY + 1;
                                i_minY++;
                                i_maxY++;
                                listaLazos.push_back(l);
                        }
                        i_minX++;
                        i_maxX++;
                }

                /*
                numLazosX = discontinuidadesX + (saleX?0:1);
                numLazosY = discontinuidadesY + (saleY?0:1);
                numLazos = numLazosX * numLazosY;
                */

                for(list<Lazo>::iterator j = listaLazos.begin(); j != listaLazos.end(); j++)
                {

	               	pair<int,int> coordenadasMin = convertirCasillaACoordenadas((*j).comienzoLazo.first,(*j).comienzoLazo.second);
	               	pair<int,int> coordenadasMax = convertirCasillaACoordenadas((*j).finLazo.first,(*j).finLazo.second);

        	        if(!(*j).saleX && !(*j).saleY)
		        {
	                        canvas->RoundRect(
	                        	coordenadasMin.first + 5,
	                        	coordenadasMin.second + 5,
	                                coordenadasMax.first + TAMANYO_CELDA - 5,
	                                coordenadasMax.second + TAMANYO_CELDA - 5,
					(coordenadasMax.first - coordenadasMin.first + TAMANYO_CELDA - 10)/2,
					(coordenadasMax.second - coordenadasMin.second + TAMANYO_CELDA - 10)/2
                                );
	                }
	                else if ((*j).saleX && !(*j).saleY)
	                {
	                	// Lazo que se sale por la derecha
	                        pair<int,int> coordenadasDerecha = convertirCasillaACoordenadas((*j).comienzoLazo.first+(*j).tamanyoX-1,(*j).finLazo.second);
	                        canvas->RoundRect(
	                        	coordenadasMin.first + 5,
	                        	coordenadasMin.second + 5,
	                                coordenadasDerecha.first + TAMANYO_CELDA - 5,
	                                coordenadasDerecha.second + TAMANYO_CELDA - 5,
					(coordenadasDerecha.first  - coordenadasMin.first + TAMANYO_CELDA - 10)/2,
					(coordenadasDerecha.second  - coordenadasMin.second + TAMANYO_CELDA - 10)/2
	                                );

	                        // Lazo que se sale (entra) por la izquierda
				pair<int,int> coordenadasIzquierda = convertirCasillaACoordenadas((*j).finLazo.first-(*j).tamanyoX+1,(*j).comienzoLazo.second);
	                        canvas->RoundRect(
	                        	coordenadasIzquierda.first + 5,
	                        	coordenadasIzquierda.second + 5,
	                                coordenadasMax.first + TAMANYO_CELDA - 5,
	                                coordenadasMax.second + TAMANYO_CELDA - 5,
					(coordenadasMax.first - coordenadasIzquierda.first + TAMANYO_CELDA - 10)/2,
					(coordenadasMax.second - coordenadasIzquierda.second + TAMANYO_CELDA - 10)/2
	                                );
	                }
	                else if (!(*j).saleX && (*j).saleY)
	                {
	                	// Lazo que se sale por abajo
	                        pair<int,int> coordenadasAbajo = convertirCasillaACoordenadas((*j).finLazo.first,(*j).comienzoLazo.second+(*j).tamanyoY-1);
	                        canvas->RoundRect(
	                        	coordenadasMin.first + 5,
	                        	coordenadasMin.second + 5,
	                                coordenadasAbajo.first + TAMANYO_CELDA - 5,
	                                coordenadasAbajo.second + TAMANYO_CELDA - 5,
					(coordenadasAbajo.first  - coordenadasMin.first + TAMANYO_CELDA - 10)/2,
					(coordenadasAbajo.second  - coordenadasMin.second + TAMANYO_CELDA - 10)/2
	                                );

	                        // Lazo que se sale (entra) por arriba
				pair<int,int> coordenadasArriba = convertirCasillaACoordenadas((*j).comienzoLazo.first,(*j).finLazo.second-(*j).tamanyoY+1);
	                        canvas->RoundRect(
	                        	coordenadasArriba.first + 5,
	                        	coordenadasArriba.second + 5,
	                                coordenadasMax.first + TAMANYO_CELDA - 5,
	                                coordenadasMax.second + TAMANYO_CELDA - 5,
					(coordenadasMax.first - coordenadasArriba.first + TAMANYO_CELDA - 10)/2,
					(coordenadasMax.second - coordenadasArriba.second + TAMANYO_CELDA - 10)/2
	                                );
	                }
	                else if ((*j).saleX && (*j).saleY)
	                {
	                	// Lazo que se sale por la esquina superior-izquierda
	                        pair<int,int> coordenadasSupIzq = convertirCasillaACoordenadas((*j).finLazo.first-(*j).tamanyoX+1,(*j).finLazo.second-(*j).tamanyoY+1);
	                        canvas->RoundRect(
	                        	coordenadasSupIzq.first + 5,
	                        	coordenadasSupIzq.second + 5,
	                                coordenadasMax.first + TAMANYO_CELDA - 5,
	                                coordenadasMax.second + TAMANYO_CELDA - 5,
					(coordenadasMax.first  - coordenadasSupIzq.first + TAMANYO_CELDA - 10)/2,
					(coordenadasMax.second  - coordenadasSupIzq.second + TAMANYO_CELDA - 10)/2
	                                );

	                	// Lazo que se sale por la esquina inferior-izquierda
	                        pair<int,int> coordenadasInfIzq1 = convertirCasillaACoordenadas((*j).finLazo.first-(*j).tamanyoX+1,(*j).comienzoLazo.second);
	                        pair<int,int> coordenadasInfIzq2 = convertirCasillaACoordenadas((*j).finLazo.first,(*j).comienzoLazo.second+(*j).tamanyoY-1);
	                        canvas->RoundRect(
	                        	coordenadasInfIzq1.first + 5,
	                        	coordenadasInfIzq1.second + 5,
	                                coordenadasInfIzq2.first + TAMANYO_CELDA - 5,
	                                coordenadasInfIzq2.second + TAMANYO_CELDA - 5,
					(coordenadasInfIzq2.first  - coordenadasInfIzq1.first + TAMANYO_CELDA - 10)/2,
					(coordenadasInfIzq2.second  - coordenadasInfIzq1.second + TAMANYO_CELDA - 10)/2
	                                );

	                	// Lazo que se sale por la esquina superior-derecha
	                        pair<int,int> coordenadasSupDer1 = convertirCasillaACoordenadas((*j).comienzoLazo.first,(*j).finLazo.second-(*j).tamanyoY+1);
	                        pair<int,int> coordenadasSupDer2 = convertirCasillaACoordenadas((*j).comienzoLazo.first+(*j).tamanyoX-1,(*j).finLazo.second);
	                        canvas->RoundRect(
	                        	coordenadasSupDer1.first + 5,
	                        	coordenadasSupDer1.second + 5,
	                                coordenadasSupDer2.first + TAMANYO_CELDA - 5,
	                                coordenadasSupDer2.second + TAMANYO_CELDA - 5,
					(coordenadasSupDer2.first  - coordenadasSupDer1.first + TAMANYO_CELDA - 10)/2,
					(coordenadasSupDer2.second  - coordenadasSupDer1.second + TAMANYO_CELDA - 10)/2
	                                );

	                	// Lazo que se sale por la esquina inferior-derecha
	                        pair<int,int> coordenadasInfDer = convertirCasillaACoordenadas((*j).comienzoLazo.first+(*j).tamanyoX-1,(*j).comienzoLazo.second+(*j).tamanyoY-1);
	                        canvas->RoundRect(
	                        	coordenadasMin.first + 5,
	                        	coordenadasMin.second + 5,
	                                coordenadasInfDer.first + TAMANYO_CELDA - 5,
	                                coordenadasInfDer.second + TAMANYO_CELDA - 5,
					(coordenadasInfDer.first  - coordenadasMin.first + TAMANYO_CELDA - 10)/2,
					(coordenadasInfDer.second  - coordenadasMin.second + TAMANYO_CELDA - 10)/2
	                                );
	                }
                }
                }
        }
        canvas->Brush->Style = bsSolid;
        canvas->Brush->Color = clWhite;
        canvas->Pen->Style = psSolid;
        canvas->Pen->Color = clWhite;
        canvas->Rectangle(0, 0, Width, MARGEN_VER + margenSup + TAMANYO_CELDA);
        canvas->Rectangle(0, 0, MARGEN_HOR + margenIzq + TAMANYO_CELDA, Height);
        canvas->Rectangle(MARGEN_HOR + margenIzq + TAMANYO_CELDA*(celdasSup+1), 0, Width, Height);
        canvas->Rectangle(0, MARGEN_VER + margenSup + TAMANYO_CELDA*(celdasIzq+1),Width, Height);
}




void TKarnaugh::setTipoVK(int tipoVK)
{
	vector<int> indiceVarSup;
        vector<int> indiceVarIzq;

        varsIzq.clear();
        varsSup.clear();

        //varsIzq.reserve(numVarsIzq);
        //varsSup.reserve(numVarsSup);
        indiceVar.clear();
        //indiceVar.reserve(numVars);

        switch(tipoVK)
        {
                case 0:
                        for(size i=0;i<numVarsSup;i++)
                        {
                                varsSup.push_back(nombreVars[i]);
                                indiceVar.push_back(i);
                        }
                        for(size i=numVarsSup;i<numVars;i++)
                        {
                                varsIzq.push_back(nombreVars[i]);
                                indiceVar.push_back(i);
                        }
                break;
                case 1:
                        for(size i=0;i<numVars;i++)
                        {
                        	if(i%2==0)
                                {
                                	if(i%4==0)
                                        {
		                                varsSup.push_back(nombreVars[i]);
		                                indiceVarSup.push_back(i);
                                        }
                                        else
                                        {
		                                varsSup.insert(varsSup.begin(), nombreVars[i]);
		                                indiceVarSup.insert(indiceVarSup.begin(), i);
                                        }
                                }
                                else
                                {
                                	if(i-1%4==0)
                                        {
		                                varsIzq.push_back(nombreVars[i]);
		                                indiceVarIzq.push_back(i);
                                        }
                                        else
                                        {
		                                varsIzq.insert(varsIzq.begin(), nombreVars[i]);
		                                indiceVarIzq.insert(indiceVarIzq.begin(), i);
                                        }
                                }
                        }
                        indiceVar.insert(indiceVar.begin(), indiceVarSup.begin(), indiceVarSup.end());
                        indiceVar.insert(indiceVar.end(), indiceVarIzq.begin(), indiceVarIzq.end());
                break;
        }
        //setTipoVisuVariables(tipoVK);
}

int TKarnaugh::getTipoVK()
{
        return tipoVK;
}

void TKarnaugh::setTipoVisuVariables(int tipoVisu)
{
	 this->tipoVisu=tipoVisu;
}

int TKarnaugh::getTipoVisuVariables()
{
        return tipoVisu;
}




/// Anyade un mintermino a la funcion
void TKarnaugh::AnyadirMint(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVars;
    setMint->insert(cAux);
}

void TKarnaugh::AnyadirMintLazo(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVars;
    setMintLazo->insert(cAux);
}


void TKarnaugh::AnyadirMaxt(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVars;
    setMaxt->insert(cAux);
}


/// Anyade un termino irrelevante a la funcion
void TKarnaugh::AnyadirTI(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVars;
    setTIs->insert(cAux);
}

void TKarnaugh::AnyadirIP(const CuboBool &c)
{
    CuboBool cAux=c;

    cAux.literales = numVars;
    setIPs->insert(cAux);
}


void TKarnaugh::VaciarListas()
{
        setMint->clear();
        setMaxt->clear();
        setTIs->clear();
        setIPs->clear();
        setMintLazo->clear();
}

string TKarnaugh::ConvertirCubo(string cubo)
{
        string resultado;
        resultado.resize(numVars);

        for(int i=0;i<numVars;i++)
                resultado[i] = cubo[indiceVar[i]];

        return resultado;
}


string TKarnaugh::desconvertirCubo(string cubo)
{
        string resultado;
        resultado.resize(numVars);

        for(int i=0;i<numVars;i++)
                resultado[indiceVar[i]] = cubo[i];

        return resultado;
}


pair<int,int> TKarnaugh::encontrarCasilla(string cubo)
{
        pair<int,int> resultado;
        unsigned int sup, izq;
        string parteSup, parteIzq;
        cubo = ConvertirCubo(cubo);
        parteSup = cubo.substr(0,numVarsSup);
        parteIzq = cubo.substr(numVarsSup,numVarsIzq);
        bool encontrado = false;

        // Encontrar casilla superior
        for(sup=0;sup<celdasSup && !encontrado;sup++)
        {
                if(codSup[sup]==parteSup)
                        encontrado = true;
        }
        sup--;

        // Encontrar casilla inferior
        encontrado = false;
        for(izq=0;izq<celdasIzq && !encontrado;izq++)
        {
                if(codIzq[izq]==parteIzq)
                        encontrado = true;
        }
        izq--;

        resultado.first = sup;
        resultado.second = izq;

        return resultado;
}

pair<int,int> TKarnaugh::convertirCasillaACoordenadas(unsigned int sup, unsigned int izq)
{
        pair<int,int> resultado;
        resultado.first = TAMANYO_CELDA + MARGEN_HOR + margenIzq + sup*TAMANYO_CELDA;
        resultado.second = TAMANYO_CELDA + MARGEN_VER + margenSup + izq*TAMANYO_CELDA;
        return resultado;
}

void TKarnaugh::EscribirCentrado(int x, int y, AnsiString texto, TCanvas *canvas)
{
        int alto = canvas->TextHeight(texto);
        int ancho = canvas->TextWidth(texto);

        canvas->TextOut(x - ancho/2, y - alto/2, texto);
}

void TKarnaugh::EscribirCentradoVertical(int x, int y, AnsiString texto, TCanvas *canvas)
{
        int alto = canvas->TextHeight(texto);
        int ancho = canvas->TextWidth(texto);

        setFontVertical(canvas);
    canvas->TextOut(x - alto/2, y + ancho/2, texto); // output the rotated font
        setFontHorizontal(canvas);
}
//---------------------------------------------------------------------------


void TKarnaugh::setFontHorizontal(TCanvas *canvas)
{
    ZeroMemory(&logFontHorizontal, sizeof(LOGFONT));

    logFontHorizontal.lfHeight = 14;
    logFontHorizontal.lfCharSet = DEFAULT_CHARSET;
    strcpy(logFontHorizontal.lfFaceName, "Verdana");

    canvas->Font->Handle = CreateFontIndirect(&logFontHorizontal);


}

void TKarnaugh::setFontVertical(TCanvas *canvas)
{
    ZeroMemory(&logFontVertical, sizeof(LOGFONT));

    logFontVertical.lfHeight = 14;
    logFontVertical.lfCharSet = DEFAULT_CHARSET;
    strcpy(logFontVertical.lfFaceName, "Verdana");

    logFontVertical.lfEscapement = 10 * 90; // degrees to rotate
    logFontVertical.lfOrientation = 10 * 90;

    canvas->Font->Handle = CreateFontIndirect(&logFontVertical);
}

set<string> TKarnaugh::descombinarCubo(string cubo)
{
	queue<string> cola;
        set<string> retorno;

        cola.push(cubo);
        while(!cola.empty())
        {
        	string cuboActual = cola.front();
                cola.pop();

                bool encontrado = false;
                for(unsigned int i=0;i<cuboActual.length() && !encontrado;i++)
			if(cuboActual[i]=='-')
                        {
                        	encontrado = true;
                        	string cubo1 = cuboActual, cubo2 = cuboActual;
                                cubo1[i]='0';
                                cubo2[i]='1';
                                cola.push(cubo1);
                                cola.push(cubo2);
                        }
                if(!encontrado)
                	retorno.insert(cuboActual);
        }

        return retorno;
}

void TKarnaugh::setMuestraLazos(bool muestraLazos)
{
	this->muestraLazos = muestraLazos;
}

string TKarnaugh::convertirCasillaACubo(int x, int y)
{
	int sup, izq;

        sup = (x - TAMANYO_CELDA - MARGEN_HOR - margenIzq)/TAMANYO_CELDA;
        izq = (y - TAMANYO_CELDA - MARGEN_VER - margenSup)/TAMANYO_CELDA;

        if(sup <0 || izq < 0 || izq >= celdasIzq || sup >= celdasSup)
        	return "";
        else
        {
		string retorno = codSup[sup] + codIzq[izq];
		retorno = desconvertirCubo(retorno);

	        return retorno;
        }
}

void TKarnaugh::setLazoActivo(const CuboBool &c)
{
        lazoActivo = c;
}

void TKarnaugh::setMostrarTodosLazos(bool mostrarTodosLazos)
{
        this->mostrarTodosLazos = mostrarTodosLazos;
}

