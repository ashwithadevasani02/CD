
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

/*
Original Grammar:
E -> E + T | T
T -> T * F | F
F -> (E) | id

Grammar after removing left recursion:
E  -> T E'
E' -> + T E' | epsilon
T  -> F T'
T' -> * F T' | epsilon
F  -> (E) | id
*/

char ip[MAX];
int pos = 0;

void E(void);
void Eprime(void);
void T(void);
void Tprime(void);
void F(void);
void error(void);

void error(void)
{
    printf("Syntax error at position %d\n", pos);
    exit(1);
}

/* E -> T E' */
void E(void)
{
    T();
    Eprime();
}

/* E' -> + T E' | epsilon */
void Eprime(void)
{
    if (ip[pos] == '+')
    {
        pos++;
        T();
        Eprime();
    }
}

/* T -> F T' */
void T(void)
{
    F();
    Tprime();
}

/* T' -> * F T' | epsilon */
void Tprime(void)
{
    if (ip[pos] == '*')
    {
        pos++;
        F();
        Tprime();
    }
}

/* F -> (E) | id */
void F(void)
{
    if (ip[pos] == '(')
    {
        pos++;
        E();

        if (ip[pos] == ')')
            pos++;
        else
            error();
    }
    else if (isalpha((unsigned char)ip[pos]))
    {
        /* Recognize identifiers such as id, x, abc */
        while (isalnum((unsigned char)ip[pos]) ||
               ip[pos] == '_')
        {
            pos++;
        }
    }
    else
    {
        error();
    }
}

int main(void)
{
    printf("Enter an expression: ");

    if (fgets(ip, sizeof(ip), stdin) == NULL)
        return 1;

    /* Remove trailing newline */
    ip[strcspn(ip, "\r\n")] = '\0';

    if (ip[0] == '\0')
    {
        printf("Empty input\n");
        return 0;
    }

    pos = 0;
    E();

    if (ip[pos] == '\0')
        printf("String accepted\n");
    else
        error();

    return 0;
}
