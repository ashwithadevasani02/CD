
#include <stdio.h>
#include <string.h>
#define MAX 1000
char stack[MAX];
char input[MAX];
int top = -1, ip = 0;

/* Push an element onto the stack */
void push(char c)
{
    stack[++top] = c;
}

/* Pop an element from the stack */
char pop()
{
    return stack[top--];
}

/* Return the top element */
char peek()
{
    return stack[top];
}

/* Map non-terminals to table rows */
int row(char ch)
{
    switch (ch)
    {
        case 'E': return 0;
        case 'Q': return 1;
        case 'T': return 2;
        case 'R': return 3;
        case 'F': return 4;
        default:  return -1;
    }
}

/* Map terminals to table columns */
int col(char ch)
{
    switch (ch)
    {
        case 'i': return 0;  /* id */
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default:  return -1;
    }
}

/* Predictive parsing table
   e represents epsilon */
char *table[5][6] =
{
    /*  i      +      *      (      )      $  */
    { "TQ",  "",    "",    "TQ",  "",    ""  }, /* E */
    { "",    "+TQ", "",    "",    "e",   "e" }, /* Q */
    { "FR",  "",    "",    "FR",  "",    ""  }, /* T */
    { "",    "e",   "*FR", "",    "e",   "e" }, /* R */
    { "i",   "",    "",    "(E)", "",    ""  }  /* F */
};

/* Display FIRST and FOLLOW sets */
void firstfollow()
{
    printf("\nFIRST sets:\n");
    printf("FIRST(E) = { (, i }\n");
    printf("FIRST(Q) = { +, e }\n");
    printf("FIRST(T) = { (, i }\n");
    printf("FIRST(R) = { *, e }\n");
    printf("FIRST(F) = { (, i }\n");

    printf("\nFOLLOW sets:\n");
    printf("FOLLOW(E) = { ), $ }\n");
    printf("FOLLOW(Q) = { ), $ }\n");
    printf("FOLLOW(T) = { +, ), $ }\n");
    printf("FOLLOW(R) = { +, ), $ }\n");
    printf("FOLLOW(F) = { *, +, ), $ }\n");
}

int main()
{
    int j;

    printf("Predictive Parsing\n");
    firstfollow();

    printf("\nEnter input using i for id and ending with $: ");

    if (scanf("%999s", input) != 1) //strign read successfully
        return 1;

    if (strlen(input) == 0 ||
        input[strlen(input) - 1] != '$')
    {
        printf("Invalid string\n");
        return 0;
    }

    /* Initialize stack */
    push('$');
    push('E');

    while (top >= 0)
    {
        char x = peek();
        char a = input[ip];

        /* Accept when both stack and input reach $ */
        if (x == '$' && a == '$')
        {
            pop();
            ip++;
            printf("Valid string\n");
            return 0;
        }

        /* If stack top matches input symbol */
        if (x == a)
        {
            pop();
            ip++;
        }
        /* If stack top is a non-terminal */
        else if (row(x) != -1)
        {
            int r = row(x);
            int c = col(a);

            /* No production in parsing table */
            if (c == -1 || table[r][c][0] == '\0')
            {
                printf("Invalid string\n");
                return 0;
            }

            pop();

            /* Epsilon means push nothing */
            if (strcmp(table[r][c], "e") != 0)
            {
                int len = strlen(table[r][c]);

                /* Push production in reverse order */
                for (j = len - 1; j >= 0; j--)
                {
                    push(table[r][c][j]);
                }
            }
        }
        else
        {
            printf("Invalid string\n");
            return 0;
        }
    }

    printf("Invalid string\n");
    return 0;
}
