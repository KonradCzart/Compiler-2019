%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {Compiler}
%define parser_class_name {Parser}

%code requires{
   namespace Compiler {
      class CompilerDriver;
      class Scanner;
   }
}

%parse-param { Scanner  &scanner  }
%parse-param { CompilerDriver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   #include "driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token <std::string>  NUM
%token <std::string>  PIDENTIFIER

%token      ERROR

%token      SEMICOLON COLON LBR RBR ASSIGN
%token      EQUAL NEQUAL LESS GREAT LESSEQ GREATEQ

%token      DECLARE IN IF THEN ELSE ENDIF WHILE DO ENDWHILE ENDDO FOR FROM TO ENDFOR DOWNTO READ WRITE END
%token      ENDSCANN      0     "end of file"

%left       ADD SUB
%left       MUL DIV MOD


%locations
%start start

%%

start
   : /*empty*/
   | DECLARE declarations IN commands END { std::cout<<"dasdasda";}
   ;

declarations
   : /*empty*/
   | declarations PIDENTIFIER SEMICOLON
   | declarations PIDENTIFIER LBR NUM COLON NUM RBR SEMICOLON
   ;

commands
   : commands command
   | command
   ;

command
   : identifier ASSIGN expression SEMICOLON
   | IF condition THEN commands ELSE commands ENDIF
   | IF condition THEN commands ENDIF
   | WHILE condition DO commands ENDWHILE
   | DO commands WHILE condition ENDDO
   | FOR PIDENTIFIER FROM value TO value DO commands ENDFOR
   | FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR
   | READ identifier SEMICOLON
   | WRITE value SEMICOLON
   ;

expression
   : value {  }
   | value ADD value {  }
   | value SUB value {  }
   | value MUL value {  }
   | value DIV value {  }
   | value MOD value {  }
   ;

condition
   : value EQUAL value  {  }
   | value NEQUAL value {  }
   | value LESS value   {  }
   | value GREAT value  {  }
   | value LESSEQ value  {  }
   | value GREATEQ value {  }
   ;

value
   : NUM { std::cout << $1;  }
   | identifier {  }
   ;

identifier
   : PIDENTIFIER {  }
   | PIDENTIFIER LBR PIDENTIFIER RBR  {  }
   | PIDENTIFIER LBR NUM RBR {  }
   ;

%%
void
Compiler::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}