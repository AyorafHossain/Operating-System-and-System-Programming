#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[20], at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int visited[20] = {0};   // 0 = false, 1 = true
    int seq[20];              // execution sequence
    float total_wt = 0, total_tat = 0, total_rt = 0;

    // Input
    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("Process P%d Arrival Time: ", p[i]);
        scanf("%d", &at[i]);
        printf("Process P%d Burst Time: ", p[i]);
        scanf("%d", &bt[i]);
    }

    int completed = 0;
    int time = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 1000000000;   // large number for comparison

        // Select process with shortest BT among arrived ones
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && visited[i] == 0)
            {
                if (idx == -1 || bt[i] < min_bt ||
                    (bt[i] == min_bt && at[i] < at[idx]))
                {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        // If no process available → CPU idle
        if (idx == -1)
        {
            time++;
        }
        else
        {
            rt[idx] = time - at[idx];   // Response Time
            time += bt[idx];             // Execute process
            ct[idx] = time;              // Completion Time
            tat[idx] = ct[idx] - at[idx];// Turnaround Time
            wt[idx] = tat[idx] - bt[idx];// Waiting Time

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];

            visited[idx] = 1;
            seq[completed] = idx;        // store execution sequence
            completed++;
        }
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    // Execution Sequence
    printf("\nProcess execution sequence: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d", p[seq[i]]);
        if (i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    // Average Times
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}
