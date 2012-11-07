/*$T boole/Boole2/sistema.h GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#define MaxCir	50

// Cantidad maxima de circulos
#define MaxFle	50

// Cantidad maxima de flechas
#define AUTOMATA_COMPLETO			(0)
#define MOORE_ESTADO_SIN_SALIDA		(1)
#define MEALY_TRANSICION_SIN_SALIDA (2)
#define DEMASIADAS_TRANSICIONES		(3)
#define FALTA_TRANSICION			(4)
class	PAR
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int		primero;
	int		segundo;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	setPrimero(int a);
	void	setSegundo(int b);
	int		getPrimero(void);
	int		getSegundo(void);
};
class	CELDA
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int		ok;
	int		util;
	int		tachado;
	PAR		par[MaxCir];
	int		numpares;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CELDA(void);
	int		esOk(void);
	void	setNoOk(void);
	int		esUtil(void);
	void	setUtil(void);
	void	setNoUtil(void);
	int		esTachado(void);
	void	Tachar(void);
	int		obtenerPrimero(int i);
	int		obtenerSegundo(int i);
	void	AnyadirPar(int a, int b);
	int		obtenerNumpares(void);
};
class	SOLUCION
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	PAR		equivalentes[MaxCir];
	int		numequivalentes;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	SOLUCION(void);
	void	AnyadirEquivalentes(int a, int b);
	int		getNumeroEquivalentes(void);
	int		obtenerPrimerEq(int i);
	int		obtenerSegundoEq(int i);
};

//
// =======================================================================================================================
//    fin modificado Ainara CLASE CIRCULO
// =======================================================================================================================
//
class	CIRCULO
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int			CirculoX;

	// Coordenada X del circulo en el Sistema
	int			CirculoY;

	// Coordenada Y del circulo en el Sistema
	AnsiString	Etiqueta1;

	// El nombre del circulo
	AnsiString	Etiqueta2;

//
// -----------------------------------------------------------------------------------------------------------------------
//    La etiqueta de los numeros
// -----------------------------------------------------------------------------------------------------------------------
//
public:
	AnsiString	DevolverEtiqueta1(void);
	void		ActualizarEtiqueta1(AnsiString a);
	AnsiString	DevolverEtiqueta2(void);
	void		ActualizarEtiqueta2(AnsiString a);
	void		ActualizarCoordenadasCirculo(int X, int Y);

	// Actualiza las coordenadas X e Y del circulo
	int			CoordenadaCirculoX(void);

	// Devuelve la coordenada X del circulo
	int			CoordenadaCirculoY(void);

	// Devuelve la coordenada X del circulo
};

//
// =======================================================================================================================
//    CLASE FLECHA
// =======================================================================================================================
//
class	FLECHA
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int			FlechaX;

	// Coordenada X del centro de la flecha
	int			FlechaY;

	// Coordenada Y del centro de la flecha
	int			CirculoSale;

	// Numero de Circulo del que sale la flecha
	int			CirculoEntra;

	// Numero de Circulo al que entra la flecha
	AnsiString	Etiqueta1;

	// Etiqueta1
	AnsiString	Etiqueta2;

//
// -----------------------------------------------------------------------------------------------------------------------
//    Etiqueta2
// -----------------------------------------------------------------------------------------------------------------------
//
public:
	AnsiString	DevolverEtiqueta1(void);
	AnsiString	DevolverEtiqueta2(void);
	void		ActualizarEtiqueta1(AnsiString et1);
	void		ActualizarEtiqueta2(AnsiString et2);
	void		ActualizarCirculoSale(int i);

	// Pone el numero del circulo del que sale la flecha
	void		ActualizarCirculoEntra(int i);

	// Pone el numero del circulo al que entra la flecha
	int			FlechaCirculoEntra(void);

	// Devuelve el numero del circulo al que entra la flecha
	int			FlechaCirculoSale(void);

	// Devuelve el numero del circulo del que sale la flecha
	void		ActualizarCoordenadasFlecha(int X, int Y);

	// Actualiza las coordenadas X e Y de la flecha
	int			CoordenadaFlechaX(void);

	// Devuelve la coordenada X de la flecha
	int			CoordenadaFlechaY(void);

	// Devuelve la coordenada Y de la flecha
};

//
// =======================================================================================================================
//    CLASE SISTEMA
// =======================================================================================================================
//
class	SISTEMA
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	int			NumCarEnt;

	// Numero de caracteres de entrada
	int			NumCarSal;

	// Numero de caracteres de entrada
	int			Tipo;

	// 0=Moore 1=Mealy
	int			RatonX;

	// Coordenada X del raton en el sistema
	int			RatonY;

	// Coordenada Y del raton en el sistema
	int			numcirculos;

	// Numero de circulos actualmente en el sistema
	int			numflechas;

	// Numero de flechas actualmente en el sistema
	int			indiceInicial;

	// Circulo inicial
	int			indiceActual;

	// Circulo actual
	int			indiceFlechaActual;

	// Flecha actual
	int			circulosel;

	// Circulo seleccionado, o el valor -1 si no hay seleccionado
	int			flechasel;

	// flecha seleccionada, o el valor -1 si no hay seleccionada
	bool		circulomoviendose;

	// Circulo seleccionado moviendose
	bool		flechamoviendose;

	// Flecha seleccionada moviendose
	CIRCULO		circulo[MaxCir];

	// Un sistema es una agrupacion de circulos
	FLECHA		flecha[MaxFle];

	//
	// Un sistema es una agrupacion de flechas
	// inicio modificado Ainara
	//
	int			numcirculos2;
	int			numflechas2;

	// Numero de flechas actualmente en el Sistema
	CIRCULO		circulo2[MaxCir];

	// Un Sistema es una agrupacion de circulos
	FLECHA		flecha2[MaxFle];

	// Un Sistema es una agrupacion de flechas
	CELDA		celda[MaxCir - 1][MaxCir - 1];
	SOLUCION	solucion[MaxCir - 1];

//
// -----------------------------------------------------------------------------------------------------------------------
//    fin modificado Ainara
// -----------------------------------------------------------------------------------------------------------------------
//
public:
	void		ActualizarTipo(int t);

	// Actualiza el tipo de diagrama (1=Mealy 0=Moore)
	int			DevolverTipo(void);

	// Devuelve el tipo de diagrama (1=Mealy 0=Moore)
	void		ActualizarNumCarEnt(int t);

	// Actualizar el Numero de caracteres de la entrada del automata
	int			DevolverNumCarEnt(void);

	// Devuelve el Numero de caracteres de la entrada del automata
	void		ActualizarNumCarSal(int t);

	// Actualizar el Numero de caracteres de la salida del automata
	int			DevolverNumCarSal(void);

	// Devuelve el Numero de caracteres de la salida del automata
	void		ActualizarEtiqueta1Circulo(int num, AnsiString a);

	// Actualiza la etiqueta del circulo num desde la clase sistema
	void		ActualizarEtiqueta2Circulo(int num, AnsiString a);

	// Actualiza la etiqueta del circulo num desde la clase sistema
	void		ActualizarEtiqueta1Flecha(int num, AnsiString a);

	// Actualiza la etiqueta1 de la flecha num desde la clase sistema
	void		ActualizarEtiqueta2Flecha(int num, AnsiString a);

	// Actualiza la etiqueta2 de la flecha num desde la clase sistema
	void		ActualizarFlecha(int n, int x, int y);

	// Actualiza las coordenadas de la flecha n desde la clase sistema
	void		ActualizarCirculo(int n, int x, int y);

	// Actualiza las coordenadas del circulo n desde la clase sistema
	void		ActualizarValorSale(int n, int i);

	// Actualiza el numero de Circulo i del que sale la flecha n
	void		ActualizarValorEntra(int n, int i);

	// Actualiza el numero de Circulo i al que entra la flecha n
	void		CirculoMoviendo(bool s);

	// Quita o pone un circulo en movimiento
	void		FlechaMoviendo(bool s);

	// Quita o pone un flecha en movimiento
	bool		EstaCirculoMoviendose(void);

	// Nos informa si esta o no moviendose el circulo seleccionado
	bool		EstaFlechaMoviendose(void);

	// Nos informa si esta o no moviendose la flecha seleccionada
	void		SeleccionarCirculo(int i);

	// Selecciona un circulo y deselecciona una flecha
	void		SeleccionarFlecha(int i);

	// Selecciona una flecha y deselecciona un circulo
	CIRCULO		DevolverCirculo(int i);

	// Devuelve las atributos del circulo i (solo sirve para consultar valores)
	FLECHA		DevolverFlecha(int i);

	// Devuelve los atributos de la flecha i (solo sirve para consultar valores)
	double		Spline_CalcX(int ApX, int BpX, int CpX, int DpX, double T, double D);

	// Calcula los puntos de X de la Spline
	double		Spline_CalcY(int ApY, int BpY, int CpY, int DpY, double T, double D);

	void		DibujaSentido(int x1, int y1, int x2, int y2);

	void		Spline(int x1, int y1, int x2, int y2, int x3, int y3);
	void		DibujarLazo(int num, int x, int y);

	// Dibuja el bucle de un estado
	void		RestauraSistema(void);

	// Restaura la pantalla con la situacion actual del sistema
	void		BorrarFlecha(void);
	void		BorrarCirculo(void);
	void		MoverCirculo(void);

	// Mueve un circulo a la par que el raton
	void		MoverFlecha(void);

	// Mueve una flecha a la par que el raton
	int			CirculoSeleccionado(void);

	// Devuelve el circulo actualmente seleccionado
	int			FlechaSeleccionada(void);

	// Devuelve el circulo actualmente seleccionado
	void		ActualizarRaton(int X, int Y);

	// Actualiza las coordenadas del raton en el sistema
	void		InicializarCirculo(void);

	// Inicializa un nuevo circulo
	int			RatonEncimaCirculo(void);

	//
	// Comprueba si el raton esta encima de un circulo devuelve el numero del circulo
	// o -1
	//
	int			RatonEncimaFlecha(void);

	//
	// Comprueba si el raton esta encima del cuadrado de una flecha y devuelve el
	// numero de la flecha o -1
	//
	int			NumCirculos(void);

	// Devuelve el numero de circulos en el sistema
	int			NumFlechas(void);

	// Devuelve el numero de flechas en el sistema
	void		ActualizarNumCirculos(int a);

	// Pone el numero de circulos en el sistema
	void		ActualizarNumFlechas(int a);

	// Pone el numero de flechas en el sistema
	void		InicializarFlecha(void);

	// Inicializa una nueva flecha
	bool		RatonCercaAlgo(int Margen);

	//
	// Nos informa si el raton esta cerca de algun cuadrado o circulo
	// inicio modificado Ainara
	//
	void		crearTablaImplicacion(void);

	void		particionDeSalida(void);
	void		paresImplicados(void);
	void		tablaTerminada(void);
	void		comprobarTabla(void);
	int			pertenece(int a);
	void		particionEquivalencia(void);
	void		cambiarCirculos(void);
	void		cambiarFlechas(void);
	void		mostrarCambios(void);
	CIRCULO		getCirculo(int a);
	FLECHA		getFlecha(int a);
	FLECHA		getFlechaActual(void);

	AnsiString	CogerFlecha(int a);
	AnsiString	CogerFlecha2(int a);
	int			GetNumCirculos(void);
	int			GetNumFlechas(void);
	AnsiString	CogerSalidaActual(void);
	AnsiString	CogerNombreCirculoActual(void);
	AnsiString	cogerEtiq(int b);
	AnsiString	cogerEtiqPrima(int b);
	AnsiString	cogerEtiqF(int b);
	AnsiString	cogerEtiqF2(int b);
	AnsiString	cogerEtiqF3(int b);
	AnsiString	cogerEtiqF4(int b);

	// fin modificado Ainara
	bool		PuedeSeguir(AnsiString &ent, AnsiString &barrera);

	int			VerificarAutomata(int &estado, int &transicion, AnsiString &entrada);
};
