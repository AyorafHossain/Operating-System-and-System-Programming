#include <stdio.h>

int numProcesses, numResources;
int waitForGraph[20][20];
int isVisited[20], recStack[20];

int detectCycleDFS(int process)
{
    isVisited[process] = 1;
    recStack[process] = 1;

    for (int next = 0; next < numProcesses; next++)
    {
        if (waitForGraph[process][next])
        {
            if (!isVisited[next] && detectCycleDFS(next))
                return 1;
            if (recStack[next])
                return 1; // cycle detected
        }
    }

    recStack[process] = 0;
    return 0;
}

int main()
{
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter number of resources (single instance each): ");
    scanf("%d", &numResources);

    int allocation[20][20], request[20][20];
    int resourceOwner[20];

    printf("Enter Allocation matrix (%d x %d) (0/1):\n", numProcesses, numResources);
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request matrix (%d x %d) (0/1):\n", numProcesses, numResources);
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            scanf("%d", &request[i][j]);

    // Identify resource owners
    for (int r = 0; r < numResources; r++)
    {
        resourceOwner[r] = -1;
        for (int p = 0; p < numProcesses; p++)
        {
            if (allocation[p][r] == 1)
            {
                resourceOwner[r] = p;
                break;
            }
        }
    }

    // Initialize Wait-For Graph
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numProcesses; j++)
            waitForGraph[i][j] = 0;

    // Build Wait-For Graph
    for (int i = 0; i < numProcesses; i++)
    {
        for (int r = 0; r < numResources; r++)
        {
            if (request[i][r] == 1 && resourceOwner[r] != -1 && resourceOwner[r] != i)
            {
                waitForGraph[i][resourceOwner[r]] = 1;
            }
        }
    }

    // Cycle detection
    for (int i = 0; i < numProcesses; i++)
        isVisited[i] = recStack[i] = 0;

    int deadlockDetected = 0;
    for (int i = 0; i < numProcesses; i++)
    {
        if (!isVisited[i] && detectCycleDFS(i))
        {
            deadlockDetected = 1;
            break;
        }
    }

    if (!deadlockDetected)
        printf("\nNo Deadlock (No cycle in Wait-For Graph).\n");
    else
        printf("\nDeadlock Detected! (Cycle exists in Wait-For Graph)\n");

    return 0;
}
