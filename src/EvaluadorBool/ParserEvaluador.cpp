/* $ANTLR 2.7.2a2 (20020112-1): "bool.g" -> "ParserEvaluador.cpp"$ */
#include "ParserEvaluador.hpp"
#include <antlr/Token.hpp>
#include <antlr/AST.hpp>
#include <antlr/NoViableAltException.hpp>
#include <antlr/MismatchedTokenException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/BitSet.hpp>
#line 1 "bool.g"
#line 11 "ParserEvaluador.cpp"
ParserEvaluador::ParserEvaluador()
	: ANTLR_USE_NAMESPACE(antlr)TreeParser() {
}

bool  ParserEvaluador::expr(ANTLR_USE_NAMESPACE(antlr)RefAST _t) {
#line 99 "bool.g"
	bool r;
#line 19 "ParserEvaluador.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_AST_in = _t;
	ANTLR_USE_NAMESPACE(antlr)RefAST v = ANTLR_USE_NAMESPACE(antlr)nullAST;
#line 99 "bool.g"
	
		bool a,b;
	
#line 26 "ParserEvaluador.cpp"
	
	try {      // for error handling
		if (_t == ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = ASTNULL;
		switch ( _t->getType()) {
		case SUMA:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t31 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp1_AST_in = _t;
			match(_t,SUMA);
			_t = _t->getFirstChild();
			a=expr(_t);
			_t = _retTree;
			b=expr(_t);
			_t = _retTree;
			_t = __t31;
			_t = _t->getNextSibling();
#line 103 "bool.g"
			r= a || b;
#line 46 "ParserEvaluador.cpp"
			break;
		}
		case XOR:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t32 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp2_AST_in = _t;
			match(_t,XOR);
			_t = _t->getFirstChild();
			a=expr(_t);
			_t = _retTree;
			b=expr(_t);
			_t = _retTree;
			_t = __t32;
			_t = _t->getNextSibling();
#line 104 "bool.g"
			r= (a && !b) || (!a && b);
#line 63 "ParserEvaluador.cpp"
			break;
		}
		case PROD:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t33 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp3_AST_in = _t;
			match(_t,PROD);
			_t = _t->getFirstChild();
			a=expr(_t);
			_t = _retTree;
			b=expr(_t);
			_t = _retTree;
			_t = __t33;
			_t = _t->getNextSibling();
#line 105 "bool.g"
			r= a && b;
#line 80 "ParserEvaluador.cpp"
			break;
		}
		case NEG:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST __t34 = _t;
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp4_AST_in = _t;
			match(_t,NEG);
			_t = _t->getFirstChild();
			a=expr(_t);
			_t = _retTree;
			_t = __t34;
			_t = _t->getNextSibling();
#line 106 "bool.g"
			r= !a;
#line 95 "ParserEvaluador.cpp"
			break;
		}
		case VAR:
		{
			v = _t;
			match(_t,VAR);
			_t = _t->getNextSibling();
#line 107 "bool.g"
			r= ts->GetValorEntrada(v->getText()).second;
#line 105 "ParserEvaluador.cpp"
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(_t);
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		if ( _t != ANTLR_USE_NAMESPACE(antlr)nullAST )
			_t = _t->getNextSibling();
	}
	_retTree = _t;
	return r;
}

const char* ParserEvaluador::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"SUMA",
	"XOR",
	"PROD",
	"VAR",
	"PARENIZQ",
	"PARENDER",
	"NEG",
	"BLANCO",
	"SEMI",
	0
};



