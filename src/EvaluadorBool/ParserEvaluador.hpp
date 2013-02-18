#ifndef INC_ParserEvaluador_hpp_
#define INC_ParserEvaluador_hpp_

#include <antlr/config.hpp>
#include "ParserBooleanoTokenTypes.hpp"
/* $ANTLR 2.7.2a2 (20020112-1): "bool.g" -> "ParserEvaluador.hpp"$ */
#include <antlr/TreeParser.hpp>

#line 1 "bool.g"

#include "TablaSimbolos.h"

#line 14 "ParserEvaluador.hpp"
class ParserEvaluador : public ANTLR_USE_NAMESPACE(antlr)TreeParser, public ParserBooleanoTokenTypes
{
#line 87 "bool.g"

private:
	TablaSimbolos *ts;

public:	
	void SetTablaSimbolos(TablaSimbolos *ts)
	{
		this->ts = ts;
	}
#line 18 "ParserEvaluador.hpp"
public:
	ParserEvaluador();
	int getNumTokens() const
	{
		return ParserEvaluador::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return ParserEvaluador::tokenNames[type];
	}
	public: bool  expr(ANTLR_USE_NAMESPACE(antlr)RefAST _t);
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 13;
#else
	enum {
		NUM_TOKENS = 13
	};
#endif
	
};

#endif /*INC_ParserEvaluador_hpp_*/
