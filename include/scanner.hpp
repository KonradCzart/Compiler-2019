#ifndef __SCANNER__
#define __SCANNER__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

namespace Compiler{

class Scanner : public yyFlexLexer{
public:

   Scanner(std::istream *in) : yyFlexLexer(in)
   {
   };
   virtual ~Scanner() {
   };


   using FlexLexer::yylex;

   virtual
   int yylex( Compiler::Parser::semantic_type * const lval,
              Compiler::Parser::location_type *location );

   Compiler::Parser::location_type *location = nullptr;
private:
   Compiler::Parser::semantic_type *yylval = nullptr;
};

} 

#endif