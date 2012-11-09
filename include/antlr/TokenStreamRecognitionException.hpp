#ifndef INC_TokenStreamRecognitionException_hpp__
#define INC_TokenStreamRecognitionException_hpp__

#include <antlr/config.hpp>
#include <antlr/TokenStreamException.hpp>
#include <exception>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class TokenStreamRecognitionException : public TokenStreamException {
public:
	RecognitionException recog;

	TokenStreamRecognitionException(RecognitionException& re)
		: TokenStreamException(re.getMessage()), recog(re) {}
	~TokenStreamRecognitionException() throw() {}

  ANTLR_USE_NAMESPACE(std)string toString() const { return recog.getFileLineColumnString()+getMessage(); }
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_TokenStreamRecognitionException_hpp__
