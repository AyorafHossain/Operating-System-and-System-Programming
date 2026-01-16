#include <stdio.h>


int p[100];  // Philosopher states
int ch[100]; // Chopstick states

void signal(int z, int N)//signal dea philosoper thinking state and chopstick free hoa jae
{
    int Right = (z + 1) % N;
    p[z] = 0;      // philosopher thinking
    ch[z] = 0;     // left chopstick free
    ch[Right] = 0; // right chopstick free
}

void wait(int y, int N)//chopstick+philosoper ke busy dekhae
{
    int Right = (y + 1) % N;

    if ((ch[y] == 0) && (ch[Right] == 0))
    {
        p[y] = 1;       // philosopher eating
        ch[y] = 1;      // left chopstick busy
        ch[Right] = 1;  // right chopstick busy
    }
    else if (p[y] == 1)
    {
        int w;
        printf("Do you want philosopher %d to stop eating? (1=yes): ", y);
        scanf("%d", &w);
        if (w == 1)
            signal(y, N);
    }
    else
    {
        printf("Chopsticks %d and %d are busy\n", y, Right);
        printf("Philosopher %d has to wait\n", y);
    }
}




int main()
{
    int N;
    printf("Enter number of philosophers: ");
    scanf("%d", &N);

    if (N < 1 )
    {
        printf("Invalid number of philosophers\n");
        return 0;
    }


    // Initialize philosophers and chopsticks
    for (int i = 0; i < N; i++)
    {
        p[i] = 0;
        ch[i] = 0;
    }



    printf("There are %d philosophers and %d chopsticks.\n\n", N, N);

    int u;
    do
    {
        // Display philosopher states
        for (int i = 0; i < N; i++)
        {
            if (p[i] == 0)
                printf("Philosopher %d is thinking\n", i);
            else
                printf("Philosopher %d is eating\n", i);
        }
        printf("\n");

        int s;
        printf("Which philosopher wants to eat : ");
        scanf("%d", &s);

        if (s < 0 || s >= N)
        {
            printf("Invalid philosopher number\n\n");
            continue;
        }

        wait(s, N);

        printf("\nDo you want to continue? Press 1: ");
        scanf("%d", &u);
        printf("\n");

    } while (u == 1);

    return 0;
}

