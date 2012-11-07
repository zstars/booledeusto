/*$T boole/Boole2/Sim.cpp GC! 1.116 05/02/01 18:53:24 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include <vcl.h>
#pragma hdrstop
USERES("Sim.res");
USEFORM("S.cpp", FormMoore);

/*
 =======================================================================================================================
 =======================================================================================================================
 */
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TFormMoore), &FormMoore);
		Application->Run();
	}

	catch(Exception & exception)
	{
		Application->ShowException(&exception);
	}

	return 0;
}
