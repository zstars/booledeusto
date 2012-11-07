//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("evaluador_bool.res");
USEFORM("fMain.cpp", formMain);
USEUNIT("LexerBooleano.cpp");
USEUNIT("ParserBooleano.cpp");
USELIB("antlr.lib");
USEUNIT("ParserEvaluador.cpp");
USEUNIT("TablaSimbolos.cpp");
USEUNIT("ParserBooleanoExt.cpp");
USEUNIT("EvaluadorBool.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TformMain), &formMain);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
