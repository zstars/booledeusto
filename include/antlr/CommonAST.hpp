#ifndef INC_CommonAST_hpp__
#define INC_CommonAST_hpp__

/*
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.7.1 MageLang Insitute, 1999, 2000, 2001
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commercial software.
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
#include <antlr/BaseAST.hpp>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

class ANTLR_API CommonAST : public BaseAST {
public:
	CommonAST();
	CommonAST( RefToken t );
	CommonAST( const CommonAST& other );

	virtual ~CommonAST();

	virtual const char* typeName( void ) const;
	/// Clone this AST node.
	virtual RefAST clone( void ) const;

	virtual ANTLR_USE_NAMESPACE(std)string getText() const;
	virtual int getType() const;

	virtual void initialize( int t, const ANTLR_USE_NAMESPACE(std)string& txt );
	virtual void initialize( RefAST t );
	virtual void initialize( RefToken t );
#ifdef ANTLR_SUPPORT_XML
	virtual void initialize( ANTLR_USE_NAMESPACE(std)istream& in );
#endif

	virtual void setText( const ANTLR_USE_NAMESPACE(std)string& txt );
	virtual void setType( int type );

	static RefAST factory();

protected:
	int ttype;
	ANTLR_USE_NAMESPACE(std)string text;
};

typedef ASTRefCount<CommonAST> RefCommonAST;

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_CommonAST_hpp__
