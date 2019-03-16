#include <cctype>
#include <fstream>
#include <cassert>
#include <sstream>

#include "driver.hpp"

Compiler::CompilerDriver::CompilerDriver(){
   assemblerMenager = new AssemblerMenager();       
}

Compiler::CompilerDriver::~CompilerDriver(){
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
   delete(assemblerMenager);
   assemblerMenager = nullptr;
   memory = nullptr;
}

void Compiler::CompilerDriver::parse( const char * const filename ){
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ){
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
}

void Compiler::CompilerDriver::parse( std::istream &stream ){
   if( ! stream.good()  && stream.eof() ){
       return;
   }
   parse_helper( stream );
}


void Compiler::CompilerDriver::parse_helper( std::istream &stream ){
   delete(scanner);
   try{
      scanner = new Compiler::Scanner( &stream );
   }
   catch( std::bad_alloc &ba ){
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   delete(parser);
   try{
      parser = new Compiler::Parser( (*scanner), (*this));
   }
   catch( std::bad_alloc &ba ){
      std::cerr << "Failed to allocate parser: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept ){
      std::cerr << "Parse failed!!\n";
   }
}


std::ostream& Compiler::CompilerDriver::print( std::ostream &stream ){
   assemblerMenager->printCompiledCode(stream);
   return(stream);
}

bool Compiler::CompilerDriver::isFinishReadFile(){
   return finishReadFile;
}

void Compiler::CompilerDriver::compaile(){
   assemblerMenager->compileAll();
}

void Compiler::CompilerDriver::declare(std::string identifier){
   if(memory->isAlreadyDeclared(identifier)){
      std::stringstream message;
      message << "Identifier " << identifier << " already exists.";
      parser->error(*(scanner->location), message.str()); 
   }
   else {
      memory->declare(identifier);
   }
}

void Compiler::CompilerDriver::declareArray(std::string identifier, long long firstIndex, long long lastIndex){
   if(memory->isAlreadyDeclared(identifier)){
      std::stringstream message;
      message << "Identifier " << identifier << " already exists.";
      parser->error(*(scanner->location), message.str());
   }
   else {
      memory->declareArray(identifier, firstIndex, lastIndex);
   }
}

VariablePointer Compiler::CompilerDriver::getDeclaredVariable(std::string identifier){
   std::stringstream errorMessage;
   bool error = false;
   VariablePointer result = std::make_shared<TmpVariable>("ERROR");

   if(memory->iteratorOnStack("ITER_" + identifier)){
      identifier = "ITER_" + identifier;
      result = std::make_shared<SimpleVariable>(identifier); 
   }
   else if(!memory->isAlreadyDeclared(identifier)){
      error = true;
      errorMessage << "Variable " << identifier << " was not declared.";
   }
   else if(memory->isArraySymbol(identifier)){
      error = true;
      errorMessage << "Incorrect use - variable " << identifier << " is array.";
   }
   else{
      result = std::make_shared<SimpleVariable>(identifier); 
   }

   if(error){
      parser->error(*(scanner->location), errorMessage.str());
   }
   return result;
}

VariablePointer Compiler::CompilerDriver::getDeclaredArray(std::string identifier, long long index){
   VariablePointer result = std::make_shared<TmpVariable>("ERROR");

   if(isCorrectDeclaredArray(identifier)){
      result = std::make_shared<ConstArrayVariable>(identifier, index); 
   }
   return result;  
}

VariablePointer Compiler::CompilerDriver::getDeclaredArray(std::string identifier, VariablePointer variableIndex){
   VariablePointer result = std::make_shared<TmpVariable>("ERROR");

   if(isCorrectDeclaredArray(identifier)){
      result = std::make_shared<IdentifierArrayVariable>(identifier, variableIndex); 
   }
   return result;  
}

VariablePointer Compiler::CompilerDriver::getIterator(std::string identifier){
   std::string iterator = "ITER_" + identifier;
   return std::make_shared<SimpleVariable>(iterator);  
}

VariablePointer Compiler::CompilerDriver::getCounter(std::string identifier){
   std::string counter = "COUNTER_" + identifier;
   return std::make_shared<SimpleVariable>(counter);
}

bool Compiler::CompilerDriver::isCorrectDeclaredArray(std::string identifier){
   bool correctArray = false;
   std::stringstream errorMessage;
   
   if(memory->isArraySymbol(identifier)){
      correctArray = true;
   }
   else if(memory->isAlreadyDeclared(identifier)) {
      errorMessage << "Incorrect use - variable " << identifier << " is not array.";
   }
   else {
      errorMessage << "Variable " << identifier << " was not declared.";
   }

   if(!correctArray){
      parser->error(*(scanner->location), errorMessage.str());
   }

   return correctArray;
}

void Compiler::CompilerDriver::initialize(VariablePointer variable){
   std::string identifier = variable->getIdentifier();
   if(memory->isAlreadyDeclared(identifier)){
      memory->initialize(identifier);
   }
}

void Compiler::CompilerDriver::checkInitialized(VariablePointer variable){
   std::string identifier = variable->getIdentifier();
   if(memory->isAlreadyDeclared(identifier)){
      if(!memory->isInitialized(identifier)){
         std::stringstream message;
         message << "Variable " << identifier << " was not initialized";
         parser->error(*(scanner->location), message.str());
      }
   }
}

void Compiler::CompilerDriver::checkModificationIterator(VariablePointer iterator){
   std::string identifier = iterator->getIdentifier();

   if(memory->iteratorOnStack(identifier)){
      std::stringstream message;
      message << "Iterator " << identifier << " can not be modified.";
      parser->error(*(scanner->location), message.str());
   }
}

void Compiler::CompilerDriver::validateAndPushIterator(std::string identifier){
   std::string iterator = "ITER_" + identifier;
   std::stringstream message;
   if(memory->isAlreadyDeclared(identifier)){
      message << "Identifier " << identifier << " already exists.";
      parser->error(*(scanner->location), message.str());
   }
   else if(memory->iteratorOnStack(iterator)){
      message << "Identifier " << identifier << " is already used as an iterator.";
      parser->error(*(scanner->location), message.str());
   }

   if(!memory->isAlreadyDeclared(iterator)){
      std::string counter = "COUNTER_" + identifier;
      declare(iterator);
      memory->initialize(iterator);
      declare(counter);
   }
   memory->pushIterator(iterator);
}