#include "EvaluadorBool.hpp"
#include <exception>


EvaluadorBool::EvaluadorBool()
{
        ts = new TablaSimbolos();
        filename = "<cin>";
        tablaVerdad = new vector<bool>();
        vars = new vector<string>();
        evaluador = new ParserEvaluador();
        evaluador->SetTablaSimbolos(ts);
}

EvaluadorBool::~EvaluadorBool()
{
        delete evaluador;
        delete ts;
        delete tablaVerdad;
        delete vars;
}


unsigned int EvaluadorBool::getNumVars()
{
        return ts->NumEntradas();
}

unsigned int EvaluadorBool::getNumMinterminos()
{
        return (1ul << getNumVars());
}

void EvaluadorBool::evaluar(const char *expr)
{
        ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)
        try
        {
        tablaVerdad->clear();
        vars->clear();

	input_string = new istringstream();
        input_string->str(expr);

        istream *input = input_string;

        lexer = new LexerBooleano(*input);
        lexer->setFilename(filename);
        lexer->SetTablaSimbolos(ts);

        parser = new ParserBooleanoExt(*lexer);
        parser->setFilename(filename);

       	parser->expr();


        ast = parser->getAST();

        int j=0;
        for(map<string, EntradaTS>::iterator i = ts->Begin();i!=ts->End();i++,j++)
        {
                vars->push_back((*i).second.GetNombre());
        }



        delete input_string;
        delete lexer;
        delete parser;
        }
        catch(TokenStreamException &e) {
                throw(exception());
        }
        catch(RecognitionException &re) {
                throw(exception());
        }
}

string EvaluadorBool::getNombreVar(int i)
{
        return (*vars)[i];
}


string EvaluadorBool::Dec2BinFixed(unsigned int dec, int numCars)
{
	/*~~~~~~*/
	string	binario;
	int num,resto;
	/*~~~~~~*/

	binario = "";
        num = dec;

	for(int i = 0; i < numCars; i++)
	{
		resto = num % 2;
		num = num / 2;
		binario = (resto?"1":"0") + binario;
	}

	return binario;
}


bool EvaluadorBool::getValorMintermino(int i)
{
        string bin = Dec2BinFixed(i,getNumVars());
        for (unsigned int j=0;j<getNumVars();j++)
        {
                ts->SetValorEntrada(getNombreVar(j),bin[j]=='0'?false:true);
        }
        return evaluador->expr(ast);
}

bool EvaluadorBool::SetValorEntrada(string entrada, bool valor)
{
        return ts->SetValorEntrada(entrada, valor);
}

bool EvaluadorBool::getValor()
{
        return evaluador->expr(ast);
}

void EvaluadorBool::AnyadirEntrada(string entrada)
{
        ts->AnyadirEntrada(entrada);
}

