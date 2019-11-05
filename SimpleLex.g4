//Kyle Hippe
//Fall 2018
//10/10/2018
//Sources: Slides and cpluplusreference for method lookup
//no special insturctions


lexer grammar SimpleLex;

// Skip white space
WS: [ \t\n\r]+ -> skip;

// Simple Tokens

ASSIGN_OP: '=' ;
MULT_OP: '*'
DIV_OP: '/'
ADD_OP: '+' ;
SUB_OP: '-' ;
LEFT_PAREN: '(' ;
RIGHT_PAREN ')' ;
COMMA: ',' ;
SEMI_COLON: ';' ;
LEFT_BRACE: '{' ;
RIGHT_BRACE '}' ;
QUOTE: '"' ;
PERIOD: '.' ;

//Identifier and Int literals
KEYWORD: IF | ELSE | FOR | DO | WHILE | SWITCH 
            | CASE | DEFAULT | BREAK | VOID | RETURN ;
FLOAT_LIT: ([DIGIT]+ . [DIGIT]* 'f'?) ; 
STRING_LIT: QUOTE STRINGS* QUOTE ;
IDENT: LETTER (LETTER | DIGIT)*;
INT_LIT: DIGIT+;

//Fragments to help with idents + others
fragment LETTER: [a-zA-Z];
fragment DIGIT: [0-9];
fragment IF: ([i][f]);
fragment ELSE: ([e][l][s][e]);
fragment FOR: ([f][o][r]); 
fragment DO: ([d][o]);
fragment WHILE: ([w][h][i][l][e]); 
fragment SWITCH: ([s][w][i][t][c][h]);
fragment CASE: ([c][a][s][e]);
fragment DEFAULT: ([d][e][f][a][u][l][t]);
fragment BREAK: ([b][r][e][a][k]); 
fragment VOID: ([v][o][i][d]): 
fragment RETURN: ([r][e][t][u][r][n]);
fragment STRINGS: 'a'..'z' | 'A'..'Z' | '0'..'9' | ':' | '.' | '&' | '/' | '\\' | ';';
