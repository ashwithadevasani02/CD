
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char ip[MAX];
int pos = 0;

void S(void);
void L(void);
void Lprime(void);

void error(void)
{
    printf("Syntax error: String not accepted\n");
    exit(1);
}

/* S -> (L) | a */
void S(void)
{
    if (ip[pos] == '(')
    {
        pos++;
        L();

        if (ip[pos] == ')')
            pos++;
        else
            error();
    }
    else if (ip[pos] == 'a')
    {
        pos++;
    }
    else
    {
        error();
    }
}

/* L -> S L' */
void L(void)
{
    S();
    Lprime();
}

/* L' -> , S L' | epsilon */
void Lprime(void)
{
    if (ip[pos] == ',')
    {
        pos++;
        S();
        Lprime();
    }
    /* Otherwise, epsilon: return without consuming input */
}

int main(void)
{
    printf("Enter string: ");

    if (fgets(ip, sizeof(ip), stdin) == NULL)
        return 1;

    ip[strcspn(ip, "\r\n")] = '\0';

    if (ip[0] == '\0')
    {
        error();
    }

    pos = 0;
    S();

    if (ip[pos] == '\0')
        printf("String is accepted\n");
    else
        error();

    return 0;
}
