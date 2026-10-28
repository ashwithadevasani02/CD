
%{
#include <stdio.h>
%}

%%
[0-9]*\.[0-9]+ {
    int i;

    for (i = 0; yytext[i] != '.'; i++)
        printf("%c", yytext[i]);

    printf("\n");
}
%%

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
lex realtoint.l
cc lex.yy.c -ll
