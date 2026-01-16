#include <stdio.h>

int main()
{
    int n, i, j;
    int p[20], at[20], bt[20], wt[20], tat[20], ct[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("Process P%d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort processes by arrival time (simple bubble sort)
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                // swap arrival
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // swap burst
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // swap process id
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Completion time calculation
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++)
    {
        if (at[i] > ct[i - 1])// CPU is idle
        {

            ct[i] = at[i] + bt[i];
        }
        else
        {
            ct[i] = ct[i - 1] + bt[i];
        }
    }

    // Turnaround time (TAT) and Waiting time (WT)
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Process execution sequence:");
    for(i=0;i<n;i++)
    {
        printf("P%d",p[i]);
        if (i != n - 1)
            {
                printf(" -> ");
            }
    }
    printf("\n \nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}

