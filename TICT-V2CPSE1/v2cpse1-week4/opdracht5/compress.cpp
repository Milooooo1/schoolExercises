#include <iostream>
#include <fstream>

#include "../07-library/compressor.hpp"
#include "../07-library/decompressor.hpp"

int main( void ){	
   lz_compressor< 4096 > compressor;
 
   std::ifstream f1;
   f1.open( "wilhelmus.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   std::ofstream f2;
   f2.open( "compressed.asm" );
   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }
   
   f2 << "\t\t.data\ntxt:\t.asciz \""; 

   compressor.compress( 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
      [ &f2 ]( char c ){ if(c == '\n'){ f2 << "\\n"; } else { f2.put( c ); } }
  );

   f2 << "\"\n\n\t\t.cpu cortex-m0\n\t\t.text\n\t\t.align 2\n\t\t.global txt\n";
   
   f1.close();
   f2.close();
}