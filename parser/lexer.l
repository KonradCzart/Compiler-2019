%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */
#include "scanner.hpp"
#undef  YY_DECL
#define YY_DECL int Compiler::Scanner::yylex( Compiler::Parser::semantic_type * const lval, Compiler::Parser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = Compiler::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::ENDSCANN )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="Compiler::Scanner"
%option noyywrap
%option c++
%x COMMENT
%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}
"[" { BEGIN(COMMENT); }
[0-9]+ 	    { yylval->build< std::string >( yytext ); return(token::NUM);}
[_a-z]+     { yylval->build< std::string >( yytext ); return(token::PIDENTIFIER); }

"DECLARE"   { return(token::DECLARE); }
"IN"        { return(token::IN); }
"END"       { return(token::END); }

"IF"        { return(token::IF); }
"THEN"      { return(token::THEN); }
"ELSE"      { return(token::ELSE); }
"ENDIF"     { return(token::ENDIF);}

"WHILE"     { return(token::WHILE); }
"DO"        { return(token::DO); }
"ENDWHILE"  { return(token::ENDWHILE); }
"ENDDO"     { return(token::ENDDO); }

"FOR"       { return(token::FOR); }
"FROM"      { return(token::FROM); }
"TO"        { return(token::TO); }
"DOWNTO"    { return(token::DOWNTO); }
"ENDFOR"    { return(token::ENDFOR); }

"READ"      { return(token::READ); }
"WRITE"     { return(token::WRITE); }

"("         { return(token::LBR); }
")"         { return(token::RBR); }

"+"	        { return(token::ADD); }
"-"	        { return(token::SUB); }
"*"	        { return(token::MUL); }
"/"	        { return(token::DIV); }
"%"	        { return(token::MOD); }
":="        { return(token::ASSIGN); }

"="         { return(token::EQUAL); }
"!="        { return(token::NEQUAL); }
"<"         { return(token::LESS); }
">"         { return(token::GREAT); }
"<="        { return(token::LESSEQ); }
">="        { return(token::GREATEQ); }

";"         { return(token::SEMICOLON); }
":"         { return(token::COLON); }
\n          { loc->lines(yyleng);}
[ \n\t\r]   {}
.	          { return(token::ERROR); }

<COMMENT>"]"      { BEGIN(INITIAL); }
<COMMENT>\n       {}
<COMMENT>.        {}
<COMMENT><<EOF>>  { return(token::ERROR); }

<<EOF>>           { yyterminate(); }


%%