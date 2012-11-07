/***************************************************************************
                          cubobool.cpp  -  description
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

#include "cubobool.h"
#include "ecubomalformado.h"


/*#########-  CONSTRUCTORES  -#########*/


/// Constructor por defecto. Inicializa el cubo sin literales.
CuboBool::CuboBool():peso(0),flag(false),literales(MAXVAR),unos(0),ceros(0)
    { };


/// Construye el cubo con el 0-subcubo representado por n
/// (numero entero sin signo)
CuboBool::CuboBool(const bitInt n):flag(false),literales(MAXVAR)
{
    unos = n;
    ceros = ~unos;
    peso = Peso(n);
}


/// Construye el cubo a partir de un array de caracteres (terminado en
/// NULL que represente el cubo en notacion cubica
/// (p.Ej: "1010", "1-0", "1-01--11-0", etc.)
CuboBool::CuboBool(const char *s):flag(false),literales(MAXVAR)
{
    int len = (int) strlen(s);

    unos=0;
    ceros=~0ul;
    peso=0;
    if (len > MAXVAR)
       throw ECuboMalFormado(string("String demasiado largo (no hay suficientes variables)"));
    else
    {
        bool formatoCorrecto = len;
        int i = 0,j;

        while (formatoCorrecto && i<len)
        {
           if (!(s[i]=='0' || s[i]=='1' || s[i]=='-'))
                formatoCorrecto = false;
           i++;
        }
        if (!formatoCorrecto)
           throw ECuboMalFormado(string("Formato incorrecto (solo '0','1','-')"));
        else
            for (i=len-1,j=0;i>=0;i--,j++)
                switch (s[i])
                {
                    case '1': set_bit(unos,j); reset_bit(ceros,j); peso++; break;
                    case '0': reset_bit(unos,j); set_bit(ceros,j); break;
                    case '-': reset_bit(unos,j); reset_bit(ceros,j); break;
                }
    }
}


/// Igual que el constructor CuboBool(const char *s), excepto que recibe un string (STL)
CuboBool::CuboBool(const string &s):flag(false),literales(MAXVAR)
{
    unos=0;
    ceros=~0ul;
    peso=0;

    if (s.length() > MAXVAR)
       throw ECuboMalFormado(string("String demasiado largo (no hay suficientes variables)"));
    else
    {
        bool formatoCorrecto = true;

        string::const_iterator i = s.begin();
        string::const_reverse_iterator k;
        unsigned int j;

        while (formatoCorrecto && i!=s.end())
        {
           if (!(*i=='0' || *i=='1' || *i=='-'))
                formatoCorrecto = false;
           i++;
        }
        if (!formatoCorrecto)
           throw ECuboMalFormado(string("Formato incorrecto (solo '0','1','-')"));
        else
            for (k=s.rbegin(),j=0;k!=s.rend();k++,j++)
                switch (*k)
                {
                    case '1': set_bit(unos,j); reset_bit(ceros,j); peso++; break;
                    case '0': reset_bit(unos,j); set_bit(ceros,j); break;
                    case '-': reset_bit(unos,j); reset_bit(ceros,j); break;
                }
    }
}


/// Constructor Copy
CuboBool::CuboBool(const CuboBool &c)
{
    this->unos = c.unos;
    this->ceros = c.ceros;
    this->peso = c.peso;
    this->flag = c.flag;
    this->literales = c.literales;

}




/*#########-  CONVERSORES  -#########*/


/// Convierte el cubo booleano a string (representado en notacion cubica)
string CuboBool::aString(const size numVar = MAXVAR) const
{
    string s;

    for (size i=0; i<numVar; i++)
        if (!existe(i))
            s.insert(s.begin(),'-');
        else if (test_bit(unos,i))
            s.insert(s.begin(),'1');
        else
            s.insert(s.begin(),'0');

    return s;
}


/// Convierte el cubo booleano a un entero (siempre y cuando sea un
/// 0-subcubo).
bitInt CuboBool::aInt(void) const
{
    return unos;
}




/*#########-  SOBRECARGA DEL OPERADOR DE ASIGNACION  -#########*/

/// Operador de asignación
CuboBool CuboBool::operator=(const CuboBool &c)
{
    this->unos = c.unos;
    this->ceros = c.ceros;
    this->peso = c.peso;
    this->flag = c.flag;
    this->literales = c.literales;
    return *this;
}




/*#########-  CONSTRUCTORES PRIVADOS  -#########*/

/// Constructor privado que recibe varios de los atributos, tanto publicos
/// como privados del cubo. Solo es utilizado por las funciones miembro de
/// CuboBool.
CuboBool::CuboBool(const bitInt unosP,const bitInt cerosP,const size pesoP, const size literalesP):peso(pesoP),flag(false),literales(literalesP),unos(unosP),ceros(cerosP)
    { };




/*#########-  METODOS PRIVADOS  -#########*/

/// Funcion estatica que devuelve el peso de un dato de tipo BitInt
/// (es decir, el numero de unos del numero)
size CuboBool::Peso(const bitInt b)
{
    size peso = 0;
    for (size i = 0; i<MAXVAR; i++)
        if (b & (1ul<<i))
            peso++;
    return peso;
}
