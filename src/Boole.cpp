/*$T boole/Boole.cpp GC! 1.116 05/02/01 18:53:22 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
USEFORM("Boole1\ExpBool.cpp", ExprBooleana);
USEFORM("Boole1\FormasN.cpp", FormasNormales);
USEFORM("Boole1\FormSimp.cpp", ExpresionSimp);
USEFORM("Boole1\Main.cpp", Principal);
USEFORM("Boole1\NandNor.cpp", NANDyNOR);
USEFORM("Boole1\NuevoSC.cpp", SistemaCombinacionalNuevo);
USEFORM("Boole1\SCCompac.cpp", SCFormasCompactas);
USEFORM("Boole1\TVComple.cpp", TablaVerdadCompleta);
USEFORM("Boole1\TVManual.cpp", TablaVerdadManual);
USEFORM("Boole1\app.cpp", ap);
USEFORM("Boole2\V_Boole2.cpp", Form1Boole2);
USEFORM("Boole2\Unit10.cpp", Form10);
USEFORM("Boole2\Unit11.cpp", Form11);
USEFORM("Boole2\Unit12.cpp", Form12);
USEFORM("Boole2\Unit13.cpp", Form13);
USEFORM("Boole2\Unit14.cpp", Form14);
USEFORM("Boole2\Unit15.cpp", Form15);
USEFORM("Boole2\Unit16.cpp", Form16);
USEFORM("Boole2\Unit2.cpp", Form2);
USEFORM("Boole2\Unit3.cpp", Form3);
USEFORM("Boole2\Unit4.cpp", Form4);
USEFORM("Boole2\Unit5.cpp", Form5);
USEFORM("Boole2\Unit6.cpp", Form6);
USEFORM("Boole2\Unit8.cpp", Form8);
USEFORM("Boole2\Unit9.cpp", Form9);
USEFORM("Circuito\V_Circuito.cpp", FormR);
USEFORM("Circuito\V_Imprimir.cpp", FormI);
USEFORM("Boole2\ayuda.cpp", fAyuda);
USEFORM("Boole2\uSimulacion.cpp", fSimulacion);
USEFORM("Boole2\uLog.cpp", fLog);
USEFORM("Comun\uTextoAsoc.cpp", fTextoAsoc);
USEFORM("Boole1\uKarnaugh.cpp", fKarnaugh);
//---------------------------------------------------------------------------
#include "ReInit.hpp"

HINSTANCE resInstance;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->Title = "BOOLE-DEUSTO";
                resInstance=(void *)LoadNewResourceModule( ( (SUBLANG_ENGLISH_US << 10) | LANG_ENGLISH) );
		Application->CreateForm(__classid(TPrincipal), &Principal);
		Application->CreateForm(__classid(TExprBooleana), &ExprBooleana);
		Application->CreateForm(__classid(TFormasNormales), &FormasNormales);
		Application->CreateForm(__classid(TExpresionSimp), &ExpresionSimp);
		Application->CreateForm(__classid(TNANDyNOR), &NANDyNOR);
		Application->CreateForm(__classid(TSistemaCombinacionalNuevo), &SistemaCombinacionalNuevo);
		Application->CreateForm(__classid(TSCFormasCompactas), &SCFormasCompactas);
		Application->CreateForm(__classid(TTablaVerdadCompleta), &TablaVerdadCompleta);
		Application->CreateForm(__classid(TTablaVerdadManual), &TablaVerdadManual);
		Application->CreateForm(__classid(Tap), &ap);
		Application->CreateForm(__classid(TForm1Boole2), &Form1Boole2);
		Application->CreateForm(__classid(TForm10), &Form10);
		Application->CreateForm(__classid(TForm11), &Form11);
		Application->CreateForm(__classid(TForm12), &Form12);
		Application->CreateForm(__classid(TForm13), &Form13);
		Application->CreateForm(__classid(TForm14), &Form14);
		Application->CreateForm(__classid(TForm15), &Form15);
		Application->CreateForm(__classid(TForm16), &Form16);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->CreateForm(__classid(TForm5), &Form5);
		Application->CreateForm(__classid(TForm6), &Form6);
		Application->CreateForm(__classid(TForm8), &Form8);
		Application->CreateForm(__classid(TForm9), &Form9);
		Application->CreateForm(__classid(TFormR), &FormR);
		Application->CreateForm(__classid(TFormI), &FormI);
		Application->CreateForm(__classid(TfAyuda), &fAyuda);
		Application->CreateForm(__classid(TfSimulacion), &fSimulacion);
		Application->CreateForm(__classid(TfLog), &fLog);
		Application->CreateForm(__classid(TfTextoAsoc), &fTextoAsoc);
		Application->CreateForm(__classid(TfKarnaugh), &fKarnaugh);
		Application->Run();
	}

	catch(Exception & exception)
	{
		Application->ShowException(&exception);
	}

	return 0;
}
