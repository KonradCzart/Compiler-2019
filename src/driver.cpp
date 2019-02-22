#include <cctype>
#include <fstream>
#include <cassert>

#include "driver.hpp"

Compiler::CompilerDriver::~CompilerDriver(){
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void Compiler::CompilerDriver::parse( const char * const filename ){
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ){
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   return;
}

void Compiler::CompilerDriver::parse( std::istream &stream ){
   if( ! stream.good()  && stream.eof() ){
       return;
   }
   parse_helper( stream );
   return;
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
   return;
}


std::ostream& Compiler::CompilerDriver::print( std::ostream &stream ){
   stream << "Results: " << "\n";
   return(stream);
}