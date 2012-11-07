/* $ANTLR 2.7.2a2 (20020112-1): "bool.g" -> "ParserBooleano.cpp"$ */
#include "ParserBooleano.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "bool.g"
#line 8 "ParserBooleano.cpp"
void ParserBooleano::_initialize(void)
{
	initializeFactory();
}
ParserBooleano::ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
	_initialize();
}

ParserBooleano::ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,1)
{
	_initialize();
}

ParserBooleano::ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
	_initialize();
}

ParserBooleano::ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,1)
{
	_initialize();
}

ParserBooleano::ParserBooleano(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,1)
{
	_initialize();
}

void ParserBooleano::expr() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		expr_suma();
		astFactory->addASTChild( currentAST, returnAST );
		ANTLR_USE_NAMESPACE(antlr)RefAST tmp5_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
		tmp5_AST = astFactory->create(LT(1));
		astFactory->addASTChild(currentAST, tmp5_AST);
		match(ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE);
		expr_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		consume();
		consumeUntil(_tokenSet_0);
	}
	returnAST = expr_AST;
}

void ParserBooleano::expr_suma() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_suma_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		expr_xor();
		astFactory->addASTChild( currentAST, returnAST );
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == SUMA)) {
				ANTLR_USE_NAMESPACE(antlr)RefAST tmp6_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
				tmp6_AST = astFactory->create(LT(1));
				astFactory->makeASTRoot(currentAST, tmp6_AST);
				match(SUMA);
				expr_xor();
				astFactory->addASTChild( currentAST, returnAST );
			}
			else {
				goto _loop4;
			}
			
		}
		_loop4:;
		} // ( ... )*
		expr_suma_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		consume();
		consumeUntil(_tokenSet_1);
	}
	returnAST = expr_suma_AST;
}

void ParserBooleano::expr_xor() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_xor_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		expr_prod();
		astFactory->addASTChild( currentAST, returnAST );
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == XOR)) {
				ANTLR_USE_NAMESPACE(antlr)RefAST tmp7_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
				tmp7_AST = astFactory->create(LT(1));
				astFactory->makeASTRoot(currentAST, tmp7_AST);
				match(XOR);
				expr_prod();
				astFactory->addASTChild( currentAST, returnAST );
			}
			else {
				goto _loop7;
			}
			
		}
		_loop7:;
		} // ( ... )*
		expr_xor_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		consume();
		consumeUntil(_tokenSet_2);
	}
	returnAST = expr_xor_AST;
}

void ParserBooleano::expr_prod() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST expr_prod_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		atom();
		astFactory->addASTChild( currentAST, returnAST );
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == PROD)) {
				ANTLR_USE_NAMESPACE(antlr)RefAST tmp8_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
				tmp8_AST = astFactory->create(LT(1));
				astFactory->makeASTRoot(currentAST, tmp8_AST);
				match(PROD);
				atom();
				astFactory->addASTChild( currentAST, returnAST );
			}
			else {
				goto _loop10;
			}
			
		}
		_loop10:;
		} // ( ... )*
		expr_prod_AST = currentAST.root;
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		consume();
		consumeUntil(_tokenSet_3);
	}
	returnAST = expr_prod_AST;
}

void ParserBooleano::atom() {
	returnAST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	ANTLR_USE_NAMESPACE(antlr)RefAST atom_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
	
	try {      // for error handling
		switch ( LA(1)) {
		case VAR:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp9_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp9_AST = astFactory->create(LT(1));
			astFactory->addASTChild(currentAST, tmp9_AST);
			match(VAR);
			atom_AST = currentAST.root;
			break;
		}
		case PARENIZQ:
		{
			{
			match(PARENIZQ);
			expr_suma();
			astFactory->addASTChild( currentAST, returnAST );
			match(PARENDER);
			}
			atom_AST = currentAST.root;
			break;
		}
		case NEG:
		{
			ANTLR_USE_NAMESPACE(antlr)RefAST tmp12_AST = ANTLR_USE_NAMESPACE(antlr)nullAST;
			tmp12_AST = astFactory->create(LT(1));
			astFactory->makeASTRoot(currentAST, tmp12_AST);
			match(NEG);
			atom();
			astFactory->addASTChild( currentAST, returnAST );
			atom_AST = currentAST.root;
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		consume();
		consumeUntil(_tokenSet_4);
	}
	returnAST = atom_AST;
}

void ParserBooleano::initializeFactory( void )
{
	if( ! astFactory )
		astFactory = new ANTLR_USE_NAMESPACE(antlr)ASTFactory();
	astFactory->setMaxNodeType(12);
}
const char* ParserBooleano::tokenNames[] = {
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

const unsigned long ParserBooleano::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet ParserBooleano::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long ParserBooleano::_tokenSet_1_data_[] = { 514UL, 0UL, 0UL, 0UL };
// EOF PARENDER 
const ANTLR_USE_NAMESPACE(antlr)BitSet ParserBooleano::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long ParserBooleano::_tokenSet_2_data_[] = { 530UL, 0UL, 0UL, 0UL };
// EOF SUMA PARENDER 
const ANTLR_USE_NAMESPACE(antlr)BitSet ParserBooleano::_tokenSet_2(_tokenSet_2_data_,4);
const unsigned long ParserBooleano::_tokenSet_3_data_[] = { 562UL, 0UL, 0UL, 0UL };
// EOF SUMA XOR PARENDER 
const ANTLR_USE_NAMESPACE(antlr)BitSet ParserBooleano::_tokenSet_3(_tokenSet_3_data_,4);
const unsigned long ParserBooleano::_tokenSet_4_data_[] = { 626UL, 0UL, 0UL, 0UL };
// EOF SUMA XOR PROD PARENDER 
const ANTLR_USE_NAMESPACE(antlr)BitSet ParserBooleano::_tokenSet_4(_tokenSet_4_data_,4);


