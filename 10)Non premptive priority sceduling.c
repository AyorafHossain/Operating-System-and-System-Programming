#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[20], at[20], bt[20], pr[20], ct[20], tat[20], wt[20], rt[20];
    int is_completed[20] = {0};

    int seq[20], seq_len = 0;   // execution sequence (non-preemptive)

    float total_wt = 0, total_tat = 0, total_rt = 0;

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);

        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        printf("Process %d Priority (smaller = higher): ", i + 1);
        scanf("%d", &pr[i]);
    }

    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int idx = -1;
        int best_pr = 1000000000;

        // Select highest priority among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && is_completed[i] == 0)
            {
                if (pr[i] < best_pr)
                {
                    best_pr = pr[i];
                    idx = i;
                }
                // tie-breaker: earlier arrival
                else if (pr[i] == best_pr && at[i] < at[idx])
                {
                    idx = i;
                }
                // if still tie, smaller PID
                else if (pr[i] == best_pr && at[i] == at[idx] && pid[i] < pid[idx])
                {
                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1)
        {
            current_time++;
        }
        else
        {
            // Response Time
            rt[idx] = current_time - at[idx];

            // Store execution sequence
            seq[seq_len++] = pid[idx];

            // Execute FULL burst (non-preemptive)
            current_time += bt[idx];

            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];

            is_completed[idx] = 1;
            completed++;
        }
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i], rt[i]);
    }

    // Execution Sequence
    printf("\nExecution Sequence:\n");
    for (int i = 0; i < seq_len; i++)
    {
        printf("P%d", seq[i]);
        if (i != seq_len - 1)
            printf(" -> ");
    }

    // Throughput
    float throughput = (float)n / current_time;

    printf("\n\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f", total_rt / n);
    printf("\nThroughput: %.2f processes/unit time\n", throughput);

    return 0;
}
