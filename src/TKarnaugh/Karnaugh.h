//---------------------------------------------------------------------------

#ifndef KarnaughH
#define KarnaughH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>

#include "reductio/rdsimplificador.h"
#include <vector>
#include <string>
using namespace std;


#define MARGEN_VER (15)
#define MARGEN_HOR (15)
#define TAMANYO_CELDA (40)
#define DISTANCIA_LINEAS (15)

#define BINARIO (0)
#define LINEAS (1)


//---------------------------------------------------------------------------
class PACKAGE TKarnaugh : public TPaintBox
{
private:
        vector<string> nombreVars, varsIzq, varsSup, codIzq, codSup;
        vector<int> indiceVar;
        size numVars;

        void Dibujar(TCanvas *canvas);

        void BorrarMapa(TCanvas *canvas);
        void DibujarMatriz(TCanvas *canvas);
        void DibujarVariables(TCanvas *canvas);
        void DibujarTerminos(TCanvas *canvas);
        void DibujarLazos(TCanvas *canvas);

        /// Conjunto de Minterminos de la funcion.
        set<CuboBool> *setMint;
        /// Conjunto de Maxterminos de la funcion.
        set<CuboBool> *setMaxt;
        /// Conjunto de Terminos Irrelevantes de la función.
        set<CuboBool> *setTIs;
        /// Conjunto de Implicantes Primos (esenciales) de la función.
        set<CuboBool> *setIPs;

        set<CuboBool> *setMintLazo;

        pair<int,int> encontrarCasilla(string cubo);
        pair<int,int> convertirCasillaACoordenadas(unsigned int sup, unsigned int izq);
        string ConvertirCubo(string cubo);
        string desconvertirCubo(string cubo);
        void EscribirCentrado(int x, int y, AnsiString texto, TCanvas *canvas);
	void EscribirCentradoVertical(int x, int y, AnsiString texto, TCanvas *canvas);

        LOGFONT logFontHorizontal, logFontVertical;
	void setFontHorizontal(TCanvas *canvas);
	void setFontVertical(TCanvas *canvas);
	set<string> descombinarCubo(string cubo);

        int tipoVK;
        int tipoVisu;

        bool muestraLazos, mostrarTodosLazos;

        CuboBool lazoActivo;


protected:
public:
	__fastcall TKarnaugh(TComponent* Owner);
        __fastcall TKarnaugh::~TKarnaugh();
        void setNumVars(size NumVars);
        void setNombreVars(string nombreVars[]);
    /// Anyade un mintermino a la funcion
    void AnyadirMint(const CuboBool &c);
    void AnyadirMaxt(const CuboBool &c);
    /// Anyade un termino irrelevante a la funcion
    void AnyadirTI(const CuboBool &c);
    void AnyadirIP(const CuboBool &c);

    void AnyadirMintLazo(const CuboBool &c);

        void VaciarListas();
        unsigned int celdasIzq, celdasSup;
        size numVarsIzq, numVarsSup;
        int margenIzq, margenSup;
        void setTipoVK(int tipoVK);
        int getTipoVK();

        void setTipoVisuVariables(int tipoVisu);
        int getTipoVisuVariables();
        void Redibujar(void);
        void setMuestraLazos(bool muestraLazos);
        string convertirCasillaACubo(int x, int y);

        void setLazoActivo(const CuboBool &c);
        void setMostrarTodosLazos(bool mostrarTodosLazos);

        
__published:
};
//---------------------------------------------------------------------------
#endif
