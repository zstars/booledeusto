#ifndef INC_MismatchedTokenException_hpp__
#define INC_MismatchedTokenException_hpp__

/*
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.7.1 MageLang Insitute, 1999, 2000, 2001
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commerical software.
 * <p>
 * We encourage users to develop software with ANTLR. However,
 * we do ask that credit is given to us for developing
 * ANTLR. By "credit", we mean that if you use ANTLR or
 * incorporate any source code into one of your programs
 * (commercial product, research project, or otherwise) that
 * you acknowledge this fact somewhere in the documentation,
 * research report, etc... If you like ANTLR and have
 * developed a nice tool with the output, please mention that
 * you developed it using ANTLR. In addition, we ask that the
 * headers remain intact in our source code. As long as these
 * guidelines are kept, we expect to continue enhancing this
 * system and expect to make other tools available as they are
 * completed.
 * <p>
 * The ANTLR gang:
 * @version ANTLR 2.7.1 MageLang Insitute, 1999, 2000, 2001
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 * @author <br><a href="mailto:pete@yamuna.demon.co.uk">Pete Wells</a>
 */

#include <antlr/config.hpp>
#include <antlr/RecognitionException.hpp>
#include <antlr/BitSet.hpp>
#include <antlr/Token.hpp>
#include <antlr/AST.hpp>
#include <vector>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class ANTLR_API MismatchedTokenException : public RecognitionException {
public:
	MismatchedTokenException();

	/// Expected range / not range
	MismatchedTokenException(
		const char* const* tokenNames_,
		const int numTokens_,
		RefAST node_,
		int lower,
		int upper_,
		bool matchNot
	);

	// Expected token / not token
	MismatchedTokenException(
		const char* const* tokenNames_,
		const int numTokens_,
		RefAST node_,
		int expecting_,
		bool matchNot
	);

	// Expected BitSet / not BitSet
	MismatchedTokenException(
		const char* const* tokenNames_,
		const int numTokens_,
		RefAST node_,
		BitSet set_,
		bool matchNot
	);

	// Expected range / not range
	MismatchedTokenException(
		const char* const* tokenNames_,
		const int numTokens_,
		RefToken token_,
		int lower,
		int upper_,
		bool matchNot,
		const ANTLR_USE_NAMESPACE(std)string& fileName_
	);

	// Expected token / not token
	MismatchedTokenException(
		const char* const* tokenNames_,
		const int numTokens_,
		RefToken token_,
		int expecting_,
		bool matchNot,
		const ANTLR_USE_NAMESPACE(std)string& fileName_
	);

	// Expected BitSet / not BitSet
	MismatchedTokenException(
		const char* const* tokenNames_,
		const int numTokens_,
		RefToken token_,
		BitSet set_,
		bool matchNot,
		const ANTLR_USE_NAMESPACE(std)string& fileName_
	);
	~MismatchedTokenException() throw() {}

	/**
	 * Returns a clean error message (no line number/column information)
	 */
	ANTLR_USE_NAMESPACE(std)string getMessage() const;

public:
	/// The token that was encountered
	const RefToken token;
	/// The offending AST node if tree walking
	const RefAST node;
	/// taken from node or token object
	ANTLR_USE_NAMESPACE(std)string tokenText;

	/// Types of tokens
#ifndef NO_STATIC_CONSTS
	static const int TOKEN = 1;
	static const int NOT_TOKEN = 2;
	static const int RANGE = 3;
	static const int NOT_RANGE = 4;
	static const int SET = 5;
	static const int NOT_SET = 6;
#else
	enum {
		TOKEN = 1,
		NOT_TOKEN = 2,
		RANGE = 3,
		NOT_RANGE = 4,
		SET = 5,
		NOT_SET = 6
	};
#endif

public:
	/// One of the above
	int mismatchType;

	/// For TOKEN/NOT_TOKEN and RANGE/NOT_RANGE
	int expecting;

	/// For RANGE/NOT_RANGE (expecting is lower bound of range)
	int upper;

	/// For SET/NOT_SET
	BitSet set;

private:
	/// Token names array for formatting
	const char* const* tokenNames;
	/// Max number of tokens in tokenNames
	const int numTokens;
	/// Return token name for tokenType
	ANTLR_USE_NAMESPACE(std)string tokenName(int tokenType) const;
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_MismatchedTokenException_hpp__
