#include <cstdlib>
#include "Lexer.h"
using std::string;

Lexer::Lexer( const string & fileName ): nextToken(EOF), charClass(UNKNOWN), nextChar(' ') {
  inputStream.open( fileName.c_str(), std::ifstream::in ); 
}

Lexer::~Lexer() {
  inputStream.close();
}

int Lexer::getNextToken() const {
  return nextToken;
}

string Lexer::getLexeme() const {
  return lexeme;
}

// lookup - a function to lookup operators and parentheses
//          and return the token
int Lexer::lookup(char ch)
{
  switch( ch )
  {
    case '(': 
      addChar(); 
      nextToken=LEFT_PAREN; 
      break;
    case ')': 
      addChar(); 
      nextToken=RIGHT_PAREN; 
      break;
    case '{':
      addChar();
      nextToken= LEFT_BRACE;
      break;
    case '}':
      addChar();
      nextToken= RIGHT_BRACE;
      break;
    case '+': 
      addChar(); 
      nextToken=ADD_OP; 
      break;
    case '-': 
      addChar(); 
      nextToken=SUB_OP; 
      break;
    case '*': 
      addChar(); 
      nextToken=MULT_OP; 
      break;
    case '/': 
      addChar(); 
      nextToken=DIV_OP; 
      break;
    case '=':
      addChar();
      nextToken = ASSIGN_OP;
      break;
    case ';':
      addChar();
      nextToken= SEMI_COLON;
      break;
    case ',':
      addChar();
      nextToken= COMMA;
      break;      
    case '\"':
      addChar();
      nextToken = QUOTE;
    default:  
      addChar(); 
      nextToken=EOF; 
      break;
  }
  return nextToken;
}

// addChar() - a function to add nextChar to lexeme
void Lexer::addChar()
{
  lexeme.push_back(nextChar);
}

// getChar() - a function to get the next character of
//             input and determine its character class
void Lexer::getChar()
{
  nextChar = inputStream.get();

  if( inputStream.good() ) {
    if( isalpha(nextChar)) charClass=LETTER;
    else if( isdigit(nextChar) ) charClass=DIGIT;
    else if(nextChar == '"') charClass = STRING;
    else if(nextChar == '.') charClass = FLOAT;
    else charClass=UNKNOWN; 
  } else {
    charClass = EOF;
  }
}

// getNonBlank - a function to call getChar until it
//               returns a non-whitespace character
void Lexer::getNonBlank()
{
  while( isspace(nextChar) ) getChar();
}

// lex() - a simple lexical analyzer
int Lexer::lex()
{
  getNonBlank();
  lexeme = "";

  switch( charClass )
  {
    case LETTER: 
        addChar(); 
        getChar(); 
        while( charClass == LETTER || charClass == DIGIT ){ 
          addChar(); 
          getChar(); 
        } 

        if(keywords()){
          nextToken = KEYWORD;
        }
        else{
        nextToken=IDENT; 
        }
        break; // identifiers
    case DIGIT: 
        addChar(); 
        getChar(); 
        while( charClass == DIGIT ){ 
          addChar(); 
          getChar(); 
        } 
        if(floatLit()){
          nextToken = FLOAT_LIT;
        }
        else{
        nextToken=INT_LIT;
        } 
        getChar();
        break; // integers
    case FLOAT:
        if(floatLit()){
          nextToken = FLOAT_LIT;
        }
        else{
          printf("ERROR\n");
          nextToken=EOF; 
          lexeme = "EOF";
        }
        break;
    case UNKNOWN: 
        lookup(nextChar); 
        getChar(); 
        break; // Other characters

    case STRING:
        addChar();
        if(stringLit()){
          nextToken = STRING_LIT;
        }
        else{
          printf("ERROR NEEDS QUOTES\n");
          nextToken=EOF; 
          lexeme = "EOF";
        }
        getChar();
        break;
    case EOF: 
        nextToken=EOF; 
        lexeme = "EOF";
        break;
  }

  return nextToken;
}

bool Lexer::floatLit(){
   addChar();
   getChar();
   if(charClass != DIGIT){
     return false;
   }
   while( charClass == DIGIT ){ 
          addChar(); 
          getChar(); 
    }
    if(nextChar == 'f' || nextChar =='F'){
      addChar();
      return true;
    }
    return true;

}

bool Lexer::stringLit(){
  //addChar();
  getChar();
  while(charClass != STRING){
    if(charClass == EOF){
      return false;
    }
    addChar();
    getChar();
  }
  addChar();
  return true;

}//end stringLit

bool Lexer::keywords(){
  if(lexeme.compare("if") == 0 || lexeme.compare("else") == 0 || lexeme.compare("for") == 0 ||
      lexeme.compare("do") == 0 || lexeme.compare("while") == 0 || lexeme.compare("switch") == 0 ||
      lexeme.compare("case") == 0 || lexeme.compare("default") == 0 || lexeme.compare("break") == 0 ||
      lexeme.compare("void") == 0 || lexeme.compare("return") == 0){
    return true;
  }


}//end keywords




