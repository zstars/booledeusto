#ifndef INC_TokenStreamIOException_hpp__
#define INC_TokenStreamIOException_hpp__

#include <antlr/config.hpp>
#include <antlr/TokenStreamException.hpp>
#include <exception>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class TokenStreamIOException : public TokenStreamException {
public:
	ANTLR_USE_NAMESPACE(std)exception io;

	TokenStreamIOException() {}
	TokenStreamIOException(const ANTLR_USE_NAMESPACE(std)exception& e)
		: TokenStreamException(e.what()), io(e) {}
	~TokenStreamIOException() throw() {}
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_TokenStreamIOException_hpp__
