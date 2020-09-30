/******************************************************************* 
Name: Jason Stein 
NetID: jss670
Course: CSE 4713 Assignment: Part 1
Programming Environment: Visual Studio Code 
Purpose of File: Contains the production rules for TIPS EBNF Grammar
*******************************************************************/
#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H

extern int nextToken;
extern int level;
extern unsigned sleep();
extern set<string> symbolTable;
set<string>::iterator itr; // used this to check declaration syntax
int declNo = 0;
int factorCount = 0;

bool first_of_read(void);
bool first_of_write(void);
bool first_of_program(void);
bool first_of_block(void);
bool first_of_statement(void);
bool first_of_expression(void);
bool first_of_if(void);
bool first_of_assignment(void);
bool first_of_while(void);
bool first_of_simple_expression(void);
bool first_of_term(void);
bool first_of_factor(void);
bool first_of_compound(void);

void program();
void block();
void statement();
void assignment();
void compound();
void iff();
void w();
void tipsRead();
void tipsWrite();
void expression();
void simple_expression();
void term();
void factor();

extern "C"
{
    // Instantiate global variables used by flex
    extern char *yytext; // text of current lexeme
    extern int yylex();  // the generated lexical analyzer
}
string spaces()
{
    string str(level * 4, ' ');
    return str;
}

void output_lexeme()
{
    cout << spaces() << "-->found " << yytext << endl;
}
void tipsRead()
{
    ++level;
    cout << spaces() << "enter <read>" << endl;
    output_lexeme();
    nextToken = yylex();
    if (nextToken != TOK_OPENPAREN)
    {
        throw "9: '(' expected";
    }
    else
    {
        output_lexeme();
        nextToken = yylex();
        output_lexeme();

        if (nextToken != TOK_IDENT)
        {
            throw "2: identifier expected";
        }

        else
        {
            symbolTable.insert(yytext);
            nextToken = yylex();

            if (nextToken != TOK_CLOSEPAREN)
            {
                throw "4: ')' expected";
            }
            else
            {
                output_lexeme();
                nextToken = yylex();
            }
        }
    }

    cout << spaces() << "exit <read>" << endl;
    --level;
}

void tipsWrite()
{
    ++level;
    cout << spaces() << "enter <write>" << endl;
    output_lexeme();
    nextToken = yylex();
    if (nextToken != TOK_OPENPAREN)
    {
        throw "9: '(' expected";
    }
    else
    {
        output_lexeme();
        nextToken = yylex();

        switch (nextToken)
        {
        case TOK_IDENT:
            output_lexeme();
            nextToken = yylex();
            break;

        case TOK_STRINGLIT:
            output_lexeme();
            nextToken = yylex();
            break;

        default:
            throw "134: illegal type of operand(s)";
        }
    }
    if (nextToken != TOK_CLOSEPAREN)
    {
        throw "4: ')' expected";
    }
    else
    {
        output_lexeme();
    }
    cout << spaces() << "exit <write>" << endl;
    --level;
    nextToken = yylex();
}

void factor()
{
    ++level;
    cout << spaces() << "enter <factor>" << endl;

    switch (nextToken)
    {
    case TOK_INTLIT:
        output_lexeme();
        nextToken = yylex();
        break;

    case TOK_FLOATLIT:
        output_lexeme();
        nextToken = yylex();
        break;

    case TOK_IDENT:
        output_lexeme();
        //check symbol table to make sure ident is declared or if it is declared twice

        for (itr = symbolTable.begin(); itr != symbolTable.end(); ++itr)
        {
            string temp;
            temp = string(*itr);
            if (temp == yytext)
            {
                ++declNo;
            }
        }
        if (declNo == 0)
            throw "104: identifier not declared";

        --declNo;

        if (declNo > 1)
            throw "101: identifier declared twice";

        nextToken = yylex();
        break;

    case TOK_OPENPAREN:
        output_lexeme();
        nextToken = yylex();
        if (!first_of_expression())
            throw "144: illegal type of expression";

        expression();

        nextToken = yylex();
        if (nextToken != TOK_CLOSEPAREN)
            throw "4: ')' expected";
        break;

    case TOK_NOT:
        output_lexeme();
        nextToken = yylex();
        if (!first_of_factor())
            throw "903: illegal type of factor";
        //check symbol table to make sure ident is declared or if it is declared twice

        for (itr = symbolTable.begin(); itr != symbolTable.end(); ++itr)
        {
            string temp;
            temp = string(*itr);
            if (temp == yytext)
            {
                ++declNo;
            }
        }
        if (declNo == 0)
            throw "104: identifier not declared";

        --declNo;

        if (declNo > 1)
            throw "101: identifier declared twice";
        factor();
        break;

    case TOK_MINUS:
        output_lexeme();
        nextToken = yylex();

        if (!first_of_factor())
            throw "903: illegal type of factor";
        //check symbol table to make sure ident is declared or if it is declared twice

        for (itr = symbolTable.begin(); itr != symbolTable.end(); ++itr)
        {
            string temp;
            temp = string(*itr);
            if (temp == yytext)
            {
                ++declNo;
            }
        }
        if (declNo == 0)
            throw "104: identifier not declared";

        --declNo;

        if (declNo > 1)
            throw "101: identifier declared twice";
        output_lexeme();
        factor();

        break;

    default:
        throw "903: illegal type of factor";
    }

    cout << spaces() << "exit <factor>" << endl;
    --level;
}

void term()
{

    ++level;
    cout << spaces() << "enter <term>" << endl;
    if (!first_of_factor())
        throw "903 : illegal type of factor";

    factor();
    while (nextToken != TOK_NOT &&
           nextToken != TOK_MINUS &&
           nextToken != TOK_SEMICOLON &&
           nextToken != TOK_EOF &&
           nextToken != TOK_GREATERTHAN &&
           nextToken != TOK_LESSTHAN &&
           nextToken != TOK_EQUALTO &&
           nextToken != TOK_NOTEQUALTO &&
           nextToken != TOK_THEN &&
           nextToken != TOK_ELSE)
    {
        //cout << "check here" << endl;
        switch (nextToken)
        {
        case TOK_MULTIPLY:
            output_lexeme();
            nextToken = yylex();
            if (!first_of_factor())
                throw "903: illegal type of factor";
            factor();

            break;

        case TOK_DIVIDE:
            output_lexeme();
            nextToken = yylex();
            if (!first_of_factor())
                throw "903: illegal type of factor";
            factor();

            break;

        case TOK_AND:
            output_lexeme();
            nextToken = yylex();
            if (!first_of_factor())
                throw "903: illegal type of factor";
            factor();

            break;

        default:
            break;
        }
    }
    cout << spaces() << "exit <term>" << endl;
    --level;
}
void simple_expression()
{

    ++level;
    cout << spaces() << "enter <simple expression>" << endl;
    if (!first_of_term())
        throw "902: illegal type of term";

    term();

    while (nextToken != TOK_SEMICOLON &&
           nextToken != TOK_END &&
           nextToken != TOK_EOF &&
           nextToken != TOK_EQUALTO &&
           nextToken != TOK_GREATERTHAN &&
           nextToken != TOK_LESSTHAN &&
           nextToken != TOK_NOTEQUALTO &&
           nextToken != TOK_THEN &&
           nextToken != TOK_ELSE)

    {

        switch (nextToken)
        {
        case TOK_PLUS:

            output_lexeme();
            nextToken = yylex();
            if (!first_of_term())
            {
                throw "902: illegal type of term";
            }

            term();

            break;

        case TOK_MINUS:
            output_lexeme();
            nextToken = yylex();
            if (!first_of_term())
            {
                throw "902: illegal type of term";
            }

            term();

            break;

        case TOK_OR:

            output_lexeme();
            nextToken = yylex();

            if (!first_of_term())
            {
                throw "902: illegal type of term";
            }
            term();
            break;

        default:
            break;
        }
    }

    cout << spaces() << "exit <simple expression>" << endl;
    --level;
}

void expression()
{
    ++level;
    //debug code 6
    cout << spaces() << "enter <expression>" << endl;
    if (!first_of_simple_expression())
        throw "144: illegal type of expression";

    //debug code 7
    //cout << "did i make it to expression" << endl;
    simple_expression();

    switch (nextToken)
    {
    case TOK_EQUALTO:

        output_lexeme();
        nextToken = yylex();

        if (!first_of_simple_expression())
        {
            throw "901: illegal type of simple expression";
        }

        simple_expression();

        break;

    case TOK_NOTEQUALTO:

        output_lexeme();
        nextToken = yylex();

        if (!first_of_simple_expression())
        {
            throw "901: illegal type of simple expression";
        }

        simple_expression();

        break;

    case TOK_GREATERTHAN:

        output_lexeme();
        nextToken = yylex();

        if (!first_of_simple_expression())
        {
            throw "901: illegal type of simple expression";
        }

        simple_expression();

        break;

    case TOK_LESSTHAN:
        output_lexeme();
        nextToken = yylex();

        if (!first_of_simple_expression())
        {
            throw "901: illegal type of simple expression";
        }

        simple_expression();

        break;

    default:
        break;
    }

    cout << spaces() << "exit <expression>" << endl;
    --level;
}

//w = while, expecting first token as TOK_WHILE
void w()
{
    ++level;

    cout << spaces() << "enter <while statement>" << endl;
    output_lexeme();
    if (nextToken == TOK_WHILE)
    {
        nextToken = yylex();
        if (!first_of_expression())
            throw "144: illegal type of expression";
        expression();

        if (!first_of_statement())
            throw "900: illegal type of statement";
    }

    --level;
    cout << spaces() << "exit <while statement>" << endl;
}

// iff = if, expecting first token to be tok_if
void iff()
{
    ++level;
    cout << spaces() << "enter <if statement>" << endl;
    output_lexeme();
    nextToken = yylex();

    if (!first_of_expression())
        throw "144: illegal type of expression";

    expression();

    if (nextToken != TOK_THEN)
        throw "52: 'THEN' expected";
    output_lexeme();
    nextToken = yylex();
    if (!first_of_statement())
        throw "900: illegal type of statement";
    statement();
    if (nextToken == TOK_ELSE)
    {
        output_lexeme();

        nextToken = yylex();

        if (!first_of_statement())
            throw "900: illegal type of statement";

        statement();
    }
    cout << spaces() << "exit <if statement>" << endl;
    --level;
}

void compound()
{
    ++level;
    cout << spaces() << "enter <compound_statement>" << endl;
    output_lexeme();

    nextToken = yylex();
    if (!first_of_statement())
        throw "900: illegal type of statement";
    statement();

    while (nextToken == TOK_SEMICOLON)
    {
        output_lexeme();
        nextToken = yylex();
        if (!first_of_statement())
        {
            throw "900: illegal type of statement";
        }

        statement();
    }
    output_lexeme();
    cout << spaces() << "exit <compound_statement>" << endl;
    --level;
}

void assignment()
{

    ++level;
    cout << spaces() << "enter <assignment>" << endl;
    output_lexeme();
    symbolTable.insert(yytext);

    nextToken = yylex();
    output_lexeme();

    if (nextToken != TOK_ASSIGN)
        throw "51: ':=' expected";

    nextToken = yylex();
    if (!first_of_expression())
        throw "901: illegal type of simple expression";

    expression();

    cout << spaces() << "exit <assignment>" << endl;
    --level;
}

void statement()
{
    ++level;
    cout << spaces() << "enter <statement>" << endl;

    switch (nextToken)
    {
        //if it starts with IDENT, my choice is assignment
    case TOK_IDENT:

        assignment();

        break;

    //if next token is begin, my choice is compound
    case TOK_BEGIN:
        compound();

        break;

    //if next token is if, my choice is if
    case TOK_IF:
        iff();

        break;
        //nextToken = yylex();

    case TOK_WHILE:
        w();

        //nextToken = yylex();
        break;

    case TOK_READ:
        tipsRead();

        //nextToken = yylex();
        break;

    case TOK_WRITE:

        tipsWrite();
        //nextToken = yylex();
        break;

    default:
        if (nextToken != TOK_SEMICOLON)
            throw "";

        break;
    }

    cout << spaces() << "exit <statement>" << endl;
    --level;
}

void block()
{

    ++level;
    cout << spaces() << "enter <block>" << endl;

    if (nextToken == TOK_VAR)
    {
        output_lexeme();
        nextToken = yylex();
        output_lexeme();
        if (nextToken != TOK_IDENT)
            throw "2: identifier expected";

        nextToken = yylex();
        output_lexeme();

        if (nextToken != TOK_COLON)
            throw "5 : ':' expected";

        nextToken = yylex();
        output_lexeme();

        if (nextToken != TOK_INTEGER && nextToken != TOK_REAL)
            throw "10: error in type";

        nextToken = yylex();
        output_lexeme();

        if (nextToken != TOK_SEMICOLON)
            throw "14: ';' expected";

        nextToken = yylex();

        while (nextToken != TOK_SEMICOLON && nextToken != TOK_BEGIN)
        {
            cout << endl;
            output_lexeme();
            if (nextToken != TOK_IDENT)
                throw "2: identifier expected";

            nextToken = yylex();
            output_lexeme();

            if (nextToken != TOK_COLON)
                throw "5 : ':' expected";

            nextToken = yylex();
            output_lexeme();

            if (nextToken != TOK_INTEGER && nextToken != TOK_REAL)
                throw "10: error in type";

            nextToken = yylex();
            output_lexeme();

            if (nextToken != TOK_SEMICOLON)
                throw "14: ';' expected";

            nextToken = yylex();
        }
        cout << endl;
    }
    if (nextToken != TOK_BEGIN)
        throw "18: error in declaration part OR 17: 'BEGIN' expected";

    compound();
    while (nextToken != TOK_END)
    {
        if (nextToken != TOK_SEMICOLON)
            throw "14: ';' expected";
        compound();
    }

    cout << spaces() << "exit <block>" << endl;
    --level;
}

void program()
{
    ++level;
    cout << "enter <program>" << endl;
    if (!first_of_program())
        throw "3: 'PROGRAM' expected";

    output_lexeme();

    //parse input to see if the input matches the EBNF rule for <program>
    nextToken = yylex();
    output_lexeme();
    //debug test 3

    if (nextToken != TOK_IDENT)
    {
        throw "2: identifier expected";
    }
    //debug test 2:
    //cout << "Got here" << endl;
    nextToken = yylex();
    if (nextToken != TOK_SEMICOLON)
    {
        throw " 14 : ';' expected";
    }

    output_lexeme();
    nextToken = yylex();
    if (!first_of_block())
    {
        throw "18: error in declaration part OR 17: 'BEGIN' expected";
    }
    while (nextToken != TOK_END)
    {

        block();
    }
    cout << spaces() << "exit <program>" << endl;
    nextToken = yylex();
}

//*****************************************************************************

bool first_of_program(void)
{
    return nextToken == TOK_PROGRAM;
}

bool first_of_block(void)
{
    return nextToken == TOK_VAR || nextToken == TOK_BEGIN;
}

bool first_of_statement(void)
{
    return nextToken == TOK_IDENT ||
           nextToken == TOK_BEGIN ||
           nextToken == TOK_IF ||
           nextToken == TOK_WHILE ||
           nextToken == TOK_READ ||
           nextToken == TOK_WRITE;
}

bool first_of_assignment(void)
{
    return nextToken == TOK_IDENT;
}

bool first_of_compound(void)
{
    return nextToken == TOK_BEGIN;
}

bool first_of_if(void)
{
    return nextToken == TOK_IF;
}

bool first_of_while(void)
{
    return nextToken == TOK_WHILE;
}

bool first_of_read(void)
{
    return nextToken == TOK_READ;
}

bool first_of_write(void)
{
    return nextToken == TOK_WRITE;
}

bool first_of_expression(void)
{
    return nextToken == TOK_INTLIT ||
           nextToken == TOK_FLOATLIT ||
           nextToken == TOK_IDENT ||
           nextToken == TOK_OPENPAREN ||
           nextToken == TOK_NOT ||
           nextToken == TOK_MINUS;
}

bool first_of_simple_expression(void)
{
    return nextToken == TOK_INTLIT ||
           nextToken == TOK_FLOATLIT ||
           nextToken == TOK_IDENT ||
           nextToken == TOK_OPENPAREN ||
           nextToken == TOK_NOT ||
           nextToken == TOK_MINUS;
}

bool first_of_term(void)
{
    return nextToken == TOK_INTLIT ||
           nextToken == TOK_FLOATLIT ||
           nextToken == TOK_IDENT ||
           nextToken == TOK_OPENPAREN ||
           nextToken == TOK_NOT ||
           nextToken == TOK_MINUS;
}

bool first_of_factor(void)
{
    return nextToken == TOK_INTLIT ||
           nextToken == TOK_FLOATLIT ||
           nextToken == TOK_IDENT ||
           nextToken == TOK_OPENPAREN ||
           nextToken == TOK_NOT ||
           nextToken == TOK_MINUS;
}
#endif
