#include <stdio.h>

int main()
{
    int i, j, n, m;
    int available[10], max[10][10], allocation[10][10], need[10][10];
    int finish[10], safe[10], k = 0;


    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);


     // Input Max matrix
    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++)
    {
         for (j = 0; j < m; j++)
         {
             scanf("%d", &max[i][j]);
         }

    }


    // Input Allocation matrix
    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }





    // Input Available vector
    printf("Enter Available resources:\n");
    for (i = 0; i < m; i++)
    {
         scanf("%d", &available[i]);
    }




    // Calculate Need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
             need[i][j] = max[i][j] - allocation[i][j];

        }

    }





    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
              printf("%d ", need[i][j]);
        }

        printf("\n");
    }




     // Initialize finish array
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }




    // Safe scan
    int found;
    k = 0; // safe sequence index
    while (1)
    {
        found = 0;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int can_allocate = 1;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate)
                {
                    // Process can safely execute
                    for (j = 0; j < m; j++)
                       {
                            available[j] += allocation[i][j];
                       }
                    safe[k++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break; // no  processes can proceed
    }



    // Check if system is safe
    int safe_flag = 1;
    for (i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            safe_flag = 0;
            break;
        }
    }


    if (safe_flag)
    {
        printf("\nSystem is in SAFE state.\nSafe Sequence: ");
        for (i = 0; i < n; i++)
        {
            printf("P%d ", safe[i]);
            if (i != n - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE state. Deadlock may occur.\n");
    }

    return 0;
}

