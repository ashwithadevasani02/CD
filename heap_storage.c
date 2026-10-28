
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nb, np, i, j, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    int *block = malloc(nb * sizeof(int));

    printf("Enter sizes of memory blocks:\n");
    for (i = 0; i < nb; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int *process = malloc(np * sizeof(int));
    int *allocation = malloc(np * sizeof(int));

    printf("Enter sizes of processes:\n");
    for (i = 0; i < np; i++)
    {
        scanf("%d", &process[i]);
        allocation[i] = -1;
    }

    printf("\n1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    for (i = 0; i < np; i++)
    {
        int index = -1;

        for (j = 0; j < nb; j++)
        {
            if (block[j] >= process[i])
            {
                if (choice == 1)
                {
                    index = j;
                    break;
                }

                if (choice == 2 &&
                    (index == -1 || block[j] < block[index]))
                {
                    index = j;
                }

                if (choice == 3 &&
                    (index == -1 || block[j] > block[index]))
                {
                    index = j;
                }
            }
        }

        if (index != -1)
        {
            allocation[i] = index;
            block[index] -= process[i];
        }
    }

    printf("\nProcess Size\tBlock Allocated\n");

    for (i = 0; i < np; i++)
    {
        printf("%d\t\t", process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    printf("\nRemaining memory in each block:\n");

    for (i = 0; i < nb; i++)
        printf("Block %d: %d\n", i + 1, block[i]);

    free(block);
    free(process);
    free(allocation);

    return 0;
}
