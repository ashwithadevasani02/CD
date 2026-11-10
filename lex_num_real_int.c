
%{
#include <stdio.h>
%}

%%
\+?[0-9]+\.[0-9]+    { printf("%s : positive real number\n", yytext); }
-[0-9]+\.[0-9]+      { printf("%s : negative real number\n", yytext); }
\+?[0-9]+            { printf("%s : positive integer\n", yytext); }
-[0-9]+              { printf("%s : negative integer\n", yytext); }
[ \t\n]+             { /* Ignore whitespace */ }
.                    { printf("%s : invalid input\n", yytext); }
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


lex noformat.l
gcc lex.yy.c -ll -o lexer
./lexer