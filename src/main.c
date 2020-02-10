
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"

int yylex();

STMT *root;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        fprintf(stderr, "Usage: ./minic <mode>\n + mode: scan|tokens|parse\n");
    }
    else if (strcmp(argv[1], "tokens") == 0)
    {
        int token = yylex();
        while (token != 0)
        {
            switch (token)
            {
                case tREAD:
                    printf("tREAD\n");
                    break;
                case tPRINT:
                    printf("tPRINT\n");
                    break;
                case tIF:
                    printf("tIF\n");
                    break;
                case tELSE:
                    printf("tELSE\n");
                    break;
                case tWHILE:
                    printf("tWHILE\n");
                    break;
                case tVAR:
                    printf("tVAR\n");
                    break;
                case tSTR:
                    printf("tSTR\n");
                    break;
                case tINT:
                    printf("tINT\n");
                    break;
                case tFLOAT:
                    printf("tFLOAT\n");
                    break;
                case tBOOL:
                    printf("tBOOL\n");
                    break;
                case tSTRVAL:
                    printf("STRVAL(%s)\n", yylval.strval);
                    break;
                case tBOOLVAL:
                    printf("tBOOLVAL(%s)\n", yylval.boolval ? "True" : "False");
                    break;
                case tINTVAL:
                    printf("tINTVAL(%d)\n", yylval.intval);
                    break;
                case tFLOATVAL:
                    printf("tFLOATVAL(%f)\n", yylval.floatval);
                    break;
                case tIDENTIFIER:
                    printf("tIDENTIFIER(%s)\n", yylval.identifier);
                    break;
                case tEQ:
                    printf("==\n");
                    break;
                case tNEQ:
                    printf("!=\n");
                    break;
                case tGTEQ:
                    printf(">=\n");
                    break;
                case tLTEQ:
                    printf("<=\n");
                    break;
                case tAND:
                    printf("&&\n");
                    break;
                case tOR:
                    printf("||\n");
                    break;
                default:
                    printf("%c\n", token);
            }

            token = yylex();
        }
    }
    else if (strcmp(argv[1], "scan") == 0)
    {
        while (yylex() != 0) {}
        printf("OK\n");
    }
    else if (strcmp(argv[1], "parse") == 0)
    {
        yyparse();
        printf("OK\n");
    }
    else
    {
        fprintf(stderr, "Error: Unknown mode \"%s\"\n", argv[1]);
        fprintf(stderr, "Usage: ./minic <mode>\n + mode: scan|tokens|parse\n");
    }
    
    return 0;
}
