/*$T boole/Boole1/DINARRAY.H GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef DinArrayH
#define DinArrayH

class	DinArray
{
	struct nodoSalida
	{
		char		dato;
		nodoSalida	*siguienteSalida;
	};

	struct nodoEntrada
	{
		long		nOrden;
		nodoSalida	*estaFila;
		nodoEntrada *siguienteEntrada;
	};

	AnsiString	nombre;
	int			vEntradas, filas, columnas;
	nodoEntrada *matriz;
	AnsiString	entradas;
	AnsiString	salidas;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void		DinX(AnsiString, int, int);
	void		BorrarDinArray(void);
	void		EscribirNombre(AnsiString);
	AnsiString	LeerNombre(void);
	char		LeerDinArray(int, int);
	void		EscribirDinArray(int, int, char);
	int			NumEntradas(void);
	int			NumFilas(void);
	int			NumColumnas(void);
	AnsiString	LeerEntrada(int);
	AnsiString	LeerSalida(int);
	void		AnadirEntrada(AnsiString);
	void		AnadirSalida(AnsiString);
	void		BorrarEntradas(void);
	void		BorrarSalidas(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void		borrarEntradas(nodoEntrada *);
	void		borrarSalidas(nodoSalida *);
};
#endif
