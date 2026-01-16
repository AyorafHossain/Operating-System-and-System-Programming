#include <stdio.h>

int main()
{
    int n, tq;
    int pid[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int rem[20];         // Remaining burst time
    int rq[50];           // Ready queue
    int seq[100];         // Execution sequence
    int seq_index = 0;

    int front = 0, rear = 0;
    int time = 0, completed = 0;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input Burst Time for all processes
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process P%d Burst Time: ", pid[i]);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        rt[i] = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // All processes arrive at time 0 → add all to ready queue initially
    for (int i = 0; i < n; i++)
        rq[rear++] = i;

    while (completed < n)
    {
        if (front == rear)
        {
            time++;
            continue;
        }

        int i = rq[front++];  // get process from front

        // Store in execution sequence
        seq[seq_index++] = i;

        if (rt[i] == -1)
            rt[i] = time;   // Response time = first time it gets CPU for first processs it is 0

        if (rem[i] > tq)
        {
            time += tq;
            rem[i] -= tq;
        }
        else
        {
            time += rem[i];
            rem[i] = 0;
            ct[i] = time;
            tat[i] = ct[i];      // AT = 0
            wt[i] = tat[i] - bt[i];

            total_wt += wt[i];
            total_tat += tat[i];
            total_rt += rt[i];

            completed++;
        }

        // Reinsert current process if not finished
        if (rem[i] > 0)
            rq[rear++] = i;
    }

    // Output Table
    printf("\nProcess\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",pid[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
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

