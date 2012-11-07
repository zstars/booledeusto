//---------------------------------------------------------------------------

#ifndef ParserBooleanoExtH
#define ParserBooleanoExtH

#include "ParserBooleano.hpp"

class ParserBooleanoExt: public ParserBooleano
{
        public:
        ParserBooleanoExt(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer):ParserBooleano(lexer)
        {
        }

	void inline reportError(const ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex)
        {
                throw(ex);
        }

	void inline reportError(const ANTLR_USE_NAMESPACE(std)string& s)
        {
                throw(new ANTLR_USE_NAMESPACE(antlr)RecognitionException(s));
        };

};

//---------------------------------------------------------------------------
#endif
