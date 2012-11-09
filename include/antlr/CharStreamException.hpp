#ifndef INC_CharStreamException_hpp__
#define INC_CharStreamException_hpp__

#include <antlr/config.hpp>
#include <antlr/ANTLRException.hpp>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class ANTLR_API CharStreamException : public ANTLRException {
public:
	CharStreamException(const ANTLR_USE_NAMESPACE(std)string& s)
		: ANTLRException(s) {}
	~CharStreamException() throw() {}
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_CharStreamException_hpp__
