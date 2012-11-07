//---------------------------------------------------------------------------
#include "TablaSimbolos.h"


EntradaTS::EntradaTS(string nomVariable)
{
        this->nomVariable=nomVariable;
}


void EntradaTS::SetValor(bool valor)
{
        this->valor = valor;
}


bool EntradaTS::GetValor()
{
        return valor;
}

string EntradaTS::GetNombre()
{
        return nomVariable;
}

TablaSimbolos::TablaSimbolos()
{
        tabla = new map<string, EntradaTS>;
}


TablaSimbolos::~TablaSimbolos()
{
        delete tabla;
}


void TablaSimbolos::AnyadirEntrada(string entrada)
{
        tabla->insert(map<string, EntradaTS>::value_type(entrada, EntradaTS(entrada)));
}

int TablaSimbolos::NumEntradas()
{
        return tabla->size();
}


bool TablaSimbolos::SetValorEntrada(string entrada, bool valor)
{
        map<string, EntradaTS>::iterator i;

        if((i=tabla->find(entrada))!=tabla->end())
        {
                (*i).second.SetValor(valor);
                return true;
        }
        else
                return false;
}


pair<bool,bool> TablaSimbolos::GetValorEntrada(string entrada)
{
        map<string, EntradaTS>::iterator i;

        if((i=tabla->find(entrada))!=tabla->end())
                return pair<bool,bool>(true,(*i).second.GetValor());
        else
                return pair<bool,bool>(false,false);
}

map<string, EntradaTS>::iterator TablaSimbolos::Begin()
{
        return tabla->begin();
}

map<string, EntradaTS>::iterator TablaSimbolos::End()
{
        return tabla->end();
}

//---------------------------------------------------------------------------

