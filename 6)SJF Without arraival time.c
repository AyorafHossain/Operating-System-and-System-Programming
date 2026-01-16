#include <stdio.h>

int main()
{
    int n, i, j, temp;
    int bt[10], wt[10], tat[10], ct[10], rt[10], pid[10];
    float sum_wt = 0, sum_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;   // store process number
        printf("Process P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    /* Sorting processes by Burst Time (SJF) */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j]|| (bt[i] == bt[j] && pid[i] > pid[j]))
            {
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    /* First process */
    wt[0] = 0;
    rt[0] = wt[0];
    ct[0] = bt[0];
    tat[0] = ct[0];


    /* Remaining processes */
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
        rt[i] = wt[i];
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i];
    }

    printf("\nProcess\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

        sum_wt += wt[i];
        sum_tat += tat[i];
    }


    printf("Process execution sequence:");
    for(i=0;i<n;i++)
    {
        printf("P%d",pid[i]);
        if (i != n - 1)
            {
                printf(" -> ");
            }
    }

    printf("\nAverage Waiting Time: %.2f\n", sum_wt / n);
    printf("Average Turnaround Time: %.2f\n", sum_tat / n);

    return 0;
}
