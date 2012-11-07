/***************************************************************************
                          rdObtenerIPsQM.cpp  -  description
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

#include "rdObtenerIPsQM.h"
#include <vector>
#include <list>
#include <algorithm>


/// Constructor. Recibe un puntero al simplificador al que pertenece.
rdObtenerIPs_QM::rdObtenerIPs_QM(rdSimplificador *padre):rdObtenerIPs(padre)
{
}


/// Destructor
rdObtenerIPs_QM::~rdObtenerIPs_QM()
{
}


/// A partir de los minterminos de la función, obtiene los implicantes
/// primos de la función.	
void rdObtenerIPs_QM::obtenerIPs()
{
    vector< list<CuboBool> > *v1, *v2, *pral, *aux;

		v1 = new vector< list<CuboBool> >(simp->numVar +1, list<CuboBool>() );
		v2 = new vector< list<CuboBool> >(simp->numVar +1, list<CuboBool>() );

		pral = v1;
		aux = v2;

    size subEspacio=0;
    register list<CuboBool>::iterator i,j;
    bool vacioPral;

    for (set<CuboBool>::iterator i=simp->setMint->begin(); i!=simp->setMint->end(); i++)
        (*pral)[(*i).peso].push_back(*i);

    for (set<CuboBool>::iterator i=simp->setTIs->begin(); i!=simp->setTIs->end(); i++)
        (*pral)[(*i).peso].push_back(*i);

    do
    {
        for (register size peso = 0; peso < simp->numVar-subEspacio; peso++)
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

        for (register size peso = 0; peso <= simp->numVar-subEspacio; peso++)
        {
            for(i=(*pral)[peso].begin(); i!=(*pral)[peso].end(); i++)
                if(!(*i).flag)
                    simp->setIPs->insert(*i);
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
}
