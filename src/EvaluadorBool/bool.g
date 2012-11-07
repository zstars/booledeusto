header{
#include "TablaSimbolos.h"
}

options {
	language="Cpp";
}

class ParserBooleano extends Parser;
options {
	buildAST = true;
}


expr	:	expr_suma EOF
	;

expr_suma
	:	expr_xor (SUMA^ expr_xor)* 
	;

expr_xor
	:	expr_prod (XOR^ expr_prod)* 
	;

expr_prod
	:	atom (PROD^ atom)*
	;

atom	:	VAR
	|	(PARENIZQ! expr_suma PARENDER!)
	|	NEG^ atom
	;

class LexerBooleano extends Lexer;

options {
   k=2;
}
{
private:
	TablaSimbolos *ts;

public:	
	void SetTablaSimbolos(TablaSimbolos *ts)
	{
		this->ts = ts;
	}
}

BLANCO	:	(' '
	|	'\t'
	|	'\n'
	|	'\r')
		{ _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; }
	;

PARENIZQ:	'('
	;

PARENDER:	')'
	;

PROD	:	('*' | '&' | "&&")
	;

XOR	:	('^')
	;

SUMA	:	('+' | '|' | "||")
	;

NEG	:	('-' | '~')
	;

SEMI	: 	';'
	;

VAR
	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')*
		{ts->AnyadirEntrada($getText);}
	;

class ParserEvaluador extends TreeParser;


{
private:
	TablaSimbolos *ts;

public:	
	void SetTablaSimbolos(TablaSimbolos *ts)
	{
		this->ts = ts;
	}
}


expr returns [bool r]
{
	bool a,b;
}
	:	#(SUMA a=expr b=expr)	{r= a || b;}
	|	#(XOR a=expr b=expr)	{r= (a && !b) || (!a && b);}
	|	#(PROD a=expr b=expr)	{r= a && b;}
	|	#(NEG a=expr)		{r= !a;}
	|	v:VAR			{r= ts->GetValorEntrada(v->getText()).second;}
	;

