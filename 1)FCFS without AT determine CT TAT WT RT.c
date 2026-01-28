#include <stdio.h>
int main()
{
    int n, i;
    int bt[10], wt[10], tat[10], ct[10], rt[10];
    float sum_wt = 0, sum_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // First process
    wt[0] = 0;  // waiting time of P1
    rt[0] = wt[0]; // response time = waiting time for FCFS
    ct[0] = bt[0]; // completion time
    tat[0] = ct[0]; // turnaround time = CT - AT (AT=0)

    // Other processes
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1]; // waiting time
        rt[i] = wt[i];                 // response time = waiting time (in FCFS)
        ct[i] = ct[i - 1] + bt[i];     // completion time
        tat[i] = ct[i];                // turnaround time = CT - AT (AT=0)
    }

    printf("\nProcess\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], ct[i], tat[i], wt[i], rt[i]);
        sum_wt += wt[i];
        sum_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", sum_wt / n);
    printf("Average Turnaround Time: %.2f\n", sum_tat / n);

    return 0;
}

