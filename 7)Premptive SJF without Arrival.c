#include <stdio.h>

int main()
{
    int n;
    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int rem[20];
    int seq[1000];       // increased size for every time unit
    int seq_index = 0;

    int current_time = 0, completed = 0;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        at[i] = 0;                 // ❗ No Arrival Time (all arrive at 0)
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        rt[i] = -1;
    }

    while (completed < n)
    {
        int idx = -1;
        int min_rem = 100000;

        // Select process with minimum remaining time
        for (int i = 0; i < n; i++)
        {
            if (rem[i] > 0 && rem[i] < min_rem)
            {
                min_rem = rem[i];
                idx = i;
            }
        }

        //idle cpu
        if (idx == -1)
        {
            current_time++;
            continue;
        }

        // Store execution sequence **for every time unit**
        seq[seq_index++] = idx;

        // Response Time
        if (rt[idx] == -1)
        {
            rt[idx] = current_time;
        }

        // Execute for 1 unit (preemptive)
        rem[idx]--;
        current_time++;

        // If process completes
        if (rem[idx] == 0)
        {
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];

            completed++;
        }
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    // Execution Sequence
    printf("\nProcess execution sequence (every time unit):\n");
    for (int i = 0; i < seq_index; i++)
    {
        printf("P%d", pid[seq[i]]);
        if (i != seq_index - 1)
            printf(" -> ");
    }
    printf("\n");

    // Average Times
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}
