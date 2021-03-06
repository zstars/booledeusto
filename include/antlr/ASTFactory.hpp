#ifndef INC_ASTFactory_hpp__
#define INC_ASTFactory_hpp__

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
#include <antlr/AST.hpp>
#include <antlr/ASTArray.hpp>
#include <antlr/ASTPair.hpp>

#include <utility>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

/** AST Support code shared by TreeParser and Parser.
 *  We use delegation to share code (and have only one
 *  bit of code to maintain) rather than subclassing
 *  or superclassing (forces AST support code to be
 *  loaded even when you don't want to do AST stuff).
 *
 *  Typically, setASTNodeType is used to specify the
 *  type of node to create, but you can override
 *  create to make heterogeneous nodes etc...
 *
 * @todo check all this code for possible use of references in
 * stead of RefAST's.
 */
class ANTLR_API ASTFactory {
public:
	typedef RefAST (*factory_type)();
	typedef ANTLR_USE_NAMESPACE(std)pair< const char*, factory_type > factory_descriptor;
	typedef ANTLR_USE_NAMESPACE(std)vector< factory_descriptor* > factory_descriptor_list;
protected:
	/* The mapping of AST node type to factory..
	 */
	factory_descriptor default_factory_descriptor;
	factory_descriptor_list nodeFactories;
public:
	/// Make new factory
	ASTFactory();
	/** Initialize factory with a non default node type.
	 * factory_node_name should be the name of the AST node type the factory
	 * generates. (should exist during the existance of this ASTFactory
	 * instance)
	 */
	ASTFactory( const char* factory_node_name, factory_type factory );
	/// Destroy factory
	virtual ~ASTFactory();

	/// Register a node factory for the node type type with name ast_name
	void registerFactory( int type, const char* ast_name, factory_type factory );
	/// Set the maximum node (AST) type this factory may encounter
	void setMaxNodeType( int type );

	/// Add a child to the current AST
	void addASTChild(ASTPair& currentAST, RefAST child);
	/// Create new empty AST node. The right default type shou
	virtual RefAST create();
	/// Create AST node of the right type for 'type'
	RefAST create(int type);
	/// Create AST node of the right type for 'type' and initialize with txt
	RefAST create(int type, const ANTLR_USE_NAMESPACE(std)string& txt);
	/// Create duplicatie of tr
	RefAST create(RefAST tr);
	/// Create new AST node and initialize contents from a token.
	RefAST create(RefToken tok);
	/// Create new AST node and initialize contents from a stream.
	RefAST create(const ANTLR_USE_NAMESPACE(std)string& txt, ANTLR_USE_NAMESPACE(std)istream& infile );
	/** Deep copy a single node. This function the new clone() methods in the
	 * AST interface. Returns a new RefAST(nullASTptr) if t is null.
	 */
	RefAST dup(RefAST t);
	/// Duplicate tree including siblings of root.
	RefAST dupList(RefAST t);
	/** Duplicate a tree, assuming this is a root node of a tree--
	 * duplicate that node and what's below; ignore siblings of root node.
	 */
	RefAST dupTree(RefAST t);
	/** Make a tree from a list of nodes. The first element in the
	 * array is the root. If the root is null, then the tree is
	 * a simple list not a tree. Handles null children nodes correctly.
	 * For example, make(a, b, null, c) yields tree (a b c).  make(null,a,b)
	 * yields tree (nil a b).
	 */
	RefAST make(ANTLR_USE_NAMESPACE(std)vector<RefAST>& nodes);
	/** Make a tree from a list of nodes, where the nodes are contained
	 * in an ASTArray object. The ASTArray is deleted after use.
	 * @todo FIXME! I have a feeling we can get rid of this ugly ASTArray thing
	 */
	RefAST make(ASTArray* nodes);
	/// Make an AST the root of current AST
	void makeASTRoot(ASTPair& currentAST, RefAST root);

	/** Set a new default AST type.
	 * factory_node_name should be the name of the AST node type the factory
	 * generates. (should exist during the existance of this ASTFactory
	 * instance).
	 * Only change factory between parser runs. You might get unexpected results
	 * otherwise.
	 */
	void setASTNodeFactory( const char* factory_node_name, factory_type factory );

	/** Load a XML AST from stream. Make sure you have all the factories
	 * registered before use.
	 */
	RefAST LoadAST( ANTLR_USE_NAMESPACE(std)istream& infile );
protected:
	void loadChildren( ANTLR_USE_NAMESPACE(std)istream& infile, RefAST current );
	void loadSiblings( ANTLR_USE_NAMESPACE(std)istream& infile, RefAST current );
	bool checkCloseTag( ANTLR_USE_NAMESPACE(std)istream& infile );

#ifdef ANTLR_VECTOR_HAS_AT
	inline RefAST getNodeOfType( unsigned int type )
	{
		return RefAST(nodeFactories.at(type)->second());
	}
#else
	inline RefAST getNodeOfType( unsigned int type )
	{
		return RefAST(nodeFactories[type]->second());
	}
#endif

private:
	// no copying and such..
	ASTFactory( const ASTFactory& );
	ASTFactory& operator=( const ASTFactory& );
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_ASTFactory_hpp__
