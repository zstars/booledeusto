/***************************************************************************
                          rdCoberturaMinima.cpp  -  description
                             -------------------
    begin                : Fri Apr 13 2001
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
 #include <stdio.h>
 #include <vcl.h>
#include "rdCoberturaMinima.h"
FILE * ContadorRecursividades;
TDateTime diaHora;
AnsiString ahora;

long bucles;   // ***************************************************

/** Constructor. Recibe la lista de minterminos (listMint) de la cual se quiere
	* encontrar la cobertura minima. Tambien se reciben los IPs (listIPs) de los
	* que se dispone para encontrar la cobertura minima, el numero de variables (numV),
	* y un parametro que indica si se desea o no sesgar el arbol de busqueda (sesg).
	* En el momento en el que se crea el objeto, se haya la cobertura minima, y se
	* deposita el resultado en el miembro 'listaMinima'.
	*/
rdCoberturaMinima::rdCoberturaMinima(list<CuboBool> *listIPs, list<CuboBool> *listMint, size numV, bool sesg):listaIPs(listIPs),listaMint(listMint),numVar(numV),sesgo(sesg)
{
	for(list<CuboBool>::iterator i=listaIPs->begin(); i!=listaIPs->end(); i++)
  	listaMinima.push_front(&(*i));

	nivel = 0;
	coste = 0;
	combProcesadas = 0;
	tamanyoMejor = numIPs = listaIPs->size();
	costeMejor = numVar * tamanyoMejor;

    //    ContadorRecursividades = fopen("ContadorRecursividades.txt", "w");//**********************
    //    fprintf(ContadorRecursividades, "\n %20u", combProcesadas);   //************************


	combProcesadas = recorrer(listaIPs->begin());
 //              char cadena[25];                     // *********************************
 //             ShowMessage(ltoa(bucles, cadena,10));   // *********************************
 //     fclose(ContadorRecursividades);                 //**********************************
	elaborarMensaje();
}


/// Destructor
rdCoberturaMinima::~rdCoberturaMinima()
{
}


/// Función que recorre recursivamente el arbol de busqueda.
long rdCoberturaMinima::recorrer(list<CuboBool>::iterator i)
{
       char cadena[25];                                     //*************************
       static unsigned long w=0;                            // *********************************
    w++;                                                     //********************
    if (w % 1000 == 0)                                        //**************************
    {
        ContadorRecursividades = fopen("ContadorRecursividades.txt", "a"); //*********************
        diaHora = diaHora.CurrentDateTime();                           //***********************
        fprintf(ContadorRecursividades, "\n %30s %20u %20u",           //********************
                  ((ahora=diaHora.DateTimeString().c_str())), w, combProcesadas); // ***************************
      fclose(ContadorRecursividades);                      //**********************************
     }

    if(i==listaIPs->end())
    {
        coste -= (*(pila.front())).literales;
        pila.pop_front();
        nivel--;
    }
    else
    {
       long x= listaIPs->size();
        while(i!=listaIPs->end())
        {
            pila.push_front(&(*i));
            coste += (*i).literales;
            nivel++;
            // Tratamiento!
            for(list<CuboBool>::iterator j=listaMint->begin(); j!=listaMint->end(); j++)
                listaMintAux.push_front(&(*j));
            for(list<CuboBool*>::iterator j=pila.begin(); j!=pila.end() && !listaMintAux.empty(); j++)
            {
                list<CuboBool*>::iterator k=listaMintAux.begin();
                while(k!=listaMintAux.end())
                    if (*(*j) >> *(*k))
                        listaMintAux.erase(k++);
                    else
                        k++;
            }
            if(listaMintAux.empty())
                if (nivel < tamanyoMejor? true : nivel == tamanyoMejor ? coste < costeMejor : false)
                //El conjunto de IPs en curso es valido
                {
                    listaMinima.clear();
                    listaMinima.insert(listaMinima.begin(), pila.begin(), pila.end());
                    costeMejor = coste;
                    tamanyoMejor = nivel;
                }
            combProcesadas++;

            bucles = combProcesadas;    //**********************************************

 //           if ( combProcesadas % 2000 == 0)                    // *********************************
 //               ShowMessage(ltoa(combProcesadas, cadena,10));   // *********************************


                                                 // *********************************
            if (nivel < tamanyoMejor || !sesgo)  //  && (combProcesadas < 6000))//? true : nivel == tamanyoMejor ? coste < costeMejor : false)
                 recorrer(++i);
             else
            {
                pila.pop_front();
                nivel--;
                i++;
             }
            if (i==listaIPs->end())
            {
               if(!pila.empty())
               {
                   coste -= (*(pila.front())).literales;
                   pila.pop_front();
                }
               nivel--;

            }

        }

    }
}


/// Elabora el mensaje con datos estadisticos.
void rdCoberturaMinima::elaborarMensaje(void)
{
	string m;
	char aux[20];
	
	m = "Se ha llegado a una tabla ciclica con ";
	sprintf(aux,"%lu",numIPs);
	m += aux;
	m += " IPs. ";
	m += "Se han procesado ";
	sprintf(aux,"%lu",combProcesadas);
	m += aux;
	m += " combinaciones hasta llegar a la cobertura minima. ";
	if (numIPs > MAXVAR)
		m += "No puede computarse el numero posible de combinaciones (demasiados IPs). ";
	else
	{
		bitInt posibles = 0;
		float sesgo;
		for(unsigned int i=0; i < numIPs; i++)
			posibles |= (1<<i);
		m += "El numero posible de combinaciones era ";
		sprintf(aux,"%lu",posibles+1);
		m += aux;
		
		m += ". ";
		if(this->sesgo)
		{
			m+="Han sido sesgadas el ";
			sesgo = ((float)(posibles - combProcesadas)/posibles)*100;
			sprintf(aux,"%2.2f",sesgo);
			m += aux;
			m += "% de las combinaciones.";
		}
	}
	mensaje = m;
}
