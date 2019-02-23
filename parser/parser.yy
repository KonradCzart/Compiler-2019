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

   #include "Variable.hpp"
   #include "MemoryTable.hpp"
   #include "Expression.hpp"
   #include "Condition.hpp"
}

%parse-param { Scanner  &scanner  }
%parse-param { CompilerDriver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <memory>

   #include "driver.hpp"
   #include "Variable.hpp"
   #include "MemoryTable.hpp"
   #include "Expression.hpp"
   #include "Condition.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%type <VariablePointer> identifier
%type <VariablePointer> value
%type <Expression> expression
%type <Condition> condition
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
   : identifier ASSIGN expression SEMICOLON {
         $3.print();
      }
   | IF condition THEN commands ELSE commands ENDIF {

      }
   | IF condition THEN commands ENDIF{
         $2.print();
      }
   | WHILE condition DO commands ENDWHILE{

      }
   | DO commands WHILE condition ENDDO
   | FOR PIDENTIFIER FROM value TO value DO commands ENDFOR
   | FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR
   | READ identifier SEMICOLON
   | WRITE value SEMICOLON
   ;

expression
   : value { $$ = Expression(Expression::Type::EMPTY, $1, $1); }
   | value ADD value { $$ = Expression(Expression::Type::ADDITION, $1, $3);}
   | value SUB value { $$ = Expression(Expression::Type::SUBTRACTION, $1, $3); }
   | value MUL value { $$ = Expression(Expression::Type::MULTIPLICATION, $1, $3); }
   | value DIV value { $$ = Expression(Expression::Type::DIVISION, $1, $3); }
   | value MOD value { $$ = Expression(Expression::Type::MODULO, $1, $3); }
   ;

condition
   : value EQUAL value  { $$ = Condition(Condition::Type::EQUAL, $1, $3); }
   | value NEQUAL value { $$ = Condition(Condition::Type::NOT_EQUAL, $1, $3); }
   | value LESS value   { $$ = Condition(Condition::Type::LESSER, $1, $3); }
   | value GREAT value  { $$ = Condition(Condition::Type::GREATER, $1, $3); }
   | value LESSEQ value  { $$ = Condition(Condition::Type::LESSER_EQUAL, $1, $3); }
   | value GREATEQ value { $$ = Condition(Condition::Type::GREATER_EQUAL, $1, $3); }
   ;

value
   : NUM { 
         long long value = stoll($1);
         $$ = std::make_shared<ConstVariable>(value);
     }
   | identifier { $$ = $1; }
   ;

identifier
   : PIDENTIFIER { 
         $$ = std::make_shared<SimpleVariable>($1); 
      }
   | PIDENTIFIER LBR PIDENTIFIER RBR  {
         VariablePointer var = std::make_shared<SimpleVariable>($3); 
         $$ = std::make_shared<IdentifierArrayVariable>($1, var); 
      }
   | PIDENTIFIER LBR NUM RBR {  
         long long index = stoll($3);
         $$ = std::make_shared<ConstArrayVariable>($1, index); 
      }
   ;

%%
void
Compiler::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}