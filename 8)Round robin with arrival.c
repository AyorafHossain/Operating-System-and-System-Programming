#include <stdio.h>

int main()
{
    int n, tq;
    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int rem[20];
    int rq[50];
    int seq[100];    // execution sequence
    int seq_index = 0;

    int front = 0, rear = 0;
    int current_time = 0, completed = 0;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        rt[i] = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Add first arriving process
    int min_at = 0;
    for (int i = 1; i < n; i++)
    {
         if (at[i] < at[min_at])
            min_at = i;
    }


    current_time = at[min_at];
    rq[rear++] = min_at;

    int visited[20] = {0};
    visited[min_at] = 1;

    while (completed < n)
    {
        if (front == rear)
        {
            current_time++;
            continue;
        }

        int i = rq[front++];

        // Store in execution sequence
        seq[seq_index++] = i;

        if (rt[i] == -1)
        {
            rt[i] = current_time - at[i];
        }


        if (rem[i] > tq)
        {
            current_time += tq;
            rem[i] -= tq;
        }
        else
        {
            current_time += rem[i];
            rem[i] = 0;
            ct[i] = current_time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            total_wt += wt[i];
            total_tat += tat[i];
            total_rt += rt[i];

            completed++;
        }

        // Add newly arrived processes
        for (int j = 0; j < n; j++)
        {
            if (at[j] <= current_time && rem[j] > 0 && visited[j] == 0)
            {
                rq[rear++] = j;
                visited[j] = 1;
            }
        }

        // Reinsert current process if not finished
        if (rem[i] > 0)
            rq[rear++] = i;
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    // Execution Sequence
    printf("\nProcess execution sequence: ");
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

