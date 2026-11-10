
%{
#include <stdio.h>

int year;
void leap(void);
%}

%%
jan|mar|may|jul|aug|oct|dec {
    printf("31 days\n");
}

apr|jun|sep|nov {
    printf("30 days\n");
}

feb {
    leap();
}

[a-zA-Z]+ {
    printf("Invalid month\n");
}

[ \t\n]+    ;
%%

void leap(void)
{
    printf("Enter year: ");
    if (scanf("%d", &year) != 1)
        return;

    if ((year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0))
        printf("29 days\n");
    else
        printf("28 days\n");
}

int main(void)
{
    printf("Enter month (jan, feb, mar, etc.): ");
    yylex();
    return 0;
}

int yywrap(void)
{
    return 1;
}


lex daysinamonth.l
cc lex.yy.c -ll
