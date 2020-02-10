%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

extern int yylineno;
int yylex();

void yyerror(const char *s) {
    fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
    exit(1);
}

extern STMT *root;
%}

%code requires
{
	#include "tree.h"
}

// the contents of yylval
%union {
    int   intval;
    int   boolval;
    float floatval;
    char  *strval;
    char  *identifier;

    EXP *exp;
    IFSTMT *ifstmt;
    STMT *stmt;
}

%type <exp> exp
%type <ifstmt> ifstmt
%type <stmt> stmt 
%type <stmt> stmts
%type <stmt> program

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

program : stmts { root = $1; };

stmts : stmts stmt { $$ = $2; $$->next = $1; }
      | %empty {$$ = NULL;} 
      ;

stmt : tVAR tIDENTIFIER ':' tINT '=' exp ';' { $$ = makeSTMT_declaration($2, INT, $6); }
     | tVAR tIDENTIFIER ':' tFLOAT '=' exp ';' { $$ = makeSTMT_declaration($2, FLOAT, $6); }
     | tVAR tIDENTIFIER ':' tBOOL '=' exp ';' { $$ = makeSTMT_declaration($2, BOOL, $6); }
     | tVAR tIDENTIFIER ':' tSTR '=' exp ';' { $$ = makeSTMT_declaration($2, STR, $6); }
     | tVAR tIDENTIFIER '=' exp ';' { $$ = makeSTMT_declaration($2, INFERRED, $4); }
     | tREAD '(' tIDENTIFIER ')' ';' { $$ = makeSTMT_read($3); }
     | tPRINT '(' exp ')' ';' { $$ = makeSTMT_print($3); }
     | tIDENTIFIER '=' exp ';' { $$ = makeSTMT_assign($1, $3); }
     | ifstmt { $$ = makeSTMT_if($1); }
     | tWHILE '(' exp ')' '{' stmts '}' { $$ = makeSTMT_while($3, $6); }
     ;

ifstmt : tIF '(' exp ')' '{' stmts '}' { $$ = makeIFSTMT_ifElse($3, $6, NULL); }
       | tIF '(' exp ')' '{' stmts '}' tELSE '{' stmts '}' { $$ = makeIFSTMT_ifElse($3, $6, $10); }
       | tIF '(' exp ')' '{' stmts '}' tELSE ifstmt { $$ = makeIFSTMT_ifElseIf($3, $6, $9); }
       ;

exp : tIDENTIFIER { $$ = makeEXP_identifier($1); }
    | tINTVAL { $$ = makeEXP_intLiteral($1); }
    | tFLOATVAL { $$ = makeEXP_}
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

