
%{
#include <stdio.h>
%}

%%
[ \t\n]+   ;

if|else|while|do|switch|case|break|for|default
           { printf("%s : Keyword\n", yytext); }

IF|ELSE|WHILE|DO|SWITCH|CASE|BREAK|FOR|DEFAULT
           { printf("%s : Keyword\n", yytext); }

[A-Za-z_][A-Za-z0-9_]*
           { printf("%s : Identifier\n", yytext); }

.          { printf("%s : Invalid character\n", yytext); }

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
