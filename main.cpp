#include "Lexer.h"

int main() {
  
  Lexer lex( "test.txt" );

  do {
    lex.lex();   // Get next token

    int tok = lex.getNextToken();
    std::string text = lex.getLexeme();

    printf("Next token is: %d, Next lexeme is %s\n",tok,text.c_str());
  } while( lex.getNextToken() != EOF );

}
