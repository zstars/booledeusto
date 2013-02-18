#ifndef INC_RecognitionException_hpp__
# define INC_RecognitionException_hpp__

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
 * @version ANTLR 2.7.1 MageLang Insitute
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 * @author <br><a href="mailto:pete@yamuna.demon.co.uk">Pete Wells</a>
 * @author <br><a href="mailto:svincent@svincent.com">Shawn P. Vincent</a>
 */

# include <antlr/config.hpp>
# include <antlr/ANTLRException.hpp>

# ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr
{
# endif
	class ANTLR_API RecognitionException : public ANTLRException
	{
	public:
		RecognitionException();
		RecognitionException(const ANTLR_USE_NAMESPACE(std)string& s);
		RecognitionException(const ANTLR_USE_NAMESPACE(std)string& s,
									const ANTLR_USE_NAMESPACE(std)string& fileName_,
									int line_,int column_);

		virtual ~RecognitionException() throw()
		{
		}

		/// Return file where mishap occurred.
		virtual ANTLR_USE_NAMESPACE(std)string getFilename() const
		{
			return fileName;
		}
		/**
		 * @return the line number that this exception happened on.
		 */
		virtual int getLine() const
		{
			return line;
		}
		/**
		 * @return the column number that this exception happened on.
		 */
		virtual int getColumn() const
		{
			return column;
		}
#if 0
		/**
		 * @deprecated As of ANTLR 2.7.0
		 */
		virtual ANTLR_USE_NAMESPACE(std)string getErrorMessage() const
		{
			return getMessage();
		}
#endif

		/// Return complete error message with line/column number info (if present)
		virtual ANTLR_USE_NAMESPACE(std)string toString() const;

		/// See what file/line/column info is present and return it as a string
		virtual ANTLR_USE_NAMESPACE(std)string getFileLineColumnString() const;
	protected:
		ANTLR_USE_NAMESPACE(std)string fileName; // not used by treeparsers
		int line;    // not used by treeparsers
		int column;  // not used by treeparsers
	};

# ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
# endif

#endif //INC_RecognitionException_hpp__
