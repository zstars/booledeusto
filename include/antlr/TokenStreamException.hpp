#ifndef INC_TokenStreamException_hpp__
#define INC_TokenStreamException_hpp__

#include <antlr/config.hpp>
#include <antlr/ANTLRException.hpp>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class ANTLR_API TokenStreamException : public ANTLRException {
public:
	TokenStreamException() {}
	TokenStreamException(const ANTLR_USE_NAMESPACE(std)string& s)
		: ANTLRException(s) {}
	virtual ~TokenStreamException() throw() {}
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_TokenStreamException_hpp__
