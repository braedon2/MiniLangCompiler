%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
int yylex();

void yyerror(const char *s) {
    fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
    exit(1);
}
%}

// the contents of yylval
%union {
    int   intval;
    int   boolval;
    float floatval;
    char  *strval;
    char  *identifier;
}


%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <identifier> tIDENTIFIER
%token <boolval> tBOOLVAL
%token <strval> tSTRVAL
%token tUMINUS tEQ tNEQ tGTEQ tLTEQ tAND tOR

%token tVAR tINT tFLOAT tBOOL tSTR tREAD tPRINT tIF tELSE tWHILE

/* precedence */
%left tOR
%left tAND
%left tEQ tNEQ
%left tGTEQ tLTEQ '>' '<'
%left '+' '-'
%left '*' '/'
%left tUMINUS '!'

%start program

%locations
%error-verbose

%%

program: stmts;

stmts: stmts stmt | ;

stmt : tVAR tIDENTIFIER ':' tINT '=' exp ';'
     | tVAR tIDENTIFIER ':' tFLOAT '=' exp ';'
     | tVAR tIDENTIFIER ':' tBOOL '=' exp ';'
     | tVAR tIDENTIFIER ':' tSTR '=' exp ';'
     | tVAR tIDENTIFIER '=' exp ';'
     | tREAD '(' tIDENTIFIER ')' ';'
     | tPRINT '(' exp ')' ';'
     | tIDENTIFIER '=' exp ';'
     | ifstmt
     | tWHILE '(' exp ')' '{' stmts '}'
     ;

ifstmt : tIF '(' exp ')' '{' stmts '}'
        | tIF '(' exp ')' '{' stmts '}' tELSE '{' stmts '}'
        | tIF '(' exp ')' '{' stmts '}' tELSE ifstmt

exp : tIDENTIFIER
    | tINTVAL 
    | tFLOATVAL
    | tSTRVAL
    | tBOOLVAL
    | exp '*' exp
    | exp '/' exp
    | exp '+' exp 
    | exp '-' exp
    | exp tGTEQ exp 
    | exp tLTEQ exp
    | exp '>' exp 
    | exp '<' exp
    | exp tEQ exp
    | exp tNEQ exp
    | exp tAND exp
    | exp tOR exp 
    | '!' exp 
    | '-' exp %prec tUMINUS
    | '(' exp ')'
    ;

%%

