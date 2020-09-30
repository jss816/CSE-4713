
/*********************************************************************
Name: Jason Stein 
NetID: jss670
Course: CSE 4713 Assignment: Part 1
Programming Environment: Visual Studio Code
Purpose of File: Contains the ruleset for the yylex to pattern match
*********************************************************************/

/******************************************************************* 
Starting point your rules.l file for TIPS
*******************************************************************/
%option noyywrap
%{
#include "lexer.h"
#include <math.h>


// global variable to hold current line number being read
int line_number = 1;

%}



%%

\n {++line_number;}

 /* Keywords */ 
 "BEGIN"   {return TOK_BEGIN;}
 "BREAK"   {return TOK_BREAK;}
 "CONTINUE" {return TOK_CONTINUE;}
 "DOWNTO"   {return TOK_DOWNTO;}
 "ELSE" {return TOK_ELSE;}
 "END"  {return TOK_END;}
 "FOR"  {return TOK_FOR;}
 "IF"   {return TOK_IF;}
 "LET"  {return TOK_LET;}
 "PROGRAM"  {return TOK_PROGRAM;}
 "READ" {return TOK_READ;}
 "THEN" {return TOK_THEN;}
 "TO"  {return TOK_TO;}
 "VAR"  {return TOK_VAR;}
 "WHILE"   {return TOK_WHILE;}
 "WRITE"   {return TOK_WRITE;}

 /* Datatype Specifiers */
"INTEGER" {return TOK_INTEGER;}
"REAL" {return TOK_REAL;}

 /* Punctuation */
\:         { return TOK_COLON; }
\; {return TOK_SEMICOLON;}
\( {return TOK_OPENPAREN;}
\)  {return TOK_CLOSEPAREN;}
\{ {return TOK_OPENBRACE;}
\} {return TOK_CLOSEBRACE;}



 /* Operators */
\+ {return TOK_PLUS;}
\- {return TOK_MINUS;}
\* {return TOK_MULTIPLY;}
\/ {return TOK_DIVIDE;}
\:= {return TOK_ASSIGN;}
\= {return TOK_EQUALTO;}
\< {return TOK_LESSTHAN;}
\> {return TOK_GREATERTHAN;}
\<> {return TOK_NOTEQUALTO;}
"MOD" {return TOK_MOD;}
"AND" {return TOK_AND;}
"NOT" {return TOK_NOT;}
"OR" {return TOK_OR;}

 /* Abstractions */
[A-Z][A-Z0-9_]{0,7} {return TOK_IDENT;}
[0-9]+ {return TOK_INTLIT;}
[0-9]*\.[0-9]+ {return TOK_FLOATLIT;}
\'[^\']*\'  {return TOK_STRINGLIT;}
\^[\0]^\" {return TOK_EOF_SL;}

 /* Eat any whitespace */

[ \t\r]             /* nop */


 /* Found an unknown character */

.     { return TOK_UNKNOWN; }


 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }


