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
   #include "Command.hpp"
   #include "CommandStrategy.hpp" 
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
   #include "Command.hpp"
   #include "CommandStrategy.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%type <VariablePointer> identifier
%type <VariablePointer> value
%type <Expression> expression
%type <Condition> condition
%type <CommandBlock> command
%type <CommandBlock> commands
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
   | DECLARE declarations IN commands END { std::cout<<"dasdasda" << std::endl; $4.print(); }
   ;

declarations
   : /*empty*/
   | declarations PIDENTIFIER SEMICOLON
   | declarations PIDENTIFIER LBR NUM COLON NUM RBR SEMICOLON
   ;

commands
   : commands command { 
         $1.append($2);
         $$ = $1;
      }
   | command { 
         $$ = $1; 
      }
   ;

command
   : identifier ASSIGN expression SEMICOLON {
         $$ = CommandBlock(Command($3.createCommand($1)));
      }
   | IF condition THEN commands ELSE commands ENDIF {
         $$ = driver.commandMenager.getCommandIfElse($2, $4, $6);
      }
   | IF condition THEN commands ENDIF {
         $$ = driver.commandMenager.getCommandIf($2,$4);
      }
   | WHILE condition DO commands ENDWHILE {
         $$ = driver.commandMenager.getCommandWhileDo($2,$4);
      }
   | DO commands WHILE condition ENDDO {
         $$ = driver.commandMenager.getCommandDoWhile($4,$2);
      }
   | FOR PIDENTIFIER FROM value TO value DO commands ENDFOR {

      }
   | FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR {

      }
   | READ identifier SEMICOLON {
         $$ = CommandBlock(Command(IOCommandStrategy::create(IOCommandStrategy::Type::READ, $2)));
      }
   | WRITE value SEMICOLON {
         $$ = CommandBlock(Command(IOCommandStrategy::create(IOCommandStrategy::Type::WRITE, $2)));
      }
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