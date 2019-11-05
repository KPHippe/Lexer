#pragma once

/* 
 * This is a C++ version of the lexer provided in the Sebesta
 * text in Section 4.2
 */

#include <fstream>
#include <string>

// Character classes
#define LETTER 0
#define DIGIT 1
#define STRING 2
#define FLOAT 3
#define UNKNOWN 99

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define COMMA 60
#define SEMI_COLON 100
#define LEFT_BRACE 27
#define RIGHT_BRACE 28
#define KEYWORD 50
#define STRING_LIT 40
#define FLOAT_LIT 41
#define QUOTE 43
#define PERIOD 44

class Lexer {

private:
  std::string lexeme;
  int nextToken;
  int charClass;
  char nextChar;
  std::ifstream inputStream;

public:
  Lexer( const std::string & fileName );
  ~Lexer();

  int lex();
  int getNextToken() const;
  std::string getLexeme() const;

private:
  void getNonBlank();
  void getChar();
  void addChar();
  int lookup(char ch);
  bool floatLit();
  bool stringLit();
  bool keywords();
};
