#ifndef INC_CharStreamIOException_hpp__
#define INC_CharStreamIOException_hpp__

#include <antlr/config.hpp>
#include <antlr/CharStreamException.hpp>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class ANTLR_API CharStreamIOException : public CharStreamException {
public:
	ANTLR_USE_NAMESPACE(std)exception io;

	CharStreamIOException(ANTLR_USE_NAMESPACE(std)exception& e)
		: CharStreamException(e.what()), io(e) {}
	~CharStreamIOException() throw() {}
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_CharStreamIOException_hpp__
