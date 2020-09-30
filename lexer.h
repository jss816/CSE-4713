//*****************************************************************************
// CSE 4713 / 6713 Project - List of tokens for TIPS
//*****************************************************************************

#ifndef LEXER_H
#define LEXER_H

// List of token codes

// Keywords
#define TOK_BEGIN    1000
#define TOK_BREAK    1001
#define TOK_CONTINUE 1002
#define TOK_DOWNTO   1003
#define TOK_ELSE     1004
#define TOK_END      1005
#define TOK_FOR      1006
#define TOK_IF       1007
#define TOK_LET      1008
#define TOK_PROGRAM  1009
#define TOK_READ     1010
#define TOK_THEN     1012
#define TOK_TO       1013
#define TOK_VAR      1014
#define TOK_WHILE    1015
#define TOK_WRITE    1016

// Datatype Specifiers
#define TOK_INTEGER  1100
#define TOK_REAL     1101

// Punctuation
#define TOK_SEMICOLON  2000
#define TOK_COLON      2001
#define TOK_OPENPAREN  2002
#define TOK_CLOSEPAREN 2003
#define TOK_OPENBRACE  2004
#define TOK_CLOSEBRACE 2005

// Operators
#define TOK_PLUS        3000
#define TOK_MINUS       3001
#define TOK_MULTIPLY    3002
#define TOK_DIVIDE      3003
#define TOK_ASSIGN      3004
#define TOK_EQUALTO     3005
#define TOK_LESSTHAN    3006
#define TOK_GREATERTHAN 3007
#define TOK_NOTEQUALTO  3008
#define TOK_MOD         3009
#define TOK_NOT         3010
#define TOK_OR          3011
#define TOK_AND         3012

// Useful abstractions
#define TOK_IDENT       4000  // identifier
#define TOK_INTLIT      4001  // integer literal
#define TOK_FLOATLIT    4002  // floating point literal
#define TOK_STRINGLIT   4003  // string literal
#define TOK_ERROR_SL    4004  // string literal is too long
#define TOK_EOF         5000  // end of file
#define TOK_EOF_SL      5001  // end of file while parsing a string literal
#define TOK_UNKNOWN     6000  // unknown lexeme

#endif

