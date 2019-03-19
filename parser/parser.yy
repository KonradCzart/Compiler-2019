%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {Compiler}
%define parser_class_name {Parser}
%define parse.error verbose

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
   #include <sstream>

   bool errorFlag = false;

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
   | DECLARE declarations IN commands END { 
         if(errorFlag){
            return 1;
         }
         else {
            $4.addCommandToEnd(Command(CodeCommandStrategy::create(CodeCommandStrategy::HALT, "END_PROGRAM")));
            driver.assemblerMenager->setCommandBlock($4);  
            driver.finishReadFile = true;
         }
      }
   ;

declarations
   : /*empty*/
   | declarations PIDENTIFIER SEMICOLON {
         driver.declare($2);
      }
   | declarations PIDENTIFIER LBR NUM COLON NUM RBR SEMICOLON {
         long long firstIndex = stoll($4);
         long long lastIndex = stoll($6);
         driver.declareArray($2, firstIndex, lastIndex);
      }
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
         driver.checkModificationIterator($1);
         driver.initialize($1);
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
   | FOR PIDENTIFIER FROM value TO value  {
         driver.validateAndPushIterator($2);
      }
      DO commands ENDFOR { 
         VariablePointer iteratorVariable = driver.getIterator($2);
         VariablePointer counterVariable = driver.getCounter($2);

         driver.memory->popIterator();
         $$ = driver.commandMenager.getCommandFor(iteratorVariable, counterVariable, $4, $6, $9);   
      }
   | FOR PIDENTIFIER FROM value DOWNTO value {
         driver.validateAndPushIterator($2);
      }
      DO commands ENDFOR {
         VariablePointer iteratorVariable = driver.getIterator($2);
         VariablePointer counterVariable = driver.getCounter($2);

         driver.memory->popIterator();
         $$ = driver.commandMenager.getCommandForDown(iteratorVariable, counterVariable, $4, $6, $9);  
      }
   | READ identifier SEMICOLON {
         driver.checkModificationIterator($2);
         driver.initialize($2);
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
   | identifier { 
         driver.checkInitialized($1);
         $$ = $1; 
      }
   ;

identifier
   : PIDENTIFIER { 
         $$ = driver.getDeclaredVariable($1);
      }
   | PIDENTIFIER LBR PIDENTIFIER RBR  {
         VariablePointer indexArray = driver.getDeclaredVariable($3);
         $$ = driver.getDeclaredArray($1, indexArray);
      }
   | PIDENTIFIER LBR NUM RBR {  
         long long indexArray = stoll($3);
         $$ = driver.getDeclaredArray($1, indexArray);
      }
   ;

%%
void
Compiler::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
   errorFlag = true;
}
