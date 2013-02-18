#ifndef INC_ParserBooleano_hpp_
#define INC_ParserBooleano_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.2a2 (20020112-1): "bool.g" -> "ParserBooleano.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "ParserBooleanoTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 1 "bool.g"

#include "TablaSimbolos.h"

#line 16 "ParserBooleano.hpp"
class ParserBooleano : public ANTLR_USE_NAMESPACE(antlr)LLkParser, public ParserBooleanoTokenTypes
{
#line 1 "bool.g"
#line 20 "ParserBooleano.hpp"
public:
	void initializeFactory( void );
	// called from constructors
	void _initialize( void );
protected:
	ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k);
public:
	ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf);
protected:
	ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k);
public:
	ParserBooleano(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer);
	ParserBooleano(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state);
	int getNumTokens() const
	{
		return ParserBooleano::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return ParserBooleano::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return ParserBooleano::tokenNames;
	}
	public: void expr();
	public: void expr_suma();
	public: void expr_xor();
	public: void expr_prod();
	public: void atom();
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 13;
#else
	enum {
		NUM_TOKENS = 13
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_4;
};

#endif /*INC_ParserBooleano_hpp_*/
