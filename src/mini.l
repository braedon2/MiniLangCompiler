%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

%option yylineno

%%

[ \t\r\n]+

"var"    return tVAR;
"string" return tSTR;
"float"  return tFLOAT;
"int"    return tINT;
"bool"   return tBOOL;
"read"   return tREAD;
"print"  return tPRINT;
"if"     return tIF;
"else"   return tELSE;
"while"  return tWHILE;

"True" {
	yylval.boolval = 1;
	return tBOOLVAL;
}

"False" {
	yylval.boolval = 0;
	return tBOOLVAL;
}
":"     return ':';
"="     return '=';
";"     return ';';
"{"     return '{';
"}"     return '}';
"+"     return '+';
"-"     return '-';
"*"     return '*';
"/"     return '/';
"("     return '(';
")"     return ')';
"!"     return '!';
"<"     return '<';
">"     return '>';

"=="    return tEQ;
"!="    return tNEQ;
">="    return tGTEQ;
"<="    return tLTEQ;
"&&"    return tAND;
"||"    return tOR;

#.*\n   /* discard comments */

0|([1-9][0-9]*) {
	yylval.intval = atoi(yytext);
	return tINTVAL;
}
(0|([1-9][0-9]*))"."[0-9]+ {
    yylval.floatval = atof(yytext);
    return tFLOATVAL;
}
[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.identifier = strdup(yytext);
	return tIDENTIFIER;
}

\"[^"\n]*\" {
	yylval.strval = strdup(yytext);
	return tSTRVAL;
}

. 	{ fprintf (stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }

%%
