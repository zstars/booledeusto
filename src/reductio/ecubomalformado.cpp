/***************************************************************************
                          ecubomalformado.cpp  -  description
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

#include "ecubomalformado.h"

/// Constructor. Recibe como parametro el mensaje de la excepcion.
ECuboMalFormado::ECuboMalFormado(const string &s): mensaje(s)
{ };
