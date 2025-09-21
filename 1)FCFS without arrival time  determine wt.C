#include <stdio.h>
int main()
{
    int n, i, bt[10], wt[10];
    float sum_wt=0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;//1st process never wait

    for(i=1; i<n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\n", i + 1, bt[i], wt[i]);
        sum_wt=sum_wt+wt[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", sum_wt/n);
    return 0;
}
