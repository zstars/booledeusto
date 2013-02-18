#ifndef EvaluadorBoolH
#define EvaluadorBoolH

#include <iostream>
#include <sstream>
#include "TablaSimbolos.h"
#include "LexerBooleano.hpp"
#include "ParserBooleano.hpp"
#include "ParserEvaluador.hpp"
#include <antlr/TokenStreamException.hpp>
#include <antlr/RecognitionException.hpp>
#include "ParserBooleanoExt.h"
#include "EvaluadorBool.hpp"

class EvaluadorBool
{
        private:
                TablaSimbolos *ts;
                char *filename;
                LexerBooleano *lexer;
                ParserBooleanoExt *parser;
                ParserEvaluador *evaluador;
                istringstream *input_string;
                vector<bool> *tablaVerdad;
                vector<string> *vars;
                antlr::RefAST ast;

                string Dec2BinFixed(unsigned int dec, int numCars);                

        public:
                EvaluadorBool();
                ~EvaluadorBool();

                unsigned int getNumVars();
                unsigned int getNumMinterminos();
                string getNombreVar(int i);
                bool getValorMintermino(int i);
                void evaluar(const char *expr);
                bool SetValorEntrada(string entrada, bool valor);
                bool getValor();
                void AnyadirEntrada(string entrada);
};


#endif
