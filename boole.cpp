//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>
using namespace std;
//---------------------------------------------------------------------------
USEFORM("src\Boole1\app.cpp", ap);
USEFORM("src\Boole1\calc.cpp", Calculando);
USEFORM("src\Boole1\uKarnaugh.cpp", fKarnaugh);
USEFORM("src\Boole1\ExpBool.cpp", ExprBooleana);
USEFORM("src\Boole1\FormasN.cpp", FormasNormales);
USEFORM("src\Boole1\FormSimp.cpp", ExpresionSimp);
USEFORM("src\Boole1\Main.cpp", Principal);
USEFORM("src\Boole1\NandNor.cpp", NANDyNOR);
USEFORM("src\Boole1\NuevoSC.cpp", SistemaCombinacionalNuevo);
USEFORM("src\Boole1\SCCompac.cpp", SCFormasCompactas);
USEFORM("src\Boole1\TVComple.cpp", TablaVerdadCompleta);
USEFORM("src\Boole1\TVManual.cpp", TablaVerdadManual);
USEFORM("src\Boole2\FCalculando.cpp", FormCalculando);
USEFORM("src\Boole2\ayuda.cpp", fAyuda);
USEFORM("src\Boole2\uLog.cpp", fLog);
USEFORM("src\Boole2\Unit15.cpp", Form15);
USEFORM("src\Boole2\Unit11.cpp", Form11);
USEFORM("src\Boole2\Unit12.cpp", Form12);
USEFORM("src\Boole2\Unit13.cpp", Form13);
USEFORM("src\Boole2\Unit14.cpp", Form14);
USEFORM("src\Boole2\Unit10.cpp", Form10);
USEFORM("src\Boole2\V_Boole2.cpp", Form1Boole2);
USEFORM("src\Boole2\Unit2.cpp", Form2);
USEFORM("src\Boole2\Unit3.cpp", Form3);
USEFORM("src\Boole2\Unit4.cpp", NewDiagramForm);
USEFORM("src\Boole2\Unit5.cpp", Form5);
USEFORM("src\Boole2\Unit6.cpp", Form6);
USEFORM("src\Boole2\Unit8.cpp", Form8);
USEFORM("src\Boole2\Unit9.cpp", Form9);
USEFORM("src\Boole2\uSimulacion.cpp", fSimulacion);
USEFORM("src\Boole2\Unit16.cpp", Form16);
USEFORM("src\Circuito\V_Imprimir.cpp", FormI);
USEFORM("src\Circuito\V_Circuito.cpp", FormR);
USEFORM("src\Comun\uTextoAsoc.cpp", fTextoAsoc);
USEFORM("src\Boole1\Weblab.cpp", WeblabForm);
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
                /*try{
                	ifstream in("boole.lang");
                        string lang;
                        in >> lang;
                        if (lang == "en")
                        	resInstance=(void *)LoadNewResourceModule( ( (SUBLANG_ENGLISH_US << 10) | LANG_ENGLISH) );
                        else if (lang == "eu")
                        	resInstance=(void *)LoadNewResourceModule( ( (SUBLANG_DEFAULT << 10) | LANG_BASQUE) );

		} catch(ios_base::failure& var)
                { }*/

                // ~lrg
                // COMMENTED OUT THE FOLLOWING THREE LINES BECAUSE I HAVE YET TO FIGURE
                // OUT HOW TO ADD A FORM TO THE PROJECT WITHOUT BREAKING IT (IF THESE LINES
                // ARE NOT COMMENTED WEIRD RESOURCE NOT FOUND MESSAGES MAKE THE PROGRAM
                // CRASH ON STARTUP).
              	//resInstance=(void *)LoadNewResourceModule( ( (SUBLANG_ENGLISH_US << 10) | LANG_ENGLISH) );
               	//if(!resInstance)
                //	resInstance=(void *)LoadNewResourceModule( ( (SUBLANG_DEFAULT << 10) | LANG_BASQUE) );
		 Application->CreateForm(__classid(TPrincipal), &Principal);
                 Application->CreateForm(__classid(Tap), &ap);
                 Application->CreateForm(__classid(TCalculando), &Calculando);
                 Application->CreateForm(__classid(TfKarnaugh), &fKarnaugh);
                 Application->CreateForm(__classid(TExprBooleana), &ExprBooleana);
                 Application->CreateForm(__classid(TFormasNormales), &FormasNormales);
                 Application->CreateForm(__classid(TExpresionSimp), &ExpresionSimp);
                 Application->CreateForm(__classid(TSistemaCombinacionalNuevo), &SistemaCombinacionalNuevo);
                 Application->CreateForm(__classid(TSCFormasCompactas), &SCFormasCompactas);
                 Application->CreateForm(__classid(TTablaVerdadCompleta), &TablaVerdadCompleta);
                 Application->CreateForm(__classid(TTablaVerdadManual), &TablaVerdadManual);
                 Application->CreateForm(__classid(TNANDyNOR), &NANDyNOR);
                 Application->CreateForm(__classid(TFormCalculando), &FormCalculando);
                 Application->CreateForm(__classid(TfAyuda), &fAyuda);
                 Application->CreateForm(__classid(TfLog), &fLog);
                 Application->CreateForm(__classid(TForm15), &Form15);
                 Application->CreateForm(__classid(TForm11), &Form11);
                 Application->CreateForm(__classid(TForm12), &Form12);
                 Application->CreateForm(__classid(TForm13), &Form13);
                 Application->CreateForm(__classid(TForm14), &Form14);
                 Application->CreateForm(__classid(TForm10), &Form10);
                 Application->CreateForm(__classid(TForm1Boole2), &Form1Boole2);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TForm3), &Form3);
                 Application->CreateForm(__classid(TNewDiagramForm), &NewDiagramForm);
                 Application->CreateForm(__classid(TForm5), &Form5);
                 Application->CreateForm(__classid(TForm6), &Form6);
                 Application->CreateForm(__classid(TForm8), &Form8);
                 Application->CreateForm(__classid(TForm9), &Form9);
                 Application->CreateForm(__classid(TfSimulacion), &fSimulacion);
                 Application->CreateForm(__classid(TForm16), &Form16);
                 Application->CreateForm(__classid(TFormI), &FormI);
                 Application->CreateForm(__classid(TFormR), &FormR);
                 Application->CreateForm(__classid(TfTextoAsoc), &fTextoAsoc);
                 Application->CreateForm(__classid(TWeblabForm), &WeblabForm);
                 Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
