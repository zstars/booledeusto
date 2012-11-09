#ifndef INC_ASTRefCount_hpp__
# define INC_ASTRefCount_hpp__

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

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

	class AST;

struct ANTLR_API ASTRef
{
	AST* const ptr;
	unsigned int count;

	ASTRef(AST* p);
	~ASTRef();
	ASTRef* increment();
	bool decrement();

	static ASTRef* getRef(const AST* p);
private:
	ASTRef( const ASTRef& );
	ASTRef& operator=( const ASTRef& );
};

template<class T>
	class ANTLR_API ASTRefCount
{
private:
	ASTRef* ref;

public:
	ASTRefCount(const AST* p=0)
		: ref(p ? ASTRef::getRef(p) : 0)
	{
	}
	ASTRefCount(const ASTRefCount<T>& other)
		: ref(other.ref ? other.ref->increment() : 0)
	{
	}
	~ASTRefCount()
	{
		if (ref && ref->decrement()) delete ref;
	}
	ASTRefCount<T>& operator=(AST* other)
	{
		ASTRef* tmp=ASTRef::getRef(other);
		if (ref && ref->decrement()) delete ref;
		ref=tmp;
		return *this;
	}
	ASTRefCount<T>& operator=(const ASTRefCount<T>& other)
	{
		ASTRef* tmp=other.ref ? other.ref->increment() : 0;
		if (ref && ref->decrement()) delete ref;
		ref=tmp;
		return *this;
	}

	operator T* () const
		{ return ref ? static_cast<T*>(ref->ptr) : 0; }
	T* operator->() const
		{ return ref ? static_cast<T*>(ref->ptr) : 0; }
	T* get() const
		{ return ref ? static_cast<T*>(ref->ptr) : 0; }
};

#if defined(_MSC_VER) && !defined(__ICL) // Microsoft Visual C++
extern template class ANTLR_API ASTRefCount<AST>;
#endif

typedef ASTRefCount<AST> RefAST;

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_ASTRefCount_hpp__
