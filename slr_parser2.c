
#include <stdio.h>
#include <string.h>

#define MAX 100

/*
Grammar:
1. S -> AB
2. A -> a
3. A -> epsilon
4. B -> b
5. B -> epsilon
*/

/* ACTION columns: a, b, $ */
int action[6][3] = {
    {  3, -3, -3 },
    {  0,  0, 999 },
    {  0,  5, -5 },
    {  0, -2, -2 },
    {  0,  0, -1 },
    {  0,  0, -4 }
};

/* GOTO columns: S, A, B */
int gototable[6][3] = {
    { 1, 2, 0 },
    { 0, 0, 0 },
    { 0, 0, 4 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 }
};

int getcol(char ch)
{
    if (ch == 'a') return 0;
    if (ch == 'b') return 1;
    if (ch == '$') return 2;

    return -1;
}

int gotocol(char ch)
{
    if (ch == 'S') return 0;
    if (ch == 'A') return 1;
    if (ch == 'B') return 2;

    return -1;
}

void printstack(int stack[], int top)
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%d ", stack[i]);
}

void printprod(int p)
{
    switch (p)
    {
        case 1:
            printf("Reduce S -> AB");
            break;

        case 2:
            printf("Reduce A -> a");
            break;

        case 3:
            printf("Reduce A -> epsilon");
            break;

        case 4:
            printf("Reduce B -> b");
            break;

        case 5:
            printf("Reduce B -> epsilon");
            break;
    }
}

int main(void)
{
    char input[MAX];
    int stack[MAX];
    int top = 0;
    int ip = 0;
    int len, k;

    printf("Enter input string over a and b: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    /* Remove the newline */
    input[strcspn(input, "\r\n")] = '\0';

    /* Allow an optional $ at the end */
    len = strlen(input);

    if (len > 0 && input[len - 1] == '$')
        input[--len] = '\0';

    /* Validate input */
    for (k = 0; k < len; k++)
    {
        if (input[k] != 'a' && input[k] != 'b')
        {
            printf("Invalid input\n");
            return 0;
        }
    }

    if (len >= MAX - 1)
    {
        printf("Input too long\n");
        return 1;
    }

    input[len] = '$';
    input[len + 1] = '\0';

    /* Initialize stack */
    stack[0] = 0;

    printf("\n%-15s %-15s %s\n",
           "Stack", "Input", "Action");

    while (1)
    {
        int state = stack[top];
        int col = getcol(input[ip]);
        int act;

        if (col == -1)
        {
            printf("Invalid input\n");
            break;
        }

        act = action[state][col];

        printstack(stack, top);
        printf("%*s", 15 - (top + 1) * 2, "");
        printf("%-15s ", input + ip);

        if (act == 999)
        {
            printf("String Accepted\n");
            break;
        }

        if (act == 0)
        {
            printf("String Rejected\n");
            break;
        }

        /* Shift */
        if (act > 0)
        {
            printf("Shift %d\n", act);

            if (top >= MAX - 1)
            {
                printf("Stack overflow\n");
                break;
            }

            stack[++top] = act;
            ip++;
        }
        /* Reduce */
        else
        {
            int prod = -act;
            char lhs;
            int rhslen, gc, prev, next;

            switch (prod)
            {
                case 1:
                    lhs = 'S';
                    rhslen = 2;
                    break;

                case 2:
                    lhs = 'A';
                    rhslen = 1;
                    break;

                case 3:
                    lhs = 'A';
                    rhslen = 0;
                    break;

                case 4:
                    lhs = 'B';
                    rhslen = 1;
                    break;

                case 5:
                    lhs = 'B';
                    rhslen = 0;
                    break;

                default:
                    printf("Invalid reduction\n");
                    return 1;
            }

            printprod(prod);
            printf("\n");

            /* Pop the RHS length */
            top -= rhslen;

            gc = gotocol(lhs);
            prev = stack[top];
            next = gototable[prev][gc];

            if (next < 0 || next >= 6)
            {
                printf("GOTO error\n");
                break;
            }

            if (top >= MAX - 1)
            {
                printf("Stack overflow\n");
                break;
            }

            stack[++top] = next;
        }
    }

    return 0;
}
