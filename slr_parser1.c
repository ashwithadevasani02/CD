#include <stdio.h>
#include <string.h>
int state[100];
char symbol[100];
int top = -1;

/* ACTION table: columns id, +, *, (, ), $ */
int action[12][6] = {
    { 5,  0,  0,  4,  0,   0 },
    { 0,  6,  0,  0,  0, 999 },
    { 0, -2,  7,  0, -2,  -2 },
    { 0, -4, -4,  0, -4,  -4 },
    { 5,  0,  0,  4,  0,   0 },
    { 0, -6, -6,  0, -6,  -6 },
    { 5,  0,  0,  4,  0,   0 },
    { 5,  0,  0,  4,  0,   0 },
    { 0,  6,  0,  0, 11,   0 },
    { 0, -1,  7,  0, -1,  -1 },
    { 0, -3, -3,  0, -3,  -3 },
    { 0, -5, -5,  0, -5,  -5 }
};

/* GOTO table: columns E, T, F */
int goTo[12][3] = {
    { 1,  2,  3 },
    {-1, -1, -1 },
    {-1, -1, -1 },
    {-1, -1, -1 },
    { 8,  2,  3 },
    {-1, -1, -1 },
    {-1,  9,  3 },
    {-1, -1, 10 },
    {-1, -1, -1 },
    {-1, -1, -1 },
    {-1, -1, -1 },
    {-1, -1, -1 }
};

int getcol(char *input)
{
    if (strcmp(input, "id") == 0) return 0;
    if (strcmp(input, "+") == 0)  return 1;
    if (strcmp(input, "*") == 0)  return 2;
    if (strcmp(input, "(") == 0)  return 3;
    if (strcmp(input, ")") == 0)  return 4;
    if (strcmp(input, "$") == 0)  return 5;

    return -1;
}

int gotocol(char ch)
{
    if (ch == 'E') return 0;
    if (ch == 'T') return 1;
    if (ch == 'F') return 2;

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

    printf("Enter tokens (id, +, *, (, )):\n");

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

        printStack();
        printf("\t\t\t\t");

        for (j = i; j <= n; j++)
            printf("%s", input[j]);

        printf("\t\t\t\t");

        if (act == 999)
        {
            printf("String Accepted\n");
            break;
        }

        else if (act > 0)
        {
            printf("Shift %d\n", act);

            push(strcmp(input[i], "id") == 0
                 ? 'i' : input[i][0], act);

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
                    lhs = 'E';
                    len = 3;
                    printf("Reduce E -> E+T\n");
                    break;

                case 2:
                    lhs = 'E';
                    len = 1;
                    printf("Reduce E -> T\n");
                    break;

                case 3:
                    lhs = 'T';
                    len = 3;
                    printf("Reduce T -> T*F\n");
                    break;

                case 4:
                    lhs = 'T';
                    len = 1;
                    printf("Reduce T -> F\n");
                    break;

                case 5:
                    lhs = 'F';
                    len = 3;
                    printf("Reduce F -> (E)\n");
                    break;

                case 6:
                    lhs = 'F';
                    len = 1;
                    printf("Reduce F -> id\n");
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
