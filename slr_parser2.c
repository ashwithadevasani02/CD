
#include <stdio.h>
#include <string.h>

/* Stack */
int state[100];
char symbol[100];
int top = -1;

/*
Grammar:
1. S -> AB
2. A -> a
3. A -> epsilon
4. B -> b
5. B -> epsilon
*/

/* ACTION table: columns a, b, $ */
int action[6][3] = {
    {  3, -3, -3 },
    {  0,  0, 999 },
    {  0,  5, -5 },
    {  0, -2, -2 },
    {  0,  0, -1 },
    {  0,  0, -4 }
};

/* GOTO table: columns S, A, B */
int goTo[6][3] = {
    { 1, 2, -1 },
    {-1, -1, -1 },
    {-1, -1,  4 },
    {-1, -1, -1 },
    {-1, -1, -1 },
    {-1, -1, -1 }
};

int getcol(char *input)
{
    if (strcmp(input, "a") == 0) return 0;
    if (strcmp(input, "b") == 0) return 1;
    if (strcmp(input, "$") == 0) return 2;

    return -1;
}

int gotocol(char ch)
{
    if (ch == 'S') return 0;
    if (ch == 'A') return 1;
    if (ch == 'B') return 2;

    return -1;
}

void push(char ch, int st)
{
    top++;
    symbol[top] = ch;
    state[top] = st;
}

void pop(int n)
{
    top -= n;
}

void printStack(void)
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%c%d ", symbol[i], state[i]);
}

int main(void)
{
    char input[100][10];
    int n, i, j;

    printf("Enter number of tokens: ");
    scanf("%d", &n);

    printf("Enter tokens (a, b):\n");

    for (i = 0; i < n; i++)
        scanf("%9s", input[i]);

    strcpy(input[n], "$");

    /* Initialize stack */
    push('$', 0);
    i = 0;

    printf("\n%-25s %-20s %s\n",
           "Stack", "Input", "Action");

    while (1)
    {
        int st = state[top];
        int c = getcol(input[i]);
        int act;

        if (c == -1)
        {
            printf("Invalid input token\n");
            break;
        }

        act = action[st][c];

        /* Print stack */
        printStack();
        printf("\t\t");

        for (j = i; j <= n; j++)
            printf("%s", input[j]);

        printf("\t\t");

        if (act == 999)
        {
            printf("String Accepted\n");
            break;
        }

        else if (act > 0)
        {
            printf("Shift %d\n", act);

            push(input[i][0], act);

            i++;
        }

        else if (act < 0)
        {
            int prod = -act;
            char lhs;
            int len, gc, next;

            switch (prod)
            {
                case 1:
                    lhs = 'S';
                    len = 2;
                    printf("Reduce S -> AB\n");
                    break;

                case 2:
                    lhs = 'A';
                    len = 1;
                    printf("Reduce A -> a\n");
                    break;

                case 3:
                    lhs = 'A';
                    len = 0;
                    printf("Reduce A -> epsilon\n");
                    break;

                case 4:
                    lhs = 'B';
                    len = 1;
                    printf("Reduce B -> b\n");
                    break;

                case 5:
                    lhs = 'B';
                    len = 0;
                    printf("Reduce B -> epsilon\n");
                    break;

                default:
                    printf("Invalid reduction\n");
                    return 0;
            }

            pop(len);

            gc = gotocol(lhs);
            next = goTo[state[top]][gc];

            if (next == -1)
            {
                printf("GOTO error\n");
                break;
            }

            push(lhs, next);
        }

        else
        {
            printf("String Rejected\n");
            break;
        }
    }

    return 0;
}
