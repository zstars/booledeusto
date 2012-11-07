#ifndef INC_LexerBooleano_hpp_
#define INC_LexerBooleano_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.2a2 (20020112-1): "bool.g" -> "LexerBooleano.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "ParserBooleanoTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#line 1 "bool.g"

#include "TablaSimbolos.h"

#line 16 "LexerBooleano.hpp"
class LexerBooleano : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public ParserBooleanoTokenTypes
{
#line 40 "bool.g"

private:
	TablaSimbolos *ts;

public:	
	void SetTablaSimbolos(TablaSimbolos *ts)
	{
		this->ts = ts;
	}
#line 20 "LexerBooleano.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const;
public:
	LexerBooleano(ANTLR_USE_NAMESPACE(std)istream& in);
	LexerBooleano(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	LexerBooleano(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mBLANCO(bool _createToken);
	public: void mPARENIZQ(bool _createToken);
	public: void mPARENDER(bool _createToken);
	public: void mPROD(bool _createToken);
	public: void mXOR(bool _createToken);
	public: void mSUMA(bool _createToken);
	public: void mNEG(bool _createToken);
	public: void mSEMI(bool _createToken);
	public: void mVAR(bool _createToken);
private:
	
};

#endif /*INC_LexerBooleano_hpp_*/
