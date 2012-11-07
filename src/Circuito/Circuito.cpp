/*$T boole/Circuito/Circuito.cpp GC! 1.116 05/02/01 18:53:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
USERES("Circuito.res");
USEUNIT("Entrada.cpp");
USEUNIT("funciones.cpp");
USEUNIT("FlipFlopJK.cpp");
USEUNIT("Puerta.cpp");
USEUNIT("PuertaAnd.cpp");
USEUNIT("PuertaNand.cpp");
USEUNIT("PuertaNor.cpp");
USEUNIT("PuertaOr.cpp");
USEFORM("V_Circuito.cpp", FormR);
USEUNIT("CircuitoCombinacional.cpp");
USEUNIT("CircuitoSecuencial.cpp");
USEUNIT("FlipFlop.cpp");
USEUNIT("FlipFlopD.cpp");
USEFORM("V_Imprimir.cpp", FormI);

/*
 =======================================================================================================================
 =======================================================================================================================
 */
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TFormR), &FormR);
		Application->CreateForm(__classid(TFormI), &FormI);
		Application->Run();
	}

	catch(Exception & exception)
	{
		Application->ShowException(&exception);
	}

	return 0;
}
