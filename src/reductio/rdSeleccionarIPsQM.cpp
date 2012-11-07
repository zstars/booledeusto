/***************************************************************************
                          rdSeleccionarIPsQM.cpp  -  description
                             -------------------
    begin                : Thu Apr 12 2001
    copyright            : (C) 2001 by Borja Sotomayor
    email                : borja@borjanet.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "rdSeleccionarIPsQM.h"
#include <vector>
#include <list>
#include <stack>
#include <algorithm>


/// Constructor. Recibe un puntero al simplificador al que pertenece.
rdSeleccionarIPs_QM::rdSeleccionarIPs_QM(rdSimplificador *padre):rdSeleccionarIPs(padre)
{

}


/** Una vez que se han obtenido los implicantes primos de la función,
	* este metodo hace una selección de IPs.
	*/
void rdSeleccionarIPs_QM::SeleccionarIPs(void)
{
    setIPsAux = *(simp->setIPs);
    tipoIPE=PRIMARIO;


    while(!simp->setMint->empty())
    {
        if(EncontrarIPEs())
        {
            BuscarTerminosNoCubiertos();
            tipoIPE=(tipoIPE==PRIMARIO?SECUNDARIO:tipoIPE);
        }
        else
        {
            tipoIPE=NO_ESENCIAL;
            ResolucionCiclica();
            //BuscarTerminosNoCubiertos();
        }
        EliminarRedundantes();
        EliminarNoDeseables();
    }
}


/** Encuentra los implicantes primos esenciales de la funcion booleana
 	* basandose en el conjunto de implicantes primos y minterminos.
	*/
bool rdSeleccionarIPs_QM::EncontrarIPEs(void)
{
    bool encontrado = false;

    set<CuboBool> setIPsAux2(setIPsAux);

    set<CuboBool>::iterator i=setIPsAux.begin();

    while(i!=setIPsAux.end())
    {
        set<CuboBool> sharp(*(simp->setMint));
        set<CuboBool>::iterator j=sharp.begin();
        while(j!=sharp.end())
            if(!((*i)>>(*j)))
                sharp.erase(j++);
            else
                j++;
        for(set<CuboBool>::iterator k=setIPsAux2.begin(); k!=setIPsAux2.end(); k++)
            if ((*i)!=(*k))
            {
                j=sharp.begin();
                while(j!=sharp.end())
                    if((*k)>>(*j))
                        sharp.erase(j++);
                    else
                        j++;
            }
        if (!sharp.empty())
        {
            simp->ipe[tipoIPE]->insert((*i));
            setIPsAux.erase(i++);
            encontrado = true;
        }
        else
            i++;
    }
    return encontrado;
}


/// Busca los minterminos que quedan por cubrir.
void rdSeleccionarIPs_QM::BuscarTerminosNoCubiertos(void)
{
    for(int i = PRIMARIO; i<=2; i++)
        for(set<CuboBool>::iterator j=simp->ipe[i]->begin(); j!=simp->ipe[i]->end(); j++)
        {
            set<CuboBool>::iterator k=simp->setMint->begin();
            while(k!=simp->setMint->end())
                if ((*j)>>(*k))
                    simp->setMint->erase(k++);
                else
                    k++;
        }
}


/// Elimina los implicantes primos redundantes del conjunto de IPs.
void rdSeleccionarIPs_QM::EliminarRedundantes(void)
{
    set<CuboBool>::iterator i=setIPsAux.begin();
    while(i!=setIPsAux.end())
    {
        bool CubreAlguno = false;
        for(set<CuboBool>::iterator j=simp->setMint->begin(); j!=simp->setMint->end() && !CubreAlguno; j++)
            CubreAlguno=CubreAlguno || ((*i)>>(*j));
        if(!CubreAlguno)
            setIPsAux.erase(i++);
        else
            i++;
    }
}


/// Elimina los implicantes primos no deseables del conjunto de IPS.
void rdSeleccionarIPs_QM::EliminarNoDeseables(void)
{
    set<CuboBool>::iterator i=setIPsAux.begin();

    while(i!=setIPsAux.end())
    {
        set<CuboBool> sharp(*(simp->setMint));
        bool noDeseable = false;

        set<CuboBool>::iterator j=sharp.begin();
        while(j!=sharp.end())
            if(!((*i)>>(*j)))
                sharp.erase(j++);
            else
                j++;

        for(set<CuboBool>::iterator k=setIPsAux.begin(); k!=setIPsAux.end() && !noDeseable; k++)
            if (i!=k)
            {
                bool loCubre = true;
                for(set<CuboBool>::iterator j=sharp.begin(); j!=sharp.end() && loCubre; j++)
                    loCubre=loCubre && ((*k)>>(*j));
                if (loCubre)
                    noDeseable=true;
            }
        if (noDeseable)
        {
            setIPsAux.erase(i++);
        }
        else
            i++;
    }
}
