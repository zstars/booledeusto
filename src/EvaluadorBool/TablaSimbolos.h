//---------------------------------------------------------------------------

#ifndef TablaSimbolosH
#define TablaSimbolosH

#include <map>
#include <string>
using namespace std;

class EntradaTS
{
        private:
                string nomVariable;
                bool valor;

        public:
                EntradaTS(string nomVariable);
                void SetValor(bool valor);
                bool GetValor();
                string GetNombre();
};


class TablaSimbolos
{
        private:
                map<string, EntradaTS> *tabla;


        public:
                TablaSimbolos();
                ~TablaSimbolos();
                void AnyadirEntrada(string entrada);
                int NumEntradas();
                bool SetValorEntrada(string entrada, bool valor);
                pair<bool,bool> GetValorEntrada(string entrada);
                map<string, EntradaTS>::iterator TablaSimbolos::Begin();
                map<string, EntradaTS>::iterator TablaSimbolos::End();
                string getNombreVar(int i);
};

//---------------------------------------------------------------------------
#endif
